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
class StaBackgroundScanCapabilities {
public:
  int32_t maxCacheSize = 0;
  int32_t maxBuckets = 0;
  int32_t maxApCachePerScan = 0;
  int32_t maxReportingThreshold = 0;

  inline bool operator!=(const StaBackgroundScanCapabilities& rhs) const {
    return std::tie(maxCacheSize, maxBuckets, maxApCachePerScan, maxReportingThreshold) != std::tie(rhs.maxCacheSize, rhs.maxBuckets, rhs.maxApCachePerScan, rhs.maxReportingThreshold);
  }
  inline bool operator<(const StaBackgroundScanCapabilities& rhs) const {
    return std::tie(maxCacheSize, maxBuckets, maxApCachePerScan, maxReportingThreshold) < std::tie(rhs.maxCacheSize, rhs.maxBuckets, rhs.maxApCachePerScan, rhs.maxReportingThreshold);
  }
  inline bool operator<=(const StaBackgroundScanCapabilities& rhs) const {
    return std::tie(maxCacheSize, maxBuckets, maxApCachePerScan, maxReportingThreshold) <= std::tie(rhs.maxCacheSize, rhs.maxBuckets, rhs.maxApCachePerScan, rhs.maxReportingThreshold);
  }
  inline bool operator==(const StaBackgroundScanCapabilities& rhs) const {
    return std::tie(maxCacheSize, maxBuckets, maxApCachePerScan, maxReportingThreshold) == std::tie(rhs.maxCacheSize, rhs.maxBuckets, rhs.maxApCachePerScan, rhs.maxReportingThreshold);
  }
  inline bool operator>(const StaBackgroundScanCapabilities& rhs) const {
    return std::tie(maxCacheSize, maxBuckets, maxApCachePerScan, maxReportingThreshold) > std::tie(rhs.maxCacheSize, rhs.maxBuckets, rhs.maxApCachePerScan, rhs.maxReportingThreshold);
  }
  inline bool operator>=(const StaBackgroundScanCapabilities& rhs) const {
    return std::tie(maxCacheSize, maxBuckets, maxApCachePerScan, maxReportingThreshold) >= std::tie(rhs.maxCacheSize, rhs.maxBuckets, rhs.maxApCachePerScan, rhs.maxReportingThreshold);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
