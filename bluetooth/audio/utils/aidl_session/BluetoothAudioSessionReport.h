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

#pragma once

#include "BluetoothAudioSession.h"

namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace audio {

class BluetoothAudioSessionReport {
 public:
  /***
   * The API reports the Bluetooth stack has started the session, and will
   * inform registered bluetooth_audio outputs
   ***/
  static void OnSessionStarted(
      const SessionType& session_type,
      const std::shared_ptr<IBluetoothAudioPort> host_iface,
      const DataMQDesc* data_mq, const AudioConfiguration& audio_config,
      const std::vector<LatencyMode>& latency_modes,
      uint8_t index = 0) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type, index);
    if (session_ptr != nullptr) {
      session_ptr->OnSessionStarted(host_iface, data_mq, audio_config,
                                    latency_modes);
    }
  }

  /***
   * The API reports the Bluetooth stack has ended the session, and will
   * inform registered bluetooth_audio outputs
   ***/
  static void OnSessionEnded(const SessionType& session_type, uint8_t index = 0) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type, index);
    if (session_ptr != nullptr) {
      session_ptr->OnSessionEnded();
    }
  }

  /***
   * The API reports the Bluetooth stack has replied the result of startStream
   * or suspendStream, and will inform registered bluetooth_audio outputs
   ***/
  static void ReportControlStatus(const SessionType& session_type,
                                  const bool& start_resp,
                                  BluetoothAudioStatus status,
                                  uint8_t index = 0) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type, index);
    if (session_ptr != nullptr) {
      session_ptr->ReportControlStatus(start_resp, status);
    }
  }
  /***
   * The API reports the Bluetooth stack has replied the changed of the audio
   * configuration, and will inform registered bluetooth_audio outputs
   ***/
  static void ReportAudioConfigChanged(const SessionType& session_type,
                                       const AudioConfiguration& audio_config,
                                       uint8_t index = 0) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type, index);
    if (session_ptr != nullptr) {
      session_ptr->ReportAudioConfigChanged(audio_config);
    }
  }
  /***
   * The API reports the Bluetooth stack has replied the changed of the low
   * latency audio allowed, and will inform registered bluetooth_audio outputs
   ***/
  static void ReportLowLatencyModeAllowedChanged(
    const SessionType& session_type, bool allowed,
    uint8_t index = 0) {
    std::shared_ptr<BluetoothAudioSession> session_ptr =
        BluetoothAudioSessionInstance::GetSessionInstance(session_type, index);
    if (session_ptr != nullptr) {
      session_ptr->ReportLowLatencyModeAllowedChanged(allowed);
    }
  }
};

}  // namespace audio
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
