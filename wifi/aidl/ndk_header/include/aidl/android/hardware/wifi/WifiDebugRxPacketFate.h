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
enum class WifiDebugRxPacketFate : int32_t {
  SUCCESS = 0,
  FW_QUEUED = 1,
  FW_DROP_FILTER = 2,
  FW_DROP_INVALID = 3,
  FW_DROP_NOBUFS = 4,
  FW_DROP_OTHER = 5,
  DRV_QUEUED = 6,
  DRV_DROP_FILTER = 7,
  DRV_DROP_INVALID = 8,
  DRV_DROP_NOBUFS = 9,
  DRV_DROP_OTHER = 10,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiDebugRxPacketFate val) {
  switch(val) {
  case WifiDebugRxPacketFate::SUCCESS:
    return "SUCCESS";
  case WifiDebugRxPacketFate::FW_QUEUED:
    return "FW_QUEUED";
  case WifiDebugRxPacketFate::FW_DROP_FILTER:
    return "FW_DROP_FILTER";
  case WifiDebugRxPacketFate::FW_DROP_INVALID:
    return "FW_DROP_INVALID";
  case WifiDebugRxPacketFate::FW_DROP_NOBUFS:
    return "FW_DROP_NOBUFS";
  case WifiDebugRxPacketFate::FW_DROP_OTHER:
    return "FW_DROP_OTHER";
  case WifiDebugRxPacketFate::DRV_QUEUED:
    return "DRV_QUEUED";
  case WifiDebugRxPacketFate::DRV_DROP_FILTER:
    return "DRV_DROP_FILTER";
  case WifiDebugRxPacketFate::DRV_DROP_INVALID:
    return "DRV_DROP_INVALID";
  case WifiDebugRxPacketFate::DRV_DROP_NOBUFS:
    return "DRV_DROP_NOBUFS";
  case WifiDebugRxPacketFate::DRV_DROP_OTHER:
    return "DRV_DROP_OTHER";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
