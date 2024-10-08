/*
 * Copyright (c) 2023, 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <thread>

#include <rpc/util/log_common.h>
#include <rpc/util/properties.h>
#include <rpc/util/someip_server.h>

#include <wifi_message_def.h>

#include "wifi_rpc_event.h"
#include "wifi_rpc_message.h"
#include "wifi_rpc_server.h"

#define WIFI_HAL_INSTANCE_ID_CHM                           ((uint16_t) 0x1110)
#define WIFI_HAL_INSTANCE_ID_CEM                           ((uint16_t) 0x1111)
#define WIFI_HAL_EVENTGROUP_ID                             ((uint16_t) 0xAAA0)

using qti::hal::rpc::SomeipContext;
using qti::hal::rpc::SomeipCallback;
using qti::hal::rpc::SomeipMessage;
using qti::hal::rpc::Someip;
using qti::hal::rpc::SomeipServer;

std::string WIFI_HAL_SERVICE_NAME = "wifihal_someip_service";
std::shared_ptr<SomeipServer> wifihal_someip_server;

bool WifiRpcInitSomeipService()
{
    uint16_t wifirpc_instance_id;
    std::array<char, PROPERTY_VALUE_MAX> someip_config_file;
    property_get("persist.vendor.someip.config_file", someip_config_file.data(), "/etc/someip/vsomeip_server.json");
    if(strstr(someip_config_file.data(), "cem")){
        wifirpc_instance_id = WIFI_HAL_INSTANCE_ID_CEM;
    }else{
        wifirpc_instance_id = WIFI_HAL_INSTANCE_ID_CHM;
    }
    SomeipContext context(WIFI_HAL_SERVICE_ID, wifirpc_instance_id,
        WIFI_HAL_EVENTGROUP_ID, wifiRpcEventArray);
    SomeipCallback cb(nullptr,
                      WifiRpcProcessSomeIPRequestMessage);

    Someip::setup(cb);
    wifihal_someip_server = std::make_shared<SomeipServer>(WIFI_HAL_SERVICE_NAME, context);

    ALOGI("Wifi-Hal someip service is initialized");

    return true;
}

void WifiRpcDeinitSomeipService()
{
    if (!wifihal_someip_server)
        return;

    ALOGI("Wifi-Hal someip service deinit...");
    wifihal_someip_server = nullptr;
}

bool WifiRpcStartSomeipService()
{
    ALOGI("Wifi-Hal someip service loop starting...");
    wifihal_someip_server->start();

    return true;
}

void WifiRpcStopSomeipService()
{
    if (!wifihal_someip_server)
        return;

    ALOGI("Wifi-Hal someip service main loop stop...");
    wifihal_someip_server->stop();
}

bool someip_send_event(uint16_t method_id, std::vector<uint8_t> &data)
{
    if (!wifihal_someip_server)
        return false;
    return wifihal_someip_server->sendEvent(method_id, data);
}

bool someip_send_message(std::shared_ptr<SomeipMessage> message)
{
    if (!wifihal_someip_server)
        return false;
    return wifihal_someip_server->sendMessage(message);
}
