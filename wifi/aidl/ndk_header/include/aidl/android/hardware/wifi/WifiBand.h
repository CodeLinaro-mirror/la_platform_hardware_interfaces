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
enum class WifiBand : int32_t {
  BAND_UNSPECIFIED = 0,
  BAND_24GHZ = 1,
  BAND_5GHZ = 2,
  BAND_5GHZ_DFS = 4,
  BAND_5GHZ_WITH_DFS = 6,
  BAND_24GHZ_5GHZ = 3,
  BAND_24GHZ_5GHZ_WITH_DFS = 7,
  BAND_6GHZ = 8,
  BAND_5GHZ_6GHZ = 10,
  BAND_24GHZ_5GHZ_6GHZ = 11,
  BAND_24GHZ_5GHZ_WITH_DFS_6GHZ = 15,
  BAND_60GHZ = 16,
  BAND_24GHZ_5GHZ_6GHZ_60GHZ = 27,
  BAND_24GHZ_5GHZ_WITH_DFS_6GHZ_60GHZ = 31,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiBand val) {
  switch(val) {
  case WifiBand::BAND_UNSPECIFIED:
    return "BAND_UNSPECIFIED";
  case WifiBand::BAND_24GHZ:
    return "BAND_24GHZ";
  case WifiBand::BAND_5GHZ:
    return "BAND_5GHZ";
  case WifiBand::BAND_5GHZ_DFS:
    return "BAND_5GHZ_DFS";
  case WifiBand::BAND_5GHZ_WITH_DFS:
    return "BAND_5GHZ_WITH_DFS";
  case WifiBand::BAND_24GHZ_5GHZ:
    return "BAND_24GHZ_5GHZ";
  case WifiBand::BAND_24GHZ_5GHZ_WITH_DFS:
    return "BAND_24GHZ_5GHZ_WITH_DFS";
  case WifiBand::BAND_6GHZ:
    return "BAND_6GHZ";
  case WifiBand::BAND_5GHZ_6GHZ:
    return "BAND_5GHZ_6GHZ";
  case WifiBand::BAND_24GHZ_5GHZ_6GHZ:
    return "BAND_24GHZ_5GHZ_6GHZ";
  case WifiBand::BAND_24GHZ_5GHZ_WITH_DFS_6GHZ:
    return "BAND_24GHZ_5GHZ_WITH_DFS_6GHZ";
  case WifiBand::BAND_60GHZ:
    return "BAND_60GHZ";
  case WifiBand::BAND_24GHZ_5GHZ_6GHZ_60GHZ:
    return "BAND_24GHZ_5GHZ_6GHZ_60GHZ";
  case WifiBand::BAND_24GHZ_5GHZ_WITH_DFS_6GHZ_60GHZ:
    return "BAND_24GHZ_5GHZ_WITH_DFS_6GHZ_60GHZ";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
