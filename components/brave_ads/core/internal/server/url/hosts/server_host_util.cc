/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_ads/core/internal/server/url/hosts/server_host_util.h"

#include <memory>

#include "base/check.h"
#include "brave/components/brave_ads/core/internal/server/url/hosts/server_host_types.h"
#include "brave/components/brave_ads/core/internal/server/url/hosts/server_hosts_factory.h"

namespace brave_ads::server {

namespace {

std::string GetHost(const ServerHostType type) {
  std::unique_ptr<ServerHostInterface> server_host =
      ServerHostsFactory::Build(type);
  DCHECK(server_host);

  return server_host->Get();
}

}  // namespace

std::string GetStaticHost() {
  return GetHost(ServerHostType::kStatic);
}

std::string GetGeoHost() {
  return GetHost(ServerHostType::kGeo);
}

std::string GetNonAnonymousHost() {
  return GetHost(ServerHostType::kNonAnonymous);
}

std::string GetAnonymousHost() {
  return GetHost(ServerHostType::kAnonymous);
}

std::string GetAnonymousSearchHost() {
  return GetHost(ServerHostType::kAnonymousSearch);
}

}  // namespace brave_ads::server
