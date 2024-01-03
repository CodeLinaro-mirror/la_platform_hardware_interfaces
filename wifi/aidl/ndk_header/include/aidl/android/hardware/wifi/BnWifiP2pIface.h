/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifiP2pIface.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifiP2pIface : public IWifiP2pIface {
public:
  BnWifiP2pIface() {}
  virtual ~BnWifiP2pIface() {}
};

class IWifiP2pIfaceDelegator : public BnWifiP2pIface {
public:
  explicit IWifiP2pIfaceDelegator(const std::shared_ptr<IWifiP2pIface> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus getName(std::string* _aidl_return) override {
    return _impl->getName(_aidl_return);
  }
protected:
private:
  std::shared_ptr<IWifiP2pIface> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
