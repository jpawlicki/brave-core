/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ADS_CONTENT_BROWSER_SEARCH_RESULT_AD_SEARCH_RESULT_AD_PARSING_H_
#define BRAVE_COMPONENTS_BRAVE_ADS_CONTENT_BROWSER_SEARCH_RESULT_AD_SEARCH_RESULT_AD_PARSING_H_

#include <map>
#include <string>

#include "brave/components/brave_ads/content/browser/search_result_ad/search_result_ad_info.h"
#include "third_party/blink/public/mojom/document_metadata/document_metadata.mojom.h"

namespace brave_ads {

using SearchResultAdMap = std::map<std::string, SearchResultAdInfo>;

SearchResultAdMap ParseWebPageEntities(blink::mojom::WebPagePtr web_page,
                                       SearchResultAdState state);

}  // namespace brave_ads

#endif  // BRAVE_COMPONENTS_BRAVE_ADS_CONTENT_BROWSER_SEARCH_RESULT_AD_SEARCH_RESULT_AD_PARSING_H_
