/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef WIFI_HAL_SOMEIP_SERVER_H
#define WIFI_HAL_SOMEIP_SERVER_H

bool WifiHalSomeIPServerInit();
void WifiHalSomeIPServerDeinit();

bool WifiHalSomeIPServerStart();
void WifiHalSomeIPServerStop();

#endif /* WIFI_HAL_SOMEIP_SERVER_H */
