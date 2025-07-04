/*
 * Copyright (C) 2023 The Android Open Source Project
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
 */

#include <cmath>
#include <limits>

#define LOG_TAG "AHAL_StreamAlsa"
#include <android-base/logging.h>
#include <system/audio.h>
#include <hardware/audio_alsaops.h>
#include <cutils/properties.h>

#include <Utils.h>
#include <audio_utils/clock.h>
#include <error/expected_utils.h>

#include "core-impl/StreamAlsa.h"

namespace aidl::android::hardware::audio::core {

StreamAlsa::StreamAlsa(StreamContext* context, const Metadata& metadata, int readWriteRetries)
    : StreamCommonImpl(context, metadata),
      mBufferSizeFrames(getContext().getBufferSizeInFrames()),
      mFrameSizeBytes(getContext().getFrameSize()),
      mSampleRate(getContext().getSampleRate()),
      mIsInput(isInput(metadata)),
      mConfig(alsa::getPcmConfig(getContext(), mIsInput)),
      mReadWriteRetries(readWriteRetries) {}

::android::status_t StreamAlsa::init() {
    return mConfig.has_value() ? ::android::OK : ::android::NO_INIT;
}

::android::status_t StreamAlsa::drain(StreamDescriptor::DrainMode) {
    if (!mIsInput) {
        static constexpr float kMicrosPerSecond = MICROS_PER_SECOND;
        const size_t delayUs = static_cast<size_t>(
                std::roundf(mBufferSizeFrames * kMicrosPerSecond / mSampleRate));
        usleep(delayUs);
    }
    return ::android::OK;
}

::android::status_t StreamAlsa::flush() {
    return ::android::OK;
}

::android::status_t StreamAlsa::pause() {
    return ::android::OK;
}

::android::status_t StreamAlsa::standby() {
    mAlsaDeviceProxies.clear();
    return ::android::OK;
}

::android::status_t StreamAlsa::start() {
    if (!mAlsaDeviceProxies.empty()) {
        // This is a resume after a pause.
        return ::android::OK;
    }
    decltype(mAlsaDeviceProxies) alsaDeviceProxies;
    for (const auto& device : getDeviceProfiles()) {
        alsa::DeviceProxy proxy;
        if (device.isExternal) {
            // Always ask alsa configure as required since the configuration should be supported
            // by the connected device. That is guaranteed by `setAudioPortConfig` and
            // `setAudioPatch`.
            proxy = alsa::openProxyForExternalDevice(
                    device, const_cast<struct pcm_config*>(&mConfig.value()),
                    true /*require_exact_match*/);
        } else {
            proxy = alsa::openProxyForAttachedDevice(
                    device, const_cast<struct pcm_config*>(&mConfig.value()), mBufferSizeFrames);
        }
        if (proxy.get() == nullptr) {
            return ::android::NO_INIT;
        }
        alsaDeviceProxies.push_back(std::move(proxy));
    }
    mAlsaDeviceProxies = std::move(alsaDeviceProxies);
    return ::android::OK;
}

size_t StreamAlsa::split_audio_haptic_data(void* buffer, size_t bytesToTransfer)
{
    size_t bytes_per_sample = audio_bytes_per_sample(audio_format_from_pcm_format(mConfig->format));
    size_t frame_size = mConfig->channels * bytes_per_sample;
    size_t frame_count = bytesToTransfer / frame_size;
    // To be removed the haptic channel hardcoding
    int    haptic_channel_count = 2;

    size_t haptic_frame_size = bytes_per_sample * haptic_channel_count;
    size_t audio_frame_size = frame_size - haptic_frame_size;
    size_t total_haptic_buffer_size = frame_count * haptic_frame_size;
    if (mHaptic_Buffer == NULL) {
        mHaptic_Buffer = (uint8_t *)calloc(1, total_haptic_buffer_size);
        if(mHaptic_Buffer == NULL) {
           LOG(ERROR) << __func__ << ": mHaptic_Buffer is null";
           return -1;
        }
    }

    size_t src_index = 0, aud_index = 0, hap_index = 0;
    uint8_t *audio_buffer = (uint8_t *)buffer;
    uint8_t *haptic_buffer  = (uint8_t *)mHaptic_Buffer;
    for (size_t i = 0; i < frame_count; i++) {
        memcpy(audio_buffer + aud_index, audio_buffer + src_index,
               audio_frame_size);
        aud_index += audio_frame_size;
        src_index += audio_frame_size;
        memcpy(haptic_buffer + hap_index, audio_buffer + src_index,
                haptic_frame_size);
        hap_index += haptic_frame_size;
        src_index += haptic_frame_size;
    }
    mHaptic_Buffer_Size = frame_count * haptic_frame_size;
    return frame_count * audio_frame_size;
}

::android::status_t StreamAlsa::transfer(void* buffer, size_t frameCount, size_t* actualFrameCount,
                                         int32_t* latencyMs) {
    if (mAlsaDeviceProxies.empty()) {
        LOG(FATAL) << __func__ << ": no opened devices";
        return ::android::NO_INIT;
    }
    const size_t bytesToTransfer = frameCount * mFrameSizeBytes;
    unsigned maxLatency = 0;
    if (mIsInput) {
        // For input case, only support single device.
        proxy_read_with_retries(mAlsaDeviceProxies[0].get(), buffer, bytesToTransfer,
                                mReadWriteRetries);
        maxLatency = proxy_get_latency(mAlsaDeviceProxies[0].get());
    } else {
        if (property_get_bool("vendor.audio.gaming.enabled", false /* default_value */)) {
            size_t contracted_audio_bytes = 0;
            int num_write_buff_bytes = 0;
            contracted_audio_bytes = split_audio_haptic_data(buffer, bytesToTransfer);
            for( auto& proxy : mAlsaDeviceProxies) {
                void * write_buff = buffer;
                size_t writeBytes =  bytesToTransfer;
                if (proxy.get()->profile->card == USB_DEVICE_TYPE::HAPTIC) {
                    num_write_buff_bytes = mHaptic_Buffer_Size;
                    write_buff = mHaptic_Buffer;
                } else if (proxy.get()->profile->card == USB_DEVICE_TYPE::AUDIO) {
                    num_write_buff_bytes = contracted_audio_bytes;
                }
                proxy_write_with_retries(proxy.get(), write_buff, num_write_buff_bytes, mReadWriteRetries);
                maxLatency = std::max(maxLatency, proxy_get_latency(proxy.get()));
            }
        } else {
            for( auto& proxy : mAlsaDeviceProxies) {
                proxy_write_with_retries(proxy.get(), buffer, bytesToTransfer, mReadWriteRetries);
                maxLatency = std::max(maxLatency, proxy_get_latency(proxy.get()));
            }
        }
    }
    *actualFrameCount = frameCount;
    maxLatency = std::min(maxLatency, static_cast<unsigned>(std::numeric_limits<int32_t>::max()));
    *latencyMs = maxLatency;
    return ::android::OK;
}

::android::status_t StreamAlsa::refinePosition(StreamDescriptor::Position* position) {
    if (mAlsaDeviceProxies.empty()) {
        LOG(WARNING) << __func__ << ": no opened devices";
        return ::android::NO_INIT;
    }
    // Since the proxy can only count transferred frames since its creation,
    // we override its counter value with ours and let it to correct for buffered frames.
    if (property_get_bool("vendor.audio.gaming.enabled", false /* default_value */)) {
        // To update positin from Audio device as HAPTIC is registered at first
        for( auto& proxy : mAlsaDeviceProxies) {
            if (proxy.get()->profile->card == USB_DEVICE_TYPE::AUDIO) {
                alsa::resetTransferredFrames(proxy, position->frames);
            }
        }
    } else {
        alsa::resetTransferredFrames(mAlsaDeviceProxies[0], position->frames);
    }
    if (mIsInput) {
        if (property_get_bool("vendor.audio.gaming.enabled", false /* default_value */)) {
            // To update positin from Audio device as HAPTIC is registered at first
            for( auto& proxy : mAlsaDeviceProxies) {
                if (proxy.get()->profile->card == USB_DEVICE_TYPE::AUDIO) {
                    if (int ret = proxy_get_capture_position(proxy.get(), &position->frames,
                                                             &position->timeNs);
                        ret != 0) {
                        LOG(WARNING) << __func__ << ": failed to retrieve capture position: " << ret;
                        return ::android::INVALID_OPERATION;
                    }
                }
            }
        } else {
            if (int ret = proxy_get_capture_position(mAlsaDeviceProxies[0].get(), &position->frames,
                                                     &position->timeNs);
                ret != 0) {
                LOG(WARNING) << __func__ << ": failed to retrieve capture position: " << ret;
                return ::android::INVALID_OPERATION;
            }
        }
    } else {
        uint64_t hwFrames;
        struct timespec timestamp;
        if (property_get_bool("vendor.audio.gaming.enabled", false /* default_value */)) {
            // To update positin from Audio device as HAPTIC is registered at first
            for( auto& proxy : mAlsaDeviceProxies) {
                if (proxy.get()->profile->card == USB_DEVICE_TYPE::AUDIO) {
                    if (int ret = proxy_get_presentation_position(proxy.get(), &hwFrames,
                                                                  &timestamp);
                        ret == 0) {
                        if (hwFrames > std::numeric_limits<int64_t>::max()) {
                            hwFrames -= std::numeric_limits<int64_t>::max();
                        }
                        position->frames = static_cast<int64_t>(hwFrames);
                        position->timeNs = audio_utils_ns_from_timespec(&timestamp);
                    } else {
                        LOG(WARNING) << __func__ << ": failed to retrieve presentation position: " << ret;
                        return ::android::INVALID_OPERATION;
                    }
                }
            }
        } else {
            if (int ret = proxy_get_presentation_position(mAlsaDeviceProxies[0].get(), &hwFrames,
                                                          &timestamp);
                ret == 0) {
                if (hwFrames > std::numeric_limits<int64_t>::max()) {
                    hwFrames -= std::numeric_limits<int64_t>::max();
                }
                position->frames = static_cast<int64_t>(hwFrames);
                position->timeNs = audio_utils_ns_from_timespec(&timestamp);
            } else {
                LOG(WARNING) << __func__ << ": failed to retrieve presentation position: " << ret;
                return ::android::INVALID_OPERATION;
            }
        }
    }
    return ::android::OK;
}

void StreamAlsa::shutdown() {
    mAlsaDeviceProxies.clear();
    free(mHaptic_Buffer);
    mHaptic_Buffer = NULL;
    mHaptic_Buffer_Size = 0;
}

}  // namespace aidl::android::hardware::audio::core
