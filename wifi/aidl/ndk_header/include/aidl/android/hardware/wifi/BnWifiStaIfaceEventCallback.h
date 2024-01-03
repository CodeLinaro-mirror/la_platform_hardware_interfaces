/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include "aidl/android/hardware/wifi/IWifiStaIfaceEventCallback.h"

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class BnWifiStaIfaceEventCallback : public IWifiStaIfaceEventCallback {
public:
  BnWifiStaIfaceEventCallback() {}
  virtual ~BnWifiStaIfaceEventCallback() {}
};

class IWifiStaIfaceEventCallbackDelegator : public BnWifiStaIfaceEventCallback {
public:
  explicit IWifiStaIfaceEventCallbackDelegator(const std::shared_ptr<IWifiStaIfaceEventCallback> &impl) : _impl(impl) {}

  ::ndk::ScopedAStatus onBackgroundFullScanResult(int32_t in_cmdId, int32_t in_bucketsScanned, const ::aidl::android::hardware::wifi::StaScanResult& in_result) override {
    return _impl->onBackgroundFullScanResult(in_cmdId, in_bucketsScanned, in_result);
  }
  ::ndk::ScopedAStatus onBackgroundScanFailure(int32_t in_cmdId) override {
    return _impl->onBackgroundScanFailure(in_cmdId);
  }
  ::ndk::ScopedAStatus onBackgroundScanResults(int32_t in_cmdId, const std::vector<::aidl::android::hardware::wifi::StaScanData>& in_scanDatas) override {
    return _impl->onBackgroundScanResults(in_cmdId, in_scanDatas);
  }
  ::ndk::ScopedAStatus onRssiThresholdBreached(int32_t in_cmdId, const std::array<uint8_t, 6>& in_currBssid, int32_t in_currRssi) override {
    return _impl->onRssiThresholdBreached(in_cmdId, in_currBssid, in_currRssi);
  }
private:
  std::shared_ptr<IWifiStaIfaceEventCallback> _impl;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
