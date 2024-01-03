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
class WifiDebugRingBufferStatus {
public:
  std::string ringName;
  int32_t flags = 0;
  int32_t ringId = 0;
  int32_t sizeInBytes = 0;
  int32_t freeSizeInBytes = 0;
  int32_t verboseLevel = 0;

  inline bool operator!=(const WifiDebugRingBufferStatus& rhs) const {
    return std::tie(ringName, flags, ringId, sizeInBytes, freeSizeInBytes, verboseLevel) != std::tie(rhs.ringName, rhs.flags, rhs.ringId, rhs.sizeInBytes, rhs.freeSizeInBytes, rhs.verboseLevel);
  }
  inline bool operator<(const WifiDebugRingBufferStatus& rhs) const {
    return std::tie(ringName, flags, ringId, sizeInBytes, freeSizeInBytes, verboseLevel) < std::tie(rhs.ringName, rhs.flags, rhs.ringId, rhs.sizeInBytes, rhs.freeSizeInBytes, rhs.verboseLevel);
  }
  inline bool operator<=(const WifiDebugRingBufferStatus& rhs) const {
    return std::tie(ringName, flags, ringId, sizeInBytes, freeSizeInBytes, verboseLevel) <= std::tie(rhs.ringName, rhs.flags, rhs.ringId, rhs.sizeInBytes, rhs.freeSizeInBytes, rhs.verboseLevel);
  }
  inline bool operator==(const WifiDebugRingBufferStatus& rhs) const {
    return std::tie(ringName, flags, ringId, sizeInBytes, freeSizeInBytes, verboseLevel) == std::tie(rhs.ringName, rhs.flags, rhs.ringId, rhs.sizeInBytes, rhs.freeSizeInBytes, rhs.verboseLevel);
  }
  inline bool operator>(const WifiDebugRingBufferStatus& rhs) const {
    return std::tie(ringName, flags, ringId, sizeInBytes, freeSizeInBytes, verboseLevel) > std::tie(rhs.ringName, rhs.flags, rhs.ringId, rhs.sizeInBytes, rhs.freeSizeInBytes, rhs.verboseLevel);
  }
  inline bool operator>=(const WifiDebugRingBufferStatus& rhs) const {
    return std::tie(ringName, flags, ringId, sizeInBytes, freeSizeInBytes, verboseLevel) >= std::tie(rhs.ringName, rhs.flags, rhs.ringId, rhs.sizeInBytes, rhs.freeSizeInBytes, rhs.verboseLevel);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
