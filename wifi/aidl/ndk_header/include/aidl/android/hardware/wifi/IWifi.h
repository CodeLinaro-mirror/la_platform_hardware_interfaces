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

namespace aidl::android::hardware::wifi {
class IWifiChip;
class IWifiEventCallback;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class IWifi : public ::ndk::ICInterface {
public:
  virtual ::ndk::ScopedAStatus getChip(int32_t in_chipId, std::shared_ptr<::aidl::android::hardware::wifi::IWifiChip>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus getChipIds(std::vector<int32_t>* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus isStarted(bool* _aidl_return) = 0;
  virtual ::ndk::ScopedAStatus registerEventCallback(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiEventCallback>& in_callback) = 0;
  virtual ::ndk::ScopedAStatus start() = 0;
  virtual ::ndk::ScopedAStatus stop() = 0;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
