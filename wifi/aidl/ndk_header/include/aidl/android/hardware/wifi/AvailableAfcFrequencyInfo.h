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
class AvailableAfcFrequencyInfo {
public:
  int32_t startFrequencyMhz = 0;
  int32_t endFrequencyMhz = 0;
  int32_t maxPsd = 0;

  inline bool operator!=(const AvailableAfcFrequencyInfo& rhs) const {
    return std::tie(startFrequencyMhz, endFrequencyMhz, maxPsd) != std::tie(rhs.startFrequencyMhz, rhs.endFrequencyMhz, rhs.maxPsd);
  }
  inline bool operator<(const AvailableAfcFrequencyInfo& rhs) const {
    return std::tie(startFrequencyMhz, endFrequencyMhz, maxPsd) < std::tie(rhs.startFrequencyMhz, rhs.endFrequencyMhz, rhs.maxPsd);
  }
  inline bool operator<=(const AvailableAfcFrequencyInfo& rhs) const {
    return std::tie(startFrequencyMhz, endFrequencyMhz, maxPsd) <= std::tie(rhs.startFrequencyMhz, rhs.endFrequencyMhz, rhs.maxPsd);
  }
  inline bool operator==(const AvailableAfcFrequencyInfo& rhs) const {
    return std::tie(startFrequencyMhz, endFrequencyMhz, maxPsd) == std::tie(rhs.startFrequencyMhz, rhs.endFrequencyMhz, rhs.maxPsd);
  }
  inline bool operator>(const AvailableAfcFrequencyInfo& rhs) const {
    return std::tie(startFrequencyMhz, endFrequencyMhz, maxPsd) > std::tie(rhs.startFrequencyMhz, rhs.endFrequencyMhz, rhs.maxPsd);
  }
  inline bool operator>=(const AvailableAfcFrequencyInfo& rhs) const {
    return std::tie(startFrequencyMhz, endFrequencyMhz, maxPsd) >= std::tie(rhs.startFrequencyMhz, rhs.endFrequencyMhz, rhs.maxPsd);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
