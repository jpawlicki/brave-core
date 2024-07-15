// Copyright (c) 2022 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at https://mozilla.org/MPL/2.0/.

import * as React from 'react'

import { Provider } from 'react-redux'
import { MemoryRouter } from 'react-router-dom'

// types
import { PanelState, UIState, WalletState } from '../../constants/types'

// theme
import LightDarkThemeProvider from '../../../common/BraveCoreThemeProvider'
import walletDarkTheme from '../../theme/wallet-dark'
import walletLightTheme from '../../theme/wallet-light'

// Mocks
import { ApiProxyContext } from '../../common/context/api-proxy.context'
import { createMockStore } from '../../utils/test-utils'
import { WalletApiDataOverrides } from '../../constants/testing_types'
import getAPIProxy from '../../common/async/bridge' // aut-mocked by complier
import '../locale'

const mockedProxy = getAPIProxy()

export interface WalletPanelStoryProps {
  walletStateOverride?: Partial<WalletState>
  panelStateOverride?: Partial<PanelState>
  uiStateOverride?: Partial<UIState>
  walletApiDataOverrides?: WalletApiDataOverrides
}

export const WalletPanelStory: React.FC<
  React.PropsWithChildren<WalletPanelStoryProps>
> = ({
  children,
  panelStateOverride,
  walletStateOverride,
  uiStateOverride,
  walletApiDataOverrides
}) => {
  // redux
  const store = React.useMemo(() => {
    return createMockStore(
      {
        walletStateOverride,
        panelStateOverride,
        uiStateOverride: uiStateOverride
      },
      walletApiDataOverrides
    )
  }, [
    walletStateOverride,
    panelStateOverride,
    walletApiDataOverrides,
    uiStateOverride
  ])

  // render
  return (
    <MemoryRouter initialEntries={['/']}>
      <Provider store={store}>
        <ApiProxyContext.Provider value={mockedProxy}>
          {children}
        </ApiProxyContext.Provider>
      </Provider>
    </MemoryRouter>
  )
}

export const WalletPanelTestWrapper = (
  props: React.PropsWithChildren<WalletPanelStoryProps>
) => (
  <LightDarkThemeProvider
    initialThemeType={'Light'}
    dark={walletDarkTheme}
    light={walletLightTheme}
  >
    <WalletPanelStory {...props} />
  </LightDarkThemeProvider>
)

export default WalletPanelStory
