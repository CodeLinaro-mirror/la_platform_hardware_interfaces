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
#include <aidl/android/hardware/wifi/AfcChannelAllowance.h>
#include <aidl/android/hardware/wifi/IWifiApIface.h>
#include <aidl/android/hardware/wifi/IWifiChipEventCallback.h>
#ifdef CONFIG_NAN
#include <aidl/android/hardware/wifi/IWifiNanIface.h>
#endif
#ifdef CONFIG_P2P
#include <aidl/android/hardware/wifi/IWifiP2pIface.h>
#endif
#ifdef CONFIG_RTT
#include <aidl/android/hardware/wifi/IWifiRttController.h>
#endif
#include <aidl/android/hardware/wifi/IWifiStaIface.h>
#include <aidl/android/hardware/wifi/IfaceConcurrencyType.h>
#include <aidl/android/hardware/wifi/IfaceType.h>
#include <aidl/android/hardware/wifi/WifiBand.h>
#include <aidl/android/hardware/wifi/WifiChipCapabilities.h>
#include <aidl/android/hardware/wifi/WifiDebugHostWakeReasonStats.h>
#include <aidl/android/hardware/wifi/WifiDebugRingBufferStatus.h>
#include <aidl/android/hardware/wifi/WifiDebugRingBufferVerboseLevel.h>
#include <aidl/android/hardware/wifi/WifiRadioCombination.h>
#include <aidl/android/hardware/wifi/WifiUsableChannel.h>
#include <aidl/android/hardware/wifi/ScopedAStatus.h>

namespace aidl::android::hardware::wifi {
class AfcChannelAllowance;
class IWifiApIface;
class IWifiChipEventCallback;
#ifdef CONFIG_NAN
class IWifiNanIface;
#endif
#ifdef CONFIG_P2P
class IWifiP2pIface;
#endif
#ifdef CONFIG_RTT
class IWifiRttController;
#endif
class IWifiStaIface;
class WifiChipCapabilities;
class WifiDebugHostWakeReasonStats;
class WifiDebugRingBufferStatus;
class WifiRadioCombination;
class WifiUsableChannel;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class IWifiChip : public ::ndk::ICInterface {
public:

  enum class FeatureSetMask : int32_t {
    SET_TX_POWER_LIMIT = 1,
    D2D_RTT = 2,
    D2AP_RTT = 4,
    USE_BODY_HEAD_SAR = 8,
    SET_LATENCY_MODE = 16,
    P2P_RAND_MAC = 32,
    WIGIG = 64,
    SET_AFC_CHANNEL_ALLOWANCE = 128,
    T2LM_NEGOTIATION = 256,
  };

  class ChipConcurrencyCombinationLimit {
  public:
    std::vector<::aidl::android::hardware::wifi::IfaceConcurrencyType> types;
    int32_t maxIfaces = 0;

    inline bool operator!=(const ChipConcurrencyCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) != std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator<(const ChipConcurrencyCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) < std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator<=(const ChipConcurrencyCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) <= std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator==(const ChipConcurrencyCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) == std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator>(const ChipConcurrencyCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) > std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator>=(const ChipConcurrencyCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) >= std::tie(rhs.types, rhs.maxIfaces);
    }
  };
  class ChipConcurrencyCombination {
  public:
    std::vector<::aidl::android::hardware::wifi::IWifiChip::ChipConcurrencyCombinationLimit> limits;

    inline bool operator!=(const ChipConcurrencyCombination& rhs) const {
      return std::tie(limits) != std::tie(rhs.limits);
    }
    inline bool operator<(const ChipConcurrencyCombination& rhs) const {
      return std::tie(limits) < std::tie(rhs.limits);
    }
    inline bool operator<=(const ChipConcurrencyCombination& rhs) const {
      return std::tie(limits) <= std::tie(rhs.limits);
    }
    inline bool operator==(const ChipConcurrencyCombination& rhs) const {
      return std::tie(limits) == std::tie(rhs.limits);
    }
    inline bool operator>(const ChipConcurrencyCombination& rhs) const {
      return std::tie(limits) > std::tie(rhs.limits);
    }
    inline bool operator>=(const ChipConcurrencyCombination& rhs) const {
      return std::tie(limits) >= std::tie(rhs.limits);
    }

  };
  class ChipDebugInfo {
  public:
    std::string driverDescription;
    std::string firmwareDescription;

    inline bool operator!=(const ChipDebugInfo& rhs) const {
      return std::tie(driverDescription, firmwareDescription) != std::tie(rhs.driverDescription, rhs.firmwareDescription);
    }
    inline bool operator<(const ChipDebugInfo& rhs) const {
      return std::tie(driverDescription, firmwareDescription) < std::tie(rhs.driverDescription, rhs.firmwareDescription);
    }
    inline bool operator<=(const ChipDebugInfo& rhs) const {
      return std::tie(driverDescription, firmwareDescription) <= std::tie(rhs.driverDescription, rhs.firmwareDescription);
    }
    inline bool operator==(const ChipDebugInfo& rhs) const {
      return std::tie(driverDescription, firmwareDescription) == std::tie(rhs.driverDescription, rhs.firmwareDescription);
    }
    inline bool operator>(const ChipDebugInfo& rhs) const {
      return std::tie(driverDescription, firmwareDescription) > std::tie(rhs.driverDescription, rhs.firmwareDescription);
    }
    inline bool operator>=(const ChipDebugInfo& rhs) const {
      return std::tie(driverDescription, firmwareDescription) >= std::tie(rhs.driverDescription, rhs.firmwareDescription);
    }

  };
  class ChipIfaceCombinationLimit {
  public:
    std::vector<::aidl::android::hardware::wifi::IfaceType> types;
    int32_t maxIfaces = 0;

    inline bool operator!=(const ChipIfaceCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) != std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator<(const ChipIfaceCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) < std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator<=(const ChipIfaceCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) <= std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator==(const ChipIfaceCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) == std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator>(const ChipIfaceCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) > std::tie(rhs.types, rhs.maxIfaces);
    }
    inline bool operator>=(const ChipIfaceCombinationLimit& rhs) const {
      return std::tie(types, maxIfaces) >= std::tie(rhs.types, rhs.maxIfaces);
    }

  };
  class ChipIfaceCombination {
  public:
    std::vector<::aidl::android::hardware::wifi::IWifiChip::ChipIfaceCombinationLimit> limits;

    inline bool operator!=(const ChipIfaceCombination& rhs) const {
      return std::tie(limits) != std::tie(rhs.limits);
    }
    inline bool operator<(const ChipIfaceCombination& rhs) const {
      return std::tie(limits) < std::tie(rhs.limits);
    }
    inline bool operator<=(const ChipIfaceCombination& rhs) const {
      return std::tie(limits) <= std::tie(rhs.limits);
    }
    inline bool operator==(const ChipIfaceCombination& rhs) const {
      return std::tie(limits) == std::tie(rhs.limits);
    }
    inline bool operator>(const ChipIfaceCombination& rhs) const {
      return std::tie(limits) > std::tie(rhs.limits);
    }
    inline bool operator>=(const ChipIfaceCombination& rhs) const {
      return std::tie(limits) >= std::tie(rhs.limits);
    }

  };
  class ChipMode {
  public:
    int32_t id = 0;
    std::vector<::aidl::android::hardware::wifi::IWifiChip::ChipConcurrencyCombination> availableCombinations;

    inline bool operator!=(const ChipMode& rhs) const {
      return std::tie(id, availableCombinations) != std::tie(rhs.id, rhs.availableCombinations);
    }
    inline bool operator<(const ChipMode& rhs) const {
      return std::tie(id, availableCombinations) < std::tie(rhs.id, rhs.availableCombinations);
    }
    inline bool operator<=(const ChipMode& rhs) const {
      return std::tie(id, availableCombinations) <= std::tie(rhs.id, rhs.availableCombinations);
    }
    inline bool operator==(const ChipMode& rhs) const {
      return std::tie(id, availableCombinations) == std::tie(rhs.id, rhs.availableCombinations);
    }
    inline bool operator>(const ChipMode& rhs) const {
      return std::tie(id, availableCombinations) > std::tie(rhs.id, rhs.availableCombinations);
    }
    inline bool operator>=(const ChipMode& rhs) const {
      return std::tie(id, availableCombinations) >= std::tie(rhs.id, rhs.availableCombinations);
    }

  };
  enum class CoexRestriction : int32_t {
    WIFI_DIRECT = 1,
    SOFTAP = 2,
    WIFI_AWARE = 4,
  };

  class CoexUnsafeChannel {
  public:
    ::aidl::android::hardware::wifi::WifiBand band = ::aidl::android::hardware::wifi::WifiBand(0);
    int32_t channel = 0;
    int32_t powerCapDbm = 0;

    inline bool operator!=(const CoexUnsafeChannel& rhs) const {
      return std::tie(band, channel, powerCapDbm) != std::tie(rhs.band, rhs.channel, rhs.powerCapDbm);
    }
    inline bool operator<(const CoexUnsafeChannel& rhs) const {
      return std::tie(band, channel, powerCapDbm) < std::tie(rhs.band, rhs.channel, rhs.powerCapDbm);
    }
    inline bool operator<=(const CoexUnsafeChannel& rhs) const {
      return std::tie(band, channel, powerCapDbm) <= std::tie(rhs.band, rhs.channel, rhs.powerCapDbm);
    }
    inline bool operator==(const CoexUnsafeChannel& rhs) const {
      return std::tie(band, channel, powerCapDbm) == std::tie(rhs.band, rhs.channel, rhs.powerCapDbm);
    }
    inline bool operator>(const CoexUnsafeChannel& rhs) const {
      return std::tie(band, channel, powerCapDbm) > std::tie(rhs.band, rhs.channel, rhs.powerCapDbm);
    }
    inline bool operator>=(const CoexUnsafeChannel& rhs) const {
      return std::tie(band, channel, powerCapDbm) >= std::tie(rhs.band, rhs.channel, rhs.powerCapDbm);
    }

  };
  enum class LatencyMode : int32_t {
    NORMAL = 0,
    LOW = 1,
  };

  enum class MultiStaUseCase : int8_t {
    DUAL_STA_TRANSIENT_PREFER_PRIMARY = 0,
    DUAL_STA_NON_TRANSIENT_UNBIASED = 1,
  };

  enum class TxPowerScenario : int32_t {
    VOICE_CALL = 0,
    ON_HEAD_CELL_OFF = 1,
    ON_HEAD_CELL_ON = 2,
    ON_BODY_CELL_OFF = 3,
    ON_BODY_CELL_ON = 4,
  };

  enum class UsableChannelFilter : int32_t {
    CELLULAR_COEXISTENCE = 1,
    CONCURRENCY = 2,
    NAN_INSTANT_MODE = 4,
  };

  enum class ChannelCategoryMask : int32_t {
    INDOOR_CHANNEL = 1,
    DFS_CHANNEL = 2,
  };

  enum class ChipMloMode : int32_t {
    DEFAULT = 0,
    LOW_LATENCY = 1,
    HIGH_THROUGHPUT = 2,
    LOW_POWER = 3,
  };

  virtual ::ndk::ScopedAStatus configureChip(int32_t in_modeId) = 0;
  virtual ::ndk::ScopedAStatus createApIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiApIface>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus createBridgedApIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiApIface>* _aidl_return) = 0;
#ifdef CONFIG_NAN
  virtual ::ndk::ScopedAStatus createNanIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiNanIface>* _aidl_return) = 0;
#endif
#ifdef CONFIG_P2P
  virtual ::ndk::ScopedAStatus createP2pIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiP2pIface>* _aidl_return) = 0;
#endif
#ifdef CONFIG_RTT
  virtual ::ndk::ScopedAStatus createRttController(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIface>& in_boundIface, std::shared_ptr<::aidl::android::hardware::wifi::IWifiRttController>* _aidl_return) = 0;
#endif
  virtual ::ndk::ScopedAStatus createStaIface(std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIface>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus enableDebugErrorAlerts(bool in_enable) = 0;
  virtual ::ndk::ScopedAStatus flushRingBufferToFile() = 0;
  virtual ::ndk::ScopedAStatus forceDumpToDebugRingBuffer(const std::string& in_ringName) = 0;
  virtual ::ndk::ScopedAStatus getApIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiApIface>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getApIfaceNames(std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getAvailableModes(std::vector<::aidl::android::hardware::wifi::IWifiChip::ChipMode>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getFeatureSet(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getDebugHostWakeReasonStats(::aidl::android::hardware::wifi::WifiDebugHostWakeReasonStats* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getDebugRingBuffersStatus(std::vector<::aidl::android::hardware::wifi::WifiDebugRingBufferStatus>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getId(int32_t* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getMode(int32_t* _aidl_return) = 0;
#ifdef CONFIG_NAN
  virtual ::ndk::ScopedAStatus getNanIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiNanIface>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getNanIfaceNames(std::vector<std::string>* _aidl_return) = 0;
#endif
#ifdef CONFIG_P2P
  virtual ::ndk::ScopedAStatus getP2pIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiP2pIface>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getP2pIfaceNames(std::vector<std::string>* _aidl_return) = 0;
#endif
  virtual ::ndk::ScopedAStatus getStaIface(const std::string& in_ifname, std::shared_ptr<::aidl::android::hardware::wifi::IWifiStaIface>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getStaIfaceNames(std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getSupportedRadioCombinations(std::vector<::aidl::android::hardware::wifi::WifiRadioCombination>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getWifiChipCapabilities(::aidl::android::hardware::wifi::WifiChipCapabilities* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getUsableChannels(::aidl::android::hardware::wifi::WifiBand in_band, int32_t in_ifaceModeMask, int32_t in_filterMask, std::vector<::aidl::android::hardware::wifi::WifiUsableChannel>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus setAfcChannelAllowance(const ::aidl::android::hardware::wifi::AfcChannelAllowance& in_afcChannelAllowance) = 0;
  virtual ::ndk::ScopedAStatus registerEventCallback(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiChipEventCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus removeApIface(const std::string& in_ifname) = 0;
  virtual ::ndk::ScopedAStatus removeIfaceInstanceFromBridgedApIface(const std::string& in_brIfaceName, const std::string& in_ifaceInstanceName) = 0;
#ifdef CONFIG_NAN
  virtual ::ndk::ScopedAStatus removeNanIface(const std::string& in_ifname) = 0;
#endif
#ifdef CONFIG_P2P
  virtual ::ndk::ScopedAStatus removeP2pIface(const std::string& in_ifname) = 0;
#endif
  virtual ::ndk::ScopedAStatus removeStaIface(const std::string& in_ifname) = 0;
  virtual ::ndk::ScopedAStatus requestChipDebugInfo(::aidl::android::hardware::wifi::IWifiChip::ChipDebugInfo* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus requestDriverDebugDump(std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus requestFirmwareDebugDump(std::vector<uint8_t>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus resetTxPowerScenario() = 0;
  virtual ::ndk::ScopedAStatus selectTxPowerScenario(::aidl::android::hardware::wifi::IWifiChip::TxPowerScenario in_scenario) = 0;
  virtual ::ndk::ScopedAStatus setCoexUnsafeChannels(const std::vector<::aidl::android::hardware::wifi::IWifiChip::CoexUnsafeChannel>& in_unsafeChannels, int32_t in_restrictions) = 0;
  virtual ::ndk::ScopedAStatus setCountryCode(const std::array<uint8_t, 2>& in_code) = 0;
  virtual ::ndk::ScopedAStatus setLatencyMode(::aidl::android::hardware::wifi::IWifiChip::LatencyMode in_mode) = 0;
  virtual ::ndk::ScopedAStatus setMultiStaPrimaryConnection(const std::string& in_ifName) = 0;
  virtual ::ndk::ScopedAStatus setMultiStaUseCase(::aidl::android::hardware::wifi::IWifiChip::MultiStaUseCase in_useCase) = 0;
  virtual ::ndk::ScopedAStatus startLoggingToDebugRingBuffer(const std::string& in_ringName, ::aidl::android::hardware::wifi::WifiDebugRingBufferVerboseLevel in_verboseLevel, int32_t in_maxIntervalInSec, int32_t in_minDataSizeInBytes) = 0;
  virtual ::ndk::ScopedAStatus stopLoggingToDebugRingBuffer() = 0;
  virtual ::ndk::ScopedAStatus triggerSubsystemRestart() = 0;
  virtual ::ndk::ScopedAStatus enableStaChannelForPeerNetwork(int32_t in_channelCategoryEnableFlag) = 0;
  virtual ::ndk::ScopedAStatus setMloMode(::aidl::android::hardware::wifi::IWifiChip::ChipMloMode in_mode) = 0;
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::FeatureSetMask val) {
  switch(val) {
  case IWifiChip::FeatureSetMask::SET_TX_POWER_LIMIT:
    return "SET_TX_POWER_LIMIT";
  case IWifiChip::FeatureSetMask::D2D_RTT:
    return "D2D_RTT";
  case IWifiChip::FeatureSetMask::D2AP_RTT:
    return "D2AP_RTT";
  case IWifiChip::FeatureSetMask::USE_BODY_HEAD_SAR:
    return "USE_BODY_HEAD_SAR";
  case IWifiChip::FeatureSetMask::SET_LATENCY_MODE:
    return "SET_LATENCY_MODE";
  case IWifiChip::FeatureSetMask::P2P_RAND_MAC:
    return "P2P_RAND_MAC";
  case IWifiChip::FeatureSetMask::WIGIG:
    return "WIGIG";
  case IWifiChip::FeatureSetMask::SET_AFC_CHANNEL_ALLOWANCE:
    return "SET_AFC_CHANNEL_ALLOWANCE";
  case IWifiChip::FeatureSetMask::T2LM_NEGOTIATION:
    return "T2LM_NEGOTIATION";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::CoexRestriction val) {
  switch(val) {
  case IWifiChip::CoexRestriction::WIFI_DIRECT:
    return "WIFI_DIRECT";
  case IWifiChip::CoexRestriction::SOFTAP:
    return "SOFTAP";
  case IWifiChip::CoexRestriction::WIFI_AWARE:
    return "WIFI_AWARE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::LatencyMode val) {
  switch(val) {
  case IWifiChip::LatencyMode::NORMAL:
    return "NORMAL";
  case IWifiChip::LatencyMode::LOW:
    return "LOW";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::MultiStaUseCase val) {
  switch(val) {
  case IWifiChip::MultiStaUseCase::DUAL_STA_TRANSIENT_PREFER_PRIMARY:
    return "DUAL_STA_TRANSIENT_PREFER_PRIMARY";
  case IWifiChip::MultiStaUseCase::DUAL_STA_NON_TRANSIENT_UNBIASED:
    return "DUAL_STA_NON_TRANSIENT_UNBIASED";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::TxPowerScenario val) {
  switch(val) {
  case IWifiChip::TxPowerScenario::VOICE_CALL:
    return "VOICE_CALL";
  case IWifiChip::TxPowerScenario::ON_HEAD_CELL_OFF:
    return "ON_HEAD_CELL_OFF";
  case IWifiChip::TxPowerScenario::ON_HEAD_CELL_ON:
    return "ON_HEAD_CELL_ON";
  case IWifiChip::TxPowerScenario::ON_BODY_CELL_OFF:
    return "ON_BODY_CELL_OFF";
  case IWifiChip::TxPowerScenario::ON_BODY_CELL_ON:
    return "ON_BODY_CELL_ON";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::UsableChannelFilter val) {
  switch(val) {
  case IWifiChip::UsableChannelFilter::CELLULAR_COEXISTENCE:
    return "CELLULAR_COEXISTENCE";
  case IWifiChip::UsableChannelFilter::CONCURRENCY:
    return "CONCURRENCY";
  case IWifiChip::UsableChannelFilter::NAN_INSTANT_MODE:
    return "NAN_INSTANT_MODE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::ChannelCategoryMask val) {
  switch(val) {
  case IWifiChip::ChannelCategoryMask::INDOOR_CHANNEL:
    return "INDOOR_CHANNEL";
  case IWifiChip::ChannelCategoryMask::DFS_CHANNEL:
    return "DFS_CHANNEL";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IWifiChip::ChipMloMode val) {
  switch(val) {
  case IWifiChip::ChipMloMode::DEFAULT:
    return "DEFAULT";
  case IWifiChip::ChipMloMode::LOW_LATENCY:
    return "LOW_LATENCY";
  case IWifiChip::ChipMloMode::HIGH_THROUGHPUT:
    return "HIGH_THROUGHPUT";
  case IWifiChip::ChipMloMode::LOW_POWER:
    return "LOW_POWER";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
