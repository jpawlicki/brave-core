// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation

/// An action that can be performed in the menu
public struct ActionType: Identifiable {
  /// Additional attributes that may affect the display or behaviour of the action
  public struct Attributes {
    /// Whether or not the menu remains presented upon performing the action
    public var keepsMenuPresented: Bool = false
    /// Whether or not the menu item is only displayed when a web context is provided
    public var isWebContextRequired: Bool = false
  }

  /// The unique identifier of this action.
  public var id: String
  /// The display title
  public var title: String
  /// A design system image that will be shown
  public var braveSystemImage: String
  /// Attributes associated with this action
  public var attributes: Attributes = .init()
}

extension ActionType {
  static let addBookmark: ActionType = .init(
    id: "add-bookmark",
    title: "Add Bookmark",
    braveSystemImage: "leo.browser.bookmark-add"
  )
  static let toggleFavorite: ActionType = .init(
    id: "toggle-bookmark",
    title: "Add to Favorites",
    braveSystemImage: "leo.widget.generic"
  )
}
