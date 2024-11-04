/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * you can obtain one at https://mozilla.org/MPL/2.0/. */

import { CrDialogElement } from '//resources/cr_elements/cr_dialog/cr_dialog.js'
import { CrLitElement } from '//resources/lit/v3_0/lit.rollup.js'
import { getCss } from './brave_account_dialog.css.js'
import { getHtml } from './brave_account_dialog.html.js'

/**
 * @fileoverview
 * 'settings-brave-account-dialog'...
 */

export interface SettingsBraveAccountDialogElement {
  $: {
    dialog: CrDialogElement,
  }
}

export class SettingsBraveAccountDialogElement extends CrLitElement {
  static get is() {
    return 'settings-brave-account-dialog'
  }

  static override get styles() {
    return getCss()
  }

  override render() {
    return getHtml.bind(this)()
  }

  static override get properties() {
    return {
      showBackButton: { type: Boolean },
      headerTextTop: { type: String },
      headerTextBottom: { type: String },
      horizontalButtons: { type: Boolean },
    }
  }

  protected showBackButton: boolean
  protected headerTextTop: string
  protected headerTextBottom: string
  protected horizontalButtons: boolean
}

declare global {
  interface HTMLElementTagNameMap {
    'settings-brave-account-dialog': SettingsBraveAccountDialogElement
  }
}

customElements.define(
  SettingsBraveAccountDialogElement.is, SettingsBraveAccountDialogElement)
