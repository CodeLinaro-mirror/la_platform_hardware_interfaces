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
#include <aidl/android/hardware/wifi/StaLinkLayerIfaceContentionTimeStats.h>
#include <aidl/android/hardware/wifi/StaLinkLayerIfacePacketStats.h>
#include <aidl/android/hardware/wifi/StaLinkLayerLinkStats.h>
#include <aidl/android/hardware/wifi/StaPeerInfo.h>

namespace aidl::android::hardware::wifi {
class StaLinkLayerIfaceContentionTimeStats;
class StaLinkLayerIfacePacketStats;
class StaPeerInfo;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaLinkLayerLinkStats {
public:
  enum class StaLinkState : int32_t {
    UNKNOWN = 0,
    NOT_IN_USE = 1,
    IN_USE = 2,
  };

  int32_t linkId = 0;
  int32_t radioId = 0;
  int32_t frequencyMhz = 0;
  int32_t beaconRx = 0;
  int32_t avgRssiMgmt = 0;
  ::aidl::android::hardware::wifi::StaLinkLayerIfacePacketStats wmeBePktStats;
  ::aidl::android::hardware::wifi::StaLinkLayerIfacePacketStats wmeBkPktStats;
  ::aidl::android::hardware::wifi::StaLinkLayerIfacePacketStats wmeViPktStats;
  ::aidl::android::hardware::wifi::StaLinkLayerIfacePacketStats wmeVoPktStats;
  int8_t timeSliceDutyCycleInPercent = 0;
  ::aidl::android::hardware::wifi::StaLinkLayerIfaceContentionTimeStats wmeBeContentionTimeStats;
  ::aidl::android::hardware::wifi::StaLinkLayerIfaceContentionTimeStats wmeBkContentionTimeStats;
  ::aidl::android::hardware::wifi::StaLinkLayerIfaceContentionTimeStats wmeViContentionTimeStats;
  ::aidl::android::hardware::wifi::StaLinkLayerIfaceContentionTimeStats wmeVoContentionTimeStats;
  std::vector<::aidl::android::hardware::wifi::StaPeerInfo> peers;
  ::aidl::android::hardware::wifi::StaLinkLayerLinkStats::StaLinkState state = ::aidl::android::hardware::wifi::StaLinkLayerLinkStats::StaLinkState(0);

  inline bool operator!=(const StaLinkLayerLinkStats& rhs) const {
    return std::tie(linkId, radioId, frequencyMhz, beaconRx, avgRssiMgmt, wmeBePktStats, wmeBkPktStats, wmeViPktStats, wmeVoPktStats, timeSliceDutyCycleInPercent, wmeBeContentionTimeStats, wmeBkContentionTimeStats, wmeViContentionTimeStats, wmeVoContentionTimeStats, peers, state) != std::tie(rhs.linkId, rhs.radioId, rhs.frequencyMhz, rhs.beaconRx, rhs.avgRssiMgmt, rhs.wmeBePktStats, rhs.wmeBkPktStats, rhs.wmeViPktStats, rhs.wmeVoPktStats, rhs.timeSliceDutyCycleInPercent, rhs.wmeBeContentionTimeStats, rhs.wmeBkContentionTimeStats, rhs.wmeViContentionTimeStats, rhs.wmeVoContentionTimeStats, rhs.peers, rhs.state);
  }
  inline bool operator<(const StaLinkLayerLinkStats& rhs) const {
    return std::tie(linkId, radioId, frequencyMhz, beaconRx, avgRssiMgmt, wmeBePktStats, wmeBkPktStats, wmeViPktStats, wmeVoPktStats, timeSliceDutyCycleInPercent, wmeBeContentionTimeStats, wmeBkContentionTimeStats, wmeViContentionTimeStats, wmeVoContentionTimeStats, peers, state) < std::tie(rhs.linkId, rhs.radioId, rhs.frequencyMhz, rhs.beaconRx, rhs.avgRssiMgmt, rhs.wmeBePktStats, rhs.wmeBkPktStats, rhs.wmeViPktStats, rhs.wmeVoPktStats, rhs.timeSliceDutyCycleInPercent, rhs.wmeBeContentionTimeStats, rhs.wmeBkContentionTimeStats, rhs.wmeViContentionTimeStats, rhs.wmeVoContentionTimeStats, rhs.peers, rhs.state);
  }
  inline bool operator<=(const StaLinkLayerLinkStats& rhs) const {
    return std::tie(linkId, radioId, frequencyMhz, beaconRx, avgRssiMgmt, wmeBePktStats, wmeBkPktStats, wmeViPktStats, wmeVoPktStats, timeSliceDutyCycleInPercent, wmeBeContentionTimeStats, wmeBkContentionTimeStats, wmeViContentionTimeStats, wmeVoContentionTimeStats, peers, state) <= std::tie(rhs.linkId, rhs.radioId, rhs.frequencyMhz, rhs.beaconRx, rhs.avgRssiMgmt, rhs.wmeBePktStats, rhs.wmeBkPktStats, rhs.wmeViPktStats, rhs.wmeVoPktStats, rhs.timeSliceDutyCycleInPercent, rhs.wmeBeContentionTimeStats, rhs.wmeBkContentionTimeStats, rhs.wmeViContentionTimeStats, rhs.wmeVoContentionTimeStats, rhs.peers, rhs.state);
  }
  inline bool operator==(const StaLinkLayerLinkStats& rhs) const {
    return std::tie(linkId, radioId, frequencyMhz, beaconRx, avgRssiMgmt, wmeBePktStats, wmeBkPktStats, wmeViPktStats, wmeVoPktStats, timeSliceDutyCycleInPercent, wmeBeContentionTimeStats, wmeBkContentionTimeStats, wmeViContentionTimeStats, wmeVoContentionTimeStats, peers, state) == std::tie(rhs.linkId, rhs.radioId, rhs.frequencyMhz, rhs.beaconRx, rhs.avgRssiMgmt, rhs.wmeBePktStats, rhs.wmeBkPktStats, rhs.wmeViPktStats, rhs.wmeVoPktStats, rhs.timeSliceDutyCycleInPercent, rhs.wmeBeContentionTimeStats, rhs.wmeBkContentionTimeStats, rhs.wmeViContentionTimeStats, rhs.wmeVoContentionTimeStats, rhs.peers, rhs.state);
  }
  inline bool operator>(const StaLinkLayerLinkStats& rhs) const {
    return std::tie(linkId, radioId, frequencyMhz, beaconRx, avgRssiMgmt, wmeBePktStats, wmeBkPktStats, wmeViPktStats, wmeVoPktStats, timeSliceDutyCycleInPercent, wmeBeContentionTimeStats, wmeBkContentionTimeStats, wmeViContentionTimeStats, wmeVoContentionTimeStats, peers, state) > std::tie(rhs.linkId, rhs.radioId, rhs.frequencyMhz, rhs.beaconRx, rhs.avgRssiMgmt, rhs.wmeBePktStats, rhs.wmeBkPktStats, rhs.wmeViPktStats, rhs.wmeVoPktStats, rhs.timeSliceDutyCycleInPercent, rhs.wmeBeContentionTimeStats, rhs.wmeBkContentionTimeStats, rhs.wmeViContentionTimeStats, rhs.wmeVoContentionTimeStats, rhs.peers, rhs.state);
  }
  inline bool operator>=(const StaLinkLayerLinkStats& rhs) const {
    return std::tie(linkId, radioId, frequencyMhz, beaconRx, avgRssiMgmt, wmeBePktStats, wmeBkPktStats, wmeViPktStats, wmeVoPktStats, timeSliceDutyCycleInPercent, wmeBeContentionTimeStats, wmeBkContentionTimeStats, wmeViContentionTimeStats, wmeVoContentionTimeStats, peers, state) >= std::tie(rhs.linkId, rhs.radioId, rhs.frequencyMhz, rhs.beaconRx, rhs.avgRssiMgmt, rhs.wmeBePktStats, rhs.wmeBkPktStats, rhs.wmeViPktStats, rhs.wmeVoPktStats, rhs.timeSliceDutyCycleInPercent, rhs.wmeBeContentionTimeStats, rhs.wmeBkContentionTimeStats, rhs.wmeViContentionTimeStats, rhs.wmeVoContentionTimeStats, rhs.peers, rhs.state);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(StaLinkLayerLinkStats::StaLinkState val) {
  switch(val) {
  case StaLinkLayerLinkStats::StaLinkState::UNKNOWN:
    return "UNKNOWN";
  case StaLinkLayerLinkStats::StaLinkState::NOT_IN_USE:
    return "NOT_IN_USE";
  case StaLinkLayerLinkStats::StaLinkState::IN_USE:
    return "IN_USE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
