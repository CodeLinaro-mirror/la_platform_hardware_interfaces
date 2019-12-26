/*
 * Copyright (C) 2019 The Android Open Source Project
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

#include <cstddef>
#include <iostream>
#include <limits>
#include <random>

#include <android-base/logging.h>
#include <android-base/macros.h>
#include <private/android_filesystem_config.h>

#undef NAN
#include "wifi_iface_util.h"

namespace {
// Constants to set the local bit & clear the multicast bit.
constexpr uint8_t kMacAddressMulticastMask = 0x01;
constexpr uint8_t kMacAddressLocallyAssignedMask = 0x02;
}  // namespace

namespace android {
namespace hardware {
namespace wifi {
namespace V1_3 {
namespace implementation {
namespace iface_util {

WifiIfaceUtil::WifiIfaceUtil(
    const std::weak_ptr<wifi_system::InterfaceTool> iface_tool)
    : iface_tool_(iface_tool),
      random_mac_address_(nullptr),
      event_handlers_map_() {

    LOG(INFO) << "bridge_tool_ initialized";
    bridge_tool_ = std::make_shared<android::wifi_system::BridgeTool>();
}

std::array<uint8_t, 6> WifiIfaceUtil::getFactoryMacAddress(
    const std::string& iface_name) {
    return iface_tool_.lock()->GetFactoryMacAddress(iface_name.c_str());
}

bool WifiIfaceUtil::setMacAddress(const std::string& iface_name,
                                  const std::array<uint8_t, 6>& mac) {
    if (!iface_tool_.lock()->SetUpState(iface_name.c_str(), false)) {
        LOG(ERROR) << "SetUpState(false) failed.";
        return false;
    }
    if (!iface_tool_.lock()->SetMacAddress(iface_name.c_str(), mac)) {
        LOG(ERROR) << "SetMacAddress failed.";
        return false;
    }
    if (!iface_tool_.lock()->SetUpState(iface_name.c_str(), true)) {
        LOG(ERROR) << "SetUpState(true) failed.";
        return false;
    }
    IfaceEventHandlers event_handlers = {};
    const auto it = event_handlers_map_.find(iface_name);
    if (it != event_handlers_map_.end()) {
        event_handlers = it->second;
    }
    if (event_handlers.on_state_toggle_off_on != nullptr) {
        event_handlers.on_state_toggle_off_on(iface_name);
    }
    LOG(DEBUG) << "Successfully SetMacAddress.";
    return true;
}

std::array<uint8_t, 6> WifiIfaceUtil::getOrCreateRandomMacAddress() {
    if (random_mac_address_) {
        return *random_mac_address_.get();
    }
    random_mac_address_ =
        std::make_unique<std::array<uint8_t, 6>>(createRandomMacAddress());
    return *random_mac_address_.get();
}

void WifiIfaceUtil::registerIfaceEventHandlers(const std::string& iface_name,
                                               IfaceEventHandlers handlers) {
    event_handlers_map_[iface_name] = handlers;
}

void WifiIfaceUtil::unregisterIfaceEventHandlers(
    const std::string& iface_name) {
    event_handlers_map_.erase(iface_name);
}

std::array<uint8_t, 6> WifiIfaceUtil::createRandomMacAddress() {
    std::array<uint8_t, 6> address = {};
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<uint8_t> dist(
        std::numeric_limits<uint8_t>::min(),
        std::numeric_limits<uint8_t>::max());
    for (size_t i = 0; i < address.size(); i++) {
        address[i] = dist(engine);
    }
    // Set the local bit and clear the multicast bit.
    address[0] |= kMacAddressLocallyAssignedMask;
    address[0] &= ~kMacAddressMulticastMask;
    return address;
}

bool WifiIfaceUtil::createBridge(const std::string& br_name) {
    if (bridge_tool_ == nullptr) {
        LOG(ERROR) << "bridge_tool_ is null";
        return false;
    }

    if (!bridge_tool_->createBridge(br_name)) {
        return false;
    }

    if (!iface_tool_.lock()->SetUpState(br_name.c_str(), true)) {
        LOG(INFO) << "bridge SetUpState(true) failed.";
    }

    return true;
}

bool WifiIfaceUtil::deleteBridge(const std::string& br_name) {
    if (bridge_tool_ == nullptr) {
        LOG(ERROR) << "bridge_tool_ is null";
        return false;
    }

    if (!iface_tool_.lock()->SetUpState(br_name.c_str(), false)) {
        LOG(INFO) << "SetUpState(false) failed for bridge=" << br_name.c_str();
    }

    return bridge_tool_->deleteBridge(br_name);
}

bool WifiIfaceUtil::addIfaceToBridge(const std::string& br_name, const std::string& if_name) {
    if (bridge_tool_ == nullptr) {
        LOG(ERROR) << "bridge_tool_ is null";
        return false;
    }

    return bridge_tool_->addIfaceToBridge(br_name, if_name);
}

bool WifiIfaceUtil::removeIfaceFromBridge(const std::string& br_name, const std::string& if_name) {
    if (bridge_tool_ == nullptr) {
        LOG(ERROR) << "bridge_tool_ is null";
        return false;
    }

    return bridge_tool_->removeIfaceFromBridge(br_name, if_name);
}

bool WifiIfaceUtil::GetInterfacesInBridge(std::string br_name,
                           std::vector<std::string>* interfaces) {
    if (bridge_tool_ == nullptr) {
        LOG(ERROR) << "bridge_tool_ is null";
        return false;
    }

    return bridge_tool_->GetInterfacesInBridge(br_name, interfaces);
}

}  // namespace iface_util
}  // namespace implementation
}  // namespace V1_3
}  // namespace wifi
}  // namespace hardware
}  // namespace android
