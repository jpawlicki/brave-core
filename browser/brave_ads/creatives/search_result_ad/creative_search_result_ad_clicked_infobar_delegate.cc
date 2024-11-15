/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/brave_ads/creatives/search_result_ad/creative_search_result_ad_clicked_infobar_delegate.h"

#include <memory>

#include "brave/components/brave_ads/core/public/prefs/pref_names.h"
#include "brave/grit/brave_generated_resources.h"
#include "chrome/browser/infobars/confirm_infobar_creator.h"
#include "components/infobars/content/content_infobar_manager.h"
#include "components/infobars/core/infobar.h"
#include "components/prefs/pref_service.h"
#include "components/strings/grit/components_strings.h"
#include "components/vector_icons/vector_icons.h"
#include "content/public/browser/web_contents.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/models/image_model.h"
#include "url/gurl.h"

namespace brave_ads {

namespace {

constexpr int kIconSize = 20;

constexpr char kLearnMoreUrl[] =
    "https://support.brave.com/hc/en-us/articles/360026361072-Brave-Ads-FAQ";

}  // namespace

// static
void CreativeSearchResultAdClickedInfoBarDelegate::Create(
    content::WebContents* web_contents,
    PrefService* prefs) {
  CHECK(web_contents);
  CHECK(prefs);

  if (!prefs->GetBoolean(prefs::kShouldShowSearchResultAdClickedInfoBar)) {
    return;
  }
  prefs->SetBoolean(prefs::kShouldShowSearchResultAdClickedInfoBar, false);

  infobars::ContentInfoBarManager* infobar_manager =
      infobars::ContentInfoBarManager::FromWebContents(web_contents);
  if (!infobar_manager) {
    return;
  }
  infobar_manager->AddInfoBar(
      CreateConfirmInfoBar(std::unique_ptr<ConfirmInfoBarDelegate>(
          new CreativeSearchResultAdClickedInfoBarDelegate())));
}

CreativeSearchResultAdClickedInfoBarDelegate::
    CreativeSearchResultAdClickedInfoBarDelegate() = default;

CreativeSearchResultAdClickedInfoBarDelegate::
    ~CreativeSearchResultAdClickedInfoBarDelegate() = default;

infobars::InfoBarDelegate::InfoBarIdentifier
CreativeSearchResultAdClickedInfoBarDelegate::GetIdentifier() const {
  return SEARCH_RESULT_AD_CLICKED_INFOBAR_DELEGATE;
}

ui::ImageModel CreativeSearchResultAdClickedInfoBarDelegate::GetIcon() const {
  return ui::ImageModel::FromVectorIcon(vector_icons::kProductIcon,
                                        ui::kColorIcon, kIconSize);
}

std::u16string CreativeSearchResultAdClickedInfoBarDelegate::GetMessageText()
    const {
  return l10n_util::GetStringUTF16(
      IDS_BRAVE_ADS_SEARCH_RESULT_AD_CLICKED_INFOBAR_MESSAGE);
}

int CreativeSearchResultAdClickedInfoBarDelegate::GetButtons() const {
  return BUTTON_NONE;
}

std::u16string CreativeSearchResultAdClickedInfoBarDelegate::GetLinkText()
    const {
  return l10n_util::GetStringUTF16(
      IDS_BRAVE_ADS_SEARCH_RESULT_AD_LEARN_MORE_OPT_OUT_CHOICES_LABEL);
}

GURL CreativeSearchResultAdClickedInfoBarDelegate::GetLinkURL() const {
  return GURL(kLearnMoreUrl);
}

bool CreativeSearchResultAdClickedInfoBarDelegate::LinkClicked(
    WindowOpenDisposition disposition) {
  ConfirmInfoBarDelegate::LinkClicked(disposition);
  // Return true to immediately close the infobar.
  return true;
}

}  // namespace brave_ads
