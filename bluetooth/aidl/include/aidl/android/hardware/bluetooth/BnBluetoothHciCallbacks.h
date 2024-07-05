/*
* Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
* Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
* SPDX-License-Identifier: BSD-3-Clause-Clear
*/

#pragma once

#include "aidl/android/hardware/bluetooth/IBluetoothHciCallbacks.h"


namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
class BnBluetoothHciCallbacks : IBluetoothHciCallbacks {
public:
  BnBluetoothHciCallbacks();
  virtual ~BnBluetoothHciCallbacks();
};
class IBluetoothHciCallbacksDelegator : public BnBluetoothHciCallbacks {
public:
protected:
private:
  std::shared_ptr<IBluetoothHciCallbacks> _impl;
};

}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
