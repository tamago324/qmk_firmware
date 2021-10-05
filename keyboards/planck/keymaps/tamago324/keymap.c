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
  JU_SCLN,
  JU_QUOT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_QWERTY] = LAYOUT(
      KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,        KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, \
      KC_LCTRL,      KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,        KC_J,  KC_K,    KC_L,    JU_SCLN, KC_ENT, \
      KC_LSHIFT,     KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,        KC_M,  KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX, \
      MO(_SPECIAL), _______, KC_LGUI, KC_LALT, LOWER, SFT_T(KC_SPACE),     SFT_T(KC_SPACE),  RAISE, KC_RALT, _______, _______, _______ \
    ),
    [_LOWER] = LAYOUT(
      KC_ESC,  KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  KC_PERC,       JP_AMPR, JP_QUOT, JP_ASTR, JP_LPRN, JP_RPRN, KC_DEL, \
      _______, C(KC_A), C(KC_S), C(KC_D), C(KC_F), C(KC_G),       JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC, JP_BSLS, JP_TILD, \
      _______, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B),       JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, JP_PIPE, XXXXXXX, \
      _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______ \
    ),
    [_RAISE] = LAYOUT(
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,     KC_7,     KC_8,     KC_9,    KC_0,    XXXXXXX, \
      _______, XXXXXXX, JU_QUOT, JU_QUOT, JU_QUOT, JP_TILD,        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT, XXXXXXX,  XXXXXXX, \
      _______, XXXXXXX, XXXXXXX, KC_COMM,  KC_DOT, XXXXXXX,       KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END,  XXXXXXX, XXXXXXX, \
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

  // 日本語配列の制御のためのもの
  // https://scrapbox.io/self-made-kbds-ja/QMK_Firmware_%E3%81%A7_JP_%E9%85%8D%E5%88%97%E3%81%AE%E3%82%AD%E3%83%BC%E3%83%9C%E3%83%BC%E3%83%89%E3%82%92%E4%BD%9C%E3%82%8B
  // https://discord.com/channels/376937950409392130/448305600372408326/576610674617221120
  // https://github.com/qmk/qmk_firmware/blob/master/keyboards/ergo42/keymaps/hdbx/keymap.c
  static bool lshift = false;

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

    case JU_QUOT:
      // 単体で ' でShift通すと "
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        if (lshift) {
          // https://docs.qmk.fm/#/ja/feature_macros?id=register_code16ltkcgt%e3%80%81unregister_code16ltkcgt%e3%80%81tap_code16ltkcgt
          // ここ、tap_code16 とかでもいいのかな？
          if (lshift) unregister_code(KC_LSFT);
          register_code(KC_LSFT);
          register_code(KC_2);
          unregister_code(KC_2);
          unregister_code(KC_LSFT);
          if (lshift) register_code(KC_LSFT);
        } else {
          register_code(KC_LSFT);
          register_code(KC_7);
          unregister_code(KC_7);
          unregister_code(KC_LSFT);
        }
      }
      return false;

    case JU_SCLN:
      // 単体で ; でShift通すと :
      if (record->event.pressed) {
        lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
        if (lshift) {
          if (lshift) unregister_code(KC_LSFT);
          register_code(KC_QUOT);
          unregister_code(KC_QUOT);
          if (lshift) register_code(KC_LSFT);
        } else {
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
        }
      }
      return false;

    default:
      if (record->event.pressed) {
          // LOWER でもRAISEでもない文字だった場合、戻しておく
        lower_pressed = false;
        raise_pressed = false;
      }

      break;
  }

  return true;
}
