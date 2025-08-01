/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Changes from Qualcomm Technologies, Inc. are provided under the following license:
 *
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#define LOG_TAG "BtAudioAIDLService"

#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <utils/Log.h>

#include "BluetoothAudioProviderFactory.h"

using ::aidl::android::hardware::bluetooth::audio::
    BluetoothAudioProviderFactory;

static constexpr uint8_t kMaxA2dpConn = 2;

static std::string getInstanceName(uint8_t index) {
  return std::string() + BluetoothAudioProviderFactory::descriptor +
         (index == 0 ? "/default" : "/new");
}

binder_status_t createIBluetoothAudioProviderFactoryInternal(uint8_t index) {
  auto factory = ::ndk::SharedRefBase::make<BluetoothAudioProviderFactory>(index);
  const std::string instance_name = getInstanceName(index);
  ALOGW("%s: instance_name %s", __func__, instance_name.c_str());
  binder_status_t aidl_status = AServiceManager_addService(
      factory->asBinder().get(), instance_name.c_str());
  ALOGW_IF(aidl_status != STATUS_OK, "Could not register %s, status=%d",
           instance_name.c_str(), aidl_status);
  return aidl_status;
}

extern "C" __attribute__((visibility("default"))) binder_status_t
createIBluetoothAudioProviderFactory() {
  binder_status_t final_aidl_status = STATUS_OK;
  for (uint8_t i = 0; i < kMaxA2dpConn; i++) {
    binder_status_t status = createIBluetoothAudioProviderFactoryInternal(i);
    if (final_aidl_status == STATUS_OK && status != STATUS_OK) {
      final_aidl_status = status;
    }
  }
  return final_aidl_status;
}
