/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
enum class IfaceConcurrencyType : int32_t {
  STA = 0,
  AP = 1,
  AP_BRIDGED = 2,
  P2P = 3,
  NAN_IFACE = 4,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IfaceConcurrencyType val) {
  switch(val) {
  case IfaceConcurrencyType::STA:
    return "STA";
  case IfaceConcurrencyType::AP:
    return "AP";
  case IfaceConcurrencyType::AP_BRIDGED:
    return "AP_BRIDGED";
  case IfaceConcurrencyType::P2P:
    return "P2P";
  case IfaceConcurrencyType::NAN_IFACE:
    return "NAN_IFACE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
