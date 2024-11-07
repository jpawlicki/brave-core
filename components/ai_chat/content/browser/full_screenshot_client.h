/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_AI_CHAT_CONTENT_BROWSER_FULL_SCREENSHOT_CLIENT_H_
#define BRAVE_COMPONENTS_AI_CHAT_CONTENT_BROWSER_FULL_SCREENSHOT_CLIENT_H_

#include "base/sequence_checker.h"
#include "base/types/expected.h"
#include "content/public/browser/devtools_agent_host.h"
#include "content/public/browser/devtools_agent_host_client.h"
#include "content/public/browser/web_contents.h"

namespace ai_chat {

class FullScreenshotClient : public content::DevToolsAgentHostClient {
  public:
    explicit FullScreenshotClient(content::WebContents* web_contents);
    ~FullScreenshotClient() override;
    FullScreenshotClient(const FullScreenshotClient&) = delete;
    FullScreenshotClient& operator=(const FullScreenshotClient&) = delete;

  // <base64 encoded image, error>
  using CaptureScreenshotCallback = base::OnceCallback<void(base::expected<std::string, std::string>)>;
  void CaptureScreenshot(CaptureScreenshotCallback callback);
  
  private:
    // content::DevToolsAgentHostClient
    void DispatchProtocolMessage(
        content::DevToolsAgentHost* agent_host,
        base::span<const uint8_t> message) override;
    void AgentHostClosed(content::DevToolsAgentHost* agent_host) override;
    bool MayAttachToRenderFrameHost(content::RenderFrameHost* render_frame_host) override;
    bool IsTrusted() override;

  int request_id_ = 0;
  CaptureScreenshotCallback on_screenshot_compelte_;
  scoped_refptr<content::DevToolsAgentHost> devtools_agent_host_;
  SEQUENCE_CHECKER(sequence_checker_);
};

} // namespace ai_chat

#endif  // BRAVE_COMPONENTS_AI_CHAT_CONTENT_BROWSER_FULL_SCREENSHOT_CLIENT_H_
