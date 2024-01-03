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
#include <aidl/android/hardware/wifi/StaBackgroundScanBucketParameters.h>

namespace aidl::android::hardware::wifi {
class StaBackgroundScanBucketParameters;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaBackgroundScanParameters {
public:
  int32_t basePeriodInMs = 0;
  int32_t maxApPerScan = 0;
  int32_t reportThresholdPercent = 0;
  int32_t reportThresholdNumScans = 0;
  std::vector<::aidl::android::hardware::wifi::StaBackgroundScanBucketParameters> buckets;

  inline bool operator!=(const StaBackgroundScanParameters& rhs) const {
    return std::tie(basePeriodInMs, maxApPerScan, reportThresholdPercent, reportThresholdNumScans, buckets) != std::tie(rhs.basePeriodInMs, rhs.maxApPerScan, rhs.reportThresholdPercent, rhs.reportThresholdNumScans, rhs.buckets);
  }
  inline bool operator<(const StaBackgroundScanParameters& rhs) const {
    return std::tie(basePeriodInMs, maxApPerScan, reportThresholdPercent, reportThresholdNumScans, buckets) < std::tie(rhs.basePeriodInMs, rhs.maxApPerScan, rhs.reportThresholdPercent, rhs.reportThresholdNumScans, rhs.buckets);
  }
  inline bool operator<=(const StaBackgroundScanParameters& rhs) const {
    return std::tie(basePeriodInMs, maxApPerScan, reportThresholdPercent, reportThresholdNumScans, buckets) <= std::tie(rhs.basePeriodInMs, rhs.maxApPerScan, rhs.reportThresholdPercent, rhs.reportThresholdNumScans, rhs.buckets);
  }
  inline bool operator==(const StaBackgroundScanParameters& rhs) const {
    return std::tie(basePeriodInMs, maxApPerScan, reportThresholdPercent, reportThresholdNumScans, buckets) == std::tie(rhs.basePeriodInMs, rhs.maxApPerScan, rhs.reportThresholdPercent, rhs.reportThresholdNumScans, rhs.buckets);
  }
  inline bool operator>(const StaBackgroundScanParameters& rhs) const {
    return std::tie(basePeriodInMs, maxApPerScan, reportThresholdPercent, reportThresholdNumScans, buckets) > std::tie(rhs.basePeriodInMs, rhs.maxApPerScan, rhs.reportThresholdPercent, rhs.reportThresholdNumScans, rhs.buckets);
  }
  inline bool operator>=(const StaBackgroundScanParameters& rhs) const {
    return std::tie(basePeriodInMs, maxApPerScan, reportThresholdPercent, reportThresholdNumScans, buckets) >= std::tie(rhs.basePeriodInMs, rhs.maxApPerScan, rhs.reportThresholdPercent, rhs.reportThresholdNumScans, rhs.buckets);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
