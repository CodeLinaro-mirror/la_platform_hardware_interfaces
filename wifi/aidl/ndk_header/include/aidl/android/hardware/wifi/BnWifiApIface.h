/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifiApIface.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifiApIface : public IWifiApIface {
public:
  BnWifiApIface() {}
  virtual ~BnWifiApIface() {}
};

class IWifiApIfaceDelegator : public BnWifiApIface {
public:
  explicit IWifiApIfaceDelegator(const std::shared_ptr<IWifiApIface> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus getName(std::string* _aidl_return) override {
    return _impl->getName(_aidl_return);
  }
  ::ndk::ScopedAStatus getBridgedInstances(std::vector<std::string>* _aidl_return) override {
    return _impl->getBridgedInstances(_aidl_return);
  }
  ::ndk::ScopedAStatus getFactoryMacAddress(std::array<uint8_t, 6>* _aidl_return) override {
    return _impl->getFactoryMacAddress(_aidl_return);
  }
  ::ndk::ScopedAStatus setCountryCode(const std::array<uint8_t, 2>& in_code) override {
    return _impl->setCountryCode(in_code);
  }
  ::ndk::ScopedAStatus resetToFactoryMacAddress() override {
    return _impl->resetToFactoryMacAddress();
  }
  ::ndk::ScopedAStatus setMacAddress(const std::array<uint8_t, 6>& in_mac) override {
    return _impl->setMacAddress(in_mac);
  }
private:
  std::shared_ptr<IWifiApIface> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
