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
#include <aidl/android/hardware/wifi/MacAddress.h>
#include <aidl/android/hardware/wifi/Ssid.h>

namespace aidl::android::hardware::wifi {
class MacAddress;
class Ssid;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaRoamingConfig {
public:
  std::vector<::aidl::android::hardware::wifi::MacAddress> bssidBlocklist;
  std::vector<::aidl::android::hardware::wifi::Ssid> ssidAllowlist;

  inline bool operator!=(const StaRoamingConfig& rhs) const {
    return std::tie(bssidBlocklist, ssidAllowlist) != std::tie(rhs.bssidBlocklist, rhs.ssidAllowlist);
  }
  inline bool operator<(const StaRoamingConfig& rhs) const {
    return std::tie(bssidBlocklist, ssidAllowlist) < std::tie(rhs.bssidBlocklist, rhs.ssidAllowlist);
  }
  inline bool operator<=(const StaRoamingConfig& rhs) const {
    return std::tie(bssidBlocklist, ssidAllowlist) <= std::tie(rhs.bssidBlocklist, rhs.ssidAllowlist);
  }
  inline bool operator==(const StaRoamingConfig& rhs) const {
    return std::tie(bssidBlocklist, ssidAllowlist) == std::tie(rhs.bssidBlocklist, rhs.ssidAllowlist);
  }
  inline bool operator>(const StaRoamingConfig& rhs) const {
    return std::tie(bssidBlocklist, ssidAllowlist) > std::tie(rhs.bssidBlocklist, rhs.ssidAllowlist);
  }
  inline bool operator>=(const StaRoamingConfig& rhs) const {
    return std::tie(bssidBlocklist, ssidAllowlist) >= std::tie(rhs.bssidBlocklist, rhs.ssidAllowlist);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
