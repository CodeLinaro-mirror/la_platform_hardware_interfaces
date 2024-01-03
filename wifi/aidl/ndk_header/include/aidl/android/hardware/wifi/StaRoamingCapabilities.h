/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaRoamingCapabilities {
public:
  int32_t maxBlocklistSize = 0;
  int32_t maxAllowlistSize = 0;

  inline bool operator!=(const StaRoamingCapabilities& rhs) const {
    return std::tie(maxBlocklistSize, maxAllowlistSize) != std::tie(rhs.maxBlocklistSize, rhs.maxAllowlistSize);
  }
  inline bool operator<(const StaRoamingCapabilities& rhs) const {
    return std::tie(maxBlocklistSize, maxAllowlistSize) < std::tie(rhs.maxBlocklistSize, rhs.maxAllowlistSize);
  }
  inline bool operator<=(const StaRoamingCapabilities& rhs) const {
    return std::tie(maxBlocklistSize, maxAllowlistSize) <= std::tie(rhs.maxBlocklistSize, rhs.maxAllowlistSize);
  }
  inline bool operator==(const StaRoamingCapabilities& rhs) const {
    return std::tie(maxBlocklistSize, maxAllowlistSize) == std::tie(rhs.maxBlocklistSize, rhs.maxAllowlistSize);
  }
  inline bool operator>(const StaRoamingCapabilities& rhs) const {
    return std::tie(maxBlocklistSize, maxAllowlistSize) > std::tie(rhs.maxBlocklistSize, rhs.maxAllowlistSize);
  }
  inline bool operator>=(const StaRoamingCapabilities& rhs) const {
    return std::tie(maxBlocklistSize, maxAllowlistSize) >= std::tie(rhs.maxBlocklistSize, rhs.maxAllowlistSize);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
