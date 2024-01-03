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

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
enum class WifiDebugPacketFateFrameType : int32_t {
  UNKNOWN = 0,
  ETHERNET_II = 1,
  MGMT_80211 = 2,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiDebugPacketFateFrameType val) {
  switch(val) {
  case WifiDebugPacketFateFrameType::UNKNOWN:
    return "UNKNOWN";
  case WifiDebugPacketFateFrameType::ETHERNET_II:
    return "ETHERNET_II";
  case WifiDebugPacketFateFrameType::MGMT_80211:
    return "MGMT_80211";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
