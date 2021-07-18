/* Copyright 2021 tamago324
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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY = 0,
    _LOWER,
    _RAISE
};

/* // Defines the keycodes used by our macros in process_record_user */
/* enum custom_keycodes { */
/*     LOWER = SAFE_RANGE, */
/*     RAISE */
/* }; */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        KC_A,   KC_B,        KC_D,        KC_E,
        KC_C,   MO(_LOWER),  MO(_RAISE),  KC_F
    ),
    [_LOWER] = LAYOUT(
        KC_EXLM,   KC_AT,       KC_DLR,     KC_PERC,
        KC_HASH,   MO(_LOWER),  MO(_RAISE), KC_CIRC
    ),
    [_RAISE] = LAYOUT(
        KC_1,   KC_2,        KC_4,        KC_5,
        KC_3,   MO(_LOWER),  MO(_RAISE),  KC_6
    )
};

