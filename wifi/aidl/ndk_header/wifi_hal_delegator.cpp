/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <cassert>
#include <utils/Log.h>

#include "wifi_hal_delegator.h"

using aidl::android::hardware::wifi::WifiStatusCode;

namespace {
template <class DelegatorType>
int addDelegatorToMap(int32_t id,
	const std::shared_ptr<DelegatorType> &delegator,
	std::map<int32_t, std::shared_ptr<DelegatorType>> &delegatorMap)
{
	if (delegatorMap.find(id) != delegatorMap.end())
		return 1;

	delegatorMap[id] = delegator;

	return 0;
}

template <class DelegatorType>
int removeDelegatorFromMap(int32_t id, 
	std::map<int32_t, std::shared_ptr<DelegatorType>> &delegatorMap)
{
	const auto& iter = delegatorMap.find(id);
	if (iter == delegatorMap.end())
		return 1;

	delegatorMap.erase(iter);

	return 0;
}

template <class DelegatorType>
ndk::ScopedAStatus callInterfaceMethod(int32_t id,
	const std::function<ndk::ScopedAStatus(
		std::shared_ptr<DelegatorType>)> &method,
	const std::map<int32_t, std::shared_ptr<DelegatorType>> &delegatorMap)
{
	auto delegatorIter = delegatorMap.find(id);
	if (delegatorIter == delegatorMap.end())
		return ndk::ScopedAStatus::fail(
			WifiStatusCode::ERROR_NOT_AVAILABLE);

	return method(delegatorIter->second);
}

}

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

WifiHalInterfaceManager* WifiHalInterfaceManager::_instance = NULL;

WifiHalInterfaceManager* WifiHalInterfaceManager::getInterfaceManager()
{
	if (!_instance)
		_instance = new WifiHalInterfaceManager();

	assert(_instance != NULL);
	return _instance;
}

void WifiHalInterfaceManager::destroyInterfaceManager()
{
	_wifiImpl = nullptr;
	_wifiChipImplMap.clear();
	_wifiStaIfaceImplMap.clear();
	_wifiApIfaceImplMap.clear();
#ifdef CONFIG_P2P
	_wifiP2pIfaceImplMap.clear();
#endif
	if (_instance)
		delete _instance;
	_instance = NULL;
}

void WifiHalInterfaceManager::addWifiInterface(
	const std::shared_ptr<IWifi>& impl)
{
	_wifiImpl = std::make_shared<IWifiDelegator>(impl);
}

void WifiHalInterfaceManager::addWifiChipInterface(int32_t chipId,
	const std::shared_ptr<IWifiChip>& impl)
{
	std::shared_ptr<IWifiChipDelegator> wifiChipDelegator =
		std::make_shared<IWifiChipDelegator>(impl);
	if (addDelegatorToMap(chipId, wifiChipDelegator, _wifiChipImplMap))
		ALOGE("Failed to add wifi chip delegator.");
}

void WifiHalInterfaceManager::removeWifiChipInterface(int32_t chipId)
{
	if (removeDelegatorFromMap(chipId, _wifiChipImplMap))
		ALOGE("Failed to add wifi chip delegator.");
}

void WifiHalInterfaceManager::addWifiStaIface(int32_t staIfaceId,
	const std::shared_ptr<IWifiStaIface>& impl)
{
	std::shared_ptr<IWifiStaIfaceDelegator> staIfaceDelegator =
		std::make_shared<IWifiStaIfaceDelegator>(impl);
	if (addDelegatorToMap(staIfaceId, staIfaceDelegator,
		_wifiStaIfaceImplMap))
		ALOGE("Failed to add wifi sta iface delegator.");
}

void WifiHalInterfaceManager::removeWifiStaIface(int32_t staIfaceId)
{
	if (removeDelegatorFromMap(staIfaceId, _wifiStaIfaceImplMap))
		ALOGE("Failed to remove wifi sta iface delegator.");
}

void WifiHalInterfaceManager::addWifiApIface(int32_t apIfaceId,
	const std::shared_ptr<IWifiApIface> &impl)
{
	std::shared_ptr<IWifiApIfaceDelegator> apIfaceDelegator =
		std::make_shared<IWifiApIfaceDelegator>(impl);
	if (addDelegatorToMap(apIfaceId, apIfaceDelegator, _wifiApIfaceImplMap))
		ALOGE("Failed to add wifi ap iface delegator.");
}

void WifiHalInterfaceManager::removeWifiApIface(int32_t apIfaceId)
{
	if (removeDelegatorFromMap(apIfaceId, _wifiApIfaceImplMap))
		ALOGE("Failed to remove wifi ap iface delegator.");
}

#ifdef CONFIG_P2P
void WifiHalInterfaceManager::addWifiP2pIface(int32_t p2pIfaceId,
	const std::shared_ptr<IWifiP2pIface> &impl)
{
	std::shared_ptr<IWifiP2pIfaceDelegator> p2pIfaceDelegator =
		std::make_shared<IWifiP2pIfaceDelegator>(impl);
	if (addDelegatorToMap(p2pIfaceId, p2pIfaceDelegator,
		_wifiP2pIfaceImplMap))
		ALOGE("Failed to add wifi p2p iface delegator.");
}

void WifiHalInterfaceManager::removeWifiP2pIface(int32_t p2pIfaceId)
{
	if (removeDelegatorFromMap(p2pIfaceId, _wifiP2pIfaceImplMap))
		ALOGE("Failed to remove wifi p2p iface delegator.");
}

ndk::ScopedAStatus WifiHalInterfaceManager::callWifiP2pIfaceMethod(
	int32_t p2pIfaceId,
	std::function<ndk::ScopedAStatus(
		std::shared_ptr<IWifiP2pIfaceDelegator>)> &method)
{
	return callInterfaceMethod(p2pIfaceId, method, _wifiP2pIfaceImplMap);
}
#endif

ndk::ScopedAStatus WifiHalInterfaceManager::callWifiMethod(
	const std::function<ndk::ScopedAStatus(
		std::shared_ptr<IWifiDelegator>)> &method)
{
	return method(_wifiImpl);
}

ndk::ScopedAStatus WifiHalInterfaceManager::callWifiChipMethod(int32_t chipId,
	std::function<ndk::ScopedAStatus(
		std::shared_ptr<IWifiChipDelegator>)> &method)
{
	return callInterfaceMethod(chipId, method, _wifiChipImplMap);
}

ndk::ScopedAStatus WifiHalInterfaceManager::callWifiStaIfaceMethod(
	int32_t staIfaceId,
	std::function<ndk::ScopedAStatus(
		std::shared_ptr<IWifiStaIfaceDelegator>)> &method)
{
	return callInterfaceMethod(staIfaceId, method, _wifiStaIfaceImplMap);
}

ndk::ScopedAStatus WifiHalInterfaceManager::callWifiApIfaceMethod(
	int32_t apIfaceId,
	std::function<ndk::ScopedAStatus(
		std::shared_ptr<IWifiApIfaceDelegator>)> &method)
{
	return callInterfaceMethod(apIfaceId, method, _wifiApIfaceImplMap);
}

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
