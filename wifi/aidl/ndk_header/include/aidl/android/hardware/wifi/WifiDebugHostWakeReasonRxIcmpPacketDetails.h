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
class WifiDebugHostWakeReasonRxIcmpPacketDetails {
public:
  int32_t icmpPkt = 0;
  int32_t icmp6Pkt = 0;
  int32_t icmp6Ra = 0;
  int32_t icmp6Na = 0;
  int32_t icmp6Ns = 0;

  inline bool operator!=(const WifiDebugHostWakeReasonRxIcmpPacketDetails& rhs) const {
    return std::tie(icmpPkt, icmp6Pkt, icmp6Ra, icmp6Na, icmp6Ns) != std::tie(rhs.icmpPkt, rhs.icmp6Pkt, rhs.icmp6Ra, rhs.icmp6Na, rhs.icmp6Ns);
  }
  inline bool operator<(const WifiDebugHostWakeReasonRxIcmpPacketDetails& rhs) const {
    return std::tie(icmpPkt, icmp6Pkt, icmp6Ra, icmp6Na, icmp6Ns) < std::tie(rhs.icmpPkt, rhs.icmp6Pkt, rhs.icmp6Ra, rhs.icmp6Na, rhs.icmp6Ns);
  }
  inline bool operator<=(const WifiDebugHostWakeReasonRxIcmpPacketDetails& rhs) const {
    return std::tie(icmpPkt, icmp6Pkt, icmp6Ra, icmp6Na, icmp6Ns) <= std::tie(rhs.icmpPkt, rhs.icmp6Pkt, rhs.icmp6Ra, rhs.icmp6Na, rhs.icmp6Ns);
  }
  inline bool operator==(const WifiDebugHostWakeReasonRxIcmpPacketDetails& rhs) const {
    return std::tie(icmpPkt, icmp6Pkt, icmp6Ra, icmp6Na, icmp6Ns) == std::tie(rhs.icmpPkt, rhs.icmp6Pkt, rhs.icmp6Ra, rhs.icmp6Na, rhs.icmp6Ns);
  }
  inline bool operator>(const WifiDebugHostWakeReasonRxIcmpPacketDetails& rhs) const {
    return std::tie(icmpPkt, icmp6Pkt, icmp6Ra, icmp6Na, icmp6Ns) > std::tie(rhs.icmpPkt, rhs.icmp6Pkt, rhs.icmp6Ra, rhs.icmp6Na, rhs.icmp6Ns);
  }
  inline bool operator>=(const WifiDebugHostWakeReasonRxIcmpPacketDetails& rhs) const {
    return std::tie(icmpPkt, icmp6Pkt, icmp6Ra, icmp6Na, icmp6Ns) >= std::tie(rhs.icmpPkt, rhs.icmp6Pkt, rhs.icmp6Ra, rhs.icmp6Na, rhs.icmp6Ns);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
