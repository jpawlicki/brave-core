// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_COMPONENTS_PSST_BROWSER_CONTENT_PSST_TAB_HELPER_H_
#define BRAVE_COMPONENTS_PSST_BROWSER_CONTENT_PSST_TAB_HELPER_H_

#include <string>

#include "base/component_export.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "brave/components/psst/browser/core/matched_rule.h"
#include "brave/components/script_injector/common/mojom/script_injector.mojom.h"
#include "build/build_config.h"
#include "components/sessions/core/session_id.h"
#include "content/public/browser/media_player_id.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "mojo/public/cpp/bindings/associated_remote.h"

namespace psst {

class PsstRuleRegistry;

// Used to inject PSST scripts into the page, based on PSST rules.
class COMPONENT_EXPORT(PSST_BROWSER_CONTENT) PsstTabHelper
    : public content::WebContentsObserver,
      public content::WebContentsUserData<PsstTabHelper> {
 public:
  static void MaybeCreateForWebContents(content::WebContents* contents,
                                        const int32_t world_id);
  ~PsstTabHelper() override;
  PsstTabHelper(const PsstTabHelper&) = delete;
  PsstTabHelper& operator=(const PsstTabHelper&) = delete;

 private:
  PsstTabHelper(content::WebContents*, const int32_t world_id);
  // Insert scripts for the rfh using the script_injector mojo interface.
  void InsertScriptInPage(
      const content::GlobalRenderFrameHostId& render_frame_host_id,
      const std::string& script,
      content::RenderFrameHost::JavaScriptResultCallback cb);

  // Script injection methods. The flow is:
  // 1. insert get user script and get logged in user id.
  // 2. if valid and we need to, insert test script.
  // 3. if we can make changes, insert policy script to make changes.
  void InsertUserScript(
      const content::GlobalRenderFrameHostId& render_frame_host_id,
      MatchedRule rule);
  void OnUserScriptResult(
      MatchedRule rule,
      const content::GlobalRenderFrameHostId& render_frame_host_id,
      base::Value value);
  void OnTestScriptResult(
      const std::string& policy_script,
      const content::GlobalRenderFrameHostId& render_frame_host_id,
      base::Value value);

  // Get the remote used to send the script to the renderer.
  mojo::AssociatedRemote<script_injector::mojom::ScriptInjector>& GetRemote(
      content::RenderFrameHost* rfh);
  friend class content::WebContentsUserData<PsstTabHelper>;

  // content::WebContentsObserver overrides
  void DidFinishNavigation(
      content::NavigationHandle* navigation_handle) override;
  void DocumentOnLoadCompletedInPrimaryMainFrame() override;

  const int32_t world_id_;
  const raw_ptr<PsstRuleRegistry> psst_rule_registry_;  // NOT OWNED
  bool should_process_ = false;
  // The remote used to send the script to the renderer.
  mojo::AssociatedRemote<script_injector::mojom::ScriptInjector>
      script_injector_remote_;
  base::WeakPtrFactory<PsstTabHelper> weak_factory_{this};

  WEB_CONTENTS_USER_DATA_KEY_DECL();
};

}  // namespace psst

#endif  // BRAVE_COMPONENTS_PSST_BROWSER_CONTENT_PSST_TAB_HELPER_H_
