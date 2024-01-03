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
#include <aidl/android/hardware/wifi/WifiChannelWidthInMhz.h>
#include <aidl/android/hardware/wifi/WifiRateNss.h>
#include <aidl/android/hardware/wifi/WifiRatePreamble.h>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiRateInfo {
public:
  ::aidl::android::hardware::wifi::WifiRatePreamble preamble = ::aidl::android::hardware::wifi::WifiRatePreamble(0);
  ::aidl::android::hardware::wifi::WifiRateNss nss = ::aidl::android::hardware::wifi::WifiRateNss(0);
  ::aidl::android::hardware::wifi::WifiChannelWidthInMhz bw = ::aidl::android::hardware::wifi::WifiChannelWidthInMhz(0);
  int8_t rateMcsIdx = 0;
  int32_t bitRateInKbps = 0;

  inline bool operator!=(const WifiRateInfo& rhs) const {
    return std::tie(preamble, nss, bw, rateMcsIdx, bitRateInKbps) != std::tie(rhs.preamble, rhs.nss, rhs.bw, rhs.rateMcsIdx, rhs.bitRateInKbps);
  }
  inline bool operator<(const WifiRateInfo& rhs) const {
    return std::tie(preamble, nss, bw, rateMcsIdx, bitRateInKbps) < std::tie(rhs.preamble, rhs.nss, rhs.bw, rhs.rateMcsIdx, rhs.bitRateInKbps);
  }
  inline bool operator<=(const WifiRateInfo& rhs) const {
    return std::tie(preamble, nss, bw, rateMcsIdx, bitRateInKbps) <= std::tie(rhs.preamble, rhs.nss, rhs.bw, rhs.rateMcsIdx, rhs.bitRateInKbps);
  }
  inline bool operator==(const WifiRateInfo& rhs) const {
    return std::tie(preamble, nss, bw, rateMcsIdx, bitRateInKbps) == std::tie(rhs.preamble, rhs.nss, rhs.bw, rhs.rateMcsIdx, rhs.bitRateInKbps);
  }
  inline bool operator>(const WifiRateInfo& rhs) const {
    return std::tie(preamble, nss, bw, rateMcsIdx, bitRateInKbps) > std::tie(rhs.preamble, rhs.nss, rhs.bw, rhs.rateMcsIdx, rhs.bitRateInKbps);
  }
  inline bool operator>=(const WifiRateInfo& rhs) const {
    return std::tie(preamble, nss, bw, rateMcsIdx, bitRateInKbps) >= std::tie(rhs.preamble, rhs.nss, rhs.bw, rhs.rateMcsIdx, rhs.bitRateInKbps);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
