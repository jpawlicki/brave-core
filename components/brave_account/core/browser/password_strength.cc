/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_account/core/browser/password_strength.h"

#include "third_party/zxcvbn-cpp/native-src/zxcvbn/matching.hpp"
#include "third_party/zxcvbn-cpp/native-src/zxcvbn/scoring.hpp"
#include "third_party/zxcvbn-cpp/native-src/zxcvbn/time_estimates.hpp"

namespace brave_account {

namespace {

// Passwords longer than this constant should not be checked for weakness using
// the zxcvbn-cpp library. This is because the runtime grows extremely, starting
// at a password length of 40.
// See https://github.com/dropbox/zxcvbn#runtime-latency
// Needs to stay in sync with google3 constant: http://shortn/_1ufIF61G4X
constexpr int kZxcvbnLengthCap = 40;

}  // namespace

int GetPasswordStrength(const std::string& password) {
  std::vector<zxcvbn::Match> matches =
      zxcvbn::omnimatch(password.substr(0, kZxcvbnLengthCap));
  zxcvbn::ScoringResult result =
      zxcvbn::most_guessable_match_sequence(password, matches);
  // |score| is an integer from 0 to 4 (https://github.com/dropbox/zxcvbn)
  return (zxcvbn::estimate_attack_times(result.guesses).score + 1) / 5.0 * 100;
}

}  // namespace brave_account
