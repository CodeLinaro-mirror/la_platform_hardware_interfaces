/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef WIFI_RPC_MESSAGE_H
#define WIFI_RPC_MESSAGE_H

void WifiRpcProcessSomeIPRequestMessage(
    uint16_t methodId, uint8_t *data, size_t length);

#endif /* WIFI_RPC_MESSAGE_H */
