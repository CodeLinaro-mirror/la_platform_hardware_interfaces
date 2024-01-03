/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <aidl/android/hardware/wifi/IWifiStaIfaceEventCallback.h>
#include <aidl/android/hardware/wifi/StaApfPacketFilterCapabilities.h>
#include <aidl/android/hardware/wifi/StaBackgroundScanCapabilities.h>
#include <aidl/android/hardware/wifi/StaBackgroundScanParameters.h>
#include <aidl/android/hardware/wifi/StaLinkLayerStats.h>
#include <aidl/android/hardware/wifi/StaRoamingCapabilities.h>
#include <aidl/android/hardware/wifi/StaRoamingConfig.h>
#include <aidl/android/hardware/wifi/StaRoamingState.h>
#include <aidl/android/hardware/wifi/WifiDebugRxPacketFateReport.h>
#include <aidl/android/hardware/wifi/WifiDebugTxPacketFateReport.h>
#include <aidl/android/hardware/wifi/ScopedAStatus.h>

namespace aidl::android::hardware::wifi {
class IWifiStaIfaceEventCallback;
class StaApfPacketFilterCapabilities;
class StaBackgroundScanCapabilities;
class StaBackgroundScanParameters;
class StaLinkLayerStats;
class StaRoamingCapabilities;
class StaRoamingConfig;
class WifiDebugRxPacketFateReport;
class WifiDebugTxPacketFateReport;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class IWifiStaIface : public ::ndk::ICInterface {
public:

  enum class FeatureSetMask : int32_t {
    APF = 1,
    BACKGROUND_SCAN = 2,
    LINK_LAYER_STATS = 4,
    RSSI_MONITOR = 8,
    CONTROL_ROAMING = 16,
    PROBE_IE_ALLOWLIST = 32,
    SCAN_RAND = 64,
    STA_5G = 128,
    HOTSPOT = 256,
    PNO = 512,
    TDLS = 1024,
    TDLS_OFFCHANNEL = 2048,
    ND_OFFLOAD = 4096,
    KEEP_ALIVE = 8192,
  };

  virtual ::ndk::ScopedAStatus getName(std::string* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus configureRoaming(const ::aidl::android::hardware::wifi::StaRoamingConfig& in_config) = 0;
  virtual ::ndk::ScopedAStatus disableLinkLayerStatsCollection() = 0;
  virtual ::ndk::ScopedAStatus enableLinkLayerStatsCollection(bool in_debug) = 0;
  virtual ::ndk::ScopedAStatus enableNdOffload(bool in_enable) = 0;
  virtual ::ndk::ScopedAStatus getApfPacketFilterCapabilities(::aidl::android::hardware::wifi::StaApfPacketFilterCapabilities* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getBackgroundScanCapabilities(::aidl::android::hardware::wifi::StaBackgroundScanCapabilities* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getFeatureSet(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getDebugRxPacketFates(std::vector<::aidl::android::hardware::wifi::WifiDebugRxPacketFateReport>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getDebugTxPacketFates(std::vector<::aidl::android::hardware::wifi::WifiDebugTxPacketFateReport>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getFactoryMacAddress(std::array<uint8_t, 6>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getLinkLayerStats(::aidl::android::hardware::wifi::StaLinkLayerStats* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getRoamingCapabilities(::aidl::android::hardware::wifi::StaRoamingCapabilities* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus installApfPacketFilter(const std::vector<uint8_t>& in_program) = 0;
  virtual ::ndk::ScopedAStatus readApfPacketFilterData(std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus registerEventCallback(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIfaceEventCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus setMacAddress(const std::array<uint8_t, 6>& in_mac) = 0;
  virtual ::ndk::ScopedAStatus setRoamingState(::aidl::android::hardware::wifi::StaRoamingState in_state) = 0;
  virtual ::ndk::ScopedAStatus setScanMode(bool in_enable) = 0;
  virtual ::ndk::ScopedAStatus startBackgroundScan(int32_t in_cmdId, const ::aidl::android::hardware::wifi::StaBackgroundScanParameters& in_params) = 0;
  virtual ::ndk::ScopedAStatus startDebugPacketFateMonitoring() = 0;
  virtual ::ndk::ScopedAStatus startRssiMonitoring(int32_t in_cmdId, int32_t in_maxRssi, int32_t in_minRssi) = 0;
  virtual ::ndk::ScopedAStatus startSendingKeepAlivePackets(int32_t in_cmdId, const std::vector<uint8_t>& in_ipPacketData, char16_t in_etherType, const std::array<uint8_t, 6>& in_srcAddress, const std::array<uint8_t, 6>& in_dstAddress, int32_t in_periodInMs) = 0;
  virtual ::ndk::ScopedAStatus stopBackgroundScan(int32_t in_cmdId) = 0;
  virtual ::ndk::ScopedAStatus stopRssiMonitoring(int32_t in_cmdId) = 0;
  virtual ::ndk::ScopedAStatus stopSendingKeepAlivePackets(int32_t in_cmdId) = 0;
  virtual ::ndk::ScopedAStatus setDtimMultiplier(int32_t in_multiplier) = 0;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiStaIface::FeatureSetMask val) {
  switch(val) {
  case IWifiStaIface::FeatureSetMask::APF:
    return "APF";
  case IWifiStaIface::FeatureSetMask::BACKGROUND_SCAN:
    return "BACKGROUND_SCAN";
  case IWifiStaIface::FeatureSetMask::LINK_LAYER_STATS:
    return "LINK_LAYER_STATS";
  case IWifiStaIface::FeatureSetMask::RSSI_MONITOR:
    return "RSSI_MONITOR";
  case IWifiStaIface::FeatureSetMask::CONTROL_ROAMING:
    return "CONTROL_ROAMING";
  case IWifiStaIface::FeatureSetMask::PROBE_IE_ALLOWLIST:
    return "PROBE_IE_ALLOWLIST";
  case IWifiStaIface::FeatureSetMask::SCAN_RAND:
    return "SCAN_RAND";
  case IWifiStaIface::FeatureSetMask::STA_5G:
    return "STA_5G";
  case IWifiStaIface::FeatureSetMask::HOTSPOT:
    return "HOTSPOT";
  case IWifiStaIface::FeatureSetMask::PNO:
    return "PNO";
  case IWifiStaIface::FeatureSetMask::TDLS:
    return "TDLS";
  case IWifiStaIface::FeatureSetMask::TDLS_OFFCHANNEL:
    return "TDLS_OFFCHANNEL";
  case IWifiStaIface::FeatureSetMask::ND_OFFLOAD:
    return "ND_OFFLOAD";
  case IWifiStaIface::FeatureSetMask::KEEP_ALIVE:
    return "KEEP_ALIVE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
