/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
enum class StaBackgroundScanBucketEventReportSchemeMask : int32_t {
  EACH_SCAN = 1,
  FULL_RESULTS = 2,
  NO_BATCH = 4,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(StaBackgroundScanBucketEventReportSchemeMask val) {
  switch(val) {
  case StaBackgroundScanBucketEventReportSchemeMask::EACH_SCAN:
    return "EACH_SCAN";
  case StaBackgroundScanBucketEventReportSchemeMask::FULL_RESULTS:
    return "FULL_RESULTS";
  case StaBackgroundScanBucketEventReportSchemeMask::NO_BATCH:
    return "NO_BATCH";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
