/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xFC, 0xCF, 0xA6, 0xCF, 0x1B, 0x18, 0x4A, 0xAF}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 10 }

#define LAYER_STATE_8BIT    // レイヤーの上限を8にする

// Shift が抜ける問題への対処法の1つらしい
#define USB_POLLING_INTERVAL_MS 10