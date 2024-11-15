// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/browser/ui/webui/brave_new_tab/update_observer.h"

#include "brave/browser/ntp_background/ntp_background_prefs.h"
#include "brave/components/ntp_background_images/common/pref_names.h"

namespace brave_new_tab {

UpdateObserver::UpdateObserver(PrefService* pref_service,
                               base::RepeatingCallback<void(Source)> callback)
    : callback_(callback) {
  CHECK(pref_service);
  CHECK(callback_);

  pref_change_registrar_.Init(pref_service);
  AddPrefListener(ntp_background_images::prefs::kNewTabPageShowBackgroundImage,
                  Source::kBackgroundPrefs);
  AddPrefListener(ntp_background_images::prefs::
                      kNewTabPageShowSponsoredImagesBackgroundImage,
                  Source::kBackgroundPrefs);
  AddPrefListener(NTPBackgroundPrefs::kPrefName, Source::kBackgroundPrefs);
  AddPrefListener(NTPBackgroundPrefs::kCustomImageListPrefName,
                  Source::kBackgroundPrefs);
}

UpdateObserver::~UpdateObserver() = default;

void UpdateObserver::OnUpdate(Source update_source) {
  callback_.Run(update_source);
}

void UpdateObserver::OnPrefChanged(Source update_kind,
                                   const std::string& path) {
  OnUpdate(update_kind);
}

void UpdateObserver::AddPrefListener(const std::string& path,
                                     Source update_source) {
  pref_change_registrar_.Add(
      path, base::BindRepeating(&UpdateObserver::OnPrefChanged,
                                base::Unretained(this), update_source));
}

}  // namespace brave_new_tab
