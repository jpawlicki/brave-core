/* Copyright (c) 2022 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "storage/browser/blob/blob_url_store_impl.h"

#define BlobURLStoreImpl BlobURLStoreImpl_ChromiumImpl

#include "src/storage/browser/blob/blob_url_store_impl.cc"

#undef BlobURLStoreImpl

namespace storage {

void BlobURLStoreImpl::Resolve(const GURL& url, ResolveCallback callback) {
  // If a URL is not mapped to the current `storage_key_`, it's likely stored
  // with a different StorageKey (partitioned) and should not be resolved.
  if (registry_ && !registry_->IsUrlMapped(url, storage_key_)) {
    std::move(callback).Run(mojo::NullRemote(), std::nullopt);
    return;
  }

  BlobURLStoreImpl_ChromiumImpl::Resolve(url, std::move(callback));
}

void BlobURLStoreImpl::ResolveAsURLLoaderFactory(
    const GURL& url,
    mojo::PendingReceiver<network::mojom::URLLoaderFactory> receiver,
    ResolveAsURLLoaderFactoryCallback callback) {
  // If a URL is not mapped to the current `storage_key_`, it's likely stored
  // with a different StorageKey (partitioned) and should not be resolved.
  if (registry_ && !registry_->IsUrlMapped(url, storage_key_)) {
    std::move(callback).Run(std::nullopt, std::nullopt);
    return;
  }

  BlobURLStoreImpl_ChromiumImpl::ResolveAsURLLoaderFactory(
      url, std::move(receiver), std::move(callback));
}

void BlobURLStoreImpl::ResolveForNavigation(
    const GURL& url,
    mojo::PendingReceiver<blink::mojom::BlobURLToken> token,
    ResolveForNavigationCallback callback) {
  // If a URL is not mapped to the current `storage_key_`, it's likely stored
  // with a different StorageKey (partitioned) and should not be resolved.
  if (registry_ && !registry_->IsUrlMapped(url, storage_key_)) {
    std::move(callback).Run(std::nullopt);
    return;
  }

  BlobURLStoreImpl_ChromiumImpl::ResolveForNavigation(url, std::move(token),
                                                      std::move(callback));
}

}  // namespace storage
