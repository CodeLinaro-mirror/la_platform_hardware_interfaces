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
class AvailableAfcChannelInfo {
public:
  int32_t globalOperatingClass = 0;
  int32_t channelCfi = 0;
  int32_t maxEirpDbm = 0;

  inline bool operator!=(const AvailableAfcChannelInfo& rhs) const {
    return std::tie(globalOperatingClass, channelCfi, maxEirpDbm) != std::tie(rhs.globalOperatingClass, rhs.channelCfi, rhs.maxEirpDbm);
  }
  inline bool operator<(const AvailableAfcChannelInfo& rhs) const {
    return std::tie(globalOperatingClass, channelCfi, maxEirpDbm) < std::tie(rhs.globalOperatingClass, rhs.channelCfi, rhs.maxEirpDbm);
  }
  inline bool operator<=(const AvailableAfcChannelInfo& rhs) const {
    return std::tie(globalOperatingClass, channelCfi, maxEirpDbm) <= std::tie(rhs.globalOperatingClass, rhs.channelCfi, rhs.maxEirpDbm);
  }
  inline bool operator==(const AvailableAfcChannelInfo& rhs) const {
    return std::tie(globalOperatingClass, channelCfi, maxEirpDbm) == std::tie(rhs.globalOperatingClass, rhs.channelCfi, rhs.maxEirpDbm);
  }
  inline bool operator>(const AvailableAfcChannelInfo& rhs) const {
    return std::tie(globalOperatingClass, channelCfi, maxEirpDbm) > std::tie(rhs.globalOperatingClass, rhs.channelCfi, rhs.maxEirpDbm);
  }
  inline bool operator>=(const AvailableAfcChannelInfo& rhs) const {
    return std::tie(globalOperatingClass, channelCfi, maxEirpDbm) >= std::tie(rhs.globalOperatingClass, rhs.channelCfi, rhs.maxEirpDbm);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
