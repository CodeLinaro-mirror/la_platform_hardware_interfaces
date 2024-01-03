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
class WifiDebugHostWakeReasonRxMulticastPacketDetails {
public:
  int32_t ipv4RxMulticastAddrCnt = 0;
  int32_t ipv6RxMulticastAddrCnt = 0;
  int32_t otherRxMulticastAddrCnt = 0;

  inline bool operator!=(const WifiDebugHostWakeReasonRxMulticastPacketDetails& rhs) const {
    return std::tie(ipv4RxMulticastAddrCnt, ipv6RxMulticastAddrCnt, otherRxMulticastAddrCnt) != std::tie(rhs.ipv4RxMulticastAddrCnt, rhs.ipv6RxMulticastAddrCnt, rhs.otherRxMulticastAddrCnt);
  }
  inline bool operator<(const WifiDebugHostWakeReasonRxMulticastPacketDetails& rhs) const {
    return std::tie(ipv4RxMulticastAddrCnt, ipv6RxMulticastAddrCnt, otherRxMulticastAddrCnt) < std::tie(rhs.ipv4RxMulticastAddrCnt, rhs.ipv6RxMulticastAddrCnt, rhs.otherRxMulticastAddrCnt);
  }
  inline bool operator<=(const WifiDebugHostWakeReasonRxMulticastPacketDetails& rhs) const {
    return std::tie(ipv4RxMulticastAddrCnt, ipv6RxMulticastAddrCnt, otherRxMulticastAddrCnt) <= std::tie(rhs.ipv4RxMulticastAddrCnt, rhs.ipv6RxMulticastAddrCnt, rhs.otherRxMulticastAddrCnt);
  }
  inline bool operator==(const WifiDebugHostWakeReasonRxMulticastPacketDetails& rhs) const {
    return std::tie(ipv4RxMulticastAddrCnt, ipv6RxMulticastAddrCnt, otherRxMulticastAddrCnt) == std::tie(rhs.ipv4RxMulticastAddrCnt, rhs.ipv6RxMulticastAddrCnt, rhs.otherRxMulticastAddrCnt);
  }
  inline bool operator>(const WifiDebugHostWakeReasonRxMulticastPacketDetails& rhs) const {
    return std::tie(ipv4RxMulticastAddrCnt, ipv6RxMulticastAddrCnt, otherRxMulticastAddrCnt) > std::tie(rhs.ipv4RxMulticastAddrCnt, rhs.ipv6RxMulticastAddrCnt, rhs.otherRxMulticastAddrCnt);
  }
  inline bool operator>=(const WifiDebugHostWakeReasonRxMulticastPacketDetails& rhs) const {
    return std::tie(ipv4RxMulticastAddrCnt, ipv6RxMulticastAddrCnt, otherRxMulticastAddrCnt) >= std::tie(rhs.ipv4RxMulticastAddrCnt, rhs.ipv6RxMulticastAddrCnt, rhs.otherRxMulticastAddrCnt);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
