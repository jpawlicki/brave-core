/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_wallet/browser/bitcoin_keyring.h"

#include <memory>
#include <utility>

namespace brave_wallet {

BitcoinKeyring::BitcoinKeyring(bool testnet) : testnet_(testnet) {}

std::string BitcoinKeyring::GetReceivingAddress(uint32_t account_index,
                                                uint32_t receiving_index) {
  auto key = DeriveReceivingKey(account_index, receiving_index);
  if (!key) {
    return "";
  }

  HDKey* hd_key = static_cast<HDKey*>(key.get());

  return hd_key->GetSegwitAddress(testnet_);
}

std::string BitcoinKeyring::GetChangeAddress(uint32_t account_index,
                                             uint32_t change_index) {
  auto key = DeriveChangeKey(account_index, change_index);
  if (!key) {
    return "";
  }

  HDKey* hd_key = static_cast<HDKey*>(key.get());

  return hd_key->GetSegwitAddress(testnet_);
}

std::vector<uint8_t> BitcoinKeyring::GetBitcoinPubkey(
    const mojom::BitcoinAddress& address) {
  auto hd_key_base = DeriveKey(*address.id);
  if (!hd_key_base) {
    return {};
  }

  return hd_key_base->GetPublicKeyBytes();
}

std::vector<uint8_t> BitcoinKeyring::SignBitcoinMessage(
    const mojom::BitcoinAddress& address,
    const std::vector<uint8_t>& message) {
  auto hd_key_base = DeriveKey(*address.id);
  if (!hd_key_base) {
    return {};
  }

  DCHECK_EQ(GetAddressInternal(hd_key_base.get()), address.address);

  auto* hd_key = static_cast<HDKey*>(hd_key_base.get());

  return hd_key->SignBitcoin(message);
}

std::string BitcoinKeyring::GetAddressInternal(HDKeyBase* hd_key_base) const {
  if (!hd_key_base) {
    return std::string();
  }
  HDKey* hd_key = static_cast<HDKey*>(hd_key_base);
  return hd_key->GetSegwitAddress(testnet_);
}

std::unique_ptr<HDKeyBase> BitcoinKeyring::DeriveAccount(uint32_t index) const {
  // m/84'/0'/{index}'
  return root_->DeriveHardenedChild(index);
}

std::unique_ptr<HDKeyBase> BitcoinKeyring::DeriveReceivingKey(
    uint32_t account_index,
    uint32_t receiving_index) {
  auto account_key = DeriveAccount(account_index);
  if (!account_key) {
    return nullptr;
  }

  auto receiving_key = account_key->DeriveNormalChild(0);
  if (!receiving_key) {
    return nullptr;
  }

  // m/84'/0'/{account_index}'/0/{receiving_index}
  return receiving_key->DeriveNormalChild(receiving_index);
}

std::unique_ptr<HDKeyBase> BitcoinKeyring::DeriveChangeKey(
    uint32_t account_index,
    uint32_t change_index) {
  auto account_key = DeriveAccount(account_index);
  if (!account_key) {
    return nullptr;
  }

  auto change_key = account_key->DeriveNormalChild(1);
  if (!change_key) {
    return nullptr;
  }

  // m/84'/0'/{account_index}'/1/{change_index}
  return change_key->DeriveNormalChild(change_index);
}

std::unique_ptr<HDKeyBase> BitcoinKeyring::DeriveKey(
    const mojom::BitcoinAddressId& address) {
  auto account_key = DeriveAccount(address.account);
  if (!account_key) {
    return nullptr;
  }

  auto change_key = account_key->DeriveNormalChild(address.change);
  if (!change_key) {
    return nullptr;
  }

  // m/84'/0'/{address.account}'/{address.change}/{address.index}
  return change_key->DeriveNormalChild(address.index);
}

}  // namespace brave_wallet
