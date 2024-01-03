/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#ifndef SCOPEDSTATUS_H
#define SCOPEDSTATUS_H

#include "aidl/android/hardware/wifi/WifiStatusCode.h"

namespace ndk {
using aidl::android::hardware::wifi::WifiStatusCode;
using aidl::android::hardware::wifi::WifiStatus;
class ScopedAStatus : public WifiStatus {
public:
    ScopedAStatus() : WifiStatus() {}
    ScopedAStatus(WifiStatusCode code) : WifiStatus(code) {}
    ScopedAStatus(const WifiStatusCode code, const std::string &desc)
        : WifiStatus(code, desc) {}
    ScopedAStatus(int32_t code, const char* desc)
        : WifiStatus(WifiStatusCode(code), desc) {}

    static ScopedAStatus ok() {
        return ScopedAStatus();
    }

    static ScopedAStatus fail(WifiStatusCode failCode) {
        return ScopedAStatus(failCode);
    }

    bool isOk() {
        return code == WifiStatusCode::SUCCESS;
    }

    static ScopedAStatus fromServiceSpecificError(int32_t code) {
        return ScopedAStatus(code, "");
    }

    static ScopedAStatus fromServiceSpecificErrorWithMessage(
        int32_t code, const char* description) {
        return ScopedAStatus(code, description);
    }

    WifiStatusCode getServiceSpecificError() {
        return code;
    }
};
} /* ndk */

/* Alias name from auto generated paramter structure */
using binder_status_t = ndk::ScopedAStatus;

/* Create default WifiStatus Success state */
#define STATUS_OK (ndk::ScopedAStatus::ok())

#endif /* SCOPEDSTATUS_H */
