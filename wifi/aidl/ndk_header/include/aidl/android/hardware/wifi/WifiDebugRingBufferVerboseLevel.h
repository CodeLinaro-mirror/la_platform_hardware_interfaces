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
enum class WifiDebugRingBufferVerboseLevel : int32_t {
  NONE = 0,
  DEFAULT = 1,
  VERBOSE = 2,
  EXCESSIVE = 3,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiDebugRingBufferVerboseLevel val) {
  switch(val) {
  case WifiDebugRingBufferVerboseLevel::NONE:
    return "NONE";
  case WifiDebugRingBufferVerboseLevel::DEFAULT:
    return "DEFAULT";
  case WifiDebugRingBufferVerboseLevel::VERBOSE:
    return "VERBOSE";
  case WifiDebugRingBufferVerboseLevel::EXCESSIVE:
    return "EXCESSIVE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
