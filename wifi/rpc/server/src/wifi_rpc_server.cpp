/*
 * Copyright (c) 2023, 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <iostream>
#include <thread>

#include <someip_api.h>
#include <someip_common_def.h>
#include <utils/Log.h>
#include <wifi_someip_def.h>

#include "wifi_rpc_event.h"
#include "wifi_rpc_message.h"
#include "wifi_rpc_server.h"

#define WIFI_HAL_INSTANCE_ID ((uint16_t) 0x1110)
#define WIFI_HAL_EVENTGROUP_ID ((uint16_t) 0xAAA0)
#define MAX_SOMEIP_START_TIMEOUT_IN_SEC 60
static char WIFI_HAL_SERVICE_NAME[] = "wifihal_someip_service";

static SomeipRegisterInfo serviceInfo;
bool WifiRpcInitSomeipService()
{
    serviceInfo.context.app_name = WIFI_HAL_SERVICE_NAME;
    serviceInfo.context.service_id = WIFI_HAL_SERVICE_ID;
    serviceInfo.context.service_instance_id = WIFI_HAL_INSTANCE_ID;

    serviceInfo.context.eventgroup_id = WIFI_HAL_EVENTGROUP_ID;
    serviceInfo.context.event_id_number = WIFI_HAL_SUPPORTED_EVENT_COUNT;
    serviceInfo.context.event_id = wifiRpcEventArray;

    serviceInfo.dataCallback = &WifiRpcProcessSomeIPRequestMessage;

    bool ret = someip_init(&serviceInfo);
    ALOGI("Wifi Hal Someip service initialize %s.", ret ? "success" : "fail");

    return ret;
}

void WifiRpcDeinitSomeipService()
{
    ALOGI("WiFi hal someip service deinit...");

    someip_deinit();
}

bool WifiRpcStartSomeipService()
{
    uint32_t timeoutInSec = 1, totalTimeout = 0;

    ALOGI("WiFi hal someip service main loop start...");

    while (true) {
        if (someip_open())
            break;

        ALOGE("Failed to start SomeIP Client.");
        /* Start someip every 1 second, until timeout occurs */
        if (totalTimeout < MAX_SOMEIP_START_TIMEOUT_IN_SEC) {
            sleep(timeoutInSec);
            totalTimeout += timeoutInSec;
        } else {
            ALOGE("fail to start someip in %d sec", totalTimeout);
            break;
        }
    }

    return true;
}

void WifiRpcStopSomeipService()
{
    ALOGI("WiFi hal someip service main loop stop...");
    someip_close();
    someip_deinit();
}
