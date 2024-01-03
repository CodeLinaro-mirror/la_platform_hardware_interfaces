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

#include <aidl/android/hardware/wifi/ICInterface.h>
#include <aidl/android/hardware/wifi/ScopedAStatus.h>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class IWifiApIface : public ::ndk::ICInterface {
public:
  virtual ::ndk::ScopedAStatus getName(std::string* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getBridgedInstances(std::vector<std::string>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getFactoryMacAddress(std::array<uint8_t, 6>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus setCountryCode(const std::array<uint8_t, 2>& in_code) = 0;
  virtual ::ndk::ScopedAStatus resetToFactoryMacAddress() = 0;
  virtual ::ndk::ScopedAStatus setMacAddress(const std::array<uint8_t, 6>& in_mac) = 0;
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
