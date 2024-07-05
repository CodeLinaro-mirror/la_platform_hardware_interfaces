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
namespace bluetooth {
enum class Status : int32_t {
  SUCCESS = 0,
  ALREADY_INITIALIZED = 1,
  UNABLE_TO_OPEN_INTERFACE = 2,
  HARDWARE_INITIALIZATION_ERROR = 3,
  UNKNOWN = 4,
};

}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
[[nodiscard]] static inline std::string toString(Status val) {
  switch(val) {
  case Status::SUCCESS:
    return "SUCCESS";
  case Status::ALREADY_INITIALIZED:
    return "ALREADY_INITIALIZED";
  case Status::UNABLE_TO_OPEN_INTERFACE:
    return "UNABLE_TO_OPEN_INTERFACE";
  case Status::HARDWARE_INITIALIZATION_ERROR:
    return "HARDWARE_INITIALIZATION_ERROR";
  case Status::UNKNOWN:
    return "UNKNOWN";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl

