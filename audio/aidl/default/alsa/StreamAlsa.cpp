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
      mHapticsChannelCount(alsa::getHapticsChannelCount(getContext())),
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

::android::status_t StreamAlsa::splitAndWriteAudioHapticsStream(void* buffer, size_t frameCount, int32_t* latencyMs)
{
    bool allocHapticsBuffer = false;

    uint8_t bytesPerSample = audio_bytes_per_sample(audio_format_from_pcm_format(mConfig->format));
    size_t frameSize = mConfig->channels * bytesPerSample;

    uint32_t hapticsFrameSize = bytesPerSample * mHapticsChannelCount;
    uint32_t audioFrameSize = frameSize - hapticsFrameSize;
    uint32_t totalHapticsBufferSize = frameCount * hapticsFrameSize;

    if (!mHapticsBuffer) {
        allocHapticsBuffer = true;
    } else if (mHapticsBufSize < totalHapticsBufferSize) {
        allocHapticsBuffer = true;
        mHapticsBufSize = 0;
    }

    if (allocHapticsBuffer) {
        mHapticsBuffer = std::make_unique<uint8_t[]>(totalHapticsBufferSize);
        if(!mHapticsBuffer) {
            LOG(ERROR) << __func__ << ": Failed to allocate haptic buffer";
            return -ENOMEM;
        }
        mHapticsBufSize = totalHapticsBufferSize;
    }

    size_t srcIndex = 0, audIndex = 0, hapIndex = 0;
    uint8_t *audioBuffer = (uint8_t *)buffer;
    uint8_t *hapticsBuffer  = reinterpret_cast<uint8_t*>(mHapticsBuffer.get());;

    for (size_t i = 0; i < frameCount; i++) {
        memcpy((uint8_t *)(audioBuffer) + audIndex, (uint8_t *)(audioBuffer) + srcIndex,
            audioFrameSize);
        audIndex += audioFrameSize;
        srcIndex += audioFrameSize;

        memcpy((uint8_t *)(hapticsBuffer) + hapIndex, (uint8_t *)(audioBuffer) + srcIndex,
            hapticsFrameSize);
        hapIndex += hapticsFrameSize;
        srcIndex += hapticsFrameSize;
    }

    for( auto& proxy : mAlsaDeviceProxies) {
        size_t bytesToTransfer  =  0;
        unsigned maxLatency = 0;
        if (proxy.get()->profile->card == USB_DEVICE_TYPE::HAPTIC) {
            bytesToTransfer = frameCount * hapticsFrameSize;
            proxy_write_with_retries(proxy.get(), hapticsBuffer, bytesToTransfer, mReadWriteRetries);
        } else if (proxy.get()->profile->card == USB_DEVICE_TYPE::AUDIO) {
            bytesToTransfer = frameCount * audioFrameSize;
            proxy_write_with_retries(proxy.get(), audioBuffer, bytesToTransfer, mReadWriteRetries);
        }
        *latencyMs = std::max(maxLatency, proxy_get_latency(proxy.get()));
    }
    return ::android::OK;
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
            ::android::status_t status = splitAndWriteAudioHapticsStream(buffer, frameCount, latencyMs);
            if (status < 0) {
                LOG(ERROR) << __func__ << ": write failed, ret: " << status;
                std::this_thread::sleep_for(std::chrono::milliseconds((frameCount * 1000) / 48000/* hardcoded device sample rate*/));
            }
            maxLatency = *latencyMs;
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
    if (mHapticsBuffer) {
        mHapticsBuffer = nullptr;
    }
    mHapticsBufSize = 0;
}

}  // namespace aidl::android::hardware::audio::core
