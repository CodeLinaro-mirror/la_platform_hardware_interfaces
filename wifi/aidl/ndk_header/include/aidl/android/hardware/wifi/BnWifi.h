/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifi.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifi : public IWifi {
public:
  BnWifi() {}
  virtual ~BnWifi() {}
};

class IWifiDelegator : public BnWifi {
public:
  explicit IWifiDelegator(const std::shared_ptr<IWifi> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus getChip(int32_t in_chipId, std::shared_ptr<::aidl::android::hardware::wifi::IWifiChip>* _aidl_return) override {
    return _impl->getChip(in_chipId, _aidl_return);
  }
  ::ndk::ScopedAStatus getChipIds(std::vector<int32_t>* _aidl_return) override {
    return _impl->getChipIds(_aidl_return);
  }
  ::ndk::ScopedAStatus isStarted(bool* _aidl_return) override {
    return _impl->isStarted(_aidl_return);
  }
  ::ndk::ScopedAStatus registerEventCallback(const std::shared_ptr<::aidl::android::hardware::wifi::IWifiEventCallback>& in_callback) override {
    return _impl->registerEventCallback(in_callback);
  }
  ::ndk::ScopedAStatus start() override {
    return _impl->start();
  }
  ::ndk::ScopedAStatus stop() override {
    return _impl->stop();
  }
private:
  std::shared_ptr<IWifi> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
