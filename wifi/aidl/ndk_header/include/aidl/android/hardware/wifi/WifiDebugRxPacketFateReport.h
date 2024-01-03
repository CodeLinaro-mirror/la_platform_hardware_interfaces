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
#include <aidl/android/hardware/wifi/WifiDebugPacketFateFrameInfo.h>
#include <aidl/android/hardware/wifi/WifiDebugRxPacketFate.h>

namespace aidl::android::hardware::wifi {
class WifiDebugPacketFateFrameInfo;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiDebugRxPacketFateReport {
public:
  ::aidl::android::hardware::wifi::WifiDebugRxPacketFate fate = ::aidl::android::hardware::wifi::WifiDebugRxPacketFate(0);
  ::aidl::android::hardware::wifi::WifiDebugPacketFateFrameInfo frameInfo;

  inline bool operator!=(const WifiDebugRxPacketFateReport& rhs) const {
    return std::tie(fate, frameInfo) != std::tie(rhs.fate, rhs.frameInfo);
  }
  inline bool operator<(const WifiDebugRxPacketFateReport& rhs) const {
    return std::tie(fate, frameInfo) < std::tie(rhs.fate, rhs.frameInfo);
  }
  inline bool operator<=(const WifiDebugRxPacketFateReport& rhs) const {
    return std::tie(fate, frameInfo) <= std::tie(rhs.fate, rhs.frameInfo);
  }
  inline bool operator==(const WifiDebugRxPacketFateReport& rhs) const {
    return std::tie(fate, frameInfo) == std::tie(rhs.fate, rhs.frameInfo);
  }
  inline bool operator>(const WifiDebugRxPacketFateReport& rhs) const {
    return std::tie(fate, frameInfo) > std::tie(rhs.fate, rhs.frameInfo);
  }
  inline bool operator>=(const WifiDebugRxPacketFateReport& rhs) const {
    return std::tie(fate, frameInfo) >= std::tie(rhs.fate, rhs.frameInfo);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
