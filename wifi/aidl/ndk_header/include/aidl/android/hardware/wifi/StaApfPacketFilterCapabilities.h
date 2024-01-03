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
class StaApfPacketFilterCapabilities {
public:
  int32_t version = 0;
  int32_t maxLength = 0;

  inline bool operator!=(const StaApfPacketFilterCapabilities& rhs) const {
    return std::tie(version, maxLength) != std::tie(rhs.version, rhs.maxLength);
  }
  inline bool operator<(const StaApfPacketFilterCapabilities& rhs) const {
    return std::tie(version, maxLength) < std::tie(rhs.version, rhs.maxLength);
  }
  inline bool operator<=(const StaApfPacketFilterCapabilities& rhs) const {
    return std::tie(version, maxLength) <= std::tie(rhs.version, rhs.maxLength);
  }
  inline bool operator==(const StaApfPacketFilterCapabilities& rhs) const {
    return std::tie(version, maxLength) == std::tie(rhs.version, rhs.maxLength);
  }
  inline bool operator>(const StaApfPacketFilterCapabilities& rhs) const {
    return std::tie(version, maxLength) > std::tie(rhs.version, rhs.maxLength);
  }
  inline bool operator>=(const StaApfPacketFilterCapabilities& rhs) const {
    return std::tie(version, maxLength) >= std::tie(rhs.version, rhs.maxLength);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
