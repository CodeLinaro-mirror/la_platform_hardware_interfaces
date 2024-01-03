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
class WifiChipCapabilities {
public:
  int32_t maxMloAssociationLinkCount = 0;
  int32_t maxMloStrLinkCount = 0;
  int32_t maxConcurrentTdlsSessionCount = 0;

  inline bool operator!=(const WifiChipCapabilities& rhs) const {
    return std::tie(maxMloAssociationLinkCount, maxMloStrLinkCount, maxConcurrentTdlsSessionCount) != std::tie(rhs.maxMloAssociationLinkCount, rhs.maxMloStrLinkCount, rhs.maxConcurrentTdlsSessionCount);
  }
  inline bool operator<(const WifiChipCapabilities& rhs) const {
    return std::tie(maxMloAssociationLinkCount, maxMloStrLinkCount, maxConcurrentTdlsSessionCount) < std::tie(rhs.maxMloAssociationLinkCount, rhs.maxMloStrLinkCount, rhs.maxConcurrentTdlsSessionCount);
  }
  inline bool operator<=(const WifiChipCapabilities& rhs) const {
    return std::tie(maxMloAssociationLinkCount, maxMloStrLinkCount, maxConcurrentTdlsSessionCount) <= std::tie(rhs.maxMloAssociationLinkCount, rhs.maxMloStrLinkCount, rhs.maxConcurrentTdlsSessionCount);
  }
  inline bool operator==(const WifiChipCapabilities& rhs) const {
    return std::tie(maxMloAssociationLinkCount, maxMloStrLinkCount, maxConcurrentTdlsSessionCount) == std::tie(rhs.maxMloAssociationLinkCount, rhs.maxMloStrLinkCount, rhs.maxConcurrentTdlsSessionCount);
  }
  inline bool operator>(const WifiChipCapabilities& rhs) const {
    return std::tie(maxMloAssociationLinkCount, maxMloStrLinkCount, maxConcurrentTdlsSessionCount) > std::tie(rhs.maxMloAssociationLinkCount, rhs.maxMloStrLinkCount, rhs.maxConcurrentTdlsSessionCount);
  }
  inline bool operator>=(const WifiChipCapabilities& rhs) const {
    return std::tie(maxMloAssociationLinkCount, maxMloStrLinkCount, maxConcurrentTdlsSessionCount) >= std::tie(rhs.maxMloAssociationLinkCount, rhs.maxMloStrLinkCount, rhs.maxConcurrentTdlsSessionCount);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
