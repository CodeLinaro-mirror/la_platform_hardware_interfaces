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
#include <aidl/android/hardware/wifi/WifiDebugHostWakeReasonRxIcmpPacketDetails.h>
#include <aidl/android/hardware/wifi/WifiDebugHostWakeReasonRxMulticastPacketDetails.h>
#include <aidl/android/hardware/wifi/WifiDebugHostWakeReasonRxPacketDetails.h>

namespace aidl::android::hardware::wifi {
class WifiDebugHostWakeReasonRxIcmpPacketDetails;
class WifiDebugHostWakeReasonRxMulticastPacketDetails;
class WifiDebugHostWakeReasonRxPacketDetails;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class WifiDebugHostWakeReasonStats {
public:
  int32_t totalCmdEventWakeCnt = 0;
  std::vector<int32_t> cmdEventWakeCntPerType;
  int32_t totalDriverFwLocalWakeCnt = 0;
  std::vector<int32_t> driverFwLocalWakeCntPerType;
  int32_t totalRxPacketWakeCnt = 0;
  ::aidl::android::hardware::wifi::WifiDebugHostWakeReasonRxPacketDetails rxPktWakeDetails;
  ::aidl::android::hardware::wifi::WifiDebugHostWakeReasonRxMulticastPacketDetails rxMulticastPkWakeDetails;
  ::aidl::android::hardware::wifi::WifiDebugHostWakeReasonRxIcmpPacketDetails rxIcmpPkWakeDetails;

  inline bool operator!=(const WifiDebugHostWakeReasonStats& rhs) const {
    return std::tie(totalCmdEventWakeCnt, cmdEventWakeCntPerType, totalDriverFwLocalWakeCnt, driverFwLocalWakeCntPerType, totalRxPacketWakeCnt, rxPktWakeDetails, rxMulticastPkWakeDetails, rxIcmpPkWakeDetails) != std::tie(rhs.totalCmdEventWakeCnt, rhs.cmdEventWakeCntPerType, rhs.totalDriverFwLocalWakeCnt, rhs.driverFwLocalWakeCntPerType, rhs.totalRxPacketWakeCnt, rhs.rxPktWakeDetails, rhs.rxMulticastPkWakeDetails, rhs.rxIcmpPkWakeDetails);
  }
  inline bool operator<(const WifiDebugHostWakeReasonStats& rhs) const {
    return std::tie(totalCmdEventWakeCnt, cmdEventWakeCntPerType, totalDriverFwLocalWakeCnt, driverFwLocalWakeCntPerType, totalRxPacketWakeCnt, rxPktWakeDetails, rxMulticastPkWakeDetails, rxIcmpPkWakeDetails) < std::tie(rhs.totalCmdEventWakeCnt, rhs.cmdEventWakeCntPerType, rhs.totalDriverFwLocalWakeCnt, rhs.driverFwLocalWakeCntPerType, rhs.totalRxPacketWakeCnt, rhs.rxPktWakeDetails, rhs.rxMulticastPkWakeDetails, rhs.rxIcmpPkWakeDetails);
  }
  inline bool operator<=(const WifiDebugHostWakeReasonStats& rhs) const {
    return std::tie(totalCmdEventWakeCnt, cmdEventWakeCntPerType, totalDriverFwLocalWakeCnt, driverFwLocalWakeCntPerType, totalRxPacketWakeCnt, rxPktWakeDetails, rxMulticastPkWakeDetails, rxIcmpPkWakeDetails) <= std::tie(rhs.totalCmdEventWakeCnt, rhs.cmdEventWakeCntPerType, rhs.totalDriverFwLocalWakeCnt, rhs.driverFwLocalWakeCntPerType, rhs.totalRxPacketWakeCnt, rhs.rxPktWakeDetails, rhs.rxMulticastPkWakeDetails, rhs.rxIcmpPkWakeDetails);
  }
  inline bool operator==(const WifiDebugHostWakeReasonStats& rhs) const {
    return std::tie(totalCmdEventWakeCnt, cmdEventWakeCntPerType, totalDriverFwLocalWakeCnt, driverFwLocalWakeCntPerType, totalRxPacketWakeCnt, rxPktWakeDetails, rxMulticastPkWakeDetails, rxIcmpPkWakeDetails) == std::tie(rhs.totalCmdEventWakeCnt, rhs.cmdEventWakeCntPerType, rhs.totalDriverFwLocalWakeCnt, rhs.driverFwLocalWakeCntPerType, rhs.totalRxPacketWakeCnt, rhs.rxPktWakeDetails, rhs.rxMulticastPkWakeDetails, rhs.rxIcmpPkWakeDetails);
  }
  inline bool operator>(const WifiDebugHostWakeReasonStats& rhs) const {
    return std::tie(totalCmdEventWakeCnt, cmdEventWakeCntPerType, totalDriverFwLocalWakeCnt, driverFwLocalWakeCntPerType, totalRxPacketWakeCnt, rxPktWakeDetails, rxMulticastPkWakeDetails, rxIcmpPkWakeDetails) > std::tie(rhs.totalCmdEventWakeCnt, rhs.cmdEventWakeCntPerType, rhs.totalDriverFwLocalWakeCnt, rhs.driverFwLocalWakeCntPerType, rhs.totalRxPacketWakeCnt, rhs.rxPktWakeDetails, rhs.rxMulticastPkWakeDetails, rhs.rxIcmpPkWakeDetails);
  }
  inline bool operator>=(const WifiDebugHostWakeReasonStats& rhs) const {
    return std::tie(totalCmdEventWakeCnt, cmdEventWakeCntPerType, totalDriverFwLocalWakeCnt, driverFwLocalWakeCntPerType, totalRxPacketWakeCnt, rxPktWakeDetails, rxMulticastPkWakeDetails, rxIcmpPkWakeDetails) >= std::tie(rhs.totalCmdEventWakeCnt, rhs.cmdEventWakeCntPerType, rhs.totalDriverFwLocalWakeCnt, rhs.driverFwLocalWakeCntPerType, rhs.totalRxPacketWakeCnt, rhs.rxPktWakeDetails, rhs.rxMulticastPkWakeDetails, rhs.rxIcmpPkWakeDetails);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
