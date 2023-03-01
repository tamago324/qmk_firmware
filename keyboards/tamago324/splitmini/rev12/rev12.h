/* Copyright 2022 tamago324
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
	L00, L01, L02, L03, L04,       R00, R01, R02, R03, R04, \
	L10, L11, L12, L13, L14,       R10, R11, R12, R13, R14, \
	L20, L21, L22, L23, L24,       R20, R21, R22, R23, R24, \
	          L32, L33, L34,       R30, R31, R32           \
) \
{ \
	{ L00,   L01,     L02,   L03,  L04}, \
	{ L10,   L11,     L12,   L13,  L14}, \
	{ L20,   L21,     L22,   L23,  L24}, \
	{ KC_NO, KC_NO,   L32,   L33,  L34}, \
    { R04,  R03,  R02,   R01,   R00   }, \
    { R14,  R13,  R12,   R11,   R10   }, \
    { R24,  R23,  R22,   R21,   R20   }, \
    { KC_NO,  KC_NO,  R32,   R31,   R30 }  \
}

typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi_idx;
        uint8_t scrl_div;
        uint8_t rotation_angle;
        int8_t scrl_inv;
        bool scrl_mode;
        report_mouse_t last_mouse;
    };
} splitmini_config_t;



extern splitmini_config_t splitmini_config;

// https://github.com/aki27kbd/cocot36plus/blob/main/doc/buildguide.md#%E3%82%AB%E3%82%B9%E3%82%BF%E3%83%A0%E3%82%AD%E3%83%BC%E3%82%B3%E3%83%BC%E3%83%89
enum splitmini_keycodes {
    // CPIを変更する
    CPI_DEC = SAFE_RANGE,
    CPI_INC,
    // スクロールの速度を変更する
    SCRL_SW,
    // Y軸を時計回りに回す
    ROT_RIGHT,
    // Y軸を反時計回りに回す
    ROT_LEFT,
    // 押されている間、スクロールモードになる
    SCRL_MO,
    SCRL_TO,
    SCRL_IN,
    SPLITMINI_SAFE_RANGE,
};

bool splitmini_get_scroll_mode(void);
void splitmini_set_scroll_mode(bool mode);
