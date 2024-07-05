/*
* Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
* Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
* SPDX-License-Identifier: BSD-3-Clause-Clear
*/

#pragma once

#include "aidl/android/hardware/bluetooth/IBluetoothHci.h"

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
class BnBluetoothHci : public IBluetoothHci {
public:
  BnBluetoothHci();
  virtual ~BnBluetoothHci();
};
class IBluetoothHciDelegator : public BnBluetoothHci {
public:
  explicit IBluetoothHciDelegator(const std::shared_ptr<IBluetoothHci> &impl) : _impl(impl)

protected:
private:
  std::shared_ptr<IBluetoothHci> _impl;
};

}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
