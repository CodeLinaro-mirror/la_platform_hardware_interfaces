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
#include <aidl/android/hardware/wifi/WifiRateInfo.h>

namespace aidl::android::hardware::wifi {
class WifiRateInfo;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class StaRateStat {
public:
  ::aidl::android::hardware::wifi::WifiRateInfo rateInfo;
  int32_t txMpdu = 0;
  int32_t rxMpdu = 0;
  int32_t mpduLost = 0;
  int32_t retries = 0;

  inline bool operator!=(const StaRateStat& rhs) const {
    return std::tie(rateInfo, txMpdu, rxMpdu, mpduLost, retries) != std::tie(rhs.rateInfo, rhs.txMpdu, rhs.rxMpdu, rhs.mpduLost, rhs.retries);
  }
  inline bool operator<(const StaRateStat& rhs) const {
    return std::tie(rateInfo, txMpdu, rxMpdu, mpduLost, retries) < std::tie(rhs.rateInfo, rhs.txMpdu, rhs.rxMpdu, rhs.mpduLost, rhs.retries);
  }
  inline bool operator<=(const StaRateStat& rhs) const {
    return std::tie(rateInfo, txMpdu, rxMpdu, mpduLost, retries) <= std::tie(rhs.rateInfo, rhs.txMpdu, rhs.rxMpdu, rhs.mpduLost, rhs.retries);
  }
  inline bool operator==(const StaRateStat& rhs) const {
    return std::tie(rateInfo, txMpdu, rxMpdu, mpduLost, retries) == std::tie(rhs.rateInfo, rhs.txMpdu, rhs.rxMpdu, rhs.mpduLost, rhs.retries);
  }
  inline bool operator>(const StaRateStat& rhs) const {
    return std::tie(rateInfo, txMpdu, rxMpdu, mpduLost, retries) > std::tie(rhs.rateInfo, rhs.txMpdu, rhs.rxMpdu, rhs.mpduLost, rhs.retries);
  }
  inline bool operator>=(const StaRateStat& rhs) const {
    return std::tie(rateInfo, txMpdu, rxMpdu, mpduLost, retries) >= std::tie(rhs.rateInfo, rhs.txMpdu, rhs.rxMpdu, rhs.mpduLost, rhs.retries);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
