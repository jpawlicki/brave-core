/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_APP_BRAVE_COMMAND_IDS_H_
#define BRAVE_APP_BRAVE_COMMAND_IDS_H_

// First brave id must be higher than last chrome command.
// Check chrome/app/chrome_command_ids.h when rebase.
// ID of IDC_BRAVE_COMANDS_START and first brave command should be same.

// If new main menu items are added, please consider adding a case for it
// in the switch statement of BraveAppMenu::RecordMenuUsage for P3A purposes

// PLEASE DO NOT CHANGE THE VALUE OF EXISTING VALUE.
// That could break custom shortcut feature
#define IDC_BRAVE_COMMANDS_START 56000
#define IDC_SHOW_BRAVE_REWARDS 56000
#define IDC_NEW_TOR_CONNECTION_FOR_SITE 56002
#define IDC_NEW_OFFTHERECORD_WINDOW_TOR 56003
#define IDC_CONTENT_CONTEXT_OPENLINKTOR 56004
#define IDC_SHOW_BRAVE_SYNC 56005
#define IDC_SHOW_BRAVE_WALLET 56006
#define IDC_TOGGLE_AI_CHAT 56007
#define IDC_SHOW_BRAVE_WEBCOMPAT_REPORTER 56009
#define IDC_SPEEDREADER_ICON_ONCLICK 56010
#define IDC_SIDEBAR_SHOW_OPTION_MENU 56011
#define IDC_SIDEBAR_SHOW_OPTION_ALWAYS 56012
#define IDC_SIDEBAR_SHOW_OPTION_MOUSEOVER 56013
#define IDC_SIDEBAR_SHOW_OPTION_NEVER 56015
#define IDC_SHOW_BRAVE_WALLET_PANEL 56026
#define IDC_CLOSE_BRAVE_WALLET_PANEL 56027
#define IDC_SHOW_BRAVE_VPN_PANEL 56028
#define IDC_BRAVE_VPN_MENU 56029
#define IDC_TOGGLE_BRAVE_VPN_TOOLBAR_BUTTON 56030
#define IDC_SEND_BRAVE_VPN_FEEDBACK 56031
#define IDC_ABOUT_BRAVE_VPN 56032
#define IDC_MANAGE_BRAVE_VPN_PLAN 56033
#define IDC_TOGGLE_BRAVE_VPN 56034
#define IDC_CONTENT_CONTEXT_FORCE_PASTE 56039
#define IDC_COPY_CLEAN_LINK 56040
#define IDC_TOGGLE_TAB_MUTE 56041
#define IDC_SIDEBAR_TOGGLE_POSITION 56042
#define IDC_CONTENT_CONTEXT_COPY_TEXT_FROM_IMAGE 56043
#define IDC_TOGGLE_SIDEBAR 56044

#define IDC_TOGGLE_VERTICAL_TABS 56045
#define IDC_TOGGLE_VERTICAL_TABS_WINDOW_TITLE 56046

#define IDC_CONFIGURE_BRAVE_NEWS 56047

#define IDC_CONFIGURE_SHORTCUTS 56048

#define IDC_SHOW_BRAVE_TALK 56049
#define IDC_TOGGLE_BRAVE_VPN_TRAY_ICON 56050
#define IDC_CONTENT_CONTEXT_IMPORT_IPNS_KEYS_START 56100
#define IDC_CONTENT_CONTEXT_IMPORT_IPNS_KEYS_END 56199

#define IDC_BRAVE_BOOKMARK_BAR_SUBMENU 56200
#define IDC_BRAVE_BOOKMARK_BAR_ALWAYS 56201
#define IDC_BRAVE_BOOKMARK_BAR_NTP 56202
#define IDC_BRAVE_BOOKMARK_BAR_NEVER 56203

#define IDC_TOGGLE_SHIELDS 56204
#define IDC_TOGGLE_JAVASCRIPT 56205

#define IDC_SHOW_PLAYLIST_BUBBLE 56206

#define IDC_GROUP_TABS_ON_CURRENT_ORIGIN 56207
#define IDC_MOVE_GROUP_TO_NEW_WINDOW 56208
#define IDC_CLOSE_DUPLICATE_TABS 56209
#define IDC_WINDOW_CLOSE_TABS_TO_LEFT 56210
#define IDC_WINDOW_CLOSE_UNPINNED_TABS 56211
#define IDC_WINDOW_ADD_ALL_TABS_TO_NEW_GROUP 56212

#define IDC_TOGGLE_VERTICAL_TABS_EXPANDED 56215

#define IDC_WINDOW_MUTE_ALL_TABS 56220
#define IDC_WINDOW_MUTE_OTHER_TABS 56221
#define IDC_WINDOW_UNMUTE_ALL_TABS 56222

#define IDC_SCROLL_TAB_TO_TOP 56223
#define IDC_SCROLL_TAB_TO_BOTTOM 56224

#define IDC_BRAVE_SEND_TAB_TO_SELF 56225

// AI chat commands.
#define IDC_AI_CHAT_CONTEXT_SUMMARIZE_TEXT 56226
#define IDC_AI_CHAT_CONTEXT_LEO_TOOLS 56227
#define IDC_AI_CHAT_CONTEXT_EXPLAIN 56228
#define IDC_AI_CHAT_CONTEXT_PARAPHRASE 56229
#define IDC_AI_CHAT_CONTEXT_CREATE_TAGLINE 56230
#define IDC_AI_CHAT_CONTEXT_CREATE_SOCIAL_MEDIA_POST 56231
#define IDC_AI_CHAT_CONTEXT_CREATE_SOCIAL_MEDIA_COMMENT_SHORT 56232
#define IDC_AI_CHAT_CONTEXT_CREATE_SOCIAL_MEDIA_COMMENT_LONG 56233
#define IDC_AI_CHAT_CONTEXT_CHANGE_LENGTH 56234
#define IDC_AI_CHAT_CONTEXT_IMPROVE 56235
#define IDC_AI_CHAT_CONTEXT_PERSUASIVE_TONE 56236
#define IDC_AI_CHAT_CONTEXT_CHANGE_TONE 56237
#define IDC_AI_CHAT_CONTEXT_ACADEMICIZE 56238
#define IDC_AI_CHAT_CONTEXT_PROFESSIONALIZE 56239
#define IDC_AI_CHAT_CONTEXT_CASUALIZE 56240
#define IDC_AI_CHAT_CONTEXT_FUNNY_TONE 56241
#define IDC_AI_CHAT_CONTEXT_SHORTEN 56242
#define IDC_AI_CHAT_CONTEXT_EXPAND 56243
#define IDC_AI_CHAT_CONTEXT_REWRITE 56244
#define IDC_OPEN_FULL_PAGE_CHAT 56245

// Bookmark commands.
#define IDC_TOGGLE_ALL_BOOKMARKS_BUTTON_VISIBILITY 56300
#define IDC_EXPORT_ALL_BOOKMARKS 56312

#define IDC_COMMANDER 56301

#define IDC_WINDOW_GROUP_UNGROUPED_TABS 56302
#define IDC_WINDOW_UNGROUP_GROUP 56303
#define IDC_WINDOW_REMOVE_TAB_FROM_GROUP 56304
#define IDC_WINDOW_UNGROUP_ALL_TABS 56305
#define IDC_WINDOW_NAME_GROUP 56306
#define IDC_WINDOW_NEW_TAB_IN_GROUP 56307
#define IDC_WINDOW_TOGGLE_GROUP_EXPANDED 56308
#define IDC_WINDOW_CLOSE_UNGROUPED_TABS 56309
#define IDC_WINDOW_CLOSE_TABS_NOT_IN_CURRENT_GROUP 56310
#define IDC_WINDOW_CLOSE_GROUP 56311

#define IDC_WINDOW_BRING_ALL_TABS 56320

// Commands related to split view
#define IDC_NEW_SPLIT_VIEW 56325
#define IDC_TILE_TABS 56326
#define IDC_BREAK_TILE 56327
#define IDC_SWAP_SPLIT_VIEW 56328
#define IDC_CONTENT_CONTEXT_OPENLINK_SPLIT_VIEW 56329

// Wayback machine
#define IDC_SHOW_WAYBACK_MACHINE_BUBBLE 56350

// Adblock (user-defined cosmetic filters)
#define IDC_ADBLOCK_CONTEXT_BLOCK_ELEMENTS 56351

#define IDC_SHOW_APPS_PAGE 56352

#define IDC_BRAVE_COMMANDS_LAST 57000

#endif  // BRAVE_APP_BRAVE_COMMAND_IDS_H_
