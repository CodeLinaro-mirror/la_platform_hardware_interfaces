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
class StaLinkLayerIfacePacketStats {
public:
  int64_t rxMpdu = 0L;
  int64_t txMpdu = 0L;
  int64_t lostMpdu = 0L;
  int64_t retries = 0L;

  inline bool operator!=(const StaLinkLayerIfacePacketStats& rhs) const {
    return std::tie(rxMpdu, txMpdu, lostMpdu, retries) != std::tie(rhs.rxMpdu, rhs.txMpdu, rhs.lostMpdu, rhs.retries);
  }
  inline bool operator<(const StaLinkLayerIfacePacketStats& rhs) const {
    return std::tie(rxMpdu, txMpdu, lostMpdu, retries) < std::tie(rhs.rxMpdu, rhs.txMpdu, rhs.lostMpdu, rhs.retries);
  }
  inline bool operator<=(const StaLinkLayerIfacePacketStats& rhs) const {
    return std::tie(rxMpdu, txMpdu, lostMpdu, retries) <= std::tie(rhs.rxMpdu, rhs.txMpdu, rhs.lostMpdu, rhs.retries);
  }
  inline bool operator==(const StaLinkLayerIfacePacketStats& rhs) const {
    return std::tie(rxMpdu, txMpdu, lostMpdu, retries) == std::tie(rhs.rxMpdu, rhs.txMpdu, rhs.lostMpdu, rhs.retries);
  }
  inline bool operator>(const StaLinkLayerIfacePacketStats& rhs) const {
    return std::tie(rxMpdu, txMpdu, lostMpdu, retries) > std::tie(rhs.rxMpdu, rhs.txMpdu, rhs.lostMpdu, rhs.retries);
  }
  inline bool operator>=(const StaLinkLayerIfacePacketStats& rhs) const {
    return std::tie(rxMpdu, txMpdu, lostMpdu, retries) >= std::tie(rhs.rxMpdu, rhs.txMpdu, rhs.lostMpdu, rhs.retries);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
