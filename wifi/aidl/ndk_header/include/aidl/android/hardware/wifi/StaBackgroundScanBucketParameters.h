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
#include <aidl/android/hardware/wifi/WifiBand.h>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaBackgroundScanBucketParameters {
public:
  int32_t bucketIdx = 0;
  ::aidl::android::hardware::wifi::WifiBand band = ::aidl::android::hardware::wifi::WifiBand(0);
  std::vector<int32_t> frequencies;
  int32_t periodInMs = 0;
  int32_t eventReportScheme = 0;
  int32_t exponentialMaxPeriodInMs = 0;
  int32_t exponentialBase = 0;
  int32_t exponentialStepCount = 0;

  inline bool operator!=(const StaBackgroundScanBucketParameters& rhs) const {
    return std::tie(bucketIdx, band, frequencies, periodInMs, eventReportScheme, exponentialMaxPeriodInMs, exponentialBase, exponentialStepCount) != std::tie(rhs.bucketIdx, rhs.band, rhs.frequencies, rhs.periodInMs, rhs.eventReportScheme, rhs.exponentialMaxPeriodInMs, rhs.exponentialBase, rhs.exponentialStepCount);
  }
  inline bool operator<(const StaBackgroundScanBucketParameters& rhs) const {
    return std::tie(bucketIdx, band, frequencies, periodInMs, eventReportScheme, exponentialMaxPeriodInMs, exponentialBase, exponentialStepCount) < std::tie(rhs.bucketIdx, rhs.band, rhs.frequencies, rhs.periodInMs, rhs.eventReportScheme, rhs.exponentialMaxPeriodInMs, rhs.exponentialBase, rhs.exponentialStepCount);
  }
  inline bool operator<=(const StaBackgroundScanBucketParameters& rhs) const {
    return std::tie(bucketIdx, band, frequencies, periodInMs, eventReportScheme, exponentialMaxPeriodInMs, exponentialBase, exponentialStepCount) <= std::tie(rhs.bucketIdx, rhs.band, rhs.frequencies, rhs.periodInMs, rhs.eventReportScheme, rhs.exponentialMaxPeriodInMs, rhs.exponentialBase, rhs.exponentialStepCount);
  }
  inline bool operator==(const StaBackgroundScanBucketParameters& rhs) const {
    return std::tie(bucketIdx, band, frequencies, periodInMs, eventReportScheme, exponentialMaxPeriodInMs, exponentialBase, exponentialStepCount) == std::tie(rhs.bucketIdx, rhs.band, rhs.frequencies, rhs.periodInMs, rhs.eventReportScheme, rhs.exponentialMaxPeriodInMs, rhs.exponentialBase, rhs.exponentialStepCount);
  }
  inline bool operator>(const StaBackgroundScanBucketParameters& rhs) const {
    return std::tie(bucketIdx, band, frequencies, periodInMs, eventReportScheme, exponentialMaxPeriodInMs, exponentialBase, exponentialStepCount) > std::tie(rhs.bucketIdx, rhs.band, rhs.frequencies, rhs.periodInMs, rhs.eventReportScheme, rhs.exponentialMaxPeriodInMs, rhs.exponentialBase, rhs.exponentialStepCount);
  }
  inline bool operator>=(const StaBackgroundScanBucketParameters& rhs) const {
    return std::tie(bucketIdx, band, frequencies, periodInMs, eventReportScheme, exponentialMaxPeriodInMs, exponentialBase, exponentialStepCount) >= std::tie(rhs.bucketIdx, rhs.band, rhs.frequencies, rhs.periodInMs, rhs.eventReportScheme, rhs.exponentialMaxPeriodInMs, rhs.exponentialBase, rhs.exponentialStepCount);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
