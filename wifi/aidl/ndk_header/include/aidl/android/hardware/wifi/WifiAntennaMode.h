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
enum class WifiAntennaMode : int32_t {
  WIFI_ANTENNA_MODE_UNSPECIFIED = 0,
  WIFI_ANTENNA_MODE_1X1 = 1,
  WIFI_ANTENNA_MODE_2X2 = 2,
  WIFI_ANTENNA_MODE_3X3 = 3,
  WIFI_ANTENNA_MODE_4X4 = 4,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiAntennaMode val) {
  switch(val) {
  case WifiAntennaMode::WIFI_ANTENNA_MODE_UNSPECIFIED:
    return "WIFI_ANTENNA_MODE_UNSPECIFIED";
  case WifiAntennaMode::WIFI_ANTENNA_MODE_1X1:
    return "WIFI_ANTENNA_MODE_1X1";
  case WifiAntennaMode::WIFI_ANTENNA_MODE_2X2:
    return "WIFI_ANTENNA_MODE_2X2";
  case WifiAntennaMode::WIFI_ANTENNA_MODE_3X3:
    return "WIFI_ANTENNA_MODE_3X3";
  case WifiAntennaMode::WIFI_ANTENNA_MODE_4X4:
    return "WIFI_ANTENNA_MODE_4X4";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
