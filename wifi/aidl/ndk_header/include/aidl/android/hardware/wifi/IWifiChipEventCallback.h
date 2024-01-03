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
#include <aidl/android/hardware/wifi/IfaceType.h>
#include <aidl/android/hardware/wifi/WifiBand.h>
#include <aidl/android/hardware/wifi/WifiDebugRingBufferStatus.h>
#include <aidl/android/hardware/wifi/WifiStatusCode.h>
#include <aidl/android/hardware/wifi/ICInterface.h>
#include <aidl/android/hardware/wifi/ScopedAStatus.h>

namespace aidl::android::hardware::wifi {
class WifiDebugRingBufferStatus;
}  // namespace aidl::android::hardware::wifi
namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class IWifiChipEventCallback : public ::ndk::ICInterface {
public:

  class IfaceInfo {
  public:
    std::string name;
    int32_t channel = 0;

    inline bool operator!=(const IfaceInfo& rhs) const {
      return std::tie(name, channel) != std::tie(rhs.name, rhs.channel);
    }
    inline bool operator<(const IfaceInfo& rhs) const {
      return std::tie(name, channel) < std::tie(rhs.name, rhs.channel);
    }
    inline bool operator<=(const IfaceInfo& rhs) const {
      return std::tie(name, channel) <= std::tie(rhs.name, rhs.channel);
    }
    inline bool operator==(const IfaceInfo& rhs) const {
      return std::tie(name, channel) == std::tie(rhs.name, rhs.channel);
    }
    inline bool operator>(const IfaceInfo& rhs) const {
      return std::tie(name, channel) > std::tie(rhs.name, rhs.channel);
    }
    inline bool operator>=(const IfaceInfo& rhs) const {
      return std::tie(name, channel) >= std::tie(rhs.name, rhs.channel);
    }
  };

  class RadioModeInfo {
  public:
    int32_t radioId = 0;
    ::aidl::android::hardware::wifi::WifiBand bandInfo = ::aidl::android::hardware::wifi::WifiBand(0);
    std::vector<::aidl::android::hardware::wifi::IWifiChipEventCallback::IfaceInfo> ifaceInfos;

    inline bool operator!=(const RadioModeInfo& rhs) const {
      return std::tie(radioId, bandInfo, ifaceInfos) != std::tie(rhs.radioId, rhs.bandInfo, rhs.ifaceInfos);
    }
    inline bool operator<(const RadioModeInfo& rhs) const {
      return std::tie(radioId, bandInfo, ifaceInfos) < std::tie(rhs.radioId, rhs.bandInfo, rhs.ifaceInfos);
    }
    inline bool operator<=(const RadioModeInfo& rhs) const {
      return std::tie(radioId, bandInfo, ifaceInfos) <= std::tie(rhs.radioId, rhs.bandInfo, rhs.ifaceInfos);
    }
    inline bool operator==(const RadioModeInfo& rhs) const {
      return std::tie(radioId, bandInfo, ifaceInfos) == std::tie(rhs.radioId, rhs.bandInfo, rhs.ifaceInfos);
    }
    inline bool operator>(const RadioModeInfo& rhs) const {
      return std::tie(radioId, bandInfo, ifaceInfos) > std::tie(rhs.radioId, rhs.bandInfo, rhs.ifaceInfos);
    }
    inline bool operator>=(const RadioModeInfo& rhs) const {
      return std::tie(radioId, bandInfo, ifaceInfos) >= std::tie(rhs.radioId, rhs.bandInfo, rhs.ifaceInfos);
    }
  };

  virtual ::ndk::ScopedAStatus onChipReconfigureFailure(::aidl::android::hardware::wifi::WifiStatusCode in_status) = 0;
  virtual ::ndk::ScopedAStatus onChipReconfigured(int32_t in_modeId) = 0;
  virtual ::ndk::ScopedAStatus onDebugErrorAlert(int32_t in_errorCode, const std::vector<uint8_t>& in_debugData) = 0;
  virtual ::ndk::ScopedAStatus onDebugRingBufferDataAvailable(const ::aidl::android::hardware::wifi::WifiDebugRingBufferStatus& in_status, const std::vector<uint8_t>& in_data) = 0;
  virtual ::ndk::ScopedAStatus onIfaceAdded(::aidl::android::hardware::wifi::IfaceType in_type, const std::string& in_name) = 0;
  virtual ::ndk::ScopedAStatus onIfaceRemoved(::aidl::android::hardware::wifi::IfaceType in_type, const std::string& in_name) = 0;
  virtual ::ndk::ScopedAStatus onRadioModeChange(const std::vector<::aidl::android::hardware::wifi::IWifiChipEventCallback::RadioModeInfo>& in_radioModeInfos) = 0;
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
