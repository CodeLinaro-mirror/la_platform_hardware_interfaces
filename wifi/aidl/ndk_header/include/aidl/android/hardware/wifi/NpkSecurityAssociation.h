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
#include <aidl/android/hardware/wifi/NanCipherSuiteType.h>
#include <aidl/android/hardware/wifi/NanPairingAkm.h>

namespace aidl {
namespace android {
namespace hardware {
namespace wifi {
class NpkSecurityAssociation {
public:
  std::array<uint8_t, 16> peerNanIdentityKey = {{}};
  std::array<uint8_t, 16> localNanIdentityKey = {{}};
  std::array<uint8_t, 32> npk = {{}};
  ::aidl::android::hardware::wifi::NanPairingAkm akm = ::aidl::android::hardware::wifi::NanPairingAkm(0);
  ::aidl::android::hardware::wifi::NanCipherSuiteType cipherType = ::aidl::android::hardware::wifi::NanCipherSuiteType(0);

  inline bool operator!=(const NpkSecurityAssociation& rhs) const {
    return std::tie(peerNanIdentityKey, localNanIdentityKey, npk, akm, cipherType) != std::tie(rhs.peerNanIdentityKey, rhs.localNanIdentityKey, rhs.npk, rhs.akm, rhs.cipherType);
  }
  inline bool operator<(const NpkSecurityAssociation& rhs) const {
    return std::tie(peerNanIdentityKey, localNanIdentityKey, npk, akm, cipherType) < std::tie(rhs.peerNanIdentityKey, rhs.localNanIdentityKey, rhs.npk, rhs.akm, rhs.cipherType);
  }
  inline bool operator<=(const NpkSecurityAssociation& rhs) const {
    return std::tie(peerNanIdentityKey, localNanIdentityKey, npk, akm, cipherType) <= std::tie(rhs.peerNanIdentityKey, rhs.localNanIdentityKey, rhs.npk, rhs.akm, rhs.cipherType);
  }
  inline bool operator==(const NpkSecurityAssociation& rhs) const {
    return std::tie(peerNanIdentityKey, localNanIdentityKey, npk, akm, cipherType) == std::tie(rhs.peerNanIdentityKey, rhs.localNanIdentityKey, rhs.npk, rhs.akm, rhs.cipherType);
  }
  inline bool operator>(const NpkSecurityAssociation& rhs) const {
    return std::tie(peerNanIdentityKey, localNanIdentityKey, npk, akm, cipherType) > std::tie(rhs.peerNanIdentityKey, rhs.localNanIdentityKey, rhs.npk, rhs.akm, rhs.cipherType);
  }
  inline bool operator>=(const NpkSecurityAssociation& rhs) const {
    return std::tie(peerNanIdentityKey, localNanIdentityKey, npk, akm, cipherType) >= std::tie(rhs.peerNanIdentityKey, rhs.localNanIdentityKey, rhs.npk, rhs.akm, rhs.cipherType);
  }
};
}  // namespace wifi
}  // namespace hardware
}  // namespace android
}  // namespace aidl
