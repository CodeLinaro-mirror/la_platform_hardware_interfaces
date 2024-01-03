/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifiChip.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifiChip : public IWifiChip {
public:
  BnWifiChip() {}
  virtual ~BnWifiChip() {}
};

class IWifiChipDelegator : public BnWifiChip {
public:
  explicit IWifiChipDelegator(const std::shared_ptr<IWifiChip> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus configureChip(int32_t in_modeId) override {
    return _impl->configureChip(in_modeId);
  }
  ::ndk::ScopedAStatus createApIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiApIface>* _aidl_return) override {
    return _impl->createApIface(_aidl_return);
  }
  ::ndk::ScopedAStatus createBridgedApIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiApIface>* _aidl_return) override {
    return _impl->createBridgedApIface(_aidl_return);
  }
#ifdef CONFIG_NAN
  ::ndk::ScopedAStatus createNanIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiNanIface>* _aidl_return) override {
    return _impl->createNanIface(_aidl_return);
  }
#endif
#ifdef CONFIG_P2P
  ::ndk::ScopedAStatus createP2pIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiP2pIface>* _aidl_return) override {
    return _impl->createP2pIface(_aidl_return);
  }
#endif
#ifdef CONFIG_RTT
  ::ndk::ScopedAStatus createRttController(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIface>& in_boundIface, std::shared_ptr<::aidl::android::hardware::wifi::IWifiRttController>* _aidl_return) override {
    return _impl->createRttController(in_boundIface, _aidl_return);
  }
#endif
  ::ndk::ScopedAStatus createStaIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIface>* _aidl_return) override {
    return _impl->createStaIface(_aidl_return);
  }
  ::ndk::ScopedAStatus enableDebugErrorAlerts(bool in_enable) override {
    return _impl->enableDebugErrorAlerts(in_enable);
  }
  ::ndk::ScopedAStatus flushRingBufferToFile() override {
    return _impl->flushRingBufferToFile();
  }
  ::ndk::ScopedAStatus forceDumpToDebugRingBuffer(const std::string& in_ringName) override {
    return _impl->forceDumpToDebugRingBuffer(in_ringName);
  }
  ::ndk::ScopedAStatus getApIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiApIface>* _aidl_return) override {
    return _impl->getApIface(in_ifname, _aidl_return);
  }
  ::ndk::ScopedAStatus getApIfaceNames(std::vector<std::string>* _aidl_return) override {
    return _impl->getApIfaceNames(_aidl_return);
  }
  ::ndk::ScopedAStatus getAvailableModes(std::vector<::aidl::android::hardware::wifi::IWifiChip::ChipMode>* _aidl_return) override {
    return _impl->getAvailableModes(_aidl_return);
  }
  ::ndk::ScopedAStatus getFeatureSet(int32_t* _aidl_return) override {
    return _impl->getFeatureSet(_aidl_return);
  }
  ::ndk::ScopedAStatus getDebugHostWakeReasonStats(::aidl::android::hardware::wifi::WifiDebugHostWakeReasonStats* _aidl_return) override {
    return _impl->getDebugHostWakeReasonStats(_aidl_return);
  }
  ::ndk::ScopedAStatus getDebugRingBuffersStatus(std::vector<::aidl::android::hardware::wifi::WifiDebugRingBufferStatus>* _aidl_return) override {
    return _impl->getDebugRingBuffersStatus(_aidl_return);
  }
  ::ndk::ScopedAStatus getId(int32_t* _aidl_return) override {
    return _impl->getId(_aidl_return);
  }
  ::ndk::ScopedAStatus getMode(int32_t* _aidl_return) override {
    return _impl->getMode(_aidl_return);
  }
#ifdef CONFIG_NAN
  ::ndk::ScopedAStatus getNanIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiNanIface>* _aidl_return) override {
    return _impl->getNanIface(in_ifname, _aidl_return);
  }
  ::ndk::ScopedAStatus getNanIfaceNames(std::vector<std::string>* _aidl_return) override {
    return _impl->getNanIfaceNames(_aidl_return);
  }
#endif
#ifdef CONFIG_P2P
  ::ndk::ScopedAStatus getP2pIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiP2pIface>* _aidl_return) override {
    return _impl->getP2pIface(in_ifname, _aidl_return);
  }
  ::ndk::ScopedAStatus getP2pIfaceNames(std::vector<std::string>* _aidl_return) override {
    return _impl->getP2pIfaceNames(_aidl_return);
  }
#endif
  ::ndk::ScopedAStatus getStaIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIface>* _aidl_return) override {
    return _impl->getStaIface(in_ifname, _aidl_return);
  }
  ::ndk::ScopedAStatus getStaIfaceNames(std::vector<std::string>* _aidl_return) override {
    return _impl->getStaIfaceNames(_aidl_return);
  }
  ::ndk::ScopedAStatus getSupportedRadioCombinations(std::vector<::aidl::android::hardware::wifi::WifiRadioCombination>* _aidl_return) override {
    return _impl->getSupportedRadioCombinations(_aidl_return);
  }
  ::ndk::ScopedAStatus getWifiChipCapabilities(::aidl::android::hardware::wifi::WifiChipCapabilities* _aidl_return) override {
    return _impl->getWifiChipCapabilities(_aidl_return);
  }
  ::ndk::ScopedAStatus getUsableChannels(::aidl::android::hardware::wifi::WifiBand in_band, int32_t in_ifaceModeMask, int32_t in_filterMask, std::vector<::aidl::android::hardware::wifi::WifiUsableChannel>* _aidl_return) override {
    return _impl->getUsableChannels(in_band, in_ifaceModeMask, in_filterMask, _aidl_return);
  }
  ::ndk::ScopedAStatus setAfcChannelAllowance(const ::aidl::android::hardware::wifi::AfcChannelAllowance& in_afcChannelAllowance) override {
    return _impl->setAfcChannelAllowance(in_afcChannelAllowance);
  }
  ::ndk::ScopedAStatus registerEventCallback(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiChipEventCallback>& in_callback) override {
    return _impl->registerEventCallback(in_callback);
  }
  ::ndk::ScopedAStatus removeApIface(const std::string& in_ifname) override {
    return _impl->removeApIface(in_ifname);
  }
  ::ndk::ScopedAStatus removeIfaceInstanceFromBridgedApIface(const std::string& in_brIfaceName, const std::string& in_ifaceInstanceName) override {
    return _impl->removeIfaceInstanceFromBridgedApIface(in_brIfaceName, in_ifaceInstanceName);
  }
#ifdef CONFIG_NAN
  ::ndk::ScopedAStatus removeNanIface(const std::string& in_ifname) override {
    return _impl->removeNanIface(in_ifname);
  }
#endif
#ifdef CONFIG_P2P
  ::ndk::ScopedAStatus removeP2pIface(const std::string& in_ifname) override {
    return _impl->removeP2pIface(in_ifname);
  }
#endif
  ::ndk::ScopedAStatus removeStaIface(const std::string& in_ifname) override {
    return _impl->removeStaIface(in_ifname);
  }
  ::ndk::ScopedAStatus requestChipDebugInfo(::aidl::android::hardware::wifi::IWifiChip::ChipDebugInfo* _aidl_return) override {
    return _impl->requestChipDebugInfo(_aidl_return);
  }
  ::ndk::ScopedAStatus requestDriverDebugDump(std::vector<uint8_t>* _aidl_return) override {
    return _impl->requestDriverDebugDump(_aidl_return);
  }
  ::ndk::ScopedAStatus requestFirmwareDebugDump(std::vector<uint8_t>* _aidl_return) override {
    return _impl->requestFirmwareDebugDump(_aidl_return);
  }
  ::ndk::ScopedAStatus resetTxPowerScenario() override {
    return _impl->resetTxPowerScenario();
  }
  ::ndk::ScopedAStatus selectTxPowerScenario(::aidl::android::hardware::wifi::IWifiChip::TxPowerScenario in_scenario) override {
    return _impl->selectTxPowerScenario(in_scenario);
  }
  ::ndk::ScopedAStatus setCoexUnsafeChannels(const std::vector<::aidl::android::hardware::wifi::IWifiChip::CoexUnsafeChannel>& in_unsafeChannels, int32_t in_restrictions) override {
    return _impl->setCoexUnsafeChannels(in_unsafeChannels, in_restrictions);
  }
  ::ndk::ScopedAStatus setCountryCode(const std::array<uint8_t, 2>& in_code) override {
    return _impl->setCountryCode(in_code);
  }
  ::ndk::ScopedAStatus setLatencyMode(::aidl::android::hardware::wifi::IWifiChip::LatencyMode in_mode) override {
    return _impl->setLatencyMode(in_mode);
  }
  ::ndk::ScopedAStatus setMultiStaPrimaryConnection(const std::string& in_ifName) override {
    return _impl->setMultiStaPrimaryConnection(in_ifName);
  }
  ::ndk::ScopedAStatus setMultiStaUseCase(::aidl::android::hardware::wifi::IWifiChip::MultiStaUseCase in_useCase) override {
    return _impl->setMultiStaUseCase(in_useCase);
  }
  ::ndk::ScopedAStatus startLoggingToDebugRingBuffer(const std::string& in_ringName, ::aidl::android::hardware::wifi::WifiDebugRingBufferVerboseLevel in_verboseLevel, int32_t in_maxIntervalInSec, int32_t in_minDataSizeInBytes) override {
    return _impl->startLoggingToDebugRingBuffer(in_ringName, in_verboseLevel, in_maxIntervalInSec, in_minDataSizeInBytes);
  }
  ::ndk::ScopedAStatus stopLoggingToDebugRingBuffer() override {
    return _impl->stopLoggingToDebugRingBuffer();
  }
  ::ndk::ScopedAStatus triggerSubsystemRestart() override {
    return _impl->triggerSubsystemRestart();
  }
  ::ndk::ScopedAStatus enableStaChannelForPeerNetwork(int32_t in_channelCategoryEnableFlag) override {
    return _impl->enableStaChannelForPeerNetwork(in_channelCategoryEnableFlag);
  }
  ::ndk::ScopedAStatus setMloMode(::aidl::android::hardware::wifi::IWifiChip::ChipMloMode in_mode) override {
    return _impl->setMloMode(in_mode);
  }
private:
  std::shared_ptr<IWifiChip> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
