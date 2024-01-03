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
class StaLinkLayerIfaceContentionTimeStats {
public:
  int32_t contentionTimeMinInUsec = 0;
  int32_t contentionTimeMaxInUsec = 0;
  int32_t contentionTimeAvgInUsec = 0;
  int32_t contentionNumSamples = 0;

  inline bool operator!=(const StaLinkLayerIfaceContentionTimeStats& rhs) const {
    return std::tie(contentionTimeMinInUsec, contentionTimeMaxInUsec, contentionTimeAvgInUsec, contentionNumSamples) != std::tie(rhs.contentionTimeMinInUsec, rhs.contentionTimeMaxInUsec, rhs.contentionTimeAvgInUsec, rhs.contentionNumSamples);
  }
  inline bool operator<(const StaLinkLayerIfaceContentionTimeStats& rhs) const {
    return std::tie(contentionTimeMinInUsec, contentionTimeMaxInUsec, contentionTimeAvgInUsec, contentionNumSamples) < std::tie(rhs.contentionTimeMinInUsec, rhs.contentionTimeMaxInUsec, rhs.contentionTimeAvgInUsec, rhs.contentionNumSamples);
  }
  inline bool operator<=(const StaLinkLayerIfaceContentionTimeStats& rhs) const {
    return std::tie(contentionTimeMinInUsec, contentionTimeMaxInUsec, contentionTimeAvgInUsec, contentionNumSamples) <= std::tie(rhs.contentionTimeMinInUsec, rhs.contentionTimeMaxInUsec, rhs.contentionTimeAvgInUsec, rhs.contentionNumSamples);
  }
  inline bool operator==(const StaLinkLayerIfaceContentionTimeStats& rhs) const {
    return std::tie(contentionTimeMinInUsec, contentionTimeMaxInUsec, contentionTimeAvgInUsec, contentionNumSamples) == std::tie(rhs.contentionTimeMinInUsec, rhs.contentionTimeMaxInUsec, rhs.contentionTimeAvgInUsec, rhs.contentionNumSamples);
  }
  inline bool operator>(const StaLinkLayerIfaceContentionTimeStats& rhs) const {
    return std::tie(contentionTimeMinInUsec, contentionTimeMaxInUsec, contentionTimeAvgInUsec, contentionNumSamples) > std::tie(rhs.contentionTimeMinInUsec, rhs.contentionTimeMaxInUsec, rhs.contentionTimeAvgInUsec, rhs.contentionNumSamples);
  }
  inline bool operator>=(const StaLinkLayerIfaceContentionTimeStats& rhs) const {
    return std::tie(contentionTimeMinInUsec, contentionTimeMaxInUsec, contentionTimeAvgInUsec, contentionNumSamples) >= std::tie(rhs.contentionTimeMinInUsec, rhs.contentionTimeMaxInUsec, rhs.contentionTimeAvgInUsec, rhs.contentionNumSamples);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
