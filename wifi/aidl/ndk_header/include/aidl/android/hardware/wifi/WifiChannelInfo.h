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
#include <aidl/android/hardware/wifi/WifiChannelWidthInMhz.h>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiChannelInfo {
public:
  ::aidl::android::hardware::wifi::WifiChannelWidthInMhz width = ::aidl::android::hardware::wifi::WifiChannelWidthInMhz(0);
  int32_t centerFreq = 0;
  int32_t centerFreq0 = 0;
  int32_t centerFreq1 = 0;

  inline bool operator!=(const WifiChannelInfo& rhs) const {
    return std::tie(width, centerFreq, centerFreq0, centerFreq1) != std::tie(rhs.width, rhs.centerFreq, rhs.centerFreq0, rhs.centerFreq1);
  }
  inline bool operator<(const WifiChannelInfo& rhs) const {
    return std::tie(width, centerFreq, centerFreq0, centerFreq1) < std::tie(rhs.width, rhs.centerFreq, rhs.centerFreq0, rhs.centerFreq1);
  }
  inline bool operator<=(const WifiChannelInfo& rhs) const {
    return std::tie(width, centerFreq, centerFreq0, centerFreq1) <= std::tie(rhs.width, rhs.centerFreq, rhs.centerFreq0, rhs.centerFreq1);
  }
  inline bool operator==(const WifiChannelInfo& rhs) const {
    return std::tie(width, centerFreq, centerFreq0, centerFreq1) == std::tie(rhs.width, rhs.centerFreq, rhs.centerFreq0, rhs.centerFreq1);
  }
  inline bool operator>(const WifiChannelInfo& rhs) const {
    return std::tie(width, centerFreq, centerFreq0, centerFreq1) > std::tie(rhs.width, rhs.centerFreq, rhs.centerFreq0, rhs.centerFreq1);
  }
  inline bool operator>=(const WifiChannelInfo& rhs) const {
    return std::tie(width, centerFreq, centerFreq0, centerFreq1) >= std::tie(rhs.width, rhs.centerFreq, rhs.centerFreq0, rhs.centerFreq1);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
