// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

import SwiftUI
import DesignSystem

public struct Action: Identifiable {
  public var id: String
  public var title: String
  public var braveSystemImage: String
  public var handler: (Action) -> Void
}

struct BrowserMenu: View {
  var body: some View {
    ScrollView(.vertical) {
      VStack(spacing: 16) {
        VStack(alignment: .leading) {
          HStack {
            Text("My Actions")
              .font(.caption.weight(.semibold))
              .textCase(.uppercase)
            Spacer()
            Button {

            } label: {
              Text("Edit")
                .font(.caption.weight(.semibold))
                .padding(.vertical, 4)
                .padding(.horizontal, 12)
                .background(Color(braveSystemName: .iosBrowserContainerHighlightIos), in: .capsule)
            }
          }
          .foregroundStyle(Color(braveSystemName: .textTertiary))
          QuickActionsView(actions: [
            .init(id: "1", title: "VPN Off", braveSystemImage: "leo.product.vpn", handler: { _ in }),
            .init(id: "2", title: "Add Bookmark", braveSystemImage: "leo.browser.bookmark-add", handler: { _ in }),
            .init(id: "3", title: "History", braveSystemImage: "leo.history", handler: { _ in }),
            .init(id: "4", title: "Summarize", braveSystemImage: "leo.product.brave-leo", handler: { _ in }),
            .init(id: "5", title: "Playlist", braveSystemImage: "leo.product.playlist", handler: { _ in }),
          ])
        }
        .frame(maxWidth: .infinity, maxHeight: .infinity, alignment: .leading)
        ActionsList(actions: [
          .init(id: "1", title: "VPN Off", braveSystemImage: "leo.product.vpn", handler: { _ in }),
          .init(id: "2", title: "Add Bookmark", braveSystemImage: "leo.browser.bookmark-add", handler: { _ in }),
          .init(id: "3", title: "History", braveSystemImage: "leo.history", handler: { _ in }),
          .init(id: "4", title: "Summarize", braveSystemImage: "leo.product.brave-leo", handler: { _ in }),
          .init(id: "5", title: "Playlist", braveSystemImage: "leo.product.playlist", handler: { _ in }),
        ], additionalActions: [
          .init(id: "5", title: "Playlist", braveSystemImage: "leo.product.playlist", handler: { _ in }),
          .init(id: "4", title: "Summarize", braveSystemImage: "leo.product.brave-leo", handler: { _ in }),
        ])
        ActionsList(actions: [
          .init(id: "1", title: "All Settings", braveSystemImage: "leo.settings", handler: { _ in })
        ])
      }
      .padding()
    }
    .background(Material.thick)
    // Not sure if this is needed
    // .background(Color(braveSystemName: .materialThick))
  }
}

private struct QuickActionsView: View {
  var actions: [Action]

  var visibleActions: [Action] {
    if actions.count > 5 {
      return Array(actions[0..<4])
    }
    return actions
  }

  var menuActions: [Action] {
    if actions.count <= 5 {
      return []
    }
    return Array(actions.dropFirst(4))
  }

  var body: some View {
    HStack(alignment: .top, spacing: 12) {
      ForEach(visibleActions) { action in
        Button {
          
        } label: {
          Label(action.title, braveSystemImage: action.braveSystemImage)
        }
      }
      .buttonStyle(_ButtonStyle())
//      if actions.count > 5 {
//        Menu {
//          ForEach(menuActions) { action in
//            Button {
//
//            } label: {
//              Label(action.title, braveSystemImage: action.braveSystemImage)
//            }
//          }
//        } label: {
//          Label("More Actions", braveSystemImage: "leo.more.horizontal")
//            .labelStyle(_LabelStyle())
//        }
//      }
    }
  }

  private struct _ButtonStyle: ButtonStyle {
    func makeBody(configuration: Configuration) -> some View {
      configuration.label
        .labelStyle(_LabelStyle(isPressed: configuration.isPressed))
    }
  }

  private struct _LabelStyle: LabelStyle {
    @ScaledMetric private var iconFrameSize = 22
    @ScaledMetric private var iconFontSize = 18
    var isPressed: Bool

    func makeBody(configuration: Configuration) -> some View {
      VStack(spacing: 8) {
        configuration.icon
          .frame(width: iconFrameSize, height: iconFrameSize)
          .padding(.vertical, 12)
          .font(.system(size: iconFontSize))
          .foregroundStyle(Color(braveSystemName: .iconDefault))
          .frame(maxWidth: .infinity)
          .background {
            Color(braveSystemName: .iosBrowserContainerHighlightIos)
              .overlay(Color(braveSystemName: .iosBrowserContainerHighlightIos).opacity(isPressed ? 1 : 0))
              .clipShape(.rect(cornerRadius: 14, style: .continuous))
              .hoverEffect()
          }
        configuration.title
          .font(.caption2)
          .lineLimit(2)
          .foregroundStyle(Color(braveSystemName: .textPrimary))
          .multilineTextAlignment(.center)
      }
      .contentShape(.rect)
    }
  }
}

private struct ActionsList: View {
  var actions: [Action]
  var additionalActions: [Action] = []

  @State private var isAdditionalActionsVisible: Bool = false
  @Environment(\.pixelLength) private var pixelLength

  var body: some View {
    VStack(alignment: .leading, spacing: 0) {
      ForEach(actions) { action in
        Button {

        } label: {
          Label(action.title, braveSystemImage: action.braveSystemImage)
        }
        .buttonStyle(_ButtonStyle())
        if !additionalActions.isEmpty || action.id != actions.last?.id {
          Color(braveSystemName: .materialDivider)
            .frame(height: pixelLength)
            .padding(.leading, 16)
        }
      }
      if !additionalActions.isEmpty {
        Button {
          withAnimation(.snappy) {
            isAdditionalActionsVisible.toggle()
          }
        } label: {
          HStack {
            Label("More Actions", braveSystemImage: "leo.more.horizontal")
            Spacer()
            Image(braveSystemName: "leo.carat.down")
              .rotationEffect(.degrees(isAdditionalActionsVisible ? 180 : 0))
          }
        }
        .buttonStyle(_ButtonStyle())
        if isAdditionalActionsVisible {
          Color(braveSystemName: .materialDivider)
            .frame(height: pixelLength)
            .padding(.leading, 16)
          ForEach(additionalActions) { action in
            Button {

            } label: {
              Label(action.title, braveSystemImage: action.braveSystemImage)
            }
            .buttonStyle(_ButtonStyle())
            if action.id != additionalActions.last?.id {
              Color(braveSystemName: .materialDivider)
                .frame(height: pixelLength)
                .padding(.leading, 16)
            }
          }
        }
      }
    }
    .background(Color(braveSystemName: .iosBrowserContainerHighlightIos))
    .clipShape(.rect(cornerRadius: 14, style: .continuous))
  }

  private struct _ButtonStyle: ButtonStyle {
    func makeBody(configuration: Configuration) -> some View {
      configuration.label
        .padding(.vertical, 12)
        .padding(.horizontal, 16)
        .frame(maxWidth: .infinity, minHeight: 44, alignment: .leading)
        .contentShape(.rect)
        .hoverEffect()
        .background(Color(braveSystemName: .iosBrowserContainerHighlightIos).opacity(configuration.isPressed ? 1 : 0))
        .labelStyle(_LabelStyle())
    }

    private struct _LabelStyle: LabelStyle {
      @ScaledMetric private var iconFrameSize = 22
      @ScaledMetric private var iconFontSize = 18

      func makeBody(configuration: Configuration) -> some View {
        HStack(spacing: 10) {
          configuration.icon
            .frame(width: iconFrameSize, height: iconFrameSize)
            .font(.system(size: iconFontSize))
            .foregroundStyle(Color(braveSystemName: .iconDefault))
          configuration.title
            .font(.body)
            .foregroundStyle(Color(braveSystemName: .textPrimary))
        }
      }
    }
  }
}

#if DEBUG
#Preview {
  BrowserMenu()
    .background(LinearGradient(colors: [Color.red, Color.blue, Color.purple, Color.green], startPoint: .topLeading, endPoint: .bottomTrailing))
}
#endif
