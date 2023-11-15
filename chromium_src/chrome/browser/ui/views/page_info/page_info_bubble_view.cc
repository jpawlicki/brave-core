// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/components/brave_webtorrent/browser/buildflags/buildflags.h"
#include "components/grit/brave_components_strings.h"
#include "components/page_info/page_info.h"
#include "content/public/common/url_constants.h"

#if BUILDFLAG(ENABLE_BRAVE_WEBTORRENT)
#include "brave/components/brave_webtorrent/browser/magnet_protocol_handler.h"

// Show the InternalPageInfoBubbleView when viewing a page with the webtorrent
// scheme or brave scheme.
#define IsFileOrInternalPage(url)                                      \
  IsFileOrInternalPage(url) || url.SchemeIs(url::kWebTorrentScheme) || \
      url.SchemeIs(content::kBraveUIScheme)

// Set the text for the InternalPageInfoBubbleView on webtorrent: pages.
#define kFileScheme kWebTorrentScheme)) {  \
    text = IDS_PAGE_INFO_BRAVE_WEBTORRENT; \
  } else if (url.SchemeIs(url::kFileScheme

#else
// Show the InternalPageInfoBubbleView when viewing a page with brave scheme.
#define IsFileOrInternalPage(url) \
  IsFileOrInternalPage(url) || url.SchemeIs(content::kBraveUIScheme)
#endif  // BUILDFLAG(ENABLE_BRAVE_WEBTORRENT)

// Set the text for the InternalPageInfoBubbleView on brave pages. Do nothing
// for kBraveUIScheme, this override is just to avoid hitting
// CHECK(url.SchemeIs(content::kChromeUIScheme)) in upstream code.
#define kChromeDevToolsScheme kBraveUIScheme)) {} \
  else if (url.SchemeIs(content::kChromeDevToolsScheme

#include "src/chrome/browser/ui/views/page_info/page_info_bubble_view.cc"

#undef kFileScheme
#undef IsFileOrInternalPage
#undef kChromeDevToolsScheme
