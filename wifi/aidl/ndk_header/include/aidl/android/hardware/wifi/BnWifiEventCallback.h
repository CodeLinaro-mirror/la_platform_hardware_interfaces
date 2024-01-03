/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifiEventCallback.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifiEventCallback : public IWifiEventCallback {
public:
  BnWifiEventCallback() {}
  virtual ~BnWifiEventCallback() {}
};

class IWifiEventCallbackDelegator : public BnWifiEventCallback {
public:
  explicit IWifiEventCallbackDelegator(const std::shared_ptr<IWifiEventCallback> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus onFailure(::aidl::android::hardware::wifi::WifiStatusCode in_status) override {
    return _impl->onFailure(in_status);
  }
  ::ndk::ScopedAStatus onStart() override {
    return _impl->onStart();
  }
  ::ndk::ScopedAStatus onStop() override {
    return _impl->onStop();
  }
  ::ndk::ScopedAStatus onSubsystemRestart(::aidl::android::hardware::wifi::WifiStatusCode in_status) override {
    return _impl->onSubsystemRestart(in_status);
  }
private:
  std::shared_ptr<IWifiEventCallback> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
