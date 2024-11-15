/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_BRAVE_ACCOUNT_CORE_BROWSER_PASSWORD_STRENGTH_H_
#define BRAVE_COMPONENTS_BRAVE_ACCOUNT_CORE_BROWSER_PASSWORD_STRENGTH_H_

#include <string>

namespace brave_account {

// Returns password strength on a scale from 1 to 100.
int GetPasswordStrength(const std::string& password);

}  // namespace brave_account

#endif  // BRAVE_COMPONENTS_BRAVE_ACCOUNT_CORE_BROWSER_PASSWORD_STRENGTH_H_
