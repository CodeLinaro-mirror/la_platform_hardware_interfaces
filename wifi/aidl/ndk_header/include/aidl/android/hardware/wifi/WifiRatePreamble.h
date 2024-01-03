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
enum class WifiRatePreamble : int32_t {
  OFDM = 0,
  CCK = 1,
  HT = 2,
  VHT = 3,
  RESERVED = 4,
  HE = 5,
  EHT = 6,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiRatePreamble val) {
  switch(val) {
  case WifiRatePreamble::OFDM:
    return "OFDM";
  case WifiRatePreamble::CCK:
    return "CCK";
  case WifiRatePreamble::HT:
    return "HT";
  case WifiRatePreamble::VHT:
    return "VHT";
  case WifiRatePreamble::RESERVED:
    return "RESERVED";
  case WifiRatePreamble::HE:
    return "HE";
  case WifiRatePreamble::EHT:
    return "EHT";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
