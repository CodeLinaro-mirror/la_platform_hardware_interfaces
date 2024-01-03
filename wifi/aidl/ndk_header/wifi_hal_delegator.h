/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <functional>
#include <map>
#include <memory>

#include "aidl/android/hardware/wifi/BnWifiApIface.h"
#include "aidl/android/hardware/wifi/BnWifiChip.h"
#include "aidl/android/hardware/wifi/BnWifi.h"
#ifdef CONFIG_P2P
#include "aidl/android/hardware/wifi/BnWifiP2pIface.h"
#endif
#include "aidl/android/hardware/wifi/BnWifiStaIface.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class WifiHalInterfaceManager {
public:
	static WifiHalInterfaceManager *getInterfaceManager();
	void destroyInterfaceManager();

	void addWifiInterface(const std::shared_ptr<IWifi> &impl);
	void addWifiChipInterface(int32_t chipId,
		const std::shared_ptr<IWifiChip> &impl);
	void removeWifiChipInterface(int32_t chipId);
	void addWifiStaIface(int32_t staIfaceId,
		const std::shared_ptr<IWifiStaIface> &impl);
	void removeWifiStaIface(int32_t staIfaceId);
	void addWifiApIface(int32_t apIfaceId,
		const std::shared_ptr<IWifiApIface> &impl);
	void removeWifiApIface(int32_t apIfaceId);
#ifdef CONFIG_P2P
	void addWifiP2pIface(int32_t p2pIfaceId,
		const std::shared_ptr<IWifiP2pIface> &impl);
	void removeWifiP2pIface(int32_t p2pIfaceId);
	ndk::ScopedAStatus callWifiP2pIfaceMethod(int32_t p2pIfaceId,
		std::function<ndk::ScopedAStatus(
			std::shared_ptr<IWifiP2pIfaceDelegator>)> &method);
#endif
	ndk::ScopedAStatus callWifiMethod(
		const std::function<ndk::ScopedAStatus(
			std::shared_ptr<IWifiDelegator>)> &method);
	ndk::ScopedAStatus callWifiChipMethod(int32_t chipId,
		std::function<ndk::ScopedAStatus(
			std::shared_ptr<IWifiChipDelegator>)> &method);
	ndk::ScopedAStatus callWifiStaIfaceMethod(int32_t staIfaceId,
		std::function<ndk::ScopedAStatus(
			std::shared_ptr<IWifiStaIfaceDelegator>)> &method);
	ndk::ScopedAStatus callWifiApIfaceMethod(int32_t apIfaceId,
		std::function<ndk::ScopedAStatus(
			std::shared_ptr<IWifiApIfaceDelegator>)> &method);	
private:
	WifiHalInterfaceManager() = default;
	~WifiHalInterfaceManager() = default;

	static WifiHalInterfaceManager *_instance;

	std::shared_ptr<IWifiDelegator> _wifiImpl;
	std::map<int32_t, std::shared_ptr<IWifiChipDelegator>> _wifiChipImplMap;
	std::map<int32_t, std::shared_ptr<IWifiStaIfaceDelegator>> _wifiStaIfaceImplMap;
	std::map<int32_t, std::shared_ptr<IWifiApIfaceDelegator>> _wifiApIfaceImplMap;
#ifdef CONFIG_P2P
	std::map<int32_t, std::shared_ptr<IWifiP2pIfaceDelegator>> _wifiP2pIfaceImplMap;
#endif
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
