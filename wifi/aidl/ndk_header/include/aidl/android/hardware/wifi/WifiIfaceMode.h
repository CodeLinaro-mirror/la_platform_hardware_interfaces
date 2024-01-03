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
enum class WifiIfaceMode : int32_t {
  IFACE_MODE_STA = 1,
  IFACE_MODE_SOFTAP = 2,
  IFACE_MODE_IBSS = 4,
  IFACE_MODE_P2P_CLIENT = 8,
  IFACE_MODE_P2P_GO = 16,
  IFACE_MODE_NAN = 32,
  IFACE_MODE_MESH = 64,
  IFACE_MODE_TDLS = 128,
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiIfaceMode val) {
  switch(val) {
  case WifiIfaceMode::IFACE_MODE_STA:
    return "IFACE_MODE_STA";
  case WifiIfaceMode::IFACE_MODE_SOFTAP:
    return "IFACE_MODE_SOFTAP";
  case WifiIfaceMode::IFACE_MODE_IBSS:
    return "IFACE_MODE_IBSS";
  case WifiIfaceMode::IFACE_MODE_P2P_CLIENT:
    return "IFACE_MODE_P2P_CLIENT";
  case WifiIfaceMode::IFACE_MODE_P2P_GO:
    return "IFACE_MODE_P2P_GO";
  case WifiIfaceMode::IFACE_MODE_NAN:
    return "IFACE_MODE_NAN";
  case WifiIfaceMode::IFACE_MODE_MESH:
    return "IFACE_MODE_MESH";
  case WifiIfaceMode::IFACE_MODE_TDLS:
    return "IFACE_MODE_TDLS";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
