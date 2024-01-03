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
class WifiInformationElement {
public:
  int8_t id = 0;
  std::vector<uint8_t> data;

  inline bool operator!=(const WifiInformationElement& rhs) const {
    return std::tie(id, data) != std::tie(rhs.id, rhs.data);
  }
  inline bool operator<(const WifiInformationElement& rhs) const {
    return std::tie(id, data) < std::tie(rhs.id, rhs.data);
  }
  inline bool operator<=(const WifiInformationElement& rhs) const {
    return std::tie(id, data) <= std::tie(rhs.id, rhs.data);
  }
  inline bool operator==(const WifiInformationElement& rhs) const {
    return std::tie(id, data) == std::tie(rhs.id, rhs.data);
  }
  inline bool operator>(const WifiInformationElement& rhs) const {
    return std::tie(id, data) > std::tie(rhs.id, rhs.data);
  }
  inline bool operator>=(const WifiInformationElement& rhs) const {
    return std::tie(id, data) >= std::tie(rhs.id, rhs.data);
  }

};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
