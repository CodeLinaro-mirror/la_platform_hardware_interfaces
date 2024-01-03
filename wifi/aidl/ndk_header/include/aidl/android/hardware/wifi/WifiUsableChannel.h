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
class WifiUsableChannel {
public:
  int32_t channel = 0;
  ::aidl::android::hardware::wifi::WifiChannelWidthInMhz channelBandwidth = ::aidl::android::hardware::wifi::WifiChannelWidthInMhz(0);
  int32_t ifaceModeMask = 0;

  inline bool operator!=(const WifiUsableChannel& rhs) const {
    return std::tie(channel, channelBandwidth, ifaceModeMask) != std::tie(rhs.channel, rhs.channelBandwidth, rhs.ifaceModeMask);
  }
  inline bool operator<(const WifiUsableChannel& rhs) const {
    return std::tie(channel, channelBandwidth, ifaceModeMask) < std::tie(rhs.channel, rhs.channelBandwidth, rhs.ifaceModeMask);
  }
  inline bool operator<=(const WifiUsableChannel& rhs) const {
    return std::tie(channel, channelBandwidth, ifaceModeMask) <= std::tie(rhs.channel, rhs.channelBandwidth, rhs.ifaceModeMask);
  }
  inline bool operator==(const WifiUsableChannel& rhs) const {
    return std::tie(channel, channelBandwidth, ifaceModeMask) == std::tie(rhs.channel, rhs.channelBandwidth, rhs.ifaceModeMask);
  }
  inline bool operator>(const WifiUsableChannel& rhs) const {
    return std::tie(channel, channelBandwidth, ifaceModeMask) > std::tie(rhs.channel, rhs.channelBandwidth, rhs.ifaceModeMask);
  }
  inline bool operator>=(const WifiUsableChannel& rhs) const {
    return std::tie(channel, channelBandwidth, ifaceModeMask) >= std::tie(rhs.channel, rhs.channelBandwidth, rhs.ifaceModeMask);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
