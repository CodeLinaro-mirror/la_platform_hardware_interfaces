/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <android-base/logging.h>
#include <signal.h>
#include <cassert>

#include "wifi.h"
#include "wifi_feature_flags.h"
#include "wifi_legacy_hal.h"
#include "wifi_legacy_hal_factory.h"
#include "wifi_mode_controller.h"

#include "wifi_hal_event_callback.h"
#include "wifi_hal_someip_server.h"
#include "wifi_hal_instance.h"

#include "aidl/android/hardware/wifi/IWifiEventCallback.h"
#include "aidl/android/hardware/wifi/IWifiChipEventCallback.h"
#include "aidl/android/hardware/wifi/IWifiStaIfaceEventCallback.h"

using aidl::android::hardware::wifi::IWifiEventCallback;
using aidl::android::hardware::wifi::IWifiChipEventCallback;
using aidl::android::hardware::wifi::IWifiStaIfaceEventCallback;
using aidl::android::hardware::wifi::WifiEventCallback;
using aidl::android::hardware::wifi::WifiChipEventCallback;
using aidl::android::hardware::wifi::WifiStaIfaceEventCallback;

using aidl::android::hardware::wifi::feature_flags::WifiFeatureFlags;
using aidl::android::hardware::wifi::legacy_hal::WifiLegacyHal;
using aidl::android::hardware::wifi::legacy_hal::WifiLegacyHalFactory;
using aidl::android::hardware::wifi::mode_controller::WifiModeController;

/* Global class shared ptr */
std::shared_ptr<Wifi> wifiInstance;

std::shared_ptr<Wifi> WifiHalGetWifiInstance()
{
    return wifiInstance;
}

std::shared_ptr<IWifiChip> WifiHalGetChipInstance(int32_t chipId)
{
    std::shared_ptr<IWifiChip> chipInstance;

    auto status = wifiInstance->getChip(chipId, &chipInstance);

    assert(chipInstance != nullptr);

    return chipInstance;
}

std::shared_ptr<IWifiApIface> WifiHalGetApIfaceInstance(const std::string& ifname)
{
    std::shared_ptr<IWifiApIface> apIface;
    auto chipInstance = WifiHalGetChipInstance();
    auto status = chipInstance->getApIface(ifname, &apIface);

    assert(apIface != nullptr);

    return apIface;
}

std::shared_ptr<IWifiStaIface> WifiHalGetStaIfaceInstance(const std::string& ifname)
{
    std::shared_ptr<IWifiStaIface> staIface;
    auto chipInstance = WifiHalGetChipInstance();
    auto status = chipInstance->getStaIface(ifname, &staIface);

    assert(staIface != nullptr);

    return staIface;
}

std::shared_ptr<IWifiStaIface> WifiHalGetStaIfaceByInstanceId(int32_t instanceId)
{
    std::vector<std::string> ifnames;
    std::shared_ptr<IWifiStaIface> staIface;
    auto chipInstance = WifiHalGetChipInstance();
    auto status = chipInstance->getStaIfaceNames(&ifnames);
    for (auto& name : ifnames) {
        chipInstance->getStaIface(name, &staIface);
	if (staIface &&
            (std::dynamic_pointer_cast<WifiStaIface>(staIface)->getInstanceId() ==
             instanceId))
            return staIface;
    }

    assert(false);
    return nullptr;
}

void WifiHalOnChipCreated(std::shared_ptr<WifiChip> chip)
{
    int32_t chipId;
    auto status = chip->getId(&chipId);

    LOG(INFO) << "WiFi chip created with ID " << std::to_string(chipId)
              << " Register event callback";

    std::shared_ptr<IWifiChipEventCallback> chipEventCb =
            std::make_shared<WifiChipEventCallback>(chipId);
    chip->registerEventCallback(chipEventCb);
}

void WifiHalOnApIfaceCreated(std::shared_ptr<WifiApIface> apIface)
{
    LOG(INFO) << "Wifi Ap Iface created.";
}

void WifiHalOnStaIfaceCreated(std::shared_ptr<WifiStaIface> staIface)
{
    int32_t id = staIface->getInstanceId();
    std::string ifName = staIface->getName();

    LOG(INFO) << "Wifi Sta Iface created with ifname " << ifName
              << " instance id 0x" << std::hex << id;

    std::shared_ptr<IWifiStaIfaceEventCallback> staIfaceEventCb =
            std::make_shared<WifiStaIfaceEventCallback>(id, ifName);
    staIface->registerEventCallback(staIfaceEventCb);
}

static void WifiHalInstanceInit()
{
    const auto ifaceTool = std::make_shared<::android::wifi_system::InterfaceTool>();
    const auto legacyHalFactory = std::make_shared<WifiLegacyHalFactory>(ifaceTool);
    const auto wifiModeController = std::make_shared<WifiModeController>();
    const auto wifiFeatureFlags = std::make_shared<WifiFeatureFlags>();

    wifiInstance = std::make_shared<Wifi>(ifaceTool, legacyHalFactory,
                                          wifiModeController, wifiFeatureFlags);

    std::shared_ptr<IWifiEventCallback> wifiEventCb = std::make_shared<WifiEventCallback>();
    wifiInstance->registerEventCallback(wifiEventCb);
}

void WifiHalInstanceDeinit()
{
    wifiInstance->stop();
}

int main(int /*argc*/, char** argv) {
    signal(SIGPIPE, SIG_IGN);
    android::base::InitLogging(argv, &android::base::StdioLogger);
    LOG(INFO) << "Wifi Hal is booting up...";

    /* Wifi Hal interface class instance init */
    WifiHalInstanceInit();

    /* Wifi hal someip service init */
    if (!WifiHalSomeIPServerInit())
        goto fail;

    /* Start SomeIP Main Loop */
    WifiHalSomeIPServerStart();

    LOG(INFO) << "Wifi Hal is terminating...";

    WifiHalSomeIPServerStop();

fail:
    WifiHalSomeIPServerDeinit();

    WifiHalInstanceDeinit();

    return 0;
}
