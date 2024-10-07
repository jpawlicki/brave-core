// Copyright (c) 2024 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/ios/browser/api/webcompat_reporter/webcompat_reporter_service_factory.h"

#include "brave/components/webcompat_reporter/browser/webcompat_reporter_service.h"
#include "ios/chrome/browser/shared/model/browser_state/chrome_browser_state.h"
#include "components/keyed_service/ios/browser_state_dependency_manager.h"

namespace webcompat_reporter {
    // static
WebcompatReporterService* WebcompatReporterServiceFactory::GetForBrowserState(
    ChromeBrowserState* browser_state) {
  return static_cast<WebcompatReporterService*>(
      GetInstance()->GetServiceForBrowserState(browser_state, true));
}

// static
WebcompatReporterServiceFactory* WebcompatReporterServiceFactory::GetInstance() {
  static base::NoDestructor<WebcompatReporterServiceFactory> instance;
  return instance.get();
}

WebcompatReporterServiceFactory::WebcompatReporterServiceFactory()
    : BrowserStateKeyedServiceFactory(
          "WebcompatReporterService",
          BrowserStateDependencyManager::GetInstance()) {}

WebcompatReporterServiceFactory::~WebcompatReporterServiceFactory() {}

std::unique_ptr<KeyedService> WebcompatReporterServiceFactory::BuildServiceInstanceFor(
    web::BrowserState* context) const {

  auto* browser_state = ChromeBrowserState::FromBrowserState(context);
  if (browser_state->IsOffTheRecord()) {
    return nullptr;
  }

  return std::make_unique<WebcompatReporterService>(
      context->GetSharedURLLoaderFactory());
}


}  // namespace webcompat_reporter