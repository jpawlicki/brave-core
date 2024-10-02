/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/browser/webcompat_reporter/webcompat_reporter_service_factory.h"

#include <utility>

#include "base/no_destructor.h"
#include "brave/browser/brave_browser_process.h"
#include "brave/components/brave_shields/content/browser/ad_block_service.h"
#include "brave/components/webcompat_reporter/browser/webcompat_reporter_service.h"
#include "chrome/browser/browser_process.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "content/public/browser/storage_partition.h"

namespace webcompat_reporter {

// static
WebcompatReporterServiceFactory*
WebcompatReporterServiceFactory::GetInstance() {
  static base::NoDestructor<WebcompatReporterServiceFactory> instance;
  return instance.get();
}

// static
mojo::PendingRemote<mojom::WebcompatReporterHandler>
WebcompatReporterServiceFactory::GetForContext(
    content::BrowserContext* context) {
  return static_cast<WebcompatReporterService*>(
             GetInstance()->GetServiceForBrowserContext(context, true))
      ->MakeRemote();
}

// static
WebcompatReporterService* WebcompatReporterServiceFactory::GetServiceForContext(
    content::BrowserContext* context) {
  return static_cast<WebcompatReporterService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

WebcompatReporterServiceFactory::WebcompatReporterServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "WebcompatReporterService",
          BrowserContextDependencyManager::GetInstance()) {}

WebcompatReporterServiceFactory::~WebcompatReporterServiceFactory() = default;

KeyedService* WebcompatReporterServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  auto* default_storage_partition = context->GetDefaultStoragePartition();
  auto shared_url_loader_factory =
      default_storage_partition->GetURLLoaderFactoryForBrowserProcess();
  return new WebcompatReporterService(
      g_brave_browser_process->ad_block_service(),
      g_browser_process->component_updater(), shared_url_loader_factory);
}

content::BrowserContext*
WebcompatReporterServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return chrome::GetBrowserContextRedirectedInIncognito(context);
}

}  // namespace webcompat_reporter
