/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

import { html } from '//resources/lit/v3_0/lit.rollup.js'
import { SettingsBraveAccountCreateDialogElement } from './brave_account_create_dialog.js'

export function getHtml(this: SettingsBraveAccountCreateDialogElement) {
  return html`<!--_html_template_start_-->
    <settings-brave-account-dialog dialog-description="$i18n{braveAccountCreateDialogDescription}"
                                   dialog-title="$i18n{braveAccountCreateDialogTitle}"
                                   show-back-button>
      <div slot="inputs">
        <leo-input placeholder="$i18n{braveAccountEmailAddressInputPlaceholder}"
                   showErrors
                   @input=${this.onEmailAddressInput}>
          <div class="label ${this.emailAddress.length !== 0 && !this.isEmailAddressValid
                           || this.isEmailAddressValid && this.emailAddressEndsWithBraveAlias ?
                            'red' : ''}">
            $i18n{braveAccountEmailAddressInputLabel}
          </div>
          <div class="dropdown ${this.isEmailAddressValid && this.emailAddressEndsWithBraveAlias ? 'visible' : ''}"
               id="brave-alias-dropdown"
               slot="errors">
            <leo-icon name="warning-triangle-filled"></leo-icon>
            <div>$i18n{braveAccountEmailAddressInputErrorMessage}</div>
          </div>
        </leo-input>
        <leo-input placeholder="$i18n{braveAccountAccountNameInputPlaceholder}"
                   @input=${this.onAccountNameInput}>
          <div class="label">$i18n{braveAccountAccountNameInputLabel}</div>
        </leo-input>
        <leo-input placeholder="$i18n{braveAccountPasswordInputPlaceholder}"
                   showErrors
                   type="password"
                   @input=${this.onCreatePasswordInput}>
          <div class="label">$i18n{braveAccountCreatePasswordInputLabel}</div>
          <leo-icon name="eye-off"
                    slot="right-icon"
                    @click=${this.OnEyeIconClicked}>
          </leo-icon>
          <div slot="errors" class="dropdown ${this.percent !== 0 ? 'visible' : ''} ${this.getCategory()}"
                             id="password-dropdown">
            <leo-tooltip mode="default"
                         mouseleaveTimeout="0"
                         placement="bottom">
              <div class="password-strength-indicator">
                <div class="password-strength-bar">
                  <div class="password-strength"
                       style="--password-strength: ${this.percent}">
                  </div>
                </div>
                <div class="password-strength-category">
                  ${(() => {
                    switch(this.getCategory()) {
                      case 'weak':
                        return html`$i18n{braveAccountPasswordStrengthCheckerWeak}`
                      case 'medium':
                        return html`$i18n{braveAccountPasswordStrengthCheckerMedium}`
                      case 'strong':
                        return html`$i18n{braveAccountPasswordStrengthCheckerStrong}`
                    }
                  })()}
                </div>
              </div>
              <div slot="content">
                $i18n{braveAccountPasswordStrengthCheckerTooltipTitle}
                ${this.regexps.map(([_, requirement_met, text]) => html`
                  <div class="password-requirement ${requirement_met ? 'requirement-met' : ''}">
                    <leo-icon name=${requirement_met ? 'check-circle-outline' : 'close-circle'}></leo-icon>
                    ${text}
                  </div>`
                )}
              </div>
            </leo-tooltip>
          </div>
        </leo-input>
        <leo-input placeholder="$i18n{braveAccountConfirmPasswordInputPlaceholder}"
                   showErrors
                   type="password"
                   @input=${this.onConfirmPasswordInput}>
          <div class="label ${this.passwordConfirmation.length !== 0
                           && this.passwordConfirmation !== this.password ?
                              'red' : ''}">
            $i18n{braveAccountConfirmPasswordInputLabel}
          </div>
          <leo-icon name="eye-off"
                    slot="right-icon"
                    @click=${this.OnEyeIconClicked}>
          </leo-icon>
          <div class="dropdown ${this.passwordConfirmation.length !== 0 ? 'visible' : ''}"
               id="password-confirmation-dropdown"
               slot="errors">
            <leo-icon name=${this.getIconName()}></leo-icon>
            <div>
              ${this.icon === 'check-circle-filled'
                ? html`$i18n{braveAccountConfirmPasswordInputSuccessMessage}`
                : html`$i18n{braveAccountConfirmPasswordInputErrorMessage}`
              }
            </div>
          </div>
        </leo-input>
        <leo-checkbox @change=${this.onChange}>
          <div>
            $i18nRaw{braveAccountConsentCheckboxLabel}
          </div>
        </leo-checkbox>
      </div>
      <div slot="buttons">
        <leo-button ?isDisabled=${!this.isEmailAddressValid
                               || this.isEmailAddressValid && this.emailAddressEndsWithBraveAlias
                               || !this.isAccountNameValid
                               || this.percent !== 100
                               || this.passwordConfirmation !== this.password
                               || !this.isChecked}
                    @click=${() => this.fire('create-account-button-clicked')}>
          $i18n{braveAccountCreateAccountButtonLabel}
        </leo-button>
      </div>
    </settings-brave-account-dialog>
  <!--_html_template_end_-->`
}
