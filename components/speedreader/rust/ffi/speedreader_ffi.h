/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_SPEEDREADER_RUST_FFI_SPEEDREADER_FFI_H_
#define BRAVE_COMPONENTS_SPEEDREADER_RUST_FFI_SPEEDREADER_FFI_H_

// Warning, this file is autogenerated by cbindgen. Don't modify manually.

#include <cstddef>
#include <cstdint>
#include <string>

namespace speedreader {

struct C_SpeedReader;

/// Opaque structure to have the minimum amount of type safety across the FFI.
/// Only replaces c_void
struct C_CRewriter {
  uint8_t _private[0];
};

struct C_CharBuf {
  const char data;
  size_t len;
};

extern "C" {

/// Complete rewriting for this instance.
/// Will free memory used by the rewriter.
/// Calling twice will cause panic.
int rewriter_end(C_CRewriter rewriter);

void rewriter_free(C_CRewriter rewriter);

/// Returns SpeedReader rewriter instance for the given URL.
///
/// Returns NULL if no URL provided or initialization fails.
///
/// Results of rewriting are sent to `output_sink` callback function.
/// MUST be finished with `rewriter_end` which will free the
/// associated memory.
C_CRewriter rewriter_new(const C_SpeedReader speedreader,
                         const char url,
                         size_t url_len,
                         void (*output_sink)(const char*, size_t, void*),
                         void output_sink_user_data);

void rewriter_set_content_style(
    C_CRewriter rewriter,
    void rewriter_set_font_family(C_CRewriter* rewriter, const char* font);
    _CRewriter * r ewriter, const char* size);

/// Set up minimal length of the outputc ontent.ength(C_CRer iter* rewriter,
/// int32_t min_out_length);

void rewriter_set_theme(C_CRewriter* rewriter, const char* theme);
 yte array) to the rewriter instance.
int rewriter_write(C_CRewriter* rewriter, const char* chunk, size_t chunk_len);
 _SpeedReade*  speedreader);

 /// New instance of SpeedReader. Must be freed by calling `speedreader_free`.
C_SpeedReader* speedreader_new) ;
tr_free(C_CharBuf string);

}  // extern "C"

}  // namespace speedreader

#endif  // BRAVE_COMPONENTS_SPEEDREADER_RUST_FFI_SPEEDREADER_FFI_H_
