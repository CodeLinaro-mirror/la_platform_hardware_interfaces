/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <common_util.h>
#include <someip_api.h>
#include <utils/Log.h>
#include <wifi_chip_msg.h>
#include <wifi_msg.h>
#include <wifi_someip_def.h>
#include <wifi_sta_iface_msg.h>

#include "wifi_rpc_event.h"

uint16_t wifiRpcEventArray[WIFI_HAL_SUPPORTED_EVENT_COUNT] = {
    /* WIFI_ON_FAILURE_IND, */
    /* WIFI_ON_START_IND, */
    /* WIFI_ON_STOP_IND, */
    WIFI_ON_SUBSYSTEM_RESTART_IND,

    /* WIFI_CHIP_ON_CHIP_RECONFIGURE_FAILURE_IND, */
    /* WIFI_CHIP_ON_CHIP_RECONFIGURED_IND, */
    /* WIFI_CHIP_ON_DEBUG_ERROR_ALERT_IND, */
    /* WIFI_CHIP_ON_DEBUG_RING_BUFFER_DATA_AVAILABLE_IND, */
    /* WIFI_CHIP_ON_IFACE_ADDED_IND, */
    /* WIFI_CHIP_ON_IFACE_REMOVED_IND, */
    WIFI_CHIP_ON_RADIO_MODE_CHANGE_IND,

    WIFI_STA_IFACE_ON_BACKGROUND_FULL_SCAN_RESULT_IND,
    WIFI_STA_IFACE_ON_BACKGROUND_SCAN_FAILURE_IND,
    WIFI_STA_IFACE_ON_BACKGROUND_SCAN_RESULTS_IND,
    WIFI_STA_IFACE_ON_RSSI_THRESHOLD_BREACHED_IND
};

static ndk::ScopedAStatus WifiRpcSendEvent(uint16_t eventId,
    std::vector<uint8_t>& data)
{
    if (!someip_send_event(eventId, data.data(), data.size())) {
        ALOGE("Failed to send event with ID 0x%x", eventId);
	return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_BUSY);
    }

    return ndk::ScopedAStatus::ok();
}

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

/* WifiChipEventCallback methods implement */
ndk::ScopedAStatus WifiRpcEvent::onFailure(WifiStatusCode statusCode)
{
    ALOGD("Wifi Event onFailure status %s.", toString(statusCode).c_str());

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiRpcEvent::onStart()
{
    ALOGD("Wifi Event onStart");

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiRpcEvent::onStop()
{
    ALOGD("Wifi Event onStop");

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiRpcEvent::onSubsystemRestart(
    WifiStatusCode statusCode)
{
    ALOGD("Wifi Event onSubsystemRestart status %s",
        toString(statusCode).c_str());

    std::vector<uint8_t> data;
    if (!WifiSerializeOnSubsystemRestartInd(statusCode, data)) {
        ALOGE("Serialize Wifi event on subsystem restart fail.");
        return ndk::ScopedAStatus::fail(
            WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiRpcSendEvent(WIFI_ON_SUBSYSTEM_RESTART_IND, data);
}

/* WifiChipEventCallback methods implement */
ndk::ScopedAStatus WifiChipRpcEvent::onChipReconfigureFailure(
    WifiStatusCode statusCode)
{
    ALOGD("Wifi Chip Event onChipReconfigured status %s.",
        toString(statusCode).c_str());

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiChipRpcEvent::onChipReconfigured(int32_t modeId)
{
    ALOGD("Wifi Chip Event onChipReconfigured modeId %d", modeId);

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiChipRpcEvent::onDebugErrorAlert(int32_t errorCode,
    const std::vector<uint8_t>& debugData)
{
    ALOGD("Wifi Chip Event onDebugErrorAlert error %d.", errorCode);

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiChipRpcEvent::onDebugRingBufferDataAvailable(
    const WifiDebugRingBufferStatus& status, const std::vector<uint8_t>& data)
{
    ALOGD("Wifi Chip Event onDebugRingBufferDataAvailable.");

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiChipRpcEvent::onIfaceAdded(IfaceType type,
    const std::string& name)
{
    ALOGD("Wifi Chip Event onIfaceAdded: type %s name %s.",
        toString(type).c_str(), name.c_str());

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiChipRpcEvent::onIfaceRemoved(IfaceType type,
    const std::string& name)
{
    ALOGD("Wifi Chip Event onIfaceRemoved: type %s name %s.",
        toString(type).c_str(), name.c_str());

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus WifiChipRpcEvent::onRadioModeChange(
    const std::vector<IWifiChipEventCallback::RadioModeInfo>& radioModeInfos)
{
    ALOGD("Invoke Wifi Chip Event onRadioModeChange.");

    std::vector<uint8_t> data;
    if (!WifiChipSerializeOnRadioModeChangeInd(radioModeInfos, data)) {
        ALOGE("Serialize Wifi Chip event on radio mode change fail.");
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiRpcSendEvent(WIFI_CHIP_ON_RADIO_MODE_CHANGE_IND, data);
}

/* IWifiStaIfaceRpcEvent method */
ndk::ScopedAStatus WifiStaIfaceRpcEvent::onBackgroundFullScanResult(
    int32_t cmdId, int32_t bucketsScanned, const StaScanResult& result)
{
    ALOGD("Invoke Wifi STA Event onBackgroundFullScanResult: "
        "cmd ID %d buckets scanned %d.", cmdId, bucketsScanned);

    std::vector<uint8_t> data;
    if (!WifiStaIfaceSerializeOnBackgroundFullScanResultInd(cmdId,
        bucketsScanned, result, data)) {
        ALOGE("Serialize Wifi Sta event on BG full scan result fail.");
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    ADD_INT32_TO_VECTOR(instanceId_, data);
    return WifiRpcSendEvent(
        WIFI_STA_IFACE_ON_BACKGROUND_FULL_SCAN_RESULT_IND, data);
}

ndk::ScopedAStatus WifiStaIfaceRpcEvent::onBackgroundScanFailure(
    int32_t cmdId)
{
    ALOGD("Invoke Wifi STA Event onBackgroundScanFailure cmd ID %d", cmdId);

    std::vector<uint8_t> data;
    if (!WifiStaIfaceSerializeOnBackgroundScanFailureInd(cmdId, data)) {
        ALOGE("Fail to serialize Wifi Sta event on BG scan failure.");
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    ADD_INT32_TO_VECTOR(instanceId_, data);
    return WifiRpcSendEvent(
        WIFI_STA_IFACE_ON_BACKGROUND_SCAN_FAILURE_IND, data);
}

ndk::ScopedAStatus WifiStaIfaceRpcEvent::onBackgroundScanResults(
    int32_t cmdId, const std::vector<StaScanData>& scanDatas)
{
    ALOGD("Invoke Wifi STA Event onBackgroundScanResults.");

    std::vector<uint8_t> data;
    if (!WifiStaIfaceSerializeOnBackgroundScanResultsInd(cmdId,
        scanDatas, data)) {
        ALOGE("Serialize Wifi Sta event on BG scan results fail.");
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    ADD_INT32_TO_VECTOR(instanceId_, data);
    return WifiRpcSendEvent(
        WIFI_STA_IFACE_ON_BACKGROUND_SCAN_RESULTS_IND, data);
}

ndk::ScopedAStatus WifiStaIfaceRpcEvent::onRssiThresholdBreached(
    int32_t cmdId, const std::array<uint8_t, 6>& currBssid, int32_t currRssi)
{
    ALOGD("Invoke Wifi STA Event onRssiThresholdBreached");

    std::vector<uint8_t> data;
    if (!WifiStaIfaceSerializeOnRssiThresholdBreachedInd(cmdId,
        currBssid, currRssi, data)) {
        ALOGE("Serialize Wifi Sta event onrssi threshold breached fail.");
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    ADD_INT32_TO_VECTOR(instanceId_, data);
    return WifiRpcSendEvent(
        WIFI_STA_IFACE_ON_RSSI_THRESHOLD_BREACHED_IND, data);
}

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
