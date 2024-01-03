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
enum class WifiDebugTxPacketFate : int32_t {
  ACKED = 0,
  SENT = 1,
  FW_QUEUED = 2,
  FW_DROP_INVALID = 3,
  FW_DROP_NOBUFS = 4,
  FW_DROP_OTHER = 5,
  DRV_QUEUED = 6,
  DRV_DROP_INVALID = 7,
  DRV_DROP_NOBUFS = 8,
  DRV_DROP_OTHER = 9,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiDebugTxPacketFate val) {
  switch(val) {
  case WifiDebugTxPacketFate::ACKED:
    return "ACKED";
  case WifiDebugTxPacketFate::SENT:
    return "SENT";
  case WifiDebugTxPacketFate::FW_QUEUED:
    return "FW_QUEUED";
  case WifiDebugTxPacketFate::FW_DROP_INVALID:
    return "FW_DROP_INVALID";
  case WifiDebugTxPacketFate::FW_DROP_NOBUFS:
    return "FW_DROP_NOBUFS";
  case WifiDebugTxPacketFate::FW_DROP_OTHER:
    return "FW_DROP_OTHER";
  case WifiDebugTxPacketFate::DRV_QUEUED:
    return "DRV_QUEUED";
  case WifiDebugTxPacketFate::DRV_DROP_INVALID:
    return "DRV_DROP_INVALID";
  case WifiDebugTxPacketFate::DRV_DROP_NOBUFS:
    return "DRV_DROP_NOBUFS";
  case WifiDebugTxPacketFate::DRV_DROP_OTHER:
    return "DRV_DROP_OTHER";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
