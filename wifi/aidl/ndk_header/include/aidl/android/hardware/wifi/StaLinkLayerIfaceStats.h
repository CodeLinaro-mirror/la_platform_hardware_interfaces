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
#include <aidl/android/hardware/wifi/StaLinkLayerLinkStats.h>

namespace aidl::android::hardware::wifi {
class StaLinkLayerLinkStats;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaLinkLayerIfaceStats {
public:
  std::vector<::aidl::android::hardware::wifi::StaLinkLayerLinkStats> links;

  inline bool operator!=(const StaLinkLayerIfaceStats& rhs) const {
    return std::tie(links) != std::tie(rhs.links);
  }
  inline bool operator<(const StaLinkLayerIfaceStats& rhs) const {
    return std::tie(links) < std::tie(rhs.links);
  }
  inline bool operator<=(const StaLinkLayerIfaceStats& rhs) const {
    return std::tie(links) <= std::tie(rhs.links);
  }
  inline bool operator==(const StaLinkLayerIfaceStats& rhs) const {
    return std::tie(links) == std::tie(rhs.links);
  }
  inline bool operator>(const StaLinkLayerIfaceStats& rhs) const {
    return std::tie(links) > std::tie(rhs.links);
  }
  inline bool operator>=(const StaLinkLayerIfaceStats& rhs) const {
    return std::tie(links) >= std::tie(rhs.links);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
