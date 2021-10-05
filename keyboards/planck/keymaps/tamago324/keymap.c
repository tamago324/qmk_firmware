/* Copyright 2015-2017 Jack Humbert
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
#include "keymap_jp.h"

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _SPECIAL
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  S_SPACE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_QWERTY] = LAYOUT(
      KC_TAB,        JP_Q,    JP_W,    JP_E,    JP_R,  JP_T,   JP_Y,        JP_U,  JP_I,    JP_O,    JP_P,    KC_BSPC, \
      KC_LCTRL,      JP_A,    JP_S,    JP_D,    JP_F,  JP_G,   JP_H,        JP_J,  JP_K,    JP_L,    JP_SCLN, KC_ENT, \
      KC_LSHIFT,     JP_Z,    JP_X,    JP_C,    JP_V,  JP_B,   JP_N,        JP_M,  JP_COMM, JP_DOT,  JP_SLSH, XXXXXXX, \
      MO(_SPECIAL), _______, KC_LGUI, KC_LALT, LOWER, SFT_T(KC_SPACE),     SFT_T(KC_SPACE),  RAISE, KC_RALT, _______, _______, _______ \
    ),
    [_LOWER] = LAYOUT(
      KC_ESC,  JP_EXLM, JP_AT,   JP_HASH, JP_DLR,  JP_PERC,       JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, KC_DEL, \
      _______, C(JP_A), C(JP_S), C(JP_D), C(JP_F), C(JP_G),       JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC, JP_BSLS, JP_TILD,  \
      _______, C(JP_Z), C(JP_X), C(JP_C), C(JP_V), C(JP_B),       JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, JP_PIPE, XXXXXXX, \
      _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______ \
    ),
    [_RAISE] = LAYOUT(
      _______, JP_1,    JP_2,    JP_3,    JP_4,    JP_5,          JP_6,     JP_7,     JP_8,     JP_9,    JP_0,    XXXXXXX, \
      _______, JP_DQUO, JP_DQUO, JP_QUOT, JP_QUOT, JP_GRV,        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT, XXXXXXX,  XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, JP_COMM,  JP_DOT, XXXXXXX,       KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,  XXXXXXX, XXXXXXX, \
      _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______ \
    ),
    [_ADJUST] = LAYOUT(
      KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F12, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       C(KC_PGUP),  XXXXXXX,  XXXXXXX,  C(KC_PGDN), XXXXXXX,  XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, \
      _______, _______,    _______,    _______,    _______,    _______,       _______, _______, _______, _______, _______, _______ \
    ),
    [_SPECIAL] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ASRP, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_ASDN, KC_ASUP, XXXXXXX, XXXXXXX, XXXXXXX, \
      KC_ASTG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET \
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
            tap_code(KC_MHEN);
            lower_pressed = false;
        }
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
            // https://docs.qmk.fm/#/ja/feature_macros?id=register_codeltkcgt
            // キーダウンイベント
            tap_code(KC_HENK);
            raise_pressed = false;
        }
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

    // case S_SPACE:
    //     if (record->event.pressed) {
    //         // 押した
    //         sspace_pressed = true;
    //         space_after_inputed = false;
    //     } else {
    //         // 離した
    //         if (!space_after_inputed) {
    //             // もし、なにも入力されていなければ、スペースを送信
    //             tap_code(JP_SPACE);
    //         }
    //         sspace_pressed = false;
    //     }

    //     // QMK としてはデフォルトのキーコードは送信しない
    //     return false;
    //     break;

    default:
      if (record->event.pressed) {
          // LOWER でもRAISEでもない文字だった場合、戻しておく
        lower_pressed = false;
        raise_pressed = false;
      }

        // // もし、sspace が押しっぱなしだったら、Shiftを押した状態としてキーを送信する
        // if (sspace_pressed) {
        //     if (record->event.pressed) {
        //         // Shiftを押した状態でキーコードを送信する
        //         register_code16(S(keycode));
        //         unregister_code16(S(keycode));
        //         space_after_inputed = true;
        //     }
        //     return false;
        // }
      break;
  }

  return true;
}

// //キーごとに TAPPING_TERM を設定する
// uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case SFT_T(JP_SPACE):
//             // 短くする
//             return TAPPING_TERM - 100;
//         default:
//             return TAPPING_TERM;
//     }
// }
