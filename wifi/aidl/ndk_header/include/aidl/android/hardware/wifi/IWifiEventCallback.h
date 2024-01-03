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

class IWifiEventCallback : public ::ndk::ICInterface {
public:
  virtual ::ndk::ScopedAStatus onFailure(::aidl::android::hardware::wifi::WifiStatusCode in_status) = 0;
  virtual ::ndk::ScopedAStatus onStart() = 0;
  virtual ::ndk::ScopedAStatus onStop() = 0;
  virtual ::ndk::ScopedAStatus onSubsystemRestart(::aidl::android::hardware::wifi::WifiStatusCode in_status) = 0;
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
