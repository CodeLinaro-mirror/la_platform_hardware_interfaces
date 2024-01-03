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
#include <aidl/android/hardware/wifi/WifiInformationElement.h>

namespace aidl::android::hardware::wifi {
class WifiInformationElement;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaScanResult {
public:
  int64_t timeStampInUs = 0L;
  std::vector<uint8_t> ssid;
  std::array<uint8_t, 6> bssid = {{}};
  int32_t rssi = 0;
  int32_t frequency = 0;
  char16_t beaconPeriodInMs = '\0';
  char16_t capability = '\0';
  std::vector<::aidl::android::hardware::wifi::WifiInformationElement> informationElements;

  inline bool operator!=(const StaScanResult& rhs) const {
    return std::tie(timeStampInUs, ssid, bssid, rssi, frequency, beaconPeriodInMs, capability, informationElements) != std::tie(rhs.timeStampInUs, rhs.ssid, rhs.bssid, rhs.rssi, rhs.frequency, rhs.beaconPeriodInMs, rhs.capability, rhs.informationElements);
  }
  inline bool operator<(const StaScanResult& rhs) const {
    return std::tie(timeStampInUs, ssid, bssid, rssi, frequency, beaconPeriodInMs, capability, informationElements) < std::tie(rhs.timeStampInUs, rhs.ssid, rhs.bssid, rhs.rssi, rhs.frequency, rhs.beaconPeriodInMs, rhs.capability, rhs.informationElements);
  }
  inline bool operator<=(const StaScanResult& rhs) const {
    return std::tie(timeStampInUs, ssid, bssid, rssi, frequency, beaconPeriodInMs, capability, informationElements) <= std::tie(rhs.timeStampInUs, rhs.ssid, rhs.bssid, rhs.rssi, rhs.frequency, rhs.beaconPeriodInMs, rhs.capability, rhs.informationElements);
  }
  inline bool operator==(const StaScanResult& rhs) const {
    return std::tie(timeStampInUs, ssid, bssid, rssi, frequency, beaconPeriodInMs, capability, informationElements) == std::tie(rhs.timeStampInUs, rhs.ssid, rhs.bssid, rhs.rssi, rhs.frequency, rhs.beaconPeriodInMs, rhs.capability, rhs.informationElements);
  }
  inline bool operator>(const StaScanResult& rhs) const {
    return std::tie(timeStampInUs, ssid, bssid, rssi, frequency, beaconPeriodInMs, capability, informationElements) > std::tie(rhs.timeStampInUs, rhs.ssid, rhs.bssid, rhs.rssi, rhs.frequency, rhs.beaconPeriodInMs, rhs.capability, rhs.informationElements);
  }
  inline bool operator>=(const StaScanResult& rhs) const {
    return std::tie(timeStampInUs, ssid, bssid, rssi, frequency, beaconPeriodInMs, capability, informationElements) >= std::tie(rhs.timeStampInUs, rhs.ssid, rhs.bssid, rhs.rssi, rhs.frequency, rhs.beaconPeriodInMs, rhs.capability, rhs.informationElements);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
