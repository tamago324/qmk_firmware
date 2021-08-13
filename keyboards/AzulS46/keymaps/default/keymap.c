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

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_QWERTY] = LAYOUT(
      XXXXXXX,                                                                                                     XXXXXXX,
      KC_TAB,    KC_Q, KC_W, KC_E, KC_R, KC_T,           KC_Y,           KC_U,  KC_I,    KC_O,        KC_P,    KC_BSPC,
      KC_LCTRL,  KC_A, KC_S, KC_D, KC_F, KC_G,           KC_H,           KC_J,  KC_K,    KC_L,        KC_SCLN, KC_QUOT,
      KC_LSHIFT, KC_Z, KC_X, KC_C, KC_V, KC_B,           KC_N,           KC_M,  KC_COMM, KC_DOT,      KC_SLSH, KC_RSFT,
                 KC_LGUI, KC_LALT, LOWER, KC_SPC,        SFT_T(KC_ENT),  RAISE, KC_RALT, OSL(_ADJUST)
    ),
    [_LOWER] = LAYOUT(
      XXXXXXX,                                                                                                     XXXXXXX,
      KC_ESC,  KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
      _______, XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,       KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,  \
      _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), XXXXXXX,       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD, \
                           _______,    _______,    _______,    _______,       _______, _______, _______, _______ \
    ),
    [_RAISE] = LAYOUT(
      XXXXXXX,                                                                                                     XXXXXXX,
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,     KC_7,     KC_8,     KC_9,    KC_0,     XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT, XXXXXXX,  XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,  XXXXXXX,  XXXXXXX, \
                        _______, _______, _______, _______,       _______,  _______, _______, _______ \
    ),
    [_ADJUST] = LAYOUT(
      XXXXXXX,                                                                                                     XXXXXXX,
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F12, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, \
                        _______, _______, _______, _______,       _______,  _______, _______, _______ \
    )
};

static bool lower_pressed = false;
static bool raise_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  // lower で無変換、raise で変換
  // https://okapies.hateblo.jp/entry/2019/02/02/133953
  // https://gist.github.com/okapies/5d13a174cbb13ce34dbd9faede9d0b71#file-keymap-c-L99-L164
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        lower_pressed = true;

        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (lower_pressed) {
          register_code(KC_HENK);
          unregister_code(KC_HENK);
        }
        lower_pressed = false;
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        if (raise_pressed) {
          register_code(KC_MHEN);
          unregister_code(KC_MHEN);
        }
        raise_pressed = false;
      }

      return false;
      break;

    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;

    default:
      if (record->event.pressed) {
        lower_pressed = false;
        raise_pressed = false;
      }
      break;
  }

  return true;
}
