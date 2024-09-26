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

#include <signal.h>

#include <wifi_instance_util.h>
#include <wifi_rpc_event.h>
#include <wifi_rpc_server.h>

#include <rpc/util/properties.h>
#include <rpc/util/log_common.h>

#include "wifi.h"
#include "wifi_feature_flags.h"
#include "wifi_legacy_hal.h"
#include "wifi_legacy_hal_factory.h"
#include "wifi_mode_controller.h"

#define APP_NAME    "wifihal"
#define LOG_TAG     "HAL"

using aidl::android::hardware::wifi::feature_flags::WifiFeatureFlags;
using aidl::android::hardware::wifi::legacy_hal::WifiLegacyHal;
using aidl::android::hardware::wifi::legacy_hal::WifiLegacyHalFactory;
using aidl::android::hardware::wifi::mode_controller::WifiModeController;
using aidl::android::hardware::wifi::instance_util::WifiManagerRegisterService;
using aidl::android::hardware::wifi::IWifi;
using aidl::android::hardware::wifi::IWifiEventCallback;
using aidl::android::hardware::wifi::Wifi;
using aidl::android::hardware::wifi::WifiRpcEvent;
using android::wifi_system::InterfaceTool;

int main(int /*argc*/, char** argv) {
    signal(SIGPIPE, SIG_IGN);

    property_init();
    InitLogExt(APP_NAME, 10);
    setLogTag(LOG_TAG);

    ALOGI("Wifi Hal is booting up...");

    const auto iface_tool = std::make_shared<InterfaceTool>();
    const auto legacy_hal_factory =
        std::make_shared<WifiLegacyHalFactory>(iface_tool);
    std::shared_ptr<Wifi> wifi_service = std::make_shared<Wifi>(iface_tool,
        legacy_hal_factory, std::make_shared<WifiModeController>(),
        std::make_shared<WifiFeatureFlags>());

    std::shared_ptr<IWifiEventCallback> callback =
        std::make_shared<WifiRpcEvent>();
    if (!wifi_service->registerEventCallback(callback).isOk())
        ALOGE("Failed to register wifi rpc event callback");

    WifiManagerRegisterService(wifi_service);

    if (!WifiRpcInitSomeipService()) {
        ALOGE("Wifi rpc init someip service fail");
        return -1;
    }

    ALOGI("Wifi rpc someip service is starting...");

    WifiRpcStartSomeipService();

    ALOGI("Wifi rpc someip service is stopping...");

    WifiRpcStopSomeipService();

    WifiRpcDeinitSomeipService();

    ALOGI("Wifi Hal is terminating...");

    wifi_service->stop();

    DeinitLog();
    property_exit();

    return 0;
}
