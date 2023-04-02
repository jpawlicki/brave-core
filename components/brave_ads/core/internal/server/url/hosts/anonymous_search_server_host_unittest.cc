/* Copyright (c) 2023 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/common/unittest/unittest_base.h"
#include "brave/components/brave_ads/core/internal/flags/environment/environment_types.h"
#include "brave/components/brave_ads/core/internal/flags/flag_manager.h"
#include "brave/components/brave_ads/core/internal/server/url/hosts/server_host_util.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace brave_ads {

class BatAdsAnonymousSearchServerHostTest : public UnitTestBase {};

TEST_F(BatAdsAnonymousSearchServerHostTest, GetProductionHost) {
  // Arrange
  FlagManager::GetInstance()->SetEnvironmentTypeForTesting(
      EnvironmentType::kProduction);

  // Act
  const std::string host = server::GetAnonymousHost();

  // Assert
  const std::string expected_host = "https://search.anonymous.ads.brave.com";
  EXPECT_EQ(expected_host, host);
}

TEST_F(BatAdsAnonymousSearchServerHostTest, GetStagingHost) {
  // Arrange
  FlagManager::GetInstance()->SetEnvironmentTypeForTesting(
      EnvironmentType::kStaging);

  // Act
  const std::string host = server::GetAnonymousHost();

  // Assert
  const std::string expected_host =
      "https://search.anonymous.ads.bravesoftware.com";
  EXPECT_EQ(expected_host, host);
}

}  // namespace brave_ads
