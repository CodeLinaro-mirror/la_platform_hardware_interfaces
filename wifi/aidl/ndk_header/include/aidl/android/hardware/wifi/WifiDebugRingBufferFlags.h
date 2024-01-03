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
enum class WifiDebugRingBufferFlags : int32_t {
  HAS_BINARY_ENTRIES = 1,
  HAS_ASCII_ENTRIES = 2,
  HAS_PER_PACKET_ENTRIES = 4,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiDebugRingBufferFlags val) {
  switch(val) {
  case WifiDebugRingBufferFlags::HAS_BINARY_ENTRIES:
    return "HAS_BINARY_ENTRIES";
  case WifiDebugRingBufferFlags::HAS_ASCII_ENTRIES:
    return "HAS_ASCII_ENTRIES";
  case WifiDebugRingBufferFlags::HAS_PER_PACKET_ENTRIES:
    return "HAS_PER_PACKET_ENTRIES";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
