/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at https://mozilla.org/MPL/2.0/. */

import './brave_account_dialog.js'
import { html } from '//resources/lit/v3_0/lit.rollup.js'
import { SettingsBraveAccountForgotPasswordDialogElement } from './brave_account_forgot_password_dialog.js'

export function getHtml(this: SettingsBraveAccountForgotPasswordDialogElement) {
  return html`<!--_html_template_start_-->
    <settings-brave-account-dialog show-back-button horizontal-buttons
      header-text-top="Forgot your password?"
      header-text-bottom="Confirm your Brave account email and we'll email you a link to reset your password. The link will only be valid for [X] hours.">
      <div slot="inputs">
        <leo-input id="email" placeholder="Enter your email address" @input=${this.onEmailInput}>
          <div class="label">Email address</div>
        </leo-input>
      </div>
      <div slot="buttons">
        <leo-button size="medium" kind="plain-faint" @click=${() => this.fire('cancel-button-clicked')}>
          Cancel
        </leo-button>
        <leo-button size="medium" ?isDisabled=${!this.isEmailValid}>
          Reset your password
        </leo-button>
      </div>
    </settings-brave-account-dialog>
  <!--_html_template_end_-->`
}
