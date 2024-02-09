// Copyright (c) 2018 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.
export const LOCAL_STORAGE_KEYS = {
  IS_PORTFOLIO_OVERVIEW_GRAPH_HIDDEN:
    'BRAVE_WALLET_IS_WALLET_PORTFOLIO_OVERVIEW_GRAPH_HIDDEN',
  HIDE_PORTFOLIO_BALANCES: 'BRAVE_WALLET_HIDE_PORTFOLIO_BALANCES',
  HIDE_PORTFOLIO_NFTS_TAB: 'BRAVE_WALLET_HIDE_PORTFOLIO_NFTS_TAB',
  PORTFOLIO_NETWORK_FILTER_OPTION: 'PORTFOLIO_NETWORK_FILTER_OPTION',
  PORTFOLIO_ASSET_FILTER_OPTION: 'PORTFOLIO_ASSET_FILTER_OPTION',
  PORTFOLIO_TIME_LINE_OPTION: 'PORTFOLIO_TIME_LINE_OPTION',
  IS_IPFS_BANNER_HIDDEN: 'BRAVE_WALLET_IS_IPFS_BANNER_HIDDEN',
  IS_ENABLE_NFT_AUTO_DISCOVERY_MODAL_HIDDEN:
    'BRAVE_WALLET_IS_ENABLE_NFT_AUTO_DISCOVERY_MODAL_HIDDEN',
  USER_REMOVED_NON_FUNGIBLE_TOKEN_IDS:
    'BRAVE_WALLET_USER_REMOVED_NON_FUNGIBLE_TOKEN_IDS',
  USER_DELETED_NON_FUNGIBLE_TOKEN_IDS:
    'BRAVE_WALLET_USER_DELETED_NON_FUNGIBLE_TOKEN_IDS',
  USER_REMOVED_FUNGIBLE_TOKEN_IDS:
    'BRAVE_WALLET_USER_REMOVED_FUNGIBLE_TOKEN_IDS',
  DEBUG: 'BRAVE_WALLET_DEBUG',
  FILTERED_OUT_PORTFOLIO_NETWORK_KEYS:
    'BRAVE_WALLET_FILTERED_OUT_PORTFOLIO_NETWORK_KEYS',
  FILTERED_OUT_PORTFOLIO_ACCOUNT_IDS:
    'BRAVE_WALLET_FILTERED_OUT_PORTFOLIO_ACCOUNT_IDS',
  HIDE_PORTFOLIO_SMALL_BALANCES: 'BRAVE_WALLET_HIDE_PORTFOLIO_SMALL_BALANCES',
  GROUP_PORTFOLIO_ASSETS_BY: 'BRAVE_WALLET_GROUP_PORTFOLIO_ASSETS_BY',
  SHOW_NETWORK_LOGO_ON_NFTS: 'BRAVE_WALLET_SHOW_NETWORK_LOGO_ON_NFTS',
  COLLAPSED_PORTFOLIO_ACCOUNT_IDS:
    'BRAVE_WALLET_COLLAPSED_PORTFOLIO_ACCOUNTS_IDS',
  COLLAPSED_PORTFOLIO_NETWORK_KEYS:
    'BRAVE_WALLET_COLLAPSED_PORTFOLIO_NETWORK_KEYS',
  CURRENT_PANEL: 'BRAVE_WALLET_CURRENT_PANEL',
  LAST_VISITED_PANEL: 'BRAVE_WALLET_LAST_VISITED_PANEL',
  TOKEN_BALANCES: 'BRAVE_WALLET_TOKEN_BALANCES',
  SAVED_SESSION_ROUTE: 'BRAVE_WALLET_SAVED_SESSION_ROUTE',
  USER_HIDDEN_TOKEN_IDS: 'BRAVE_WALLET_USER_HIDDEN_TOKEN_IDS',
  USER_DELETED_TOKEN_IDS: 'BRAVE_WALLET_USER_DELETED_TOKEN_IDS'
} as const

const LOCAL_STORAGE_KEYS_DEPRECATED = {
  PORTFOLIO_ACCOUNT_FILTER_OPTION: 'PORTFOLIO_ACCOUNT_FILTER_OPTION',
  SESSION_ROUTE: 'BRAVE_WALLET_SESSION_ROUTE',
  FILTERED_OUT_PORTFOLIO_ACCOUNT_ADDRESSES:
    'BRAVE_WALLET_FILTERED_OUT_PORTFOLIO_ACCOUNT_ADDRESSES',
  COLLAPSED_PORTFOLIO_ACCOUNT_ADDRESSES:
    'BRAVE_WALLET_COLLAPSED_PORTFOLIO_ACCOUNTS_ADDRESSES'
}

export const removeDeprecatedLocalStorageKeys = () => {
  Object.keys(LOCAL_STORAGE_KEYS_DEPRECATED).forEach((key) => {
    window.localStorage.removeItem(LOCAL_STORAGE_KEYS_DEPRECATED[key])
  })
}
