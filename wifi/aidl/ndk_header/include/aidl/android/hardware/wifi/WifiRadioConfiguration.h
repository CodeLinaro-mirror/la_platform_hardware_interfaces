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
#include <aidl/android/hardware/wifi/WifiAntennaMode.h>
#include <aidl/android/hardware/wifi/WifiBand.h>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiRadioConfiguration {
public:
  ::aidl::android::hardware::wifi::WifiBand bandInfo = ::aidl::android::hardware::wifi::WifiBand(0);
  ::aidl::android::hardware::wifi::WifiAntennaMode antennaMode = ::aidl::android::hardware::wifi::WifiAntennaMode(0);

  inline bool operator!=(const WifiRadioConfiguration& rhs) const {
    return std::tie(bandInfo, antennaMode) != std::tie(rhs.bandInfo, rhs.antennaMode);
  }
  inline bool operator<(const WifiRadioConfiguration& rhs) const {
    return std::tie(bandInfo, antennaMode) < std::tie(rhs.bandInfo, rhs.antennaMode);
  }
  inline bool operator<=(const WifiRadioConfiguration& rhs) const {
    return std::tie(bandInfo, antennaMode) <= std::tie(rhs.bandInfo, rhs.antennaMode);
  }
  inline bool operator==(const WifiRadioConfiguration& rhs) const {
    return std::tie(bandInfo, antennaMode) == std::tie(rhs.bandInfo, rhs.antennaMode);
  }
  inline bool operator>(const WifiRadioConfiguration& rhs) const {
    return std::tie(bandInfo, antennaMode) > std::tie(rhs.bandInfo, rhs.antennaMode);
  }
  inline bool operator>=(const WifiRadioConfiguration& rhs) const {
    return std::tie(bandInfo, antennaMode) >= std::tie(rhs.bandInfo, rhs.antennaMode);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
