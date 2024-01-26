/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <android-base/logging.h>

#include <util/common_util.h>
#include <util/someip_api.h>

#include <wifi_ind.h>
#include <wifi_chip_ind.h>
#include <wifi_sta_iface_ind.h>

#include "wifi_hal_event_callback.h"
#include "wifi_someip_def.h"

uint16_t wifiHalEventArray[WIFI_HAL_SUPPORTED_EVENT_COUNT] = {
    /* IWIFI_ON_FAILURE_IND, */
    /* IWIFI_ON_START_IND, */
    /* IWIFI_ON_STOP_IND, */
    IWIFI_ON_SUBSYSTEM_RESTART_IND,

    /* IWIFICHIP_ON_CHIP_RECONFIGURE_FAILURE_IND, */
    /* IWIFICHIP_ON_CHIP_RECONFIGURED_IND, */
    /* IWIFICHIP_ON_DEBUG_ERROR_ALERT_IND, */
    /* IWIFICHIP_ON_DEBUG_RING_BUFFER_DATA_AVAILABLE_IND, */
    /* IWIFICHIP_ON_IFACE_ADDED_IND, */
    /* IWIFICHIP_ON_IFACE_REMOVED_IND, */
    IWIFICHIP_ON_RADIO_MODE_CHANGE_IND,

    IWIFISTAIFACE_ON_BACKGROUND_FULL_SCAN_RESULT_IND,
    IWIFISTAIFACE_ON_BACKGROUND_SCAN_FAILURE_IND,
    IWIFISTAIFACE_ON_BACKGROUND_SCAN_RESULTS_IND,
    IWIFISTAIFACE_ON_RSSI_THRESHOLD_BREACHED_IND
};

static ndk::ScopedAStatus WifiHalSendEvent(uint16_t eventId, std::vector<uint8_t>& data)
{
    if (!someip_send_event(eventId, data.data(), data.size())) {
        LOG(ERROR) << "Failed to send event ID: " << eventId;
	return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_BUSY);
    }

    return ndk::ScopedAStatus::ok();
}

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

/* WifiChipEventCallback methods implement */
ndk::ScopedAStatus WifiEventCallback::onFailure(WifiStatusCode statusCode)
{
    LOG(DEBUG) << "Wifi Event onFailure status " << toString(statusCode);

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;
    if (!WifiSerializeOnFailureInd(statusCode, data)) {
        LOG(ERROR) << "Serialize Wifi event on failure fail.";
	return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFI_ON_FAILURE_IND, data);
}

ndk::ScopedAStatus WifiEventCallback::onStart()
{
    LOG(DEBUG) << "Wifi Event onStart";

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;

    return WifiHalSendEvent(IWIFI_ON_START_IND, data);
}

ndk::ScopedAStatus WifiEventCallback::onStop()
{
    LOG(DEBUG) << "Wifi Event onStop";

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;

    return WifiHalSendEvent(IWIFI_ON_STOP_IND, data);
}

ndk::ScopedAStatus WifiEventCallback::onSubsystemRestart(WifiStatusCode statusCode)
{
    LOG(DEBUG) << "Wifi Event onSubsystemRestart status " << toString(statusCode);

    std::vector<uint8_t> data;
    if (!WifiSerializeOnSubsystemRestartInd(statusCode, data)) {
        LOG(ERROR) << "Serialize Wifi event on subsystem restart fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFI_ON_SUBSYSTEM_RESTART_IND, data);
}

/* WifiChipEventCallback methods implement */

int32_t WifiChipEventCallback::getChipId()
{
    return chipId;
}

ndk::ScopedAStatus WifiChipEventCallback::onChipReconfigureFailure(WifiStatusCode statusCode)
{
    LOG(DEBUG) << "Wifi Chip Event onChipReconfigured status " << toString(statusCode);

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;
    if (!WifiChipSerializeOnChipReconfigureFailureInd(statusCode, data)) {
        LOG(ERROR) << "Serialize Wifi Chip event on reconfig fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFICHIP_ON_CHIP_RECONFIGURE_FAILURE_IND, data);
}

ndk::ScopedAStatus WifiChipEventCallback::onChipReconfigured(int32_t modeId)
{
    LOG(DEBUG) << "Wifi Chip Event onChipReconfigured modeId " << modeId;

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;
    if (!WifiChipSerializeOnChipReconfiguredInd(modeId, data)) {
        LOG(ERROR) << "Serialize Wifi Chip event on reconfiged fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFICHIP_ON_CHIP_RECONFIGURED_IND, data);
}

ndk::ScopedAStatus WifiChipEventCallback::onDebugErrorAlert(int32_t errorCode, const std::vector<uint8_t>& debugData)
{
    LOG(DEBUG) << "Wifi Chip Event onDebugErrorAlert error " << errorCode;

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;
    if (!WifiChipSerializeOnDebugErrorAlertInd(errorCode, debugData, data)) {
        LOG(ERROR) << "Serialize Wifi Chip event on debug error alert fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFICHIP_ON_DEBUG_ERROR_ALERT_IND, data);
}

ndk::ScopedAStatus WifiChipEventCallback::onDebugRingBufferDataAvailable(const WifiDebugRingBufferStatus& status, const std::vector<uint8_t>& data)
{
    LOG(DEBUG) << "Wifi Chip Event onDebugRingBufferDataAvailable";

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> outData;
    if (!WifiChipSerializeOnDebugRingBufferDataAvailableInd(status, data, outData)) {
        LOG(ERROR) << "Serialize Wifi Chip event on debug ring buf available fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFICHIP_ON_DEBUG_RING_BUFFER_DATA_AVAILABLE_IND, outData);
}

ndk::ScopedAStatus WifiChipEventCallback::onIfaceAdded(IfaceType type, const std::string& name)
{
    LOG(DEBUG) << "Wifi Chip Event onIfaceAdded: "
               << "iface type: " << toString(type)
               << "iface name: " << name;

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;
    if (!WifiChipSerializeOnIfaceAddedInd(type, name, data)) {
        LOG(ERROR) << "Serialize Wifi Chip event on iface added fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFICHIP_ON_IFACE_ADDED_IND, data);
}

ndk::ScopedAStatus WifiChipEventCallback::onIfaceRemoved(IfaceType type, const std::string& name)
{
    LOG(DEBUG) << "Wifi Chip Event onIfaceRemoved: "
               << "iface type: " << toString(type)
               << "iface name: " << name;

    /* Return okay as no need to send SomeIP event */
    return ndk::ScopedAStatus::ok();

    std::vector<uint8_t> data;
    if (!WifiChipSerializeOnIfaceRemovedInd(type, name, data)) {
        LOG(ERROR) << "Serialize Wifi Chip event on iface removed fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFICHIP_ON_IFACE_REMOVED_IND, data);
}

ndk::ScopedAStatus WifiChipEventCallback::onRadioModeChange(const std::vector<IWifiChipEventCallback::RadioModeInfo>& radioModeInfos)
{
    LOG(DEBUG) << "Invoke Wifi Chip Event onRadioModeChange";

    std::vector<uint8_t> data;
    if (!WifiChipSerializeOnRadioModeChangeInd(radioModeInfos, data)) {
        LOG(ERROR) << "Serialize Wifi Chip event on radio mode change fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    return WifiHalSendEvent(IWIFICHIP_ON_RADIO_MODE_CHANGE_IND, data);
}

/* IWifiStaIfaceEventCallback method */
int32_t WifiStaIfaceEventCallback::getStaIfaceId()
{
    return staIfaceId;
}

std::string WifiStaIfaceEventCallback::getIfaceName()
{
    return ifaceName;
}

static void WifiStaIfaceEventPushInstanceId(std::vector<uint8_t>& data, int32_t instanceId)
{
    for (int i = 0; i < 4; i++)
        data.push_back((uint8_t)((instanceId >> (i * 8)) & 0xff));
}

ndk::ScopedAStatus WifiStaIfaceEventCallback::onBackgroundFullScanResult(int32_t cmdId, int32_t bucketsScanned, const StaScanResult& result)
{
    LOG(DEBUG) << "Invoke Wifi STA Event onBackgroundFullScanResult "
               << "cmd ID: " << std::to_string(cmdId)
               << "buckets scanned: " << std::to_string(bucketsScanned);

    std::vector<uint8_t> data;
    if (!WifiStaIfaceSerializeOnBackgroundFullScanResultInd(cmdId, bucketsScanned, result, data)) {
        LOG(ERROR) << "Serialize Wifi Sta event on BG full scan result fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    int32_t instanceId = this->getStaIfaceId();
    WifiStaIfaceEventPushInstanceId(data, instanceId);

    return WifiHalSendEvent(IWIFISTAIFACE_ON_BACKGROUND_FULL_SCAN_RESULT_IND, data);
}

ndk::ScopedAStatus WifiStaIfaceEventCallback::onBackgroundScanFailure(int32_t cmdId)
{
    LOG(DEBUG) << "Invoke Wifi STA Event onBackgroundScanFailure "
               << "cmd ID: " << std::to_string(cmdId);

    std::vector<uint8_t> data;
    if (!WifiStaIfaceSerializeOnBackgroundScanFailureInd(cmdId, data)) {
        LOG(ERROR) << "Fail to serialize Wifi Sta event on BG scan failure.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    int32_t instanceId = this->getStaIfaceId();
    WifiStaIfaceEventPushInstanceId(data, instanceId);

    return WifiHalSendEvent(IWIFISTAIFACE_ON_BACKGROUND_SCAN_FAILURE_IND, data);
}

ndk::ScopedAStatus WifiStaIfaceEventCallback::onBackgroundScanResults(int32_t cmdId, const std::vector<StaScanData>& scanDatas)
{
    LOG(DEBUG) << "Invoke Wifi STA Event onBackgroundScanResults";

    std::vector<uint8_t> data;
    if (!WifiStaIfaceSerializeOnBackgroundScanResultsInd(cmdId, scanDatas, data)) {
        LOG(ERROR) << "Serialize Wifi Sta event on BG scan results fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    int32_t instanceId = this->getStaIfaceId();
    WifiStaIfaceEventPushInstanceId(data, instanceId);

    return WifiHalSendEvent(IWIFISTAIFACE_ON_BACKGROUND_SCAN_RESULTS_IND, data);
}

ndk::ScopedAStatus WifiStaIfaceEventCallback::onRssiThresholdBreached(int32_t cmdId, const std::array<uint8_t, 6>& currBssid, int32_t currRssi)
{
    LOG(DEBUG) << "Invoke Wifi STA Event onRssiThresholdBreached";

    std::vector<uint8_t> data;
    std::vector<uint8_t> bssid;
    Array2Vector(currBssid, bssid);
    if (!WifiStaIfaceSerializeOnRssiThresholdBreachedInd(cmdId, bssid, currRssi, data)) {
        LOG(ERROR) << "Serialize Wifi Sta event onrssi threshold breached fail.";
        return ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS);
    }

    int32_t instanceId = this->getStaIfaceId();
    WifiStaIfaceEventPushInstanceId(data, instanceId);

    return WifiHalSendEvent(IWIFISTAIFACE_ON_RSSI_THRESHOLD_BREACHED_IND, data);
}

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
