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
#include <aidl/android/hardware/wifi/StaRateStat.h>

namespace aidl::android::hardware::wifi {
class StaRateStat;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaPeerInfo {
public:
  char16_t staCount = '\0';
  char16_t chanUtil = '\0';
  std::vector<::aidl::android::hardware::wifi::StaRateStat> rateStats;

  inline bool operator!=(const StaPeerInfo& rhs) const {
    return std::tie(staCount, chanUtil, rateStats) != std::tie(rhs.staCount, rhs.chanUtil, rhs.rateStats);
  }
  inline bool operator<(const StaPeerInfo& rhs) const {
    return std::tie(staCount, chanUtil, rateStats) < std::tie(rhs.staCount, rhs.chanUtil, rhs.rateStats);
  }
  inline bool operator<=(const StaPeerInfo& rhs) const {
    return std::tie(staCount, chanUtil, rateStats) <= std::tie(rhs.staCount, rhs.chanUtil, rhs.rateStats);
  }
  inline bool operator==(const StaPeerInfo& rhs) const {
    return std::tie(staCount, chanUtil, rateStats) == std::tie(rhs.staCount, rhs.chanUtil, rhs.rateStats);
  }
  inline bool operator>(const StaPeerInfo& rhs) const {
    return std::tie(staCount, chanUtil, rateStats) > std::tie(rhs.staCount, rhs.chanUtil, rhs.rateStats);
  }
  inline bool operator>=(const StaPeerInfo& rhs) const {
    return std::tie(staCount, chanUtil, rateStats) >= std::tie(rhs.staCount, rhs.chanUtil, rhs.rateStats);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
