/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/ai_chat/content/browser/full_screenshot_client.h"

#include "base/json/json_reader.h"
#include "base/json/json_writer.h"
#include "base/types/expected.h"

namespace ai_chat {

FullScreenshotClient::FullScreenshotClient(content::WebContents* web_contents)
    : devtools_agent_host_(
          content::DevToolsAgentHost::GetOrCreateFor(web_contents)) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  devtools_agent_host_->AttachClient(this);
}

FullScreenshotClient::~FullScreenshotClient() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  devtools_agent_host_->DetachClient(this);
}

void FullScreenshotClient::CaptureScreenshot(
    CaptureScreenshotCallback callback) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);

  on_screenshot_compelte_ = std::move(callback);
  base::Value::Dict screenshot_cmd;
  screenshot_cmd.Set("id", request_id_++);
  screenshot_cmd.Set("method", "Page.captureScreenshot");
  auto params = base::JSONReader::Read(R"({
    "format": "jpeg",
    "quality": 25,
    "fromSurface": true,
    "captureBeyondViewport": true
  })");
  if (params) {
    screenshot_cmd.Set("params", std::move(params.value()));
  }
  std::string json_command;
  base::JSONWriter::Write(base::Value(std::move(screenshot_cmd)),
                          &json_command);
  devtools_agent_host_->DispatchProtocolMessage(
      this, base::as_bytes(base::make_span(json_command)));
}

void FullScreenshotClient::DispatchProtocolMessage(
    content::DevToolsAgentHost* agent_host,
    base::span<const uint8_t> message) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  LOG(ERROR) << __func__;
  // TODO: check id
  std::string_view message_str(reinterpret_cast<const char*>(message.data()),
                               message.size());
  auto json_message = base::JSONReader::Read(message_str);
  if (json_message) {
    auto* data = json_message->GetDict().FindStringByDottedPath("result.data");
    if (data) {
      // LOG(ERROR) << std::endl << "base64_img = b'" << *data <<"'";
      std::move(on_screenshot_compelte_).Run(base::ok(*data));
      return;
    }
  }
  std::move(on_screenshot_compelte_)
      .Run(base::unexpected("Failed to capture screenshot"));
}

void FullScreenshotClient::AgentHostClosed(
    content::DevToolsAgentHost* agent_host) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  LOG(ERROR) << __func__;
}

bool FullScreenshotClient::MayAttachToRenderFrameHost(
    content::RenderFrameHost* render_frame_host) {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  return true;
}
bool FullScreenshotClient::IsTrusted() {
  DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
  return true;
}

}  // namespace ai_chat
