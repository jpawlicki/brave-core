// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import Foundation
import Strings
import BraveStrings

struct Action: Identifiable {
//  associatedtype AssociatedValue
  var id: String
//  var title: (AssociatedValue) -> String { get }
//  var braveSystemImage: (AssociatedValue) -> String { get }
}
//
//struct ActionType: Hashable {
//  var id: String
//  var ranking: Int
//  var defaultTitle: String?
//  var defaultBraveSystemImage: String?
//
//  func hash(into hasher: inout Hasher) {
//    hasher.combine(id)
//  }
//
//  init(id: String, ranking: Int, title: String? = nil, braveSystemImage: String? = nil) {
//    self.id = id
//    self.ranking = ranking
//    self.defaultTitle = title
//    self.defaultBraveSystemImage = braveSystemImage
//  }
//}

//public struct StaticAction: Action {
//  typealias AssociatedValue = ()
//  public var id: String
//  public var title: (()) -> String
//  public var braveSystemImage: (()) -> String
//  init(id: String, title: String, braveSystemImage: String) {
//    self.id = id
//    self.title = { _ in title }
//    self.braveSystemImage = { _ in braveSystemImage }
//  }
//}

private let defaultActionRankings: [Action.ID] = [
  // Have all actions listed here ranked compared to others
  // Top N items end up within the horizontal menu
  // Instead of storing explicit order, store ranking adjustments?
  // e.g.
  //
  // if the default ranking was
  //    vpn          : 100
  //    add bookmark : 200
  //    history      : 300
  //    leo          : 400
  //    playlist     : 500
  //    ---
  //    add to favs  : 600
  //
  // and the user wanted to move `add to favs` above `playlist`, we would save the ranking of
  // `add to favs` as 401. If we were now to add a new action item that we wanted ranked higher than
  // playlist by default we could create an action with a default ranking of 450. This would let us
  // adjust defaults without potentially clobbering a users ranking
]

/*
 Potential solutions:
 - On first launch of the new menu, store the default sort order and when new items by Brave add them to the bottom of the list
   - Do we have them visible by default
 - Check whether or not the user has made alterations to the visibility & sort order of the actions: if they have,
 */

//public struct ToggleAction: Action {
//  public var id: String
//  public var title: (Bool) -> String
//  public var braveSystemImage: (Bool) -> String
//}

//public struct ValueAction<Value>: _Action {
//  public var id: String
//  public var title: String {
//
//  }
//  public var braveSystemImage: String {
//
//  }
//  var currentValue: Value
//  
//}

/// An action that can be performed in the menu
public struct ActionType: Identifiable {
  /// Additional attributes that may affect the display or behaviour of the action
  public struct Attributes: OptionSet {
    public var rawValue: Int = 0
    public init(rawValue: Int) {
      self.rawValue = rawValue
    }
    /// Whether or not the menu remains presented upon performing the action
    public static let keepsMenuPresented: Self = .init(rawValue: 1 << 0)
    /// Whether or not the menu item is only displayed when a web context is provided
    public static let webContextRequired: Self = .init(rawValue: 1 << 1)
  }

  /// The unique identifier of this action.
  public var id: String
  /// The display title
  public var title: String
  /// A design system image that will be shown
  public var braveSystemImage: String
  /// Attributes associated with this action
  public var attributes: Attributes = []
}

extension ActionType {
  static let copyCleanLink: Self = .init(
    id: "CopyCleanLink",
    title: Strings.copyCleanLink,
    braveSystemImage: "leo.broom",
    attributes: [.webContextRequired]
  )
  static let sendURL: Self = .init(
    id: "SendURL",
    title: Strings.OpenTabs.sendWebsiteShareActionTitle,
    braveSystemImage: "leo.smartphone.laptop",
    attributes: [.webContextRequired]
  )
  static let toggleReaderMode: Self = .init(
    id: "ToggleReaderMode",
    title: Strings.toggleReaderMode,
    braveSystemImage: "leo.product.speedreader",
    attributes: [.webContextRequired]
  )
  static let findInPage: Self = .init(
    id: "FindInPage",
    title: Strings.findInPage,
    braveSystemImage: "leo.search",
    attributes: [.webContextRequired]
  )
  static let pageZoom: Self = .init(
    id: "PageZoom",
    title: Strings.PageZoom.settingsTitle,
    braveSystemImage: "leo.font.size",
    attributes: [.webContextRequired]
  )
  static let addFavourites: Self = .init(
    id: "AddFavourites",
    title: Strings.addToFavorites,
    braveSystemImage: "leo.widget.generic",
    attributes: [.webContextRequired]
  )
  static let requestMobileSite: Self = .init(
    id: "ToggleUserAgent",
    title: Strings.appMenuViewMobileSiteTitleString,
    braveSystemImage: "leo.smartphone",
    attributes: [.webContextRequired]
  )
  static let requestDesktopSite: Self = .init(
    id: "ToggleUserAgent",
    title: Strings.appMenuViewDesktopSiteTitleString,
    braveSystemImage: "leo.monitor",
    attributes: [.webContextRequired]
  )
  static let addSourceNews: Self = .init(
    id: "AddSourceNews",
    title: Strings.BraveNews.addSourceShareTitle,
    braveSystemImage: "leo.rss",
    attributes: [.webContextRequired]
  )
  static let createPDF: Self = .init(
    id: "CreatePDF",
    title: Strings.createPDF,
    braveSystemImage: "leo.file.new",
    attributes: [.webContextRequired]
  )
  static let addSearchEngine: Self = .init(
    id: "AddSearchEngine",
    title: Strings.CustomSearchEngine.customEngineNavigationTitle,
    braveSystemImage: "leo.search.zoom-in",
    attributes: [.webContextRequired]
  )
  static let displaySecurityCertificate: Self = .init(
    id: "DisplaySecurityCertificate",
    title: Strings.displayCertificate,
    braveSystemImage: "leo.lock.plain",
    attributes: [.webContextRequired]
  )
  static let reportBrokenSite: Self = .init(
    id: "ReportBrokenSite",
    title: Strings.Shields.reportABrokenSite,
    braveSystemImage: "leo.warning.triangle-outline",
    attributes: [.webContextRequired]
  )
}
