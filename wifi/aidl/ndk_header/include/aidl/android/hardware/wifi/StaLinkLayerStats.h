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
#include <aidl/android/hardware/wifi/StaLinkLayerIfaceStats.h>
#include <aidl/android/hardware/wifi/StaLinkLayerRadioStats.h>

namespace aidl::android::hardware::wifi {
class StaLinkLayerIfaceStats;
class StaLinkLayerRadioStats;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaLinkLayerStats {
public:
  ::aidl::android::hardware::wifi::StaLinkLayerIfaceStats iface;
  std::vector<::aidl::android::hardware::wifi::StaLinkLayerRadioStats> radios;
  int64_t timeStampInMs = 0L;

  inline bool operator!=(const StaLinkLayerStats& rhs) const {
    return std::tie(iface, radios, timeStampInMs) != std::tie(rhs.iface, rhs.radios, rhs.timeStampInMs);
  }
  inline bool operator<(const StaLinkLayerStats& rhs) const {
    return std::tie(iface, radios, timeStampInMs) < std::tie(rhs.iface, rhs.radios, rhs.timeStampInMs);
  }
  inline bool operator<=(const StaLinkLayerStats& rhs) const {
    return std::tie(iface, radios, timeStampInMs) <= std::tie(rhs.iface, rhs.radios, rhs.timeStampInMs);
  }
  inline bool operator==(const StaLinkLayerStats& rhs) const {
    return std::tie(iface, radios, timeStampInMs) == std::tie(rhs.iface, rhs.radios, rhs.timeStampInMs);
  }
  inline bool operator>(const StaLinkLayerStats& rhs) const {
    return std::tie(iface, radios, timeStampInMs) > std::tie(rhs.iface, rhs.radios, rhs.timeStampInMs);
  }
  inline bool operator>=(const StaLinkLayerStats& rhs) const {
    return std::tie(iface, radios, timeStampInMs) >= std::tie(rhs.iface, rhs.radios, rhs.timeStampInMs);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
