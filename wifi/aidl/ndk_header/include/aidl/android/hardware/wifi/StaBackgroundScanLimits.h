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
enum class StaBackgroundScanLimits : int32_t {
  MAX_CHANNELS = 16,
  MAX_BUCKETS = 16,
  MAX_AP_CACHE_PER_SCAN = 32,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(StaBackgroundScanLimits val) {
  switch(val) {
  case StaBackgroundScanLimits::MAX_CHANNELS:
    return "MAX_CHANNELS";
  case StaBackgroundScanLimits::MAX_AP_CACHE_PER_SCAN:
    return "MAX_AP_CACHE_PER_SCAN";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
