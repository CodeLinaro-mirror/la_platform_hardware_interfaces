/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <net/if.h>

#include "wifi_instance_util.h"

namespace {

constexpr uint16_t StaIfaceInstanceIdBase = 0x0100;
#ifdef CONFIG_AP
constexpr uint16_t ApIfaceInstanceIdBase = 0x0200;
#endif
#ifdef CONFIG_P2P
constexpr uint16_t P2pIfaceInstanceIdBase = 0x0300;
#endif

}

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

namespace instance_util {

static std::shared_ptr<WifiInstanceManager> wifiInstanceManager;

void WifiManagerRegisterService(std::shared_ptr<IWifi> impl)
{
    wifiInstanceManager = std::make_shared<WifiInstanceManager>(impl);
}

std::shared_ptr<WifiInstanceManager> WifiGetInstanceManager()
{
    return wifiInstanceManager;
}

uint16_t WifiRegisterStaIfaceAndGetInstanceId(
    std::shared_ptr<IWifiStaIface> impl, const std::string& ifname,
    int32_t chip_id)
{
    if (wifiInstanceManager.get())
        return wifiInstanceManager->registerStaIfaceAndGetInstanceId(
            impl, ifname, chip_id);
    return -1;
}

uint16_t WifiGetStaIfaceInstanceId(std::shared_ptr<IWifiStaIface> impl)
{
    if (wifiInstanceManager.get())
        return wifiInstanceManager->getStaIfaceInstanceId(impl);
    return -1;
}

void WifiRemoveStaIface(std::shared_ptr<IWifiStaIface> impl)
{
    if (wifiInstanceManager.get())
        return wifiInstanceManager->removeStaIface(impl);
}

#ifdef CONFIG_AP
uint16_t WifiRegisterApIfaceAndGetInstanceId(
    std::shared_ptr<IWifiApIface> impl, const std::string& ifname,
    int32_t chip_id)
{
    if (wifiInstanceManager.get())
        return wifiInstanceManager->registerApIfaceAndGetInstanceId(
            impl, ifname, chip_id);
    return -1;
}

uint16_t WifiGetApIfaceInstanceId(std::shared_ptr<IWifiApIface> impl)
{
    if (wifiInstanceManager.get())
        return wifiInstanceManager->getApIfaceInstanceId(impl);
    return -1;
}

void WifiRemoveApIface(std::shared_ptr<IWifiApIface> impl)
{
    if (wifiInstanceManager.get())
        return wifiInstanceManager->removeApIface(impl);
}
#endif

} // namespace instance_util

WifiInstanceManager::WifiInstanceManager(std::shared_ptr<IWifi> impl)
    : _wifi_impl(impl) {}

WifiInstanceManager::~WifiInstanceManager()
{
    _wifi_impl = nullptr;
    _wifi_sta_iface_map.clear();
#ifdef CONFIG_AP
    _wifi_ap_iface_map.clear();
#endif
#ifdef CONFIG_P2P
    _wifi_p2p_iface_map.clear();
#endif
}

std::shared_ptr<IWifi> WifiInstanceManager::getWifiInstance()
{
    return _wifi_impl;
}

uint16_t WifiInstanceManager::registerStaIfaceAndGetInstanceId(
    std::shared_ptr<IWifiStaIface> impl, const std::string& ifname,
    int32_t chip_id)
{
    if (!impl.get())
        return -1;

    uint16_t instanceId = (chip_id << 12) | StaIfaceInstanceIdBase |
        (if_nametoindex(ifname.c_str()) & 0xff);

    _wifi_sta_iface_map[instanceId] = impl;

    return instanceId;
}

uint16_t WifiInstanceManager::getStaIfaceInstanceId(
    std::shared_ptr<IWifiStaIface> impl)
{
    for (auto [instanceId, staIface] : _wifi_sta_iface_map)
        if (staIface == impl)
            return instanceId;
    return -1;
}

std::shared_ptr<IWifiStaIface> WifiInstanceManager::getStaIfaceByInstanceId(
    uint16_t instance_id)
{
    auto iter = _wifi_sta_iface_map.find(instance_id);
    if (iter != _wifi_sta_iface_map.end())
        return iter->second;
    return nullptr;
}

void WifiInstanceManager::removeStaIface(std::shared_ptr<IWifiStaIface> impl)
{
    for (auto iter = _wifi_sta_iface_map.begin();
        iter != _wifi_sta_iface_map.end(); ++iter) {
        if (iter->second == impl) {
            _wifi_sta_iface_map.erase(iter);
	    break;
	}
    }
}

ndk::ScopedAStatus WifiInstanceManager::callWifiMethod(
    const std::function<ndk::ScopedAStatus(std::shared_ptr<IWifi>)> &method)
{
    return method(_wifi_impl);
}

ndk::ScopedAStatus WifiInstanceManager::callWifiChipMethod(
    const std::function<ndk::ScopedAStatus(std::shared_ptr<IWifiChip>)> &method,
    int32_t chip_id)
{
    std::shared_ptr<IWifiChip> chip;
    _wifi_impl->getChip(chip_id, &chip);
    if (chip.get())
        return method(chip);
    return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_WIFI_IFACE_INVALID);
}

ndk::ScopedAStatus WifiInstanceManager::callWifiStaIfaceMethod(
    const std::function<ndk::ScopedAStatus(std::shared_ptr<IWifiStaIface>)> &method,
    uint16_t instance_id)
{
    std::shared_ptr<IWifiStaIface> sta_iface = getStaIfaceByInstanceId(instance_id);
    if (sta_iface.get())
        return method(sta_iface);
    return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_WIFI_IFACE_INVALID);
}

#ifdef CONFIG_AP
uint16_t WifiInstanceManager::registerApIfaceAndGetInstanceId(
    std::shared_ptr<IWifiApIface> impl, const std::string& ifname,
    int32_t chip_id)
{
    if (!impl.get())
        return -1;

    uint16_t instanceId = (chip_id << 12) | ApIfaceInstanceIdBase |
        (if_nametoindex(ifname.c_str()) & 0xff);

    _wifi_ap_iface_map[instanceId] = impl;

    return instanceId;
}

uint16_t WifiInstanceManager::getApIfaceInstanceId(
    std::shared_ptr<IWifiApIface> impl)
{
    for (auto [instanceId, apIface] : _wifi_ap_iface_map)
        if (apIface == impl)
            return instanceId;
    return -1;
}

std::shared_ptr<IWifiApIface> WifiInstanceManager::getApIfaceByInstanceId(
    uint16_t instance_id)
{
    auto iter = _wifi_ap_iface_map.find(instance_id);
    if (iter != _wifi_ap_iface_map.end())
        return iter->second;
    return nullptr;
}

void WifiInstanceManager::removeApIface(std::shared_ptr<IWifiApIface> impl)
{
    for (auto iter = _wifi_ap_iface_map.begin();
        iter != _wifi_ap_iface_map.end(); ++iter) {
        if (iter->second == impl){
            _wifi_ap_iface_map.erase(iter);
            break;
        }
    }
}

ndk::ScopedAStatus WifiInstanceManager::callWifiApIfaceMethod(
    const std::function<ndk::ScopedAStatus(std::shared_ptr<IWifiApIface>)> &method,
    uint16_t instance_id)
{
    std::shared_ptr<IWifiApIface> ap_iface = getApIfaceByInstanceId(instance_id);
    if (ap_iface.get())
        return method(ap_iface);
    return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_WIFI_IFACE_INVALID);
}
#endif

#ifdef CONFIG_P2P
uint16_t WifiInstanceManager::registerP2pIfaceAndGetInstanceId(
    std::shared_ptr<IWifiP2pIface> impl,  const std::string& ifname,
    int32_t chip_id)
{
    if (!impl.get())
        return -1;

    uint16_t instanceId = (chip_id << 12) | P2pIfaceInstanceIdBase |
        (if_nametoindex(ifname.c_str()) & 0xff);

    _wifi_p2p_iface_map[instanceId] = impl;

    return instanceId;
}

uint16_t WifiInstanceManager::getP2pIfaceInstanceId(
    std::shared_ptr<IWifiP2pIface> impl)
{
    for (auto [instanceId, apIface] : _wifi_p2p_iface_map)
        if (apIface == impl)
            return instanceId;
    return -1;
}

std::shared_ptr<IWifiP2pIface> WifiInstanceManager::getP2pIfaceByInstanceId(
    uint16_t instance_id)
{
    auto iter = _wifi_p2p_iface_map.find(instance_id);
    if (iter != _wifi_p2p_iface_map.end())
        return iter->second;
    return nullptr;
}

void WifiInstanceManager::removeP2pIface(std::shared_ptr<IWifiP2pIface> impl)
{
    for (auto iter = _wifi_p2p_iface_map.begin(),
        iter != _wifi_p2p_iface_map.end(), ++iter) {
        if (iter->second == impl) {
            _wifi_p2p_iface_map.erase(iter);
            break;
        }
    }
}

ndk::ScopedAStatus WifiInstanceManager::callWifiP2pIfaceMethod(
    const std::function<ndk::ScopedAStatus(std::shared_ptr<IWifiP2pIface>)> &method,
    uint16_t instance_id)
{
    std::shared_ptr<IWifiP2pIface> p2p_iface = getP2pIfaceByInstanceId(instance_id);
    if (ap_iface.get())
        return method(p2p_iface);
    return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_WIFI_IFACE_INVALID);
}
#endif

} // namespace wifi
} // namespace hardware
} // namespace android
} // namespace aidl

