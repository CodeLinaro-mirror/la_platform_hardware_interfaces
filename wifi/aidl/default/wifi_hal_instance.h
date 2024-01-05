/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef WIFI_HAL_INSTANCE_H
#define WIFI_HAL_INSTANCE_H

#include "wifi.h"
#include "wifi_chip.h"
#include "wifi_ap_iface.h"
#include "wifi_sta_iface.h"

#include "aidl/android/hardware/wifi/IWifiChip.h"
#include "aidl/android/hardware/wifi/IWifiApIface.h"
#include "aidl/android/hardware/wifi/IWifiStaIface.h"

using aidl::android::hardware::wifi::Wifi;
using aidl::android::hardware::wifi::WifiChip;
using aidl::android::hardware::wifi::WifiApIface;
using aidl::android::hardware::wifi::WifiStaIface;
using aidl::android::hardware::wifi::IWifi;
using aidl::android::hardware::wifi::IWifiChip;
using aidl::android::hardware::wifi::IWifiApIface;
using aidl::android::hardware::wifi::IWifiStaIface;

std::shared_ptr<Wifi> WifiHalGetWifiInstance();
std::shared_ptr<IWifiChip> WifiHalGetChipInstance(int32_t chipId = 0);
std::shared_ptr<IWifiApIface> WifiHalGetApIfaceInstance(const std::string& ifname = "wlan0");
std::shared_ptr<IWifiStaIface> WifiHalGetStaIfaceInstance(const std::string& ifname = "wlan0");
std::shared_ptr<IWifiStaIface> WifiHalGetStaIfaceByInstanceId(int32_t instanceId);

void WifiHalOnChipCreated(std::shared_ptr<WifiChip> chip);
void WifiHalOnApIfaceCreated(std::shared_ptr<WifiApIface> apIface);
void WifiHalOnStaIfaceCreated(std::shared_ptr<WifiStaIface> staIface);

#endif /* WIFI_SERVICE_INSTANCE_H */
