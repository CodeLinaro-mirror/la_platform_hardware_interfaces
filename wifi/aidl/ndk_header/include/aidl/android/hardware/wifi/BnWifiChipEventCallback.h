/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifiChipEventCallback.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifiChipEventCallback : public IWifiChipEventCallback {
public:
  BnWifiChipEventCallback() {}
  virtual ~BnWifiChipEventCallback() {}
};

class IWifiChipEventCallbackDelegator : public BnWifiChipEventCallback {
public:
  explicit IWifiChipEventCallbackDelegator(const std::shared_ptr<IWifiChipEventCallback> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus onChipReconfigureFailure(::aidl::android::hardware::wifi::WifiStatusCode in_status) override {
    return _impl->onChipReconfigureFailure(in_status);
  }
  ::ndk::ScopedAStatus onChipReconfigured(int32_t in_modeId) override {
    return _impl->onChipReconfigured(in_modeId);
  }
  ::ndk::ScopedAStatus onDebugErrorAlert(int32_t in_errorCode, const std::vector<uint8_t>& in_debugData) override {
    return _impl->onDebugErrorAlert(in_errorCode, in_debugData);
  }
  ::ndk::ScopedAStatus onDebugRingBufferDataAvailable(const ::aidl::android::hardware::wifi::WifiDebugRingBufferStatus& in_status, const std::vector<uint8_t>& in_data) override {
    return _impl->onDebugRingBufferDataAvailable(in_status, in_data);
  }
  ::ndk::ScopedAStatus onIfaceAdded(::aidl::android::hardware::wifi::IfaceType in_type, const std::string& in_name) override {
    return _impl->onIfaceAdded(in_type, in_name);
  }
  ::ndk::ScopedAStatus onIfaceRemoved(::aidl::android::hardware::wifi::IfaceType in_type, const std::string& in_name) override {
    return _impl->onIfaceRemoved(in_type, in_name);
  }
  ::ndk::ScopedAStatus onRadioModeChange(const std::vector<::aidl::android::hardware::wifi::IWifiChipEventCallback::RadioModeInfo>& in_radioModeInfos) override {
    return _impl->onRadioModeChange(in_radioModeInfos);
  }
private:
  std::shared_ptr<IWifiChipEventCallback> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
