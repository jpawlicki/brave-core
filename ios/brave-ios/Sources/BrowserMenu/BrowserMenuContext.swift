// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation

/// Provides the browser menu with contextual for non-static actions
public struct BrowserMenuContext {
  public struct WebPageContext {
    public var url: URL
    public var isDesktopModeEnabled: Bool
  }
  /// The current web page context being displayed, or nil if the new tab page is showing
  public var webContext: WebPageContext?
  /// Whether or not VPN is currently enabled & connected
  public var isVPNEnabled: Bool
}
