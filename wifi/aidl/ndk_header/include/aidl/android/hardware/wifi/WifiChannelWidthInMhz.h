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
enum class WifiChannelWidthInMhz : int32_t {
  WIDTH_INVALID = -1,
  WIDTH_20 = 0,
  WIDTH_40 = 1,
  WIDTH_80 = 2,
  WIDTH_160 = 3,
  WIDTH_80P80 = 4,
  WIDTH_5 = 5,
  WIDTH_10 = 6,
  WIDTH_320 = 7,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiChannelWidthInMhz val) {
  switch(val) {
  case WifiChannelWidthInMhz::WIDTH_INVALID:
    return "WIDTH_INVALID";
  case WifiChannelWidthInMhz::WIDTH_20:
    return "WIDTH_20";
  case WifiChannelWidthInMhz::WIDTH_40:
    return "WIDTH_40";
  case WifiChannelWidthInMhz::WIDTH_80:
    return "WIDTH_80";
  case WifiChannelWidthInMhz::WIDTH_160:
    return "WIDTH_160";
  case WifiChannelWidthInMhz::WIDTH_80P80:
    return "WIDTH_80P80";
  case WifiChannelWidthInMhz::WIDTH_5:
    return "WIDTH_5";
  case WifiChannelWidthInMhz::WIDTH_10:
    return "WIDTH_10";
  case WifiChannelWidthInMhz::WIDTH_320:
    return "WIDTH_320";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
