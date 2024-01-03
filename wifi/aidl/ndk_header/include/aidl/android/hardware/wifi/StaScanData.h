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
#include <aidl/android/hardware/wifi/StaScanResult.h>

namespace aidl::android::hardware::wifi {
class StaScanResult;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaScanData {
public:
  int32_t flags = 0;
  int32_t bucketsScanned = 0;
  std::vector<::aidl::android::hardware::wifi::StaScanResult> results;

  inline bool operator!=(const StaScanData& rhs) const {
    return std::tie(flags, bucketsScanned, results) != std::tie(rhs.flags, rhs.bucketsScanned, rhs.results);
  }
  inline bool operator<(const StaScanData& rhs) const {
    return std::tie(flags, bucketsScanned, results) < std::tie(rhs.flags, rhs.bucketsScanned, rhs.results);
  }
  inline bool operator<=(const StaScanData& rhs) const {
    return std::tie(flags, bucketsScanned, results) <= std::tie(rhs.flags, rhs.bucketsScanned, rhs.results);
  }
  inline bool operator==(const StaScanData& rhs) const {
    return std::tie(flags, bucketsScanned, results) == std::tie(rhs.flags, rhs.bucketsScanned, rhs.results);
  }
  inline bool operator>(const StaScanData& rhs) const {
    return std::tie(flags, bucketsScanned, results) > std::tie(rhs.flags, rhs.bucketsScanned, rhs.results);
  }
  inline bool operator>=(const StaScanData& rhs) const {
    return std::tie(flags, bucketsScanned, results) >= std::tie(rhs.flags, rhs.bucketsScanned, rhs.results);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
