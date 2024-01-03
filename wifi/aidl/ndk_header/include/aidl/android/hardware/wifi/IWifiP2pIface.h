/*
 * Changes from Qualcomm Innovation Center, Inc. are provided under the following license:
 * Copyright (c) 2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {

class IWifiP2pIface : public ::ndk::ICInterface {
public:
  virtual ::ndk::ScopedAStatus getName(std::string* _aidl_return) = 0;
};

}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
