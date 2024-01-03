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
#include <aidl/android/hardware/wifi/AvailableAfcChannelInfo.h>
#include <aidl/android/hardware/wifi/AvailableAfcFrequencyInfo.h>

namespace aidl::android::hardware::wifi {
class AvailableAfcChannelInfo;
class AvailableAfcFrequencyInfo;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class AfcChannelAllowance {
public:
  std::vector<::aidl::android::hardware::wifi::AvailableAfcFrequencyInfo> availableAfcFrequencyInfos;
  std::vector<::aidl::android::hardware::wifi::AvailableAfcChannelInfo> availableAfcChannelInfos;
  int64_t availabilityExpireTimeMs = 0L;

  inline bool operator!=(const AfcChannelAllowance& rhs) const {
    return std::tie(availableAfcFrequencyInfos, availableAfcChannelInfos, availabilityExpireTimeMs) != std::tie(rhs.availableAfcFrequencyInfos, rhs.availableAfcChannelInfos, rhs.availabilityExpireTimeMs);
  }
  inline bool operator<(const AfcChannelAllowance& rhs) const {
    return std::tie(availableAfcFrequencyInfos, availableAfcChannelInfos, availabilityExpireTimeMs) < std::tie(rhs.availableAfcFrequencyInfos, rhs.availableAfcChannelInfos, rhs.availabilityExpireTimeMs);
  }
  inline bool operator<=(const AfcChannelAllowance& rhs) const {
    return std::tie(availableAfcFrequencyInfos, availableAfcChannelInfos, availabilityExpireTimeMs) <= std::tie(rhs.availableAfcFrequencyInfos, rhs.availableAfcChannelInfos, rhs.availabilityExpireTimeMs);
  }
  inline bool operator==(const AfcChannelAllowance& rhs) const {
    return std::tie(availableAfcFrequencyInfos, availableAfcChannelInfos, availabilityExpireTimeMs) == std::tie(rhs.availableAfcFrequencyInfos, rhs.availableAfcChannelInfos, rhs.availabilityExpireTimeMs);
  }
  inline bool operator>(const AfcChannelAllowance& rhs) const {
    return std::tie(availableAfcFrequencyInfos, availableAfcChannelInfos, availabilityExpireTimeMs) > std::tie(rhs.availableAfcFrequencyInfos, rhs.availableAfcChannelInfos, rhs.availabilityExpireTimeMs);
  }
  inline bool operator>=(const AfcChannelAllowance& rhs) const {
    return std::tie(availableAfcFrequencyInfos, availableAfcChannelInfos, availabilityExpireTimeMs) >= std::tie(rhs.availableAfcFrequencyInfos, rhs.availableAfcChannelInfos, rhs.availabilityExpireTimeMs);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
