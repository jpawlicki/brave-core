/* Copyright (c) 2024 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

const stylesheetMap = new Map<string, CSSStyleSheet>()

// Adds CSS to the document. If a stylesheet with the specified `id` has already
// been added to the document, then it will be replaced with the provided CSS.
async function addStyles(id: string, cssText: unknown) {
  if (!id) {
    throw new Error('Argument "id" cannot be empty')
  }

  let stylesheet = stylesheetMap.get(id)
  if (!stylesheet) {
    stylesheet = new CSSStyleSheet()
    stylesheetMap.set(id, stylesheet)
    document.adoptedStyleSheets.push(stylesheet)
  }

  await stylesheet.replace(String(cssText))
}

const scopeAttributeName = 'data-css-scope'

class ScopedCSSAttribute {
  [scopeAttributeName]: string

  constructor(scopeName: string) {
    this[scopeAttributeName] = scopeName
  }

  get scope() {
    return this[scopeAttributeName]
  }

  get selector() {
    return `[${scopeAttributeName}=${CSS.escape(this[scopeAttributeName])}]`
  }
}

let nextScopeID = 0xa

// A template tag that adds scoped CSS to the document. The provided CSS text
// is wrapped with a "@scope" at-rule and only applies to elements with a
// "data-css-scope" attribute whose value matches `scopeName`. The CSS rules do
// not apply to any descendant elements that have a "data-css-scope" attribute.
// Returns an object representing the CSS scope data attribute, which can be
// object-spread into a collection of HTML attributes.
export const scoped = {
  css(callsite: TemplateStringsArray, ...values: any[]) {
    const id = (nextScopeID++).toString(36)
    const attr = new ScopedCSSAttribute(id)
    addStyles(attr.selector, `
      @scope (${attr.selector}) to ([${scopeAttributeName}]) {
        ${String.raw(callsite, ...values)}
      }
    `)
    return attr
  }
}

// Returns a template tag that adds global CSS to the document. The "id"
// argument must be unique.
export function global(id: string) {
  return {
    css(callsite: TemplateStringsArray, ...values: any[]) {
      addStyles(id, String.raw(callsite, ...values))
    }
  }
}
