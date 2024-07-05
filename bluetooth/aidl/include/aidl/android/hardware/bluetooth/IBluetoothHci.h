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
#include <aidl/android/hardware/bluetooth/IBluetoothHciCallbacks.h>

namespace aidl::android::hardware::bluetooth {
class IBluetoothHciCallbacks;
}  // namespace aidl::android::hardware::bluetooth
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {

class IBluetoothHci : public ::ndk::ICInterface {
public:
  IBluetoothHci();
  virtual ~IBluetoothHci();

  static const int32_t version = 1;

};
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
