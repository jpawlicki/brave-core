/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/ui/webui/settings/brave_account_handler.h"

#include <string>

#include "base/check_op.h"
#include "base/logging.h"
#include "base/functional/bind.h"
#include "brave/components/brave_account/core/browser/password_strength.h"

BraveAccountHandler::BraveAccountHandler() = default;

BraveAccountHandler::~BraveAccountHandler() = default;

void BraveAccountHandler::RegisterMessages() {
  web_ui()->RegisterMessageCallback(
      "getPasswordStrength",
      base::BindRepeating(&BraveAccountHandler::GetPasswordStrength,
                          base::Unretained(this)));
}

void BraveAccountHandler::GetPasswordStrength(const base::Value::List& args) {
  CHECK_EQ(args.size(), 2U);

  auto* password = args[1].GetIfString();
  if (!password || password->empty()) {
    return ResolveJavascriptCallback(args[0], base::Value(0));
  }

  const auto strength = brave_account::GetPasswordStrength(*password);
  DVLOG(0) << "strength: " << strength;

  AllowJavascript();
  ResolveJavascriptCallback(args[0], base::Value(strength));
}
