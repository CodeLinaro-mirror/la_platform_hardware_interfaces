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
enum class IfaceType : int32_t {
  STA = 0,
  AP = 1,
  P2P = 2,
  NAN_IFACE = 3,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(IfaceType val) {
  switch(val) {
  case IfaceType::STA:
    return "STA";
  case IfaceType::AP:
    return "AP";
  case IfaceType::P2P:
    return "P2P";
  case IfaceType::NAN_IFACE:
    return "NAN_IFACE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
