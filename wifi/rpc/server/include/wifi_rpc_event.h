/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef WIFI_RPC_EVENT_H
#define WIFI_RPC_EVENT_H

#include <aidl/android/hardware/wifi/IfaceType.h>
#include <aidl/android/hardware/wifi/IWifi.h>
#include <aidl/android/hardware/wifi/IWifiChip.h>
#include <aidl/android/hardware/wifi/IWifiEventCallback.h>
#include <aidl/android/hardware/wifi/IWifiChipEventCallback.h>
#include <aidl/android/hardware/wifi/IWifiStaIface.h>
#include <aidl/android/hardware/wifi/IWifiStaIfaceEventCallback.h>
#include <aidl/android/hardware/wifi/WifiStatusCode.h>
#include <aidl/android/hardware/wifi/WifiDebugRingBufferStatus.h>
#include <aidl/android/hardware/wifi/StaScanResult.h>
#include <aidl/android/hardware/wifi/StaScanData.h>
#include <aidl/android/hardware/wifi/ScopedAStatus.h>

#define WIFI_HAL_SUPPORTED_EVENT_COUNT    6
extern uint16_t wifiRpcEventArray[WIFI_HAL_SUPPORTED_EVENT_COUNT];

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class WifiRpcEvent : public IWifiEventCallback {
public:
    WifiRpcEvent() {}
    virtual ~WifiRpcEvent() = default;

    ndk::ScopedAStatus onFailure(WifiStatusCode in_status) override;
    ndk::ScopedAStatus onStart() override;
    ndk::ScopedAStatus onStop() override;
    ndk::ScopedAStatus onSubsystemRestart(WifiStatusCode in_status) override;
};

class WifiChipRpcEvent : public IWifiChipEventCallback {
public:
    WifiChipRpcEvent(int32_t chipId) :  chipId_(chipId) {}
    virtual ~WifiChipRpcEvent() = default;

    ndk::ScopedAStatus onChipReconfigureFailure(
        WifiStatusCode in_status) override;
    ndk::ScopedAStatus onChipReconfigured(int32_t in_modeId) override;
    ndk::ScopedAStatus onDebugErrorAlert(int32_t in_errorCode,
        const std::vector<uint8_t>& in_debugData) override;
    ndk::ScopedAStatus onDebugRingBufferDataAvailable(
        const WifiDebugRingBufferStatus& in_status,
        const std::vector<uint8_t>& in_data) override;
    ndk::ScopedAStatus onIfaceAdded(IfaceType in_type,
        const std::string& in_name) override;
    ndk::ScopedAStatus onIfaceRemoved(IfaceType in_type,
        const std::string& in_name) override;
    ndk::ScopedAStatus onRadioModeChange(
        const std::vector<IWifiChipEventCallback::RadioModeInfo>&
            in_radioModeInfos) override;

private:
    [[maybe_unused]] int32_t chipId_;
};

class WifiStaIfaceRpcEvent : public IWifiStaIfaceEventCallback {
public:
    WifiStaIfaceRpcEvent(int32_t instanceId) : instanceId_(instanceId){}
    virtual ~WifiStaIfaceRpcEvent() = default;

    ndk::ScopedAStatus onBackgroundFullScanResult(int32_t in_cmdId,
        int32_t in_bucketsScanned, const StaScanResult& in_result) override;
    ndk::ScopedAStatus onBackgroundScanFailure(int32_t in_cmdId) override;
    ndk::ScopedAStatus onBackgroundScanResults(int32_t in_cmdId,
        const std::vector<StaScanData>& in_scanDatas) override;
    ndk::ScopedAStatus onRssiThresholdBreached(int32_t in_cmdId,
        const std::array<uint8_t, 6>& in_currBssid,
        int32_t in_currRssi) override;

private:
    int32_t instanceId_;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl

#endif /* WIFI_RPC_EVENT_H */
