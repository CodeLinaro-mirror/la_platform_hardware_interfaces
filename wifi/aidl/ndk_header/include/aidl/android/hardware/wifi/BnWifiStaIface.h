/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifiStaIface.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifiStaIface : public IWifiStaIface {
public:
  BnWifiStaIface() {}
  virtual ~BnWifiStaIface() {}
};

class IWifiStaIfaceDelegator : public BnWifiStaIface {
public:
  explicit IWifiStaIfaceDelegator(const std::shared_ptr<IWifiStaIface> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus getName(std::string* _aidl_return) override {
    return _impl->getName(_aidl_return);
  }
  ::ndk::ScopedAStatus configureRoaming(const ::aidl::android::hardware::wifi::StaRoamingConfig& in_config) override {
    return _impl->configureRoaming(in_config);
  }
  ::ndk::ScopedAStatus disableLinkLayerStatsCollection() override {
    return _impl->disableLinkLayerStatsCollection();
  }
  ::ndk::ScopedAStatus enableLinkLayerStatsCollection(bool in_debug) override {
    return _impl->enableLinkLayerStatsCollection(in_debug);
  }
  ::ndk::ScopedAStatus enableNdOffload(bool in_enable) override {
    return _impl->enableNdOffload(in_enable);
  }
  ::ndk::ScopedAStatus getApfPacketFilterCapabilities(::aidl::android::hardware::wifi::StaApfPacketFilterCapabilities* _aidl_return) override {
    return _impl->getApfPacketFilterCapabilities(_aidl_return);
  }
  ::ndk::ScopedAStatus getBackgroundScanCapabilities(::aidl::android::hardware::wifi::StaBackgroundScanCapabilities* _aidl_return) override {
    return _impl->getBackgroundScanCapabilities(_aidl_return);
  }
  ::ndk::ScopedAStatus getFeatureSet(int32_t* _aidl_return) override {
    return _impl->getFeatureSet(_aidl_return);
  }
  ::ndk::ScopedAStatus getDebugRxPacketFates(std::vector<::aidl::android::hardware::wifi::WifiDebugRxPacketFateReport>* _aidl_return) override {
    return _impl->getDebugRxPacketFates(_aidl_return);
  }
  ::ndk::ScopedAStatus getDebugTxPacketFates(std::vector<::aidl::android::hardware::wifi::WifiDebugTxPacketFateReport>* _aidl_return) override {
    return _impl->getDebugTxPacketFates(_aidl_return);
  }
  ::ndk::ScopedAStatus getFactoryMacAddress(std::array<uint8_t, 6>* _aidl_return) override {
    return _impl->getFactoryMacAddress(_aidl_return);
  }
  ::ndk::ScopedAStatus getLinkLayerStats(::aidl::android::hardware::wifi::StaLinkLayerStats* _aidl_return) override {
    return _impl->getLinkLayerStats(_aidl_return);
  }
  ::ndk::ScopedAStatus getRoamingCapabilities(::aidl::android::hardware::wifi::StaRoamingCapabilities* _aidl_return) override {
    return _impl->getRoamingCapabilities(_aidl_return);
  }
  ::ndk::ScopedAStatus installApfPacketFilter(const std::vector<uint8_t>& in_program) override {
    return _impl->installApfPacketFilter(in_program);
  }
  ::ndk::ScopedAStatus readApfPacketFilterData(std::vector<uint8_t>* _aidl_return) override {
    return _impl->readApfPacketFilterData(_aidl_return);
  }
  ::ndk::ScopedAStatus registerEventCallback(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIfaceEventCallback>& in_callback) override {
    return _impl->registerEventCallback(in_callback);
  }
  ::ndk::ScopedAStatus setMacAddress(const std::array<uint8_t, 6>& in_mac) override {
    return _impl->setMacAddress(in_mac);
  }
  ::ndk::ScopedAStatus setRoamingState(::aidl::android::hardware::wifi::StaRoamingState in_state) override {
    return _impl->setRoamingState(in_state);
  }
  ::ndk::ScopedAStatus setScanMode(bool in_enable) override {
    return _impl->setScanMode(in_enable);
  }
  ::ndk::ScopedAStatus startBackgroundScan(int32_t in_cmdId, const ::aidl::android::hardware::wifi::StaBackgroundScanParameters& in_params) override {
    return _impl->startBackgroundScan(in_cmdId, in_params);
  }
  ::ndk::ScopedAStatus startDebugPacketFateMonitoring() override {
    return _impl->startDebugPacketFateMonitoring();
  }
  ::ndk::ScopedAStatus startRssiMonitoring(int32_t in_cmdId, int32_t in_maxRssi, int32_t in_minRssi) override {
    return _impl->startRssiMonitoring(in_cmdId, in_maxRssi, in_minRssi);
  }
  ::ndk::ScopedAStatus startSendingKeepAlivePackets(int32_t in_cmdId, const std::vector<uint8_t>& in_ipPacketData, char16_t in_etherType, const std::array<uint8_t, 6>& in_srcAddress, const std::array<uint8_t, 6>& in_dstAddress, int32_t in_periodInMs) override {
    return _impl->startSendingKeepAlivePackets(in_cmdId, in_ipPacketData, in_etherType, in_srcAddress, in_dstAddress, in_periodInMs);
  }
  ::ndk::ScopedAStatus stopBackgroundScan(int32_t in_cmdId) override {
    return _impl->stopBackgroundScan(in_cmdId);
  }
  ::ndk::ScopedAStatus stopRssiMonitoring(int32_t in_cmdId) override {
    return _impl->stopRssiMonitoring(in_cmdId);
  }
  ::ndk::ScopedAStatus stopSendingKeepAlivePackets(int32_t in_cmdId) override {
    return _impl->stopSendingKeepAlivePackets(in_cmdId);
  }
  ::ndk::ScopedAStatus setDtimMultiplier(int32_t in_multiplier) override {
    return _impl->setDtimMultiplier(in_multiplier);
  }
private:
  std::shared_ptr<IWifiStaIface> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
