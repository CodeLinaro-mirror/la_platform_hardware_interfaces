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
enum class WifiStatusCode : int32_t {
  SUCCESS = 0,
  ERROR_WIFI_CHIP_INVALID = 1,
  ERROR_WIFI_IFACE_INVALID = 2,
  ERROR_WIFI_RTT_CONTROLLER_INVALID = 3,
  ERROR_NOT_SUPPORTED = 4,
  ERROR_NOT_AVAILABLE = 5,
  ERROR_NOT_STARTED = 6,
  ERROR_INVALID_ARGS = 7,
  ERROR_BUSY = 8,
  ERROR_UNKNOWN = 9,
};

class WifiStatus {
public:
    WifiStatus() :
        code(WifiStatusCode::SUCCESS), description("") {}

    WifiStatus(const WifiStatusCode &_code) :
        code(_code), description("") {}

    WifiStatus(const WifiStatusCode &_code, const std::string &_description) :
        code(_code), description(_description) {}

    inline bool operator==(const WifiStatus& other) const {
        return (code == other.code && description == other.description);
    }
    inline bool operator!=(const WifiStatus &other) const {
        return !((*this) == other);
    }

    WifiStatusCode code;
    std::string description;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
[[nodiscard]] static inline std::string toString(WifiStatusCode val) {
  switch(val) {
  case WifiStatusCode::SUCCESS:
    return "SUCCESS";
  case WifiStatusCode::ERROR_WIFI_CHIP_INVALID:
    return "ERROR_WIFI_CHIP_INVALID";
  case WifiStatusCode::ERROR_WIFI_IFACE_INVALID:
    return "ERROR_WIFI_IFACE_INVALID";
  case WifiStatusCode::ERROR_WIFI_RTT_CONTROLLER_INVALID:
    return "ERROR_WIFI_RTT_CONTROLLER_INVALID";
  case WifiStatusCode::ERROR_NOT_SUPPORTED:
    return "ERROR_NOT_SUPPORTED";
  case WifiStatusCode::ERROR_NOT_AVAILABLE:
    return "ERROR_NOT_AVAILABLE";
  case WifiStatusCode::ERROR_NOT_STARTED:
    return "ERROR_NOT_STARTED";
  case WifiStatusCode::ERROR_INVALID_ARGS:
    return "ERROR_INVALID_ARGS";
  case WifiStatusCode::ERROR_BUSY:
    return "ERROR_BUSY";
  case WifiStatusCode::ERROR_UNKNOWN:
    return "ERROR_UNKNOWN";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl

