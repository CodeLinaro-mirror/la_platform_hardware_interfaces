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
enum class WifiRateNss : int32_t {
  NSS_1x1 = 0,
  NSS_2x2 = 1,
  NSS_3x3 = 2,
  NSS_4x4 = 3,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiRateNss val) {
  switch(val) {
  case WifiRateNss::NSS_1x1:
    return "NSS_1x1";
  case WifiRateNss::NSS_2x2:
    return "NSS_2x2";
  case WifiRateNss::NSS_3x3:
    return "NSS_3x3";
  case WifiRateNss::NSS_4x4:
    return "NSS_4x4";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
