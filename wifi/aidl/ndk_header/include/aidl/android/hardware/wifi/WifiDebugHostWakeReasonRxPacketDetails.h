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

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiDebugHostWakeReasonRxPacketDetails {
public:
  int32_t rxUnicastCnt = 0;
  int32_t rxMulticastCnt = 0;
  int32_t rxBroadcastCnt = 0;

  inline bool operator!=(const WifiDebugHostWakeReasonRxPacketDetails& rhs) const {
    return std::tie(rxUnicastCnt, rxMulticastCnt, rxBroadcastCnt) != std::tie(rhs.rxUnicastCnt, rhs.rxMulticastCnt, rhs.rxBroadcastCnt);
  }
  inline bool operator<(const WifiDebugHostWakeReasonRxPacketDetails& rhs) const {
    return std::tie(rxUnicastCnt, rxMulticastCnt, rxBroadcastCnt) < std::tie(rhs.rxUnicastCnt, rhs.rxMulticastCnt, rhs.rxBroadcastCnt);
  }
  inline bool operator<=(const WifiDebugHostWakeReasonRxPacketDetails& rhs) const {
    return std::tie(rxUnicastCnt, rxMulticastCnt, rxBroadcastCnt) <= std::tie(rhs.rxUnicastCnt, rhs.rxMulticastCnt, rhs.rxBroadcastCnt);
  }
  inline bool operator==(const WifiDebugHostWakeReasonRxPacketDetails& rhs) const {
    return std::tie(rxUnicastCnt, rxMulticastCnt, rxBroadcastCnt) == std::tie(rhs.rxUnicastCnt, rhs.rxMulticastCnt, rhs.rxBroadcastCnt);
  }
  inline bool operator>(const WifiDebugHostWakeReasonRxPacketDetails& rhs) const {
    return std::tie(rxUnicastCnt, rxMulticastCnt, rxBroadcastCnt) > std::tie(rhs.rxUnicastCnt, rhs.rxMulticastCnt, rhs.rxBroadcastCnt);
  }
  inline bool operator>=(const WifiDebugHostWakeReasonRxPacketDetails& rhs) const {
    return std::tie(rxUnicastCnt, rxMulticastCnt, rxBroadcastCnt) >= std::tie(rhs.rxUnicastCnt, rhs.rxMulticastCnt, rhs.rxBroadcastCnt);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
