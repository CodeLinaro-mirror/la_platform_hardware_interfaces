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
#include <aidl/android/hardware/wifi/WifiChannelInfo.h>

namespace aidl::android::hardware::wifi {
class WifiChannelInfo;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiChannelStats {
public:
  ::aidl::android::hardware::wifi::WifiChannelInfo channel;
  int32_t onTimeInMs = 0;
  int32_t ccaBusyTimeInMs = 0;

  inline bool operator!=(const WifiChannelStats& rhs) const {
    return std::tie(channel, onTimeInMs, ccaBusyTimeInMs) != std::tie(rhs.channel, rhs.onTimeInMs, rhs.ccaBusyTimeInMs);
  }
  inline bool operator<(const WifiChannelStats& rhs) const {
    return std::tie(channel, onTimeInMs, ccaBusyTimeInMs) < std::tie(rhs.channel, rhs.onTimeInMs, rhs.ccaBusyTimeInMs);
  }
  inline bool operator<=(const WifiChannelStats& rhs) const {
    return std::tie(channel, onTimeInMs, ccaBusyTimeInMs) <= std::tie(rhs.channel, rhs.onTimeInMs, rhs.ccaBusyTimeInMs);
  }
  inline bool operator==(const WifiChannelStats& rhs) const {
    return std::tie(channel, onTimeInMs, ccaBusyTimeInMs) == std::tie(rhs.channel, rhs.onTimeInMs, rhs.ccaBusyTimeInMs);
  }
  inline bool operator>(const WifiChannelStats& rhs) const {
    return std::tie(channel, onTimeInMs, ccaBusyTimeInMs) > std::tie(rhs.channel, rhs.onTimeInMs, rhs.ccaBusyTimeInMs);
  }
  inline bool operator>=(const WifiChannelStats& rhs) const {
    return std::tie(channel, onTimeInMs, ccaBusyTimeInMs) >= std::tie(rhs.channel, rhs.onTimeInMs, rhs.ccaBusyTimeInMs);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
