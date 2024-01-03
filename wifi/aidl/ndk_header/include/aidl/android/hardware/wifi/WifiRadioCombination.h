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
#include <aidl/android/hardware/wifi/WifiRadioConfiguration.h>

namespace aidl::android::hardware::wifi {
class WifiRadioConfiguration;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiRadioCombination {
public:
  std::vector<::aidl::android::hardware::wifi::WifiRadioConfiguration> radioConfigurations;

  inline bool operator!=(const WifiRadioCombination& rhs) const {
    return std::tie(radioConfigurations) != std::tie(rhs.radioConfigurations);
  }
  inline bool operator<(const WifiRadioCombination& rhs) const {
    return std::tie(radioConfigurations) < std::tie(rhs.radioConfigurations);
  }
  inline bool operator<=(const WifiRadioCombination& rhs) const {
    return std::tie(radioConfigurations) <= std::tie(rhs.radioConfigurations);
  }
  inline bool operator==(const WifiRadioCombination& rhs) const {
    return std::tie(radioConfigurations) == std::tie(rhs.radioConfigurations);
  }
  inline bool operator>(const WifiRadioCombination& rhs) const {
    return std::tie(radioConfigurations) > std::tie(rhs.radioConfigurations);
  }
  inline bool operator>=(const WifiRadioCombination& rhs) const {
    return std::tie(radioConfigurations) >= std::tie(rhs.radioConfigurations);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
