/*
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef WIFI_RPC_MESSAGE_H
#define WIFI_RPC_MESSAGE_H

#include <rpc/util/someip_util.h>

using qti::hal::rpc::SomeipMessage;

void WifiRpcProcessSomeIPRequestMessage(
    const std::shared_ptr<SomeipMessage> &msg);

bool someip_send_message(std::shared_ptr<SomeipMessage> message);

#endif /* WIFI_RPC_MESSAGE_H */
