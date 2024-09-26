/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <functional>
#include <map>
#include <memory>

#include "aidl/android/hardware/wifi/BnWifi.h"
#ifdef CONFIG_AP
#include "aidl/android/hardware/wifi/BnWifiApIface.h"
#endif
#include "aidl/android/hardware/wifi/BnWifiChip.h"
#ifdef CONFIG_P2P
#include "aidl/android/hardware/wifi/BnWifiP2pIface.h"
#endif
#include "aidl/android/hardware/wifi/BnWifiStaIface.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class WifiInstanceManager {
public:
    WifiInstanceManager(std::shared_ptr<IWifi> impl);
    ~WifiInstanceManager();

    std::shared_ptr<IWifi> getWifiInstance();

    uint16_t registerStaIfaceAndGetInstanceId(
        std::shared_ptr<IWifiStaIface> impl,  const std::string& ifname,
        int32_t chip_id);
    uint16_t getStaIfaceInstanceId(std::shared_ptr<IWifiStaIface> impl);
    std::shared_ptr<IWifiStaIface> getStaIfaceByInstanceId(uint16_t instance_id);
    void removeStaIface(std::shared_ptr<IWifiStaIface> impl);

    ndk::ScopedAStatus callWifiMethod(const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifi>)> &method);
    ndk::ScopedAStatus callWifiChipMethod(const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiChip>)> &method,
        int32_t chip_id);
    ndk::ScopedAStatus callWifiStaIfaceMethod(const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiStaIface>)> &method,
        uint16_t instance_id);
#ifdef CONFIG_AP
    uint16_t registerApIfaceAndGetInstanceId(
        std::shared_ptr<IWifiApIface> impl,  const std::string& ifname,
        int32_t chip_id);
    uint16_t getApIfaceInstanceId(std::shared_ptr<IWifiApIface> impl);
    std::shared_ptr<IWifiApIface> getApIfaceByInstanceId(uint16_t instance_id);
    void removeApIface(std::shared_ptr<IWifiApIface> impl);
    ndk::ScopedAStatus callWifiApIfaceMethod(const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiApIface>)> &method,
        uint16_t instance_id);
#endif
#ifdef CONFIG_P2P
    uint16_t registerP2pIfaceAndGetInstanceId(
        std::shared_ptr<IWifiP2pIface> impl,  const std::string& ifname,
        int32_t chip_id);
    uint16_t getP2pIfaceInstanceId(std::shared_ptr<IWifiP2pIface> impl);
    std::shared_ptr<IWifiP2pIface> getP2pIfaceByInstanceId(uint16_t instance_id);
    void removeP2pIface(std::shared_ptr<IWifiP2pIface> impl);
    ndk::ScopedAStatus callWifiP2pIfaceMethod(const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiP2pIface>)> &method,
        uint16_t instance_id);
#endif

private:
    std::shared_ptr<IWifi> _wifi_impl;

    std::map<uint16_t, std::shared_ptr<IWifiStaIface>> _wifi_sta_iface_map;
#ifdef CONFIG_AP
    std::map<uint16_t, std::shared_ptr<IWifiApIface>> _wifi_ap_iface_map;
#endif
#ifdef CONFIG_P2P
    std::map<uint16_t, std::shared_ptr<IWifiP2pIface>> _wifi_p2p_iface_map;
#endif
};

namespace instance_util {

void WifiManagerRegisterService(std::shared_ptr<IWifi> impl);
std::shared_ptr<WifiInstanceManager> WifiGetInstanceManager();
uint16_t WifiRegisterStaIfaceAndGetInstanceId(
    std::shared_ptr<IWifiStaIface> impl,  const std::string& ifname,
    int32_t chip_id);
uint16_t WifiGetStaIfaceInstanceId(std::shared_ptr<IWifiStaIface> impl);
void WifiRemoveStaIface(std::shared_ptr<IWifiStaIface> impl);

template <typename FuncType, typename... Args>
ndk::ScopedAStatus WifiCallMethod(FuncType&& func, Args&&... args)
{
    std::shared_ptr<WifiInstanceManager> manager = WifiGetInstanceManager();
    if (manager == nullptr)
        return ndk::ScopedAStatus::fail(
            WifiStatusCode::ERROR_WIFI_IFACE_INVALID);

    const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifi>)> method =
            std::bind(func, std::placeholders::_1, std::forward<Args>(args)...);
    return manager->callWifiMethod(method);
}

template <typename FuncType, typename... Args>
ndk::ScopedAStatus WifiChipCallMethod(int32_t chip_id,
    FuncType&& func, Args&&... args)
{
    std::shared_ptr<WifiInstanceManager> manager = WifiGetInstanceManager();
    if (manager == nullptr)
        return ndk::ScopedAStatus::fail(
            WifiStatusCode::ERROR_WIFI_IFACE_INVALID);

    const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiChip>)> method =
            std::bind(func, std::placeholders::_1, std::forward<Args>(args)...);
    return manager->callWifiChipMethod(method, chip_id);
}

template <typename FuncType, typename... Args>
ndk::ScopedAStatus WifiStaIfaceCallMethod(uint16_t instance_id,
    FuncType&& func, Args&&... args)
{
    std::shared_ptr<WifiInstanceManager> manager = WifiGetInstanceManager();
    if (manager == nullptr)
        return ndk::ScopedAStatus::fail(
            WifiStatusCode::ERROR_WIFI_IFACE_INVALID);

    const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiStaIface>)> method =
            std::bind(func, std::placeholders::_1, std::forward<Args>(args)...);
    return manager->callWifiStaIfaceMethod(method, instance_id);
}

#ifdef CONFIG_AP
uint16_t WifiRegisterApIfaceAndGetInstanceId(
    std::shared_ptr<IWifiApIface> impl,  const std::string& ifname,
    int32_t chip_id);
uint16_t WifiGetApIfaceInstanceId(std::shared_ptr<IWifiApIface> impl);
void WifiRemoveApIface(std::shared_ptr<IWifiApIface> impl);
template <typename FuncType, typename... Args>
ndk::ScopedAStatus WifiApIfaceCallMethod(uint16_t instance_id,
    FuncType&& func, Args&&... args)
{
    std::shared_ptr<WifiInstanceManager> manager = WifiGetInstanceManager();
    if (manager == nullptr)
        return ndk::ScopedAStatus::fail(
            WifiStatusCode::ERROR_WIFI_IFACE_INVALID);

    const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiApIface>)> method =
            std::bind(func, std::placeholders::_1, std::forward<Args>(args)...);
    return manager->callWifiApIfaceMethod(method, instance_id);
}
#endif

#ifdef CONDIF_P2P
template <typename FuncType, typename... Args>
ndk::ScopedAStatus WifiP2pIfaceCallMethod(uint16_t instance_id,
    FuncType&& func, Args&&... args)
{
    std::shared_ptr<WifiInstanceManager> manager = WifiGetInstanceManager();
    if (manager == nullptr)
        return ndk::ScopedAStatus::fail(
            WifiStatusCode::ERROR_WIFI_IFACE_INVALID);

    const std::function<
        ndk::ScopedAStatus(std::shared_ptr<IWifiP2pIface>)> method =
            std::bind(func, std::placeholders::_1, std::forward<Args>(args)...);
    return manager->callWifiP2pIfaceMethod(method, instance_id);
}
#endif

} // namespace instance_util
} // namespace wifi
} // namespace hardware
} // namespace android
} // namespace aidl

