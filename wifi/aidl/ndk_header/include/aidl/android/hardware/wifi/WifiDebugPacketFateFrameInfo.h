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
#include <aidl/android/hardware/wifi/WifiDebugPacketFateFrameType.h>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiDebugPacketFateFrameInfo {
public:
  ::aidl::android::hardware::wifi::WifiDebugPacketFateFrameType frameType = ::aidl::android::hardware::wifi::WifiDebugPacketFateFrameType(0);
  int64_t frameLen = 0L;
  int64_t driverTimestampUsec = 0L;
  int64_t firmwareTimestampUsec = 0L;
  std::vector<uint8_t> frameContent;

  inline bool operator!=(const WifiDebugPacketFateFrameInfo& rhs) const {
    return std::tie(frameType, frameLen, driverTimestampUsec, firmwareTimestampUsec, frameContent) != std::tie(rhs.frameType, rhs.frameLen, rhs.driverTimestampUsec, rhs.firmwareTimestampUsec, rhs.frameContent);
  }
  inline bool operator<(const WifiDebugPacketFateFrameInfo& rhs) const {
    return std::tie(frameType, frameLen, driverTimestampUsec, firmwareTimestampUsec, frameContent) < std::tie(rhs.frameType, rhs.frameLen, rhs.driverTimestampUsec, rhs.firmwareTimestampUsec, rhs.frameContent);
  }
  inline bool operator<=(const WifiDebugPacketFateFrameInfo& rhs) const {
    return std::tie(frameType, frameLen, driverTimestampUsec, firmwareTimestampUsec, frameContent) <= std::tie(rhs.frameType, rhs.frameLen, rhs.driverTimestampUsec, rhs.firmwareTimestampUsec, rhs.frameContent);
  }
  inline bool operator==(const WifiDebugPacketFateFrameInfo& rhs) const {
    return std::tie(frameType, frameLen, driverTimestampUsec, firmwareTimestampUsec, frameContent) == std::tie(rhs.frameType, rhs.frameLen, rhs.driverTimestampUsec, rhs.firmwareTimestampUsec, rhs.frameContent);
  }
  inline bool operator>(const WifiDebugPacketFateFrameInfo& rhs) const {
    return std::tie(frameType, frameLen, driverTimestampUsec, firmwareTimestampUsec, frameContent) > std::tie(rhs.frameType, rhs.frameLen, rhs.driverTimestampUsec, rhs.firmwareTimestampUsec, rhs.frameContent);
  }
  inline bool operator>=(const WifiDebugPacketFateFrameInfo& rhs) const {
    return std::tie(frameType, frameLen, driverTimestampUsec, firmwareTimestampUsec, frameContent) >= std::tie(rhs.frameType, rhs.frameLen, rhs.driverTimestampUsec, rhs.firmwareTimestampUsec, rhs.frameContent);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
