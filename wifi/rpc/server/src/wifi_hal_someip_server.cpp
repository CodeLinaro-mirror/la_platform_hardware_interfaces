/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#include <iostream>
#include <thread>
#include <android-base/logging.h>

#include <util/someip_api.h>
#include <util/someip_common_def.h>

#include "wifi_hal_someip_server.h"
#include "wifi_hal_message_handler.h"
#include "wifi_hal_event_callback.h"
#include "wifi_someip_def.h"

static char WIFI_HAL_SERVICE_NAME[] = "wifihal_someip_service";

static void WifiHalInitSomeIPRegisterInfo(SomeipRegisterInfo* info)
{
    info->context.app_name = WIFI_HAL_SERVICE_NAME;
    info->context.service_id = WIFI_HAL_SERVICE_ID;
    info->context.service_instance_id = WIFI_HAL_INSTANCE_ID;

    info->context.eventgroup_id = WIFI_HAL_EVENTGROUP_ID;
    info->context.event_id_number = WIFI_HAL_SUPPORTED_EVENT_COUNT;
    info->context.event_id = wifiHalEventArray;

    info->dataCallback = &WifiHalProcessSomeIPRequestMessage;
}

bool WifiHalSomeIPServerInit()
{
    SomeipRegisterInfo registerInfo;
    WifiHalInitSomeIPRegisterInfo(&registerInfo);

    LOG(INFO) << "WiFi hal someip service init...";

    uint8_t retryCount = 0;
    while (true) {
        retryCount++;
	if (someip_init(&registerInfo)) {
            LOG(INFO) << "WiFi hal someip service app init successful";
            break;
        }

        if (retryCount > 20) {
            LOG(ERROR) << "WiFi hal Someip service init fail";
            return -1;
        }

        usleep(1000);
    }

    return true;
}

void WifiHalSomeIPServerDeinit()
{
    LOG(INFO) << "WiFi hal someip service deinit...";

    someip_deinit();
}

bool WifiHalSomeIPServerStart()
{
    LOG(INFO) << "WiFi hal someip service main loop start...";
    return someip_open();
}

void WifiHalSomeIPServerStop()
{
    LOG(INFO) << "WiFi hal someip service main loop stop...";
    someip_deinit();
}
