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

#include <aidl/android/hardware/wifi/ICInterface.h>
#include <aidl/android/hardware/wifi/ScopedAStatus.h>
#include <aidl/android/hardware/wifi/StaScanData.h>
#include <aidl/android/hardware/wifi/StaScanResult.h>

namespace aidl::android::hardware::wifi {
class StaScanData;
class StaScanResult;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class IWifiStaIfaceEventCallback : public ::ndk::ICInterface {
public:
  virtual ::ndk::ScopedAStatus onBackgroundFullScanResult(int32_t in_cmdId, int32_t in_bucketsScanned, const ::aidl::android::hardware::wifi::StaScanResult& in_result) = 0;
  virtual ::ndk::ScopedAStatus onBackgroundScanFailure(int32_t in_cmdId) = 0;
  virtual ::ndk::ScopedAStatus onBackgroundScanResults(int32_t in_cmdId, const std::vector<::aidl::android::hardware::wifi::StaScanData>& in_scanDatas) = 0;
  virtual ::ndk::ScopedAStatus onRssiThresholdBreached(int32_t in_cmdId, const std::array<uint8_t, 6>& in_currBssid, int32_t in_currRssi) = 0;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
