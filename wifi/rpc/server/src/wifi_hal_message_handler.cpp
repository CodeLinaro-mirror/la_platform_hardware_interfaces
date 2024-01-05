/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <android-base/logging.h>

#include <util/common_util.h>
#include <util/someip_api.h>

#include <wifi_reqcfm.h>
#include <wifi_chip_reqcfm.h>
#include <wifi_sta_iface_reqcfm.h>
#ifdef SUPPORT_AP
#include <wifi_ap_iface_reqcfm.h>
#endif

#include "wifi_hal_message_handler.h"
#include "wifi_someip_def.h"

#include "wifi.h"
#include "wifi_chip.h"
#include "wifi_hal_instance.h"
#include "wifi_sta_iface.h"
#ifdef SUPPORT_AP
#include "wifi_ap_iface.h"
#endif

#define WIFI_HAL_PRINT_CFM_STATUS(function, status) \
    do { \
        LOG(INFO) << "WifiHal Someip Service: " << (function) \
                   << " return status: " << toString((status).code); \
    } while (0)

static int32_t WifiHalGetInstanceId(uint8_t* data, size_t offset)
{
    return (int32_t)(data[offset] | data[offset + 1] << 8 | data[offset + 2] << 16 | data[offset + 3] << 24);
}

template <typename Param>
static void ScopedAStatus2Param(const ndk::ScopedAStatus& status, Param& param)
{
    param.status = (int32_t)status.code;
    param.info = status.description;
}

/**
 * Start IWifi interface request method function hanlder.
 */
static bool WifiSerializeStatus(const ndk::ScopedAStatus& status, std::vector<uint8_t>& outData)
{
    return WifiSerializeWifiCfm((int32_t)status.code, status.description, outData);
}

static bool WifiMsgHandlerIsStarted(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    bool isStarted = false;
    auto wifiInstance = WifiHalGetWifiInstance();
    ndk::ScopedAStatus status = wifiInstance->isStarted(&isStarted);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiParam param;
    ScopedAStatus2Param(status, param);
    return WifiSerializeIsStartedCfm(param, isStarted, outData);
}

static bool WifiMsgHandlerStart(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    auto wifiInstance = WifiHalGetWifiInstance();
    ndk::ScopedAStatus status = wifiInstance->start();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiSerializeStatus(status, outData);
}

static bool WifiMsgHandlerStop(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    auto wifiInstance = WifiHalGetWifiInstance();
    ndk::ScopedAStatus status = wifiInstance->stop();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiSerializeStatus(status, outData);
}

static bool WifiMsgHandlerGetChipIds(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<int32_t> chipIds;
    auto wifiInstance = WifiHalGetWifiInstance();
    ndk::ScopedAStatus status = wifiInstance->getChipIds(&chipIds);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiParam param;
    ScopedAStatus2Param(status, param);
    return WifiSerializeGetChipIdsCfm(param, chipIds, outData);
}

static bool WifiMsgHandlerGetChip(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    int32_t chipId;
    if (!WifiParseGetChipReq(data, length, chipId)) {
        LOG(ERROR) << "Wifi Chip parse get chip request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiSerializeStatus(status, outData);
    }

    auto wifiInstance = WifiHalGetWifiInstance();
    std::shared_ptr<IWifiChip> wifiChip;
    ndk::ScopedAStatus status = wifiInstance->getChip(chipId, &wifiChip);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiParam param;
    ScopedAStatus2Param(status, param);
    return WifiSerializeGetChipCfm(param, chipId, outData);
}

static bool WifiMsgHandlerDump(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    ndk::ScopedAStatus status(WifiStatusCode::ERROR_NOT_SUPPORTED);
    return WifiSerializeStatus(status, outData);
}

/**
 * Start IWifiChip interface request method function hanlder.
 */
static bool WifiChipSerializeStatus(const ndk::ScopedAStatus& status, std::vector<uint8_t>& outData)
{
    return WifiChipSerializeWifiChipCfm((int32_t)status.code, status.description, outData);
}

static bool WifiChipMsgHandlerGetId(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    int32_t id;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getId(&id);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetIdCfm(param, id, outData);
}

static bool WifiChipMsgHandlerGetFeatureSet(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    int32_t featureSet;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getFeatureSet(&featureSet);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetFeatureSetCfm(param, featureSet, outData);
}

static bool WifiChipMsgHandlerGetAvailableModes(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<IWifiChip::ChipMode> chipModes;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getAvailableModes(&chipModes);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetAvailableModesCfm(param, chipModes, outData);
}

static bool WifiChipMsgHandlerConfigureChip(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    int32_t modeId;
    if (!WifiChipParseConfigureChipReq(data, length, modeId)) {
        LOG(ERROR) << "Wifi Chip parse configure chip request fail.";
	ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    LOG(DEBUG) << "Wifi config chip modeId: " << modeId;

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->configureChip(modeId);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerGetMode(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    int32_t mode;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getMode(&mode);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetModeCfm(param, mode, outData);
}

#ifdef ENABLE_DEBUG
static bool WifiChipMsgHandlerRequestChipDebugInfo(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    IWifiChip::ChipDebugInfo chipDebugInfo;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->requestChipDebugInfo(&chipDebugInfo);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeRequestChipDebugInfoCfm(param, chipDebugInfo, outData);
}

static bool WifiChipMsgHandlerRequestDriverDebugDump(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<uint8_t> dbgDump;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->requestDriverDebugDump(&dbgDump);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeRequestDriverDebugDumpCfm(param, dbgDump, outData);
}

static bool WifiChipMsgHandlerRequestFirmwareDebugDump(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<uint8_t> dbgDump;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->requestFirmwareDebugDump(&dbgDump);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeRequestFirmwareDebugDumpCfm(param, dbgDump, outData);
}
#endif

#ifdef SUPPORT_AP
static bool WifiChipMsgHandlerCreateApIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::shared_ptr<IWifiApIface> wifiApIface;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->createApIface(&wifiApIface);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    int32_t instanceId;
    if (status.isOk() && wifiApIface != nullptr)
        instanceId = std::dynamic_pointer_cast<WifiApIface>(wifiApIface)->getInstanceId();
    LOG(INFO) << "WifiChipMsgHandlerCreateApIface Instance Id 0x" << std::hex << instanceId;

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeCreateStaIfaceCfm(param, instanceId, outData);
}

static bool WifiChipMsgHandlercreateBridgedApIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::shared_ptr<IWifiApIface> wifiApIface;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->createBridgedApIface(&wifiApIface);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    int32_t instanceId;
    if (status.isOk() && wifiApIface != nullptr)
        instanceId = std::dynamic_pointer_cast<WifiApIface>(wifiApIface)->getInstanceId();
    LOG(INFO) << "WifiChipMsgHandlerCreateBridgedApIface Instance Id 0x" << std::hex << instanceId;

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeCreateBridgedApIfaceCfm(param, instanceId, outData);
}

static bool WifiChipMsgHandlerGetApIfaceNames(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<std::string> apIfaceNames;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getApIfaceNames(&apIfaceNames);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetApIfaceNamesCfm(param, apIfaceNames, outData);
}

static bool WifiChipMsgHandlerGetApIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::string name;
    if (!WifiChipParseGetApIfaceReq(data, length, name)) {
        LOG(ERROR) << "Wifi Chip parse get Ap Iface request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiChipSerializeStatus(status, outData);
    }

    std::shared_ptr<IWifiApIface> apIface;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getApIface(name, &apIface);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    int32_t instanceId;
    if (status.isOk() && apIface != nullptr)
        instanceId = std::dynamic_pointer_cast<WifiApIface>(apIface)->getInstanceId();
    LOG(INFO) << "WifiChipMsgHandlerGetApIface Instance Id 0x" << std::hex << instanceId;

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetApIfaceCfm(param, instanceId, outData);
}

static bool WifiChipMsgHandlerRemoveApIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::string ifname;
    if (!WifiChipParseRemoveApIfaceReq(data, length, ifname)) {
        LOG(ERROR) << "Wifi Chip parse Remove AP iface request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiChipSerializeStatus(status, outData);
    }

    LOG(DEBUG) << "Wifi Chip remove AP iface : " << ifname.c_str();

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->removeApIface(ifname);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerRemoveIfaceInstanceFromBridgedApIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    RemoveIfaceInstanceFromBridgedApIfaceReqParam param;
    if (!WifiChipParseRemoveIfaceInstanceFromBridgedApIfaceReq(data, length, param)) {
        LOG(ERROR) << "Wifi Chip parse Remove Bridges AP iface request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiChipSerializeStatus(status, outData);
    }

    LOG(DEBUG) << "Wifi Chip remove bridgged AP: brIfaceName: " << param.brIfaceName.c_str()
               << " ifaceInstanceName : " << param.ifaceInstanceName.c_str();

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->removeIfaceInstanceFromBridgedApIface(param.brIfaceName, param.ifaceInstanceName);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}
#endif

static bool WifiChipMsgHandlerCreateStaIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::shared_ptr<IWifiStaIface> wifiStaIface;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->createStaIface(&wifiStaIface);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    int32_t instanceId;
    if (status.isOk() && wifiStaIface != nullptr)
        instanceId = std::dynamic_pointer_cast<WifiStaIface>(wifiStaIface)->getInstanceId();
    LOG(INFO) << "WifiChipMsgHandlerCreateStaIface Instance Id 0x" << std::hex << instanceId;

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeCreateStaIfaceCfm(param, instanceId, outData);
}

static bool WifiChipMsgHandlerGetStaIfaceNames(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<std::string> staIfaceNames;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getStaIfaceNames(&staIfaceNames);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetStaIfaceNamesCfm(param, staIfaceNames, outData);
}

static bool WifiChipMsgHandlerGetStaIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::string name;
    if (!WifiChipParseGetStaIfaceReq(data, length, name)) {
        LOG(ERROR) << "Wifi Chip parse get sta iface request fail.";
	ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    std::shared_ptr<IWifiStaIface> wifiStaIface;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getStaIface(name, &wifiStaIface);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    /* Get InstanceId based on staIface */
    int32_t instanceId;
    if (status.isOk() && wifiStaIface != nullptr)
        instanceId = std::dynamic_pointer_cast<WifiStaIface>(wifiStaIface)->getInstanceId();

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetStaIfaceCfm(param, instanceId, outData);
}

static bool WifiChipMsgHandlerRemoveStaIface(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::string ifname;
    if (!WifiChipParseRemoveStaIfaceReq(data, length, ifname)) {
        LOG(ERROR) << "Wifi Chip parse remove sta iface request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    LOG(DEBUG) << "Wifi Chip remove STA iface : " << ifname.c_str();

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->removeStaIface(ifname);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

#ifdef ENABLE_DEBUG
static bool WifiChipMsgHandlerGetDebugRingBuffersStatus(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<WifiDebugRingBufferStatus> dbgRingBufStatus;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getDebugRingBuffersStatus(&dbgRingBufStatus);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetDebugRingBuffersStatusCfm(param, dbgRingBufStatus, outData);
}

static bool WifiChipMsgHandlerStartLoggingToDebugRingBuffer(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    StartLoggingToDebugRingBufferReqChipParam param;
    if (!WifiChipParseStartLoggingToDebugRingBufferReq(data, length, param)) {
        LOG(ERROR) << "Wifi Chip parse start logging request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->startLoggingToDebugRingBuffer(
            param.ringName, param.verboseLevel, param.maxIntervalInSec, param.minDataSizeInBytes);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerForceDumpToDebugRingBuffer(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::string ringName;
    if (!WifiChipParseForceDumpToDebugRingBufferReq(data, length, ringName)) {
        LOG(ERROR) << "Wifi Chip parse force dump request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->forceDumpToDebugRingBuffer(ringName);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerFlushRingBufferToFile(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->flushRingBufferToFile();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerStopLoggingToDebugRingBuffer(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->stopLoggingToDebugRingBuffer();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerGetDebugHostWakeReasonStats(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    WifiDebugHostWakeReasonStats reasonStatus;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getDebugHostWakeReasonStats(&reasonStatus);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetDebugHostWakeReasonStatsCfm(param, reasonStatus, outData);
}

static bool WifiChipMsgHandlerEnableDebugErrorAlerts(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    bool enable;
    if (!WifiChipParseEnableDebugErrorAlertsReq(data, length, enable)) {
        LOG(ERROR) << "Wifi Chip parse enable debug error alert request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->enableDebugErrorAlerts(enable);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}
#endif

static bool WifiChipMsgHandlerSelectTxPowerScenario(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    IWifiChip::TxPowerScenario scenario;
    if (!WifiChipParseSelectTxPowerScenarioReq(data, length, scenario)) {
        LOG(ERROR) << "Wifi Chip parse select tx power scenario request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->selectTxPowerScenario(scenario);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerResetTxPowerScenario(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->resetTxPowerScenario();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerSetLatencyMode(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    IWifiChip::LatencyMode mode;
    if (!WifiChipParseSetLatencyModeReq(data, length, mode)) {
        LOG(ERROR) << "Wifi Chip parse select set latency mode request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->setLatencyMode(mode);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerSetMultiStaPrimaryConnection(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::string ifName;
    if (!WifiChipParseSetMultiStaPrimaryConnectionReq(data, length, ifName)) {
        LOG(ERROR) << "Wifi Chip parse select set multi sta primary conneciton request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->setMultiStaPrimaryConnection(ifName);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerSetMultiStaUseCase(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    IWifiChip::MultiStaUseCase useCase;
    if (!WifiChipParseSetMultiStaUseCaseReq(data, length, useCase)) {
        LOG(ERROR) << "Wifi Chip parse select set multi use case request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->setMultiStaUseCase(useCase);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerSetCoexUnsafeChannels(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    SetCoexUnsafeChannelsReqChipParam param;
    if (!WifiChipParseSetCoexUnsafeChannelsReq(data, length, param)) {
        LOG(ERROR) << "Wifi Chip parse set coex unsafe channels request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->setCoexUnsafeChannels(
            param.unsafeChannels, param.restrictions);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerSetCountryCode(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::array<uint8_t, 2> code;
    std::vector<uint8_t> codeVector;
    if (!WifiChipParseSetCountryCodeReq(data, length, codeVector)) {
        LOG(ERROR) << "Wifi Chip parse set country code request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }
    Vector2Array(codeVector, code);

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->setCountryCode(code);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerGetUsableChannels(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    GetUsableChannelsReqChipParam param;
    if (!WifiChipParseGetUsableChannelsReq(data, length, param)) {
        LOG(ERROR) << "Wifi Chip parse get usable channels request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    std::vector<WifiUsableChannel> channels;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getUsableChannels(
            param.band, param.ifaceModeMask, param.filterMask, &channels);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam result;
    ScopedAStatus2Param(status, result);
    return WifiChipSerializeGetUsableChannelsCfm(result, channels, outData);
}

static bool WifiChipMsgHandlerSetAfcChannelAllowance(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    AfcChannelAllowance afcChanAllow;
    if (!WifiChipParseSetAfcChannelAllowanceReq(data, length, afcChanAllow)) {
        LOG(ERROR) << "Wifi Chip parse set afc channel allowance request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->setAfcChannelAllowance(afcChanAllow);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerTriggerSubsystemRestart(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->triggerSubsystemRestart();
    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

static bool WifiChipMsgHandlerGetSupportedRadioCombinations(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<WifiRadioCombination> radioCombinations;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getSupportedRadioCombinations(
                &radioCombinations);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetSupportedRadioCombinationsCfm(param, radioCombinations, outData);
}

static bool WifiChipMsgHandlerGetWifiChipCapabilities(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    WifiChipCapabilities capabilities;
    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->getWifiChipCapabilities(&capabilities);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiChipParam param;
    ScopedAStatus2Param(status, param);
    return WifiChipSerializeGetWifiChipCapabilitiesCfm(param, capabilities, outData);
}

static bool WifiChipMsgHandlerEnableStaChannelForPeerNetwork(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    int32_t channelCategoryEnableFlag;
    if (!WifiChipParseEnableStaChannelForPeerNetworkReq(data, length, channelCategoryEnableFlag)) {
        LOG(ERROR) << "Wifi Chip parse enable sta channel for peer network request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->enableStaChannelForPeerNetwork(channelCategoryEnableFlag);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

#ifdef ENABLE_DEBUG
static bool WifiChipMsgHandlerDump(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    /* This request message handler is not useful. */
    ndk::ScopedAStatus status(WifiStatusCode::ERROR_NOT_SUPPORTED);
    return WifiChipSerializeStatus(status, outData);
}
#endif

static bool WifiChipMsgHandlerSetMloMode(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    IWifiChip::ChipMloMode mode;
    if (!WifiChipParseSetMloModeReq(data, length, mode)) {
        LOG(ERROR) << "Wifi Chip parse set mlo mode request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    auto wifiChipInstance = WifiHalGetChipInstance();
    ndk::ScopedAStatus status = wifiChipInstance->setMloMode(mode);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiChipSerializeStatus(status, outData);
}

/**
 * Start IWifiStaIface interface request method function hanlder.
 */
static bool WifiStaIfaceSerializeStatus(const ndk::ScopedAStatus& status, std::vector<uint8_t>& outData)
{
    return WifiStaIfaceSerializeWifiStaIfaceCfm((int32_t)status.code, status.description, outData);
}

static bool WifiStaIfaceMsgHandlerGetName(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
	ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    std::string staIfaceName;
    ndk::ScopedAStatus status = staIfaceInstance->getName(&staIfaceName);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetNameCfm(param, staIfaceName, outData);
}

static bool WifiStaIfaceMsgHandlerGetFeatureSet(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    int32_t featureSet;
    ndk::ScopedAStatus status = staIfaceInstance->getFeatureSet(&featureSet);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetFeatureSetCfm(param, featureSet, outData);
}

static bool WifiStaIfaceMsgHandlerGetApfPacketFilterCapabilities(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StaApfPacketFilterCapabilities pktFilterCap;
    ndk::ScopedAStatus status = staIfaceInstance->getApfPacketFilterCapabilities(&pktFilterCap);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetApfPacketFilterCapabilitiesCfm(param, pktFilterCap, outData);
}

static bool WifiStaIfaceMsgHandlerInstallApfPacketFilter(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    std::vector<uint8_t> program;
    if (!WifiStaIfaceParseInstallApfPacketFilterReq(data, length - 4, program)) {
        LOG(ERROR) << "Wifi Sta Iface parse install apf pkt filter request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->installApfPacketFilter(program);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerReadApfPacketFilterData(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    std::vector<uint8_t> readData;
    ndk::ScopedAStatus status = staIfaceInstance->readApfPacketFilterData(&readData);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeReadApfPacketFilterDataCfm(param, readData, outData);
}

static bool WifiStaIfaceMsgHandlerGetBackgroundScanCapabilities(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StaBackgroundScanCapabilities bgScanCap;
    ndk::ScopedAStatus status = staIfaceInstance->getBackgroundScanCapabilities(&bgScanCap);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetBackgroundScanCapabilitiesCfm(param, bgScanCap, outData);
}

static bool WifiStaIfaceMsgHandlerStartBackgroundScan(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StartBackgroundScanReqStaParam param;
    if (!WifiStaIfaceParseStartBackgroundScanReq(data, length - 4, param)) {
        LOG(ERROR) << "Wifi Sta Iface parse start background scan request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->startBackgroundScan(param.cmdId, param.params);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerStopBackgroundScan(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    int32_t cmdId;
    if (!WifiStaIfaceParseStopBackgroundScanReq(data, length - 4, cmdId)) {
        LOG(ERROR) << "Wifi Sta Iface parse start background scan request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->stopBackgroundScan(cmdId);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerEnableLinkLayerStatsCollection(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    bool debug;
    if (!WifiStaIfaceParseEnableLinkLayerStatsCollectionReq(data, length - 4, debug)) {
        LOG(ERROR) << "Wifi Sta Iface parse enable link layer stats collection request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->enableLinkLayerStatsCollection(debug);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerDisableLinkLayerStatsCollection(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    ndk::ScopedAStatus status = staIfaceInstance->disableLinkLayerStatsCollection();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetLinkLayerStats(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StaLinkLayerStats linkLayerStats;
    ndk::ScopedAStatus status = staIfaceInstance->getLinkLayerStats(&linkLayerStats);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetLinkLayerStatsCfm(param, linkLayerStats, outData);
}

static bool WifiStaIfaceMsgHandlerStartRssiMonitoring(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StartRssiMonitoringReqStaParam param;
    if (!WifiStaIfaceParseStartRssiMonitoringReq(data, length - 4, param)) {
        LOG(ERROR) << "Wifi Sta Iface parse start rssi monitoring request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->startRssiMonitoring(param.cmdId, param.maxRssi, param.minRssi);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerStopRssiMonitoring(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    int32_t cmdId;
    if (!WifiStaIfaceParseStopRssiMonitoringReq(data, length - 4, cmdId)) {
        LOG(ERROR) << "Wifi Sta Iface parse stop rssi monitoring request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->stopRssiMonitoring(cmdId);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetRoamingCapabilities(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StaRoamingCapabilities capbilities;
    ndk::ScopedAStatus status = staIfaceInstance->getRoamingCapabilities(&capbilities);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetRoamingCapabilitiesCfm(param, capbilities, outData);
}

static bool WifiStaIfaceMsgHandlerConfigureRoaming(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StaRoamingConfig config;
    if (!WifiStaIfaceParseConfigureRoamingReq(data, length - 4, config)) {
        LOG(ERROR) << "Wifi Sta Iface parse config roaming request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->configureRoaming(config);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerSetRoamingState(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StaRoamingState state;
    if (!WifiStaIfaceParseSetRoamingStateReq(data, length - 4, state)) {
        LOG(ERROR) << "Wifi Sta Iface parse set roaming state request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->setRoamingState(state);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerEnableNdOffload(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    bool enable;
    if (!WifiStaIfaceParseEnableNdOffloadReq(data, length - 4, enable)) {
        LOG(ERROR) << "Wifi Sta Iface parse enable Nd offload request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->enableNdOffload(enable);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerStartSendingKeepAlivePackets(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    StartSendingKeepAlivePacketsReqStaParam param;
    if (!WifiStaIfaceParseStartSendingKeepAlivePacketsReq(data, length - 4, param)) {
        LOG(ERROR) << "Wifi Sta Iface parse start sending keep alive pkts request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    std::array<uint8_t, 6> srcAddress;
    std::array<uint8_t, 6> dstAddress;
    Vector2Array(param.srcAddress, srcAddress);
    Vector2Array(param.dstAddress, dstAddress);
    ndk::ScopedAStatus status = staIfaceInstance->startSendingKeepAlivePackets(param.cmdId, param.ipPacketData,
            param.etherType, srcAddress, dstAddress, param.periodInMs);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerStopSendingKeepAlivePackets(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    int32_t cmdId;
    if (!WifiStaIfaceParseStopSendingKeepAlivePacketsReq(data, length - 4, cmdId)) {
        LOG(ERROR) << "Wifi Sta Iface parse stop sending keep alive pkts request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->stopSendingKeepAlivePackets(cmdId);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

#ifdef ENABLE_DEBUG
static bool WifiStaIfaceMsgHandlerStartDebugPacketFateMonitoring(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    ndk::ScopedAStatus status = staIfaceInstance->startDebugPacketFateMonitoring();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetDebugTxPacketFates(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    std::vector<WifiDebugTxPacketFateReport> txPktFateReport;
    ndk::ScopedAStatus status = staIfaceInstance->getDebugTxPacketFates(&txPktFateReport);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetDebugTxPacketFatesCfm(param, txPktFateReport, outData);
}

static bool WifiStaIfaceMsgHandlerGetDebugRxPacketFates(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    std::vector<WifiDebugRxPacketFateReport> rxPktFateReport;
    ndk::ScopedAStatus status = staIfaceInstance->getDebugRxPacketFates(&rxPktFateReport);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiStaIfaceSerializeGetDebugRxPacketFatesCfm(param, rxPktFateReport, outData);
}
#endif

static bool WifiStaIfaceMsgHandlerSetMacAddress(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    std::vector<uint8_t> param;
    if (!WifiStaIfaceParseSetMacAddressReq(data, length - 4, param)) {
        LOG(ERROR) << "Wifi Sta Iface parse set mac address request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    std::array<uint8_t, 6> mac;
    Vector2Array(param, mac);
    ndk::ScopedAStatus status = staIfaceInstance->setMacAddress(mac);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerGetFactoryMacAddress(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    std::array<uint8_t, 6> mac;
    ndk::ScopedAStatus status = staIfaceInstance->getFactoryMacAddress(&mac);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiStaIfaceParam param;
    ScopedAStatus2Param(status, param);
    std::vector<uint8_t> macVec;
    Array2Vector(mac, macVec);
    return WifiStaIfaceSerializeGetFactoryMacAddressCfm(param, macVec, outData);
}

static bool WifiStaIfaceMsgHandlerSetScanMode(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    bool enable;
    if (!WifiStaIfaceParseSetScanModeReq(data, length - 4, enable)) {
        LOG(ERROR) << "Wifi Sta Iface parse set scan mode request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->setScanMode(enable);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

static bool WifiStaIfaceMsgHandlerSetDtimMultiplier(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    if (!data || length < 4) {
        LOG(ERROR) << "Invalid data payload length " << std::to_string(length);
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
        return WifiStaIfaceSerializeStatus(status, outData);
    }

    int32_t staIfaceId = WifiHalGetInstanceId(data, length - 4);
    auto staIfaceInstance = WifiHalGetStaIfaceByInstanceId(staIfaceId);

    int32_t multiplier;
    if (!WifiStaIfaceParseSetDtimMultiplierReq(data, length - 4, multiplier)) {
        LOG(ERROR) << "Wifi Sta Iface parse set dtim multiplier request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiStaIfaceSerializeStatus(status, outData);
    }

    ndk::ScopedAStatus status = staIfaceInstance->setDtimMultiplier(multiplier);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiStaIfaceSerializeStatus(status, outData);
}

#ifdef SUPPORT_AP //disabled by default
/**
 * Start IWifiApIface interface request method function hanlder.
 */
static bool WifiApIfaceSerializeStatus(const ndk::ScopedAStatus& status, std::vector<uint8_t>& outData)
{
    return WifiApIfaceSerializeWifiApIfaceCfm((int32_t)status.code, status.description, outData);
}

static bool WifiApIfaceMsgHandlerGetName(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::string apIfaceName;
    auto apIfaceInstance = WifiHalGetApIfaceInstance();
    ndk::ScopedAStatus status = apIfaceInstance->getName(&apIfaceName);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiApIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiApIfaceSerializeGetNameCfm(param, apIfaceName, outData);
}

static bool WifiApIfaceMsgHandlerSetCountryCode(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<uint8_t> param;
    if (!WifiApIfaceParseSetCountryCodeReq(data, length, param)) {
        LOG(ERROR) << "Wifi Ap Iface parse set country code request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiApIfaceSerializeStatus(status, outData);
    }

    std::array<uint8_t, 2> code;
    Vector2Array(param, code);
    auto apIfaceInstance = WifiHalGetApIfaceInstance();
    ndk::ScopedAStatus status = apIfaceInstance->setCountryCode(code);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiApIfaceSerializeStatus(status, outData);
}

static bool WifiApIfaceMsgHandlerSetMacAddress(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<uint8_t> param;
    if (!WifiApIfaceParseSetMacAddressReq(data, length, param)) {
        LOG(ERROR) << "Wifi Ap Iface parse set mac address request fail.";
        ndk::ScopedAStatus status(WifiStatusCode::ERROR_INVALID_ARGS);
	return WifiChipSerializeStatus(status, outData);
    }

    std::array<uint8_t, 6> mac;
    Vector2Array(param, mac);
    auto apIfaceInstance = WifiHalGetApIfaceInstance();
    ndk::ScopedAStatus status = apIfaceInstance->setMacAddress(mac);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiApIfaceSerializeStatus(status, outData);
}

static bool WifiApIfaceMsgHandlerGetFactoryMacAddress(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::array<uint8_t, 6> mac;
    auto apIfaceInstance = WifiHalGetApIfaceInstance();
    ndk::ScopedAStatus status = apIfaceInstance->getFactoryMacAddress(&mac);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiApIfaceParam param;
    ScopedAStatus2Param(status, param);
    std::vector<uint8_t> macVec;
    Array2Vector(mac, macVec);
    return WifiApIfaceSerializeGetFactoryMacAddressCfm(param, macVec, outData);
}

static bool WifiApIfaceMsgHandlerResetToFactoryMacAddress(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    auto apIfaceInstance = WifiHalGetApIfaceInstance();
    ndk::ScopedAStatus status = apIfaceInstance->resetToFactoryMacAddress();

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    return WifiApIfaceSerializeStatus(status, outData);
}

static bool WifiApIfaceMsgHandlerGetBridgedInstances(uint8_t* data, size_t length, std::vector<uint8_t>& outData)
{
    std::vector<std::string> bridgedInstances;
    auto apIfaceInstance = WifiHalGetApIfaceInstance();
    ndk::ScopedAStatus status = apIfaceInstance->getBridgedInstances(&bridgedInstances);

    WIFI_HAL_PRINT_CFM_STATUS(__func__, status);

    WifiApIfaceParam param;
    ScopedAStatus2Param(status, param);
    return WifiApIfaceSerializeGetBridgedInstancesCfm(param, bridgedInstances, outData);
}
#endif

typedef std::function< bool (uint8_t* data, size_t length, std::vector<uint8_t>& outData) > MessageHandler;
static std::map<uint16_t, MessageHandler> msgHandlerMap = {
    /* IWifi exported method handlers */
    {IWIFI_IS_STARTED_REQ, &WifiMsgHandlerIsStarted},
    {IWIFI_START_REQ, &WifiMsgHandlerStart},
    {IWIFI_STOP_REQ, &WifiMsgHandlerStop},
    {IWIFI_GET_CHIP_IDS_REQ, &WifiMsgHandlerGetChipIds},
    {IWIFI_GET_CHIP_REQ, &WifiMsgHandlerGetChip},
    /* {IWIFI_DUMP_REQ, &WifiMsgHandlerDump}, */

    /* IWifiChip exported method handlers */
    {IWIFICHIP_GET_ID_REQ, &WifiChipMsgHandlerGetId},
    {IWIFICHIP_GET_FEATURE_SET_REQ, &WifiChipMsgHandlerGetFeatureSet},
    {IWIFICHIP_GET_AVAILABLE_MODES_REQ, &WifiChipMsgHandlerGetAvailableModes},
    {IWIFICHIP_CONFIGURE_CHIP_REQ, &WifiChipMsgHandlerConfigureChip},
    {IWIFICHIP_GET_MODE_REQ, &WifiChipMsgHandlerGetMode},
#ifdef ENABLE_DEBUG //disabled by default
    {IWIFICHIP_REQUEST_CHIP_DEBUG_INFO_REQ, &WifiChipMsgHandlerRequestChipDebugInfo},
    {IWIFICHIP_REQUEST_DRIVER_DEBUG_DUMP_REQ, &WifiChipMsgHandlerRequestDriverDebugDump},
    {IWIFICHIP_REQUEST_FIRMWARE_DEBUG_DUMP_REQ, &WifiChipMsgHandlerRequestFirmwareDebugDump},
#endif
#ifdef SUPPORT_AP //disabled by default
    {IWIFICHIP_CREATE_AP_IFACE_REQ, &WifiChipMsgHandlerCreateApIface},
    {IWIFICHIP_CREATE_BRIDGED_AP_IFACE_REQ, &WifiChipMsgHandlercreateBridgedApIface},
    {IWIFICHIP_GET_AP_IFACE_NAMES_REQ, &WifiChipMsgHandlerGetApIfaceNames},
    {IWIFICHIP_GET_AP_IFACE_REQ, &WifiChipMsgHandlerGetApIface},
    {IWIFICHIP_REMOVE_AP_IFACE_REQ, &WifiChipMsgHandlerRemoveApIface},
    {IWIFICHIP_REMOVE_IFACE_INSTANCE_FROM_BRIDGED_AP_IFACE_REQ, &WifiChipMsgHandlerRemoveIfaceInstanceFromBridgedApIface},
#endif
    {IWIFICHIP_CREATE_STA_IFACE_REQ, &WifiChipMsgHandlerCreateStaIface},
    {IWIFICHIP_GET_STA_IFACE_NAMES_REQ, &WifiChipMsgHandlerGetStaIfaceNames},
    {IWIFICHIP_GET_STA_IFACE_REQ, &WifiChipMsgHandlerGetStaIface},
    {IWIFICHIP_REMOVE_STA_IFACE_REQ, WifiChipMsgHandlerRemoveStaIface},
#ifdef ENABLE_DEBUG //disabled by default
    {IWIFICHIP_GET_DEBUG_RING_BUFFERS_STATUS_REQ,  &WifiChipMsgHandlerGetDebugRingBuffersStatus},
    {IWIFICHIP_START_LOGGING_TO_DEBUG_RING_BUFFER_REQ, &WifiChipMsgHandlerStartLoggingToDebugRingBuffer},
    {IWIFICHIP_FORCE_DUMP_TO_DEBUG_RING_BUFFER_REQ, &WifiChipMsgHandlerForceDumpToDebugRingBuffer},
    {IWIFICHIP_FLUSH_RING_BUFFER_TO_FILE_REQ, &WifiChipMsgHandlerFlushRingBufferToFile},
    {IWIFICHIP_STOP_LOGGING_TO_DEBUG_RING_BUFFER_REQ, &WifiChipMsgHandlerStopLoggingToDebugRingBuffer},
    {IWIFICHIP_GET_DEBUG_HOST_WAKE_REASON_STATS_REQ, &WifiChipMsgHandlerGetDebugHostWakeReasonStats},
    {IWIFICHIP_ENABLE_DEBUG_ERROR_ALERTS_REQ, &WifiChipMsgHandlerEnableDebugErrorAlerts},
#endif
    {IWIFICHIP_SELECT_TX_POWER_SCENARIO_REQ, &WifiChipMsgHandlerSelectTxPowerScenario},
    {IWIFICHIP_RESET_TX_POWER_SCENARIO_REQ, &WifiChipMsgHandlerResetTxPowerScenario},
    {IWIFICHIP_SET_LATENCY_MODE_REQ, &WifiChipMsgHandlerSetLatencyMode},
    {IWIFICHIP_SET_MULTI_STA_PRIMARY_CONNECTION_REQ, &WifiChipMsgHandlerSetMultiStaPrimaryConnection},
    {IWIFICHIP_SET_MULTI_STA_USE_CASE_REQ, &WifiChipMsgHandlerSetMultiStaUseCase},
    {IWIFICHIP_SET_COEX_UNSAFE_CHANNELS_REQ, &WifiChipMsgHandlerSetCoexUnsafeChannels},
    {IWIFICHIP_SET_COUNTRY_CODE_REQ, &WifiChipMsgHandlerSetCountryCode},
    {IWIFICHIP_GET_USABLE_CHANNELS_REQ, &WifiChipMsgHandlerGetUsableChannels},
    {IWIFICHIP_SET_AFC_CHANNEL_ALLOWANCE_REQ, &WifiChipMsgHandlerSetAfcChannelAllowance},
    {IWIFICHIP_TRIGGER_SUBSYSTEM_RESTART_REQ, &WifiChipMsgHandlerTriggerSubsystemRestart},
    {IWIFICHIP_GET_SUPPORTED_RADIO_COMBINATIONS_REQ, &WifiChipMsgHandlerGetSupportedRadioCombinations},
    {IWIFICHIP_GET_WIFI_CHIP_CAPABILITIES_REQ, &WifiChipMsgHandlerGetWifiChipCapabilities},
    {IWIFICHIP_ENABLE_STA_CHANNEL_FOR_PEER_NETWORK_REQ, &WifiChipMsgHandlerEnableStaChannelForPeerNetwork},
#ifdef ENABLE_DEBUG //disabled by default
    /* {IWIFICHIP_DUMP_REQ, &WifiChipMsgHandlerDump}, */
#endif
    {IWIFICHIP_SET_MLO_MODE_REQ, &WifiChipMsgHandlerSetMloMode},

    /* IWifiStaIface exported method handlers */
    {IWIFISTAIFACE_GET_NAME_REQ, &WifiStaIfaceMsgHandlerGetName},
    {IWIFISTAIFACE_GET_FEATURE_SET_REQ, &WifiStaIfaceMsgHandlerGetFeatureSet},
    {IWIFISTAIFACE_GET_APF_PACKET_FILTER_CAPABILITIES_REQ, &WifiStaIfaceMsgHandlerGetApfPacketFilterCapabilities},
    {IWIFISTAIFACE_INSTALL_APF_PACKET_FILTER_REQ, &WifiStaIfaceMsgHandlerInstallApfPacketFilter},
    {IWIFISTAIFACE_READ_APF_PACKET_FILTER_DATA_REQ, &WifiStaIfaceMsgHandlerReadApfPacketFilterData},
    {IWIFISTAIFACE_GET_BACKGROUND_SCAN_CAPABILITIES_REQ, &WifiStaIfaceMsgHandlerGetBackgroundScanCapabilities},
    {IWIFISTAIFACE_START_BACKGROUND_SCAN_REQ, &WifiStaIfaceMsgHandlerStartBackgroundScan},
    {IWIFISTAIFACE_STOP_BACKGROUND_SCAN_REQ, &WifiStaIfaceMsgHandlerStopBackgroundScan},
    {IWIFISTAIFACE_ENABLE_LINK_LAYER_STATS_COLLECTION_REQ, &WifiStaIfaceMsgHandlerEnableLinkLayerStatsCollection},
    {IWIFISTAIFACE_DISABLE_LINK_LAYER_STATS_COLLECTION_REQ, &WifiStaIfaceMsgHandlerDisableLinkLayerStatsCollection},
    {IWIFISTAIFACE_GET_LINK_LAYER_STATS_REQ, &WifiStaIfaceMsgHandlerGetLinkLayerStats},
    {IWIFISTAIFACE_START_RSSI_MONITORING_REQ, &WifiStaIfaceMsgHandlerStartRssiMonitoring},
    {IWIFISTAIFACE_STOP_RSSI_MONITORING_REQ, &WifiStaIfaceMsgHandlerStopRssiMonitoring},
    {IWIFISTAIFACE_GET_ROAMING_CAPABILITIES_REQ, &WifiStaIfaceMsgHandlerGetRoamingCapabilities},
    {IWIFISTAIFACE_CONFIGURE_ROAMING_REQ, &WifiStaIfaceMsgHandlerConfigureRoaming},
    {IWIFISTAIFACE_SET_ROAMING_STATE_REQ, &WifiStaIfaceMsgHandlerSetRoamingState},
    {IWIFISTAIFACE_ENABLE_ND_OFFLOAD_REQ, &WifiStaIfaceMsgHandlerEnableNdOffload},
    {IWIFISTAIFACE_START_SENDING_KEEP_ALIVE_PACKETS_REQ, &WifiStaIfaceMsgHandlerStartSendingKeepAlivePackets},
    {IWIFISTAIFACE_STOP_SENDING_KEEP_ALIVE_PACKETS_REQ, &WifiStaIfaceMsgHandlerStopSendingKeepAlivePackets},
#ifdef ENABLE_DEBUG //disabled by default
    {IWIFISTAIFACE_START_DEBUG_PACKET_FATE_MONITORING_REQ, &WifiStaIfaceMsgHandlerStartDebugPacketFateMonitoring},
    {IWIFISTAIFACE_GET_DEBUG_TX_PACKET_FATES_REQ, &WifiStaIfaceMsgHandlerGetDebugTxPacketFates},
    {IWIFISTAIFACE_GET_DEBUG_RX_PACKET_FATES_REQ, &WifiStaIfaceMsgHandlerGetDebugRxPacketFates},
#endif
    {IWIFISTAIFACE_SET_MAC_ADDRESS_REQ, &WifiStaIfaceMsgHandlerSetMacAddress},
    {IWIFISTAIFACE_GET_FACTORY_MAC_ADDRESS_REQ, &WifiStaIfaceMsgHandlerGetFactoryMacAddress},
    {IWIFISTAIFACE_SET_SCAN_MODE_REQ, &WifiStaIfaceMsgHandlerSetScanMode},
    {IWIFISTAIFACE_SET_DTIM_MULTIPLIER_REQ, &WifiStaIfaceMsgHandlerSetDtimMultiplier},

#ifdef SUPPORT_AP //disabled by default
    /* IWifiApIface exported method handlers */
    {IWIFIAPIFACE_GET_NAME_REQ, &WifiApIfaceMsgHandlerGetName},
    {IWIFIAPIFACE_SET_COUNTRY_CODE_REQ, &WifiApIfaceMsgHandlerSetCountryCode},
    {IWIFIAPIFACE_SET_MAC_ADDRESS_REQ, &WifiApIfaceMsgHandlerSetMacAddress},
    {IWIFIAPIFACE_GET_FACTORY_MAC_ADDRESS_REQ, &WifiApIfaceMsgHandlerGetFactoryMacAddress},
    {IWIFIAPIFACE_RESET_TO_FACTORY_MAC_ADDRESS_REQ, &WifiApIfaceMsgHandlerResetToFactoryMacAddress},
    {IWIFIAPIFACE_GET_BRIDGED_INSTANCE_REQ, &WifiApIfaceMsgHandlerGetBridgedInstances},
#endif

    {}
};

static inline MessageHandler WifiHalGetMessageHandler(uint16_t methodId)
{
    auto item = msgHandlerMap.find(methodId);
    if (item != msgHandlerMap.end())
        return item->second;

    return nullptr;
}

#ifdef ENABLE_DATA_DUMP
static void WifiHalDumpData(const char* description, uint16_t id, uint8_t *data, size_t length)
{
    LOG(INFO) << "Dump Data for " << description
              << " ID = 0x " << std::hex << id
              << " length = 0x " << std::hex << length;

    if (!data) return;

    for (int i = 0; i < length; i++) {
        printf("%02x ", data[i]);
        if ((i & 0xf) == 0xf)
            printf("\n");
    }
    printf("\n");
    LOG(INFO) << "Dump Data Completed";
}
#endif

void WifiHalProcessSomeIPRequestMessage(uint16_t methodId, uint8_t *data, size_t length)
{
    LOG(INFO) << "Recv Someip Request message with method_id 0x" << std::hex << methodId;

#ifdef ENABLE_DATA_DUMP
    WifiHalDumpData("SomeIP Request", methodId, data, length);
#endif

    MessageHandler handler = WifiHalGetMessageHandler(methodId);
    if (!handler) {
        LOG(ERROR) << "Unspported SomeIP request method id 0x" << std::hex << methodId;
	return;
    }

    std::vector<uint8_t> response;
    bool ret = handler(data, length, response);
    if (!ret) {
        LOG(ERROR) << "Process SomeIP Request fail.";
	return;
    }

#ifdef ENABLE_DATA_DUMP
    WifiHalDumpData("SomeIP Response", methodId, response.data(), response.size());
#endif
    ret = someip_send_response_msg(methodId, response.data(), response.size());
    if (!ret)
        LOG(ERROR) << "Send SomeIP Response fail.";
}
