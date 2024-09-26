/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <rpc/util/someip_api.h>
#include <rpc/util/log_common.h>
#ifdef CONFIG_AP
#include <wifi_ap_iface_msg.h>
#endif
#include <wifi_chip_msg.h>
#include <wifi_instance_util.h>
#include <wifi_message_def.h>
#include <wifi_msg.h>
#include <wifi_sta_iface_msg.h>

#include "wifi_rpc_message.h"

using namespace aidl::android::hardware::wifi;
using namespace aidl::android::hardware::wifi::instance_util;

#define WIFI_RPC_PRINT_STATUS(status) \
    do { \
        ALOGI("WifiRpc Someip Service: %s: result %s.", \
            __func__, toString((status).code).c_str()); \
    } while (0)

#define INVALID_ARGS_ERROR_STATUS \
    (ndk::ScopedAStatus::fail(WifiStatusCode::ERROR_INVALID_ARGS))

#define WIFI_PAYLOAD_MIN_SIZE 4

/*
 * Deserialize request message payload funcions.
 * For specific multi interface instance,
 * instanceId is attached at the tail of payload.
 * Get instanceId firstly, then parse the specific parameter.
 */
static bool WifiRpcParseInstanceId(uint8_t* data, size_t length, uint16_t& chipId, uint16_t& ifaceId)
{
    if (!data || length < WIFI_PAYLOAD_MIN_SIZE) {
        ALOGE("Invalid payload header length %zu", length);
        return false;
    }

    chipId = (uint16_t)data[0] | (((uint16_t)data[1]) << 8);
    ifaceId = (uint16_t)data[2] | (((uint16_t)data[3]) << 8);

    return true;
}

template <typename ReqParamType, typename ParseFunc>
static bool WifiRpcParseDataPayload(uint8_t* data, size_t length,
    uint16_t& id1, uint16_t& id2, ReqParamType& param, ParseFunc&& func)
{
    if (WifiRpcParseInstanceId(data, length, id1, id2) && func)
        return (*func)(data + WIFI_PAYLOAD_MIN_SIZE, length - WIFI_PAYLOAD_MIN_SIZE, param);

    return false;
}

/*
 * Serialize response results to message payload.
 */
static bool WifiRpcSerializeStatusResponse(const ndk::ScopedAStatus& status,
    std::vector<uint8_t>& data)
{
    return WifiSerializeHalStatus((int32_t)status.code,
        status.description, data);
}

template <typename ResultType, typename SerializeFunc>
static bool WifiRpcSerializeResultResponse(const ndk::ScopedAStatus& status,
    const ResultType& result, SerializeFunc&& func, std::vector<uint8_t>& data)
{
    if (!func)
        return false;

    HalStatusParam replyStatus;
    replyStatus.status = (int32_t)status.code;
    replyStatus.info = status.description;

    return (*func)(replyStatus, result, data);
}

/**
 * Start IWifi interface request method function hanlder.
 */
static bool WifiMsgHandlerIsStarted(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    bool isStarted = false;
    auto status = WifiCallMethod(&IWifi::isStarted, &isStarted);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, isStarted,
        &WifiSerializeIsStartedCfm, outData);
}

static bool WifiMsgHandlerStart(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    auto status = WifiCallMethod(&IWifi::start);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiMsgHandlerStop(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    auto status = WifiCallMethod(&IWifi::stop);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiMsgHandlerGetChipIds(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    std::vector<int32_t> chipIds;
    auto status = WifiCallMethod(&IWifi::getChipIds, &chipIds);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, chipIds,
        &WifiSerializeGetChipIdsCfm, outData);
}

static bool WifiMsgHandlerGetChip(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    int32_t chipId;
    if (!WifiParseGetChipReq(data + WIFI_PAYLOAD_MIN_SIZE, length - WIFI_PAYLOAD_MIN_SIZE, chipId)) {
        ALOGE("Wifi Chip parse get chip request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::shared_ptr<IWifiChip> wifiChip;
    auto status = WifiCallMethod(&IWifi::getChip, chipId, &wifiChip);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, chipId,
        &WifiSerializeGetChipCfm, outData);
}

/**
 * Start IWifiChip interface request method function hanlder.
 */
static bool WifiChipMsgHandlerGetId(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    int32_t id;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getId, &id);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, id,
        &WifiChipSerializeGetIdCfm, outData);
}

static bool WifiChipMsgHandlerGetFeatureSet(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    int32_t featureSet;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getFeatureSet, &featureSet);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, featureSet,
        &WifiChipSerializeGetFeatureSetCfm, outData);
}

static bool WifiChipMsgHandlerGetAvailableModes(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<IWifiChip::ChipMode> chipModes;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getAvailableModes, &chipModes);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, chipModes,
        &WifiChipSerializeGetAvailableModesCfm, outData);
}

static bool WifiChipMsgHandlerConfigureChip(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    int32_t modeId;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, modeId,
        &WifiChipParseConfigureChipReq)) {
        ALOGE("Wifi Chip parse configure chip request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    ALOGD("Wifi config chip modeId: %d.", modeId);

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::configureChip, modeId);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerGetMode(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    int32_t mode;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getMode, &mode);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, mode,
        &WifiChipSerializeGetModeCfm, outData);
}

#ifdef CONFIG_DEBUG
static bool WifiChipMsgHandlerRequestChipDebugInfo(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    IWifiChip::ChipDebugInfo chipDebugInfo;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::requestChipDebugInfo, &chipDebugInfo);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, chipDebugInfo,
        &WifiChipSerializeRequestChipDebugInfoCfm, outData);
}

static bool WifiChipMsgHandlerRequestDriverDebugDump(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<uint8_t> dbgDump;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::requestDriverDebugDump, &dbgDump);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, dbgDump,
        &WifiChipSerializeRequestDriverDebugDumpCfm, outData);
}

static bool WifiChipMsgHandlerRequestFirmwareDebugDump(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<uint8_t> dbgDump;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::requestFirmwareDebugDump, &dbgDump);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, dbgDump,
        &WifiChipSerializeRequestFirmwareDebugDumpCfm, outData);
}
#endif

#ifdef CONFIG_AP
static bool WifiChipMsgHandlerCreateApIface(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::shared_ptr<IWifiApIface> wifiApIface;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::createApIface, &wifiApIface);

    WIFI_RPC_PRINT_STATUS(status);

    uint16_t instanceId = WifiGetApIfaceInstanceId(wifiApIface);
    ALOGI("Wifi Chip create ap iface instance Id %d.", instanceId);

    return WifiRpcSerializeResultResponse(status, instanceId,
         &WifiChipSerializeCreateApIfaceCfm, outData);
}

static bool WifiChipMsgHandlercreateBridgedApIface(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::shared_ptr<IWifiApIface> wifiApIface;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::createBridgedApIface, &wifiApIface);

    WIFI_RPC_PRINT_STATUS(status);

    uint16_t instanceId = WifiGetApIfaceInstanceId(wifiApIface);
    ALOGI("Wifi Chip create bridged ap iface instance Id %d.", instanceId);

    return WifiRpcSerializeResultResponse(status, instanceId,
        &WifiChipSerializeCreateBridgedApIfaceCfm, outData);
}

static bool WifiChipMsgHandlerGetApIfaceNames(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<std::string> names;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getApIfaceNames, &names);
    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, names,
        &WifiChipSerializeGetApIfaceNamesCfm, outData);
}

static bool WifiChipMsgHandlerGetApIface(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::string name;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, name,
        &WifiChipParseGetApIfaceReq)) {
        ALOGE("Wifi Chip parse get Ap Iface request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::shared_ptr<IWifiApIface> apIface;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getApIface, name, &apIface);

    WIFI_RPC_PRINT_STATUS(status);

    uint16_t instanceId = WifiGetApIfaceInstanceId(apIface);
    ALOGI("Wifi Chip get ap iface instance Id %d.", instanceId);

    return WifiRpcSerializeResultResponse(status, instanceId,
        &WifiChipSerializeGetApIfaceCfm, outData);
}

static bool WifiChipMsgHandlerRemoveApIface(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::string ifname;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, ifname,
        &WifiChipParseRemoveApIfaceReq)) {
        ALOGE("Wifi Chip parse Remove AP iface request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    ALOGD("Wifi Chip remove AP iface %s.", ifname.c_str());

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::removeApIface, ifname);

    /*Call Instance manager to remove ap interface*/

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerRemoveIfaceInstanceFromBridgedApIface(
    uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    RemoveIfaceInstanceFromBridgedApIfaceReqChipParam param;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, param,
        &WifiChipParseRemoveIfaceInstanceFromBridgedApIfaceReq)) {
        ALOGE("Wifi Chip parse Remove Bridges AP iface request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    ALOGD("Wifi Chip remove bridgged AP: brIfaceName: %s "
        "ifaceInstanceName: %s.", param.brIfaceName.c_str(),
        param.ifaceInstanceName.c_str());

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::removeIfaceInstanceFromBridgedApIface,
        param.brIfaceName, param.ifaceInstanceName);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}
#endif

static bool WifiChipMsgHandlerCreateStaIface(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::shared_ptr<IWifiStaIface> staIface;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::createStaIface, &staIface);

    WIFI_RPC_PRINT_STATUS(status);

    uint16_t instanceId = WifiGetStaIfaceInstanceId(staIface);
    ALOGI("Wifi Chip create sta iface instance Id %d.", instanceId);

    return WifiRpcSerializeResultResponse(status, instanceId,
        &WifiChipSerializeCreateStaIfaceCfm, outData);
}

static bool WifiChipMsgHandlerGetStaIfaceNames(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<std::string> ifaceNames;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getStaIfaceNames, &ifaceNames);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, ifaceNames,
        &WifiChipSerializeGetStaIfaceNamesCfm, outData);
}

static bool WifiChipMsgHandlerGetStaIface(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::string name;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, name,
        &WifiChipParseGetStaIfaceReq)) {
        ALOGE("Wifi Chip parse get sta iface request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::shared_ptr<IWifiStaIface> staIface;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getStaIface, name, &staIface);

    WIFI_RPC_PRINT_STATUS(status);

    /* Get InstanceId based on staIface */
    uint16_t instanceId = WifiGetStaIfaceInstanceId(staIface);
    ALOGI("Wifi Chip create sta iface instance Id %d.", instanceId);

    return WifiRpcSerializeResultResponse(status, instanceId,
        &WifiChipSerializeGetStaIfaceCfm, outData);
}

static bool WifiChipMsgHandlerRemoveStaIface(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::string ifname;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, ifname,
        &WifiChipParseRemoveStaIfaceReq)) {
        ALOGE("Wifi Chip parse remove sta iface request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    ALOGD("Wifi Chip remove STA iface %s.", ifname.c_str());

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::removeStaIface, ifname);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

#ifdef CONFIG_DEBUG
static bool WifiChipMsgHandlerGetDebugRingBuffersStatus(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<WifiDebugRingBufferStatus> dbgRingBufStatus;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::getDebugRingBuffersStatus, &dbgRingBufStatus);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, dbgRingBufStatus,
        &WifiChipSerializeGetDebugRingBuffersStatusCfm, outData);
}

static bool WifiChipMsgHandlerStartLoggingToDebugRingBuffer(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    StartLoggingToDebugRingBufferReqChipParam param;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, param,
        &WifiChipParseStartLoggingToDebugRingBufferReq)) {
        ALOGE("Wifi Chip parse start logging request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::startLoggingToDebugRingBuffer, param.ringName,
        param.verboseLevel, param.maxIntervalInSec, param.minDataSizeInBytes);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerForceDumpToDebugRingBuffer(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::string ringName;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, ringName,
        &WifiChipParseForceDumpToDebugRingBufferReq)) {
        ALOGE("Wifi Chip parse force dump request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::forceDumpToDebugRingBuffer, ringName);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerFlushRingBufferToFile(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::flushRingBufferToFile);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerStopLoggingToDebugRingBuffer(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::stopLoggingToDebugRingBuffer);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerGetDebugHostWakeReasonStats(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    WifiDebugHostWakeReasonStats reasonStatus;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::getDebugHostWakeReasonStats, &reasonStatus);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, reasonStatus,
        &WifiChipSerializeGetDebugHostWakeReasonStatsCfm, outData);
}

static bool WifiChipMsgHandlerEnableDebugErrorAlerts(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    bool enable;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, enable,
        &WifiChipParseEnableDebugErrorAlertsReq)) {
        ALOGE("Wifi Chip parse enable debug error alert request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::enableDebugErrorAlerts, enable);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}
#endif

static bool WifiChipMsgHandlerSelectTxPowerScenario(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    IWifiChip::TxPowerScenario scenario;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, scenario,
        &WifiChipParseSelectTxPowerScenarioReq)) {
        ALOGE("Wifi Chip parse select tx power scenario request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::selectTxPowerScenario, scenario);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerResetTxPowerScenario(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::resetTxPowerScenario);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerSetLatencyMode(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    IWifiChip::LatencyMode mode;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, mode,
        &WifiChipParseSetLatencyModeReq)) {
        ALOGE("Wifi Chip parse select set latency mode request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::setLatencyMode, mode);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerSetMultiStaPrimaryConnection(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::string ifname;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, ifname,
        &WifiChipParseSetMultiStaPrimaryConnectionReq)) {
        ALOGE("Wifi Chip parse set multi sta primary conneciton request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::setMultiStaPrimaryConnection, ifname);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerSetMultiStaUseCase(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    IWifiChip::MultiStaUseCase useCase;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, useCase,
        &WifiChipParseSetMultiStaUseCaseReq)) {
        ALOGE("Wifi Chip parse select set multi use case request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::setMultiStaUseCase, useCase);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerSetCoexUnsafeChannels(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    SetCoexUnsafeChannelsReqChipParam param;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, param,
        &WifiChipParseSetCoexUnsafeChannelsReq)) {
        ALOGE("Wifi Chip parse set coex unsafe channels request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::setCoexUnsafeChannels,
        param.unsafeChannels, param.restrictions);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerSetCountryCode(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::array<uint8_t, 2> code;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, code,
        &WifiChipParseSetCountryCodeReq)) {
        ALOGE("Wifi Chip parse set country code request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::setCountryCode, code);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerGetUsableChannels(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    GetUsableChannelsReqChipParam param;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, param,
        &WifiChipParseGetUsableChannelsReq)) {
        ALOGE("Wifi Chip parse get usable channels request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<WifiUsableChannel> channels;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::getUsableChannels,
        param.band, param.ifaceModeMask, param.filterMask, &channels);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, channels,
        WifiChipSerializeGetUsableChannelsCfm, outData);
}

static bool WifiChipMsgHandlerSetAfcChannelAllowance(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    AfcChannelAllowance afcChanAllow;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, afcChanAllow,
        &WifiChipParseSetAfcChannelAllowanceReq)) {
        ALOGE("Wifi Chip parse set afc channel allowance request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::setAfcChannelAllowance, afcChanAllow);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerTriggerSubsystemRestart(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::triggerSubsystemRestart);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerGetSupportedRadioCombinations(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<WifiRadioCombination> radioCombinations;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::getSupportedRadioCombinations, &radioCombinations);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, radioCombinations,
        &WifiChipSerializeGetSupportedRadioCombinationsCfm, outData);
}

static bool WifiChipMsgHandlerGetWifiChipCapabilities(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    WifiChipCapabilities capabilities;
    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId),
        &IWifiChip::getWifiChipCapabilities, &capabilities);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, capabilities,
        &WifiChipSerializeGetWifiChipCapabilitiesCfm, outData);
}

static bool WifiChipMsgHandlerEnableStaChannelForPeerNetwork(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    int32_t channelCategoryEnableFlag;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, channelCategoryEnableFlag,
        &WifiChipParseEnableStaChannelForPeerNetworkReq)) {
        ALOGE("Wifi Chip parse enable sta channel for peer network fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::enableStaChannelForPeerNetwork,
        channelCategoryEnableFlag);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiChipMsgHandlerSetMloMode(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    IWifiChip::ChipMloMode mode;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, mode,
        &WifiChipParseSetMloModeReq)) {
        ALOGE("Wifi Chip parse set mlo mode request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiChipCallMethod(static_cast<int32_t>(chipId), &IWifiChip::setMloMode, mode);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

/**
 * Start IWifiStaIface interface request method function hanlder.
 */
static bool WifiStaIfaceMsgHandlerGetName(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::string staIfaceName;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getName, &staIfaceName);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, staIfaceName,
        &WifiStaIfaceSerializeGetNameCfm, outData);
}

static bool WifiStaIfaceMsgHandlerGetFeatureSet(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    int32_t featureSet;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getFeatureSet, &featureSet);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, featureSet,
        &WifiStaIfaceSerializeGetFeatureSetCfm, outData);
}

static bool WifiStaIfaceMsgHandlerGetApfPacketFilterCapabilities(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    StaApfPacketFilterCapabilities pktFilterCap;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getApfPacketFilterCapabilities, &pktFilterCap);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, pktFilterCap,
        &WifiStaIfaceSerializeGetApfPacketFilterCapabilitiesCfm, outData);
}

static bool WifiStaIfaceMsgHandlerInstallApfPacketFilter(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::vector<uint8_t> program;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, program,
        &WifiStaIfaceParseInstallApfPacketFilterReq)) {
        ALOGE("Wifi Sta Iface parse apf pkt filter request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::installApfPacketFilter, program);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerReadApfPacketFilterData(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<uint8_t> readData;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::readApfPacketFilterData, &readData);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, readData,
        &WifiStaIfaceSerializeReadApfPacketFilterDataCfm, outData);
}

static bool WifiStaIfaceMsgHandlerGetBackgroundScanCapabilities(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    StaBackgroundScanCapabilities bgScanCap;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getBackgroundScanCapabilities, &bgScanCap);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, bgScanCap,
        &WifiStaIfaceSerializeGetBackgroundScanCapabilitiesCfm, outData);
}

static bool WifiStaIfaceMsgHandlerStartBackgroundScan(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    StartBackgroundScanReqStaIfaceParam param;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, param,
        &WifiStaIfaceParseStartBackgroundScanReq)) {
        ALOGE("Wifi Sta Iface parse BG scan start request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::startBackgroundScan,
        param.cmdId, param.params);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerStopBackgroundScan(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    int32_t cmdId;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, cmdId,
        &WifiStaIfaceParseStopBackgroundScanReq)) {
        ALOGE("Wifi Sta Iface parse BG scan stop request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::stopBackgroundScan, cmdId);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerEnableLinkLayerStatsCollection(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    bool debug;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, debug,
        &WifiStaIfaceParseEnableLinkLayerStatsCollectionReq)) {
        ALOGE("Wifi Sta Iface parse link layer stats collect request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::enableLinkLayerStatsCollection, debug);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerDisableLinkLayerStatsCollection(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::disableLinkLayerStatsCollection);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetLinkLayerStats(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    StaLinkLayerStats linkLayerStats;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getLinkLayerStats, &linkLayerStats);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, linkLayerStats,
        &WifiStaIfaceSerializeGetLinkLayerStatsCfm, outData);
}

static bool WifiStaIfaceMsgHandlerStartRssiMonitoring(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    StartRssiMonitoringReqStaIfaceParam param;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, param,
        &WifiStaIfaceParseStartRssiMonitoringReq)) {
        ALOGE("Wifi Sta Iface parse start rssi monitoring request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::startRssiMonitoring,
        param.cmdId, param.maxRssi, param.minRssi);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerStopRssiMonitoring(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    int32_t cmdId;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, cmdId,
        &WifiStaIfaceParseStopRssiMonitoringReq)) {
        ALOGE("Wifi Sta Iface parse stop rssi monitoring request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::stopRssiMonitoring, cmdId);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetRoamingCapabilities(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    StaRoamingCapabilities capbilities;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getRoamingCapabilities, &capbilities);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, capbilities,
        &WifiStaIfaceSerializeGetRoamingCapabilitiesCfm, outData);
}

static bool WifiStaIfaceMsgHandlerConfigureRoaming(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    StaRoamingConfig config;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, config,
        &WifiStaIfaceParseConfigureRoamingReq)) {
        ALOGE("Wifi Sta Iface parse configure roaming request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::configureRoaming, config);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerSetRoamingState(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    StaRoamingState state;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, state,
        &WifiStaIfaceParseSetRoamingStateReq)) {
        ALOGE("Wifi Sta Iface parse set roaming state request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::setRoamingState, state);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerEnableNdOffload(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    bool enable;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, enable,
        &WifiStaIfaceParseEnableNdOffloadReq)) {
        ALOGE("Wifi Sta Iface parse enable nd offload request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::enableNdOffload, enable);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerStartSendingKeepAlivePackets(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    StartSendingKeepAlivePacketsReqStaIfaceParam param;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, param,
        &WifiStaIfaceParseStartSendingKeepAlivePacketsReq)) {
        ALOGE("Wifi Sta Iface parse sending keep alive pkt request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::startSendingKeepAlivePackets,
        param.cmdId, param.ipPacketData, param.etherType,
        param.srcAddress, param.dstAddress, param.periodInMs);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerStopSendingKeepAlivePackets(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    int32_t cmdId;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, cmdId,
        &WifiStaIfaceParseStopSendingKeepAlivePacketsReq)) {
        ALOGE("Wifi Sta Iface parse stop send keep alive pkt request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::stopSendingKeepAlivePackets, cmdId);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

#ifdef CONFIG_DEBUG
static bool WifiStaIfaceMsgHandlerStartDebugPacketFateMonitoring(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::startDebugPacketFateMonitoring);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetDebugTxPacketFates(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<WifiDebugTxPacketFateReport> txPktFateReport;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getDebugTxPacketFates, &txPktFateReport);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, txPktFateReport,
        &WifiStaIfaceSerializeGetDebugTxPacketFatesCfm, outData);
}

static bool WifiStaIfaceMsgHandlerGetDebugRxPacketFates(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::vector<WifiDebugRxPacketFateReport> rxPktFateReport;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getDebugRxPacketFates, &rxPktFateReport);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, rxPktFateReport,
        &WifiStaIfaceSerializeGetDebugRxPacketFatesCfm, outData);
}
#endif

static bool WifiStaIfaceMsgHandlerSetMacAddress(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::array<uint8_t, 6> mac;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, mac,
        &WifiStaIfaceParseSetMacAddressReq)) {
        ALOGE("Wifi Sta Iface parse set mac address request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::setMacAddress, mac);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetFactoryMacAddress(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    std::array<uint8_t, 6> mac;
    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::getFactoryMacAddress, &mac);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, mac,
        &WifiStaIfaceSerializeGetFactoryMacAddressCfm, outData);
}

static bool WifiStaIfaceMsgHandlerSetScanMode(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    bool enable;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, enable,
        &WifiStaIfaceParseSetScanModeReq)) {
        ALOGE("Wifi Sta Iface parse set scan mode request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::setScanMode, enable);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiStaIfaceMsgHandlerSetDtimMultiplier(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    int32_t multiplier;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, multiplier,
        &WifiStaIfaceParseSetDtimMultiplierReq)) {
        ALOGE("Wifi Sta Iface parse set dtim multiplier request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiStaIfaceCallMethod(ifaceId,
        &IWifiStaIface::setDtimMultiplier, multiplier);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

#ifdef CONFIG_AP
/**
 * Start IWifiApIface interface request method function hanlder.
 */
static bool WifiApIfaceMsgHandlerGetName(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::string apIfaceName;
    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }
    auto status = WifiApIfaceCallMethod(ifaceId,
        &IWifiApIface::getName, &apIfaceName);
    WIFI_RPC_PRINT_STATUS(status);
    return WifiRpcSerializeResultResponse(status, apIfaceName,
        &WifiApIfaceSerializeGetNameCfm, outData);
}

static bool WifiApIfaceMsgHandlerSetCountryCode(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::array<uint8_t, 2> code;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, code,
        &WifiApIfaceParseSetCountryCodeReq)) {
        ALOGE("Wifi Sta Iface parse set country code request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiApIfaceCallMethod(ifaceId,
        &IWifiApIface::setCountryCode, code);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiApIfaceMsgHandlerSetMacAddress(uint8_t* data, size_t length,
    std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::array<uint8_t, 6> mac;
    if (!WifiRpcParseDataPayload(data, length, chipId, ifaceId, mac,
        &WifiApIfaceParseSetMacAddressReq)) {
        ALOGE("Wifi Ap Iface parse set mac address request fail.");
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiApIfaceCallMethod(ifaceId,
        &IWifiApIface::setMacAddress, mac);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiApIfaceMsgHandlerGetFactoryMacAddress(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::array<uint8_t, 6> mac;

    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiApIfaceCallMethod(ifaceId,
        &IWifiApIface::getFactoryMacAddress, &mac);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, mac,
        &WifiApIfaceSerializeGetFactoryMacAddressCfm, outData);
}

static bool WifiApIfaceMsgHandlerResetToFactoryMacAddress(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;

    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiApIfaceCallMethod(ifaceId,
        &IWifiApIface::resetToFactoryMacAddress);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeStatusResponse(status, outData);
}

static bool WifiApIfaceMsgHandlerGetBridgedInstances(uint8_t* data,
    size_t length, std::vector<uint8_t>& outData)
{
    uint16_t chipId, ifaceId;
    std::vector<std::string> bridgedInstances;

    if (!WifiRpcParseInstanceId(data, length, chipId, ifaceId)) {
        ndk::ScopedAStatus status = INVALID_ARGS_ERROR_STATUS;
        return WifiRpcSerializeStatusResponse(status, outData);
    }

    auto status = WifiApIfaceCallMethod(ifaceId,
        &IWifiApIface::getBridgedInstances, &bridgedInstances);

    WIFI_RPC_PRINT_STATUS(status);

    return WifiRpcSerializeResultResponse(status, bridgedInstances,
        &WifiApIfaceSerializeGetBridgedInstancesCfm, outData);
}
#endif

typedef std::function<bool(uint8_t*, size_t, std::vector<uint8_t>&)> MsgHandler;
static std::map<uint16_t, MsgHandler> msgHandlerMap = {
    /* IWifi exported method handlers */
    {WIFI_IS_STARTED_REQ, &WifiMsgHandlerIsStarted},
    {WIFI_START_REQ, &WifiMsgHandlerStart},
    {WIFI_STOP_REQ, &WifiMsgHandlerStop},
    {WIFI_GET_CHIP_IDS_REQ, &WifiMsgHandlerGetChipIds},
    {WIFI_GET_CHIP_REQ, &WifiMsgHandlerGetChip},

    /* IWifiChip exported method handlers */
    {WIFI_CHIP_GET_ID_REQ, &WifiChipMsgHandlerGetId},
    {WIFI_CHIP_GET_FEATURE_SET_REQ, &WifiChipMsgHandlerGetFeatureSet},
    {WIFI_CHIP_GET_AVAILABLE_MODES_REQ, &WifiChipMsgHandlerGetAvailableModes},
    {WIFI_CHIP_CONFIGURE_CHIP_REQ, &WifiChipMsgHandlerConfigureChip},
    {WIFI_CHIP_GET_MODE_REQ, &WifiChipMsgHandlerGetMode},
#ifdef CONFIG_DEBUG
    {WIFI_CHIP_REQUEST_CHIP_DEBUG_INFO_REQ, &WifiChipMsgHandlerRequestChipDebugInfo},
    {WIFI_CHIP_REQUEST_DRIVER_DEBUG_DUMP_REQ, &WifiChipMsgHandlerRequestDriverDebugDump},
    {WIFI_CHIP_REQUEST_FIRMWARE_DEBUG_DUMP_REQ, &WifiChipMsgHandlerRequestFirmwareDebugDump},
#endif
#ifdef CONFIG_AP
    {WIFI_CHIP_CREATE_AP_IFACE_REQ, &WifiChipMsgHandlerCreateApIface},
    {WIFI_CHIP_CREATE_BRIDGED_AP_IFACE_REQ, &WifiChipMsgHandlercreateBridgedApIface},
    {WIFI_CHIP_GET_AP_IFACE_NAMES_REQ, &WifiChipMsgHandlerGetApIfaceNames},
    {WIFI_CHIP_GET_AP_IFACE_REQ, &WifiChipMsgHandlerGetApIface},
    {WIFI_CHIP_REMOVE_AP_IFACE_REQ, &WifiChipMsgHandlerRemoveApIface},
    {WIFI_CHIP_REMOVE_IFACE_INSTANCE_FROM_BRIDGED_AP_IFACE_REQ, &WifiChipMsgHandlerRemoveIfaceInstanceFromBridgedApIface},
#endif
    {WIFI_CHIP_CREATE_STA_IFACE_REQ, &WifiChipMsgHandlerCreateStaIface},
    {WIFI_CHIP_GET_STA_IFACE_NAMES_REQ, &WifiChipMsgHandlerGetStaIfaceNames},
    {WIFI_CHIP_GET_STA_IFACE_REQ, &WifiChipMsgHandlerGetStaIface},
    {WIFI_CHIP_REMOVE_STA_IFACE_REQ, WifiChipMsgHandlerRemoveStaIface},
#ifdef CONFIG_DEBUG
    {WIFI_CHIP_GET_DEBUG_RING_BUFFERS_STATUS_REQ,  &WifiChipMsgHandlerGetDebugRingBuffersStatus},
    {WIFI_CHIP_START_LOGGING_TO_DEBUG_RING_BUFFER_REQ, &WifiChipMsgHandlerStartLoggingToDebugRingBuffer},
    {WIFI_CHIP_FORCE_DUMP_TO_DEBUG_RING_BUFFER_REQ, &WifiChipMsgHandlerForceDumpToDebugRingBuffer},
    {WIFI_CHIP_FLUSH_RING_BUFFER_TO_FILE_REQ, &WifiChipMsgHandlerFlushRingBufferToFile},
    {WIFI_CHIP_STOP_LOGGING_TO_DEBUG_RING_BUFFER_REQ, &WifiChipMsgHandlerStopLoggingToDebugRingBuffer},
    {WIFI_CHIP_GET_DEBUG_HOST_WAKE_REASON_STATS_REQ, &WifiChipMsgHandlerGetDebugHostWakeReasonStats},
    {WIFI_CHIP_ENABLE_DEBUG_ERROR_ALERTS_REQ, &WifiChipMsgHandlerEnableDebugErrorAlerts},
#endif
    {WIFI_CHIP_SELECT_TX_POWER_SCENARIO_REQ, &WifiChipMsgHandlerSelectTxPowerScenario},
    {WIFI_CHIP_RESET_TX_POWER_SCENARIO_REQ, &WifiChipMsgHandlerResetTxPowerScenario},
    {WIFI_CHIP_SET_LATENCY_MODE_REQ, &WifiChipMsgHandlerSetLatencyMode},
    {WIFI_CHIP_SET_MULTI_STA_PRIMARY_CONNECTION_REQ, &WifiChipMsgHandlerSetMultiStaPrimaryConnection},
    {WIFI_CHIP_SET_MULTI_STA_USE_CASE_REQ, &WifiChipMsgHandlerSetMultiStaUseCase},
    {WIFI_CHIP_SET_COEX_UNSAFE_CHANNELS_REQ, &WifiChipMsgHandlerSetCoexUnsafeChannels},
    {WIFI_CHIP_SET_COUNTRY_CODE_REQ, &WifiChipMsgHandlerSetCountryCode},
    {WIFI_CHIP_GET_USABLE_CHANNELS_REQ, &WifiChipMsgHandlerGetUsableChannels},
    {WIFI_CHIP_SET_AFC_CHANNEL_ALLOWANCE_REQ, &WifiChipMsgHandlerSetAfcChannelAllowance},
    {WIFI_CHIP_TRIGGER_SUBSYSTEM_RESTART_REQ, &WifiChipMsgHandlerTriggerSubsystemRestart},
    {WIFI_CHIP_GET_SUPPORTED_RADIO_COMBINATIONS_REQ, &WifiChipMsgHandlerGetSupportedRadioCombinations},
    {WIFI_CHIP_GET_WIFI_CHIP_CAPABILITIES_REQ, &WifiChipMsgHandlerGetWifiChipCapabilities},
    {WIFI_CHIP_ENABLE_STA_CHANNEL_FOR_PEER_NETWORK_REQ, &WifiChipMsgHandlerEnableStaChannelForPeerNetwork},
    {WIFI_CHIP_SET_MLO_MODE_REQ, &WifiChipMsgHandlerSetMloMode},

    /* IWifiStaIface exported method handlers */
    {WIFI_STA_IFACE_GET_NAME_REQ, &WifiStaIfaceMsgHandlerGetName},
    {WIFI_STA_IFACE_GET_FEATURE_SET_REQ, &WifiStaIfaceMsgHandlerGetFeatureSet},
    {WIFI_STA_IFACE_GET_APF_PACKET_FILTER_CAPABILITIES_REQ, &WifiStaIfaceMsgHandlerGetApfPacketFilterCapabilities},
    {WIFI_STA_IFACE_INSTALL_APF_PACKET_FILTER_REQ, &WifiStaIfaceMsgHandlerInstallApfPacketFilter},
    {WIFI_STA_IFACE_READ_APF_PACKET_FILTER_DATA_REQ, &WifiStaIfaceMsgHandlerReadApfPacketFilterData},
    {WIFI_STA_IFACE_GET_BACKGROUND_SCAN_CAPABILITIES_REQ, &WifiStaIfaceMsgHandlerGetBackgroundScanCapabilities},
    {WIFI_STA_IFACE_START_BACKGROUND_SCAN_REQ, &WifiStaIfaceMsgHandlerStartBackgroundScan},
    {WIFI_STA_IFACE_STOP_BACKGROUND_SCAN_REQ, &WifiStaIfaceMsgHandlerStopBackgroundScan},
    {WIFI_STA_IFACE_ENABLE_LINK_LAYER_STATS_COLLECTION_REQ, &WifiStaIfaceMsgHandlerEnableLinkLayerStatsCollection},
    {WIFI_STA_IFACE_DISABLE_LINK_LAYER_STATS_COLLECTION_REQ, &WifiStaIfaceMsgHandlerDisableLinkLayerStatsCollection},
    {WIFI_STA_IFACE_GET_LINK_LAYER_STATS_REQ, &WifiStaIfaceMsgHandlerGetLinkLayerStats},
    {WIFI_STA_IFACE_START_RSSI_MONITORING_REQ, &WifiStaIfaceMsgHandlerStartRssiMonitoring},
    {WIFI_STA_IFACE_STOP_RSSI_MONITORING_REQ, &WifiStaIfaceMsgHandlerStopRssiMonitoring},
    {WIFI_STA_IFACE_GET_ROAMING_CAPABILITIES_REQ, &WifiStaIfaceMsgHandlerGetRoamingCapabilities},
    {WIFI_STA_IFACE_CONFIGURE_ROAMING_REQ, &WifiStaIfaceMsgHandlerConfigureRoaming},
    {WIFI_STA_IFACE_SET_ROAMING_STATE_REQ, &WifiStaIfaceMsgHandlerSetRoamingState},
    {WIFI_STA_IFACE_ENABLE_ND_OFFLOAD_REQ, &WifiStaIfaceMsgHandlerEnableNdOffload},
    {WIFI_STA_IFACE_START_SENDING_KEEP_ALIVE_PACKETS_REQ, &WifiStaIfaceMsgHandlerStartSendingKeepAlivePackets},
    {WIFI_STA_IFACE_STOP_SENDING_KEEP_ALIVE_PACKETS_REQ, &WifiStaIfaceMsgHandlerStopSendingKeepAlivePackets},
#ifdef CONFIG_DEBUG
    {WIFI_STA_IFACE_START_DEBUG_PACKET_FATE_MONITORING_REQ, &WifiStaIfaceMsgHandlerStartDebugPacketFateMonitoring},
    {WIFI_STA_IFACE_GET_DEBUG_TX_PACKET_FATES_REQ, &WifiStaIfaceMsgHandlerGetDebugTxPacketFates},
    {WIFI_STA_IFACE_GET_DEBUG_RX_PACKET_FATES_REQ, &WifiStaIfaceMsgHandlerGetDebugRxPacketFates},
#endif
    {WIFI_STA_IFACE_SET_MAC_ADDRESS_REQ, &WifiStaIfaceMsgHandlerSetMacAddress},
    {WIFI_STA_IFACE_GET_FACTORY_MAC_ADDRESS_REQ, &WifiStaIfaceMsgHandlerGetFactoryMacAddress},
    {WIFI_STA_IFACE_SET_SCAN_MODE_REQ, &WifiStaIfaceMsgHandlerSetScanMode},
    {WIFI_STA_IFACE_SET_DTIM_MULTIPLIER_REQ, &WifiStaIfaceMsgHandlerSetDtimMultiplier},

#ifdef CONFIG_AP
    /* IWifiApIface exported method handlers */
    {WIFI_AP_IFACE_GET_NAME_REQ, &WifiApIfaceMsgHandlerGetName},
    {WIFI_AP_IFACE_SET_COUNTRY_CODE_REQ, &WifiApIfaceMsgHandlerSetCountryCode},
    {WIFI_AP_IFACE_SET_MAC_ADDRESS_REQ, &WifiApIfaceMsgHandlerSetMacAddress},
    {WIFI_AP_IFACE_GET_FACTORY_MAC_ADDRESS_REQ, &WifiApIfaceMsgHandlerGetFactoryMacAddress},
    {WIFI_AP_IFACE_RESET_TO_FACTORY_MAC_ADDRESS_REQ, &WifiApIfaceMsgHandlerResetToFactoryMacAddress},
    {WIFI_AP_IFACE_GET_BRIDGED_INSTANCES_REQ, &WifiApIfaceMsgHandlerGetBridgedInstances},
#endif

    {}
};

static inline MsgHandler WifiRpcGetMessageHandler(uint16_t methodId)
{
    auto item = msgHandlerMap.find(methodId);
    if (item != msgHandlerMap.end())
        return item->second;

    return nullptr;
}

static void WifiRpcDumpData(const char* description, uint16_t id,
    uint8_t *data, size_t length)
{
#ifdef CONFIG_DEBUG_DUMP
    ALOGI("Wifi Hal Dump: %s: id: 0x%x length: 0x%x", description, id, length);

    if (!data)
        return;

    for (int i = 0; i < length; i++) {
        printf("%02x ", data[i]);
        if ((i & 0xf) == 0xf)
            printf("\n");
    }
    printf("\n");
    ALOGI("Dump Data Completed");
#endif
}

void WifiRpcProcessSomeIPRequestMessage(uint16_t methodId,
    uint8_t *data, size_t length)
{
    ALOGI("Recv Someip Request message : method_id: 0x%x", methodId);
    WifiRpcDumpData("SomeIP Request", methodId, data, length);

    MsgHandler handler = WifiRpcGetMessageHandler(methodId);
    if (!handler) {
        ALOGE("Unspported SomeIP request method id 0x%x", methodId);
        return;
    }

    std::vector<uint8_t> response;
    bool ret = handler(data, length, response);
    if (!ret) {
        ALOGE("Process SomeIP Request fail.");
        return;
    }

    WifiRpcDumpData("SomeIP Response", methodId,
        response.data(), response.size());
    ret = someip_send_response(methodId, response.data(), response.size());
    if (!ret)
        ALOGE("Send SomeIP Response fail.");
}
