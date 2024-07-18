/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_DAY_ZERO_BROWSER_UI_EXPT_DAY_ZERO_BROWSER_UI_EXPT_MANAGER_H_
#define BRAVE_BROWSER_DAY_ZERO_BROWSER_UI_EXPT_DAY_ZERO_BROWSER_UI_EXPT_MANAGER_H_

#include <memory>
#include <optional>

#include "base/memory/raw_ref.h"
#include "base/scoped_observation.h"
#include "chrome/browser/profiles/profile_manager_observer.h"

class PrefRegistrySimple;
class Profile;
class ProfileManager;

// Handling browser UI for day-zero experiment.
class DayZeroBrowserUIExptManager : public ProfileManagerObserver {
 public:
  static void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
  static std::unique_ptr<DayZeroBrowserUIExptManager> Create(
      ProfileManager* profile_manager);

  ~DayZeroBrowserUIExptManager() override;
  DayZeroBrowserUIExptManager(const DayZeroBrowserUIExptManager&) = delete;
  DayZeroBrowserUIExptManager& operator=(const DayZeroBrowserUIExptManager&) =
      delete;

  // ProfileManagerObserver overrides:
  void OnProfileAdded(Profile* profile) override;
  void OnProfileManagerDestroying() override;

 private:
  friend class DayZeroBrowserUIExptTest;

  explicit DayZeroBrowserUIExptManager(ProfileManager* profile_manager);

  void SetForDayZeroBrowserUI(Profile* profile);
  void ResetForDayZeroBrowserUI(Profile* profile);
  void ResetBrowserUIStateForAllProfiles();

  raw_ref<ProfileManager> profile_manager_;
  base::ScopedObservation<ProfileManager, ProfileManagerObserver> observation_{
      this};
};

#endif  // BRAVE_BROWSER_DAY_ZERO_BROWSER_UI_EXPT_DAY_ZERO_BROWSER_UI_EXPT_MANAGER_H_
