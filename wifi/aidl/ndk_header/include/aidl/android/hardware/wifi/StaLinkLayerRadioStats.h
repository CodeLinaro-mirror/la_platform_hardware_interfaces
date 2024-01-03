/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <aidl/android/hardware/wifi/WifiChannelStats.h>

namespace aidl::android::hardware::wifi {
class WifiChannelStats;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaLinkLayerRadioStats {
public:
  int32_t onTimeInMs = 0;
  int32_t txTimeInMs = 0;
  std::vector<int32_t> txTimeInMsPerLevel;
  int32_t rxTimeInMs = 0;
  int32_t onTimeInMsForScan = 0;
  int32_t onTimeInMsForNanScan = 0;
  int32_t onTimeInMsForBgScan = 0;
  int32_t onTimeInMsForRoamScan = 0;
  int32_t onTimeInMsForPnoScan = 0;
  int32_t onTimeInMsForHs20Scan = 0;
  std::vector<::aidl::android::hardware::wifi::WifiChannelStats> channelStats;
  int32_t radioId = 0;

  inline bool operator!=(const StaLinkLayerRadioStats& rhs) const {
    return std::tie(onTimeInMs, txTimeInMs, txTimeInMsPerLevel, rxTimeInMs, onTimeInMsForScan, onTimeInMsForNanScan, onTimeInMsForBgScan, onTimeInMsForRoamScan, onTimeInMsForPnoScan, onTimeInMsForHs20Scan, channelStats, radioId) != std::tie(rhs.onTimeInMs, rhs.txTimeInMs, rhs.txTimeInMsPerLevel, rhs.rxTimeInMs, rhs.onTimeInMsForScan, rhs.onTimeInMsForNanScan, rhs.onTimeInMsForBgScan, rhs.onTimeInMsForRoamScan, rhs.onTimeInMsForPnoScan, rhs.onTimeInMsForHs20Scan, rhs.channelStats, rhs.radioId);
  }
  inline bool operator<(const StaLinkLayerRadioStats& rhs) const {
    return std::tie(onTimeInMs, txTimeInMs, txTimeInMsPerLevel, rxTimeInMs, onTimeInMsForScan, onTimeInMsForNanScan, onTimeInMsForBgScan, onTimeInMsForRoamScan, onTimeInMsForPnoScan, onTimeInMsForHs20Scan, channelStats, radioId) < std::tie(rhs.onTimeInMs, rhs.txTimeInMs, rhs.txTimeInMsPerLevel, rhs.rxTimeInMs, rhs.onTimeInMsForScan, rhs.onTimeInMsForNanScan, rhs.onTimeInMsForBgScan, rhs.onTimeInMsForRoamScan, rhs.onTimeInMsForPnoScan, rhs.onTimeInMsForHs20Scan, rhs.channelStats, rhs.radioId);
  }
  inline bool operator<=(const StaLinkLayerRadioStats& rhs) const {
    return std::tie(onTimeInMs, txTimeInMs, txTimeInMsPerLevel, rxTimeInMs, onTimeInMsForScan, onTimeInMsForNanScan, onTimeInMsForBgScan, onTimeInMsForRoamScan, onTimeInMsForPnoScan, onTimeInMsForHs20Scan, channelStats, radioId) <= std::tie(rhs.onTimeInMs, rhs.txTimeInMs, rhs.txTimeInMsPerLevel, rhs.rxTimeInMs, rhs.onTimeInMsForScan, rhs.onTimeInMsForNanScan, rhs.onTimeInMsForBgScan, rhs.onTimeInMsForRoamScan, rhs.onTimeInMsForPnoScan, rhs.onTimeInMsForHs20Scan, rhs.channelStats, rhs.radioId);
  }
  inline bool operator==(const StaLinkLayerRadioStats& rhs) const {
    return std::tie(onTimeInMs, txTimeInMs, txTimeInMsPerLevel, rxTimeInMs, onTimeInMsForScan, onTimeInMsForNanScan, onTimeInMsForBgScan, onTimeInMsForRoamScan, onTimeInMsForPnoScan, onTimeInMsForHs20Scan, channelStats, radioId) == std::tie(rhs.onTimeInMs, rhs.txTimeInMs, rhs.txTimeInMsPerLevel, rhs.rxTimeInMs, rhs.onTimeInMsForScan, rhs.onTimeInMsForNanScan, rhs.onTimeInMsForBgScan, rhs.onTimeInMsForRoamScan, rhs.onTimeInMsForPnoScan, rhs.onTimeInMsForHs20Scan, rhs.channelStats, rhs.radioId);
  }
  inline bool operator>(const StaLinkLayerRadioStats& rhs) const {
    return std::tie(onTimeInMs, txTimeInMs, txTimeInMsPerLevel, rxTimeInMs, onTimeInMsForScan, onTimeInMsForNanScan, onTimeInMsForBgScan, onTimeInMsForRoamScan, onTimeInMsForPnoScan, onTimeInMsForHs20Scan, channelStats, radioId) > std::tie(rhs.onTimeInMs, rhs.txTimeInMs, rhs.txTimeInMsPerLevel, rhs.rxTimeInMs, rhs.onTimeInMsForScan, rhs.onTimeInMsForNanScan, rhs.onTimeInMsForBgScan, rhs.onTimeInMsForRoamScan, rhs.onTimeInMsForPnoScan, rhs.onTimeInMsForHs20Scan, rhs.channelStats, rhs.radioId);
  }
  inline bool operator>=(const StaLinkLayerRadioStats& rhs) const {
    return std::tie(onTimeInMs, txTimeInMs, txTimeInMsPerLevel, rxTimeInMs, onTimeInMsForScan, onTimeInMsForNanScan, onTimeInMsForBgScan, onTimeInMsForRoamScan, onTimeInMsForPnoScan, onTimeInMsForHs20Scan, channelStats, radioId) >= std::tie(rhs.onTimeInMs, rhs.txTimeInMs, rhs.txTimeInMsPerLevel, rhs.rxTimeInMs, rhs.onTimeInMsForScan, rhs.onTimeInMsForNanScan, rhs.onTimeInMsForBgScan, rhs.onTimeInMsForRoamScan, rhs.onTimeInMsForPnoScan, rhs.onTimeInMsForHs20Scan, rhs.channelStats, rhs.radioId);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
