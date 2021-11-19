/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  JU_SCLN,
  JU_QUOT
};

enum combo_events {
  CMB_ESCAPE,
  CMB_SEMICORON,
  CMB_CTRL_SPACE,
  CMB_SLASH
};

// コンボ
// DSでEscape
const uint16_t PROGMEM comb_keys_Escape[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM comb_keys_semicoron[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM comb_keys_ctrl_space[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM comb_keys_slash[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CMB_ESCAPE] = COMBO(comb_keys_Escape, KC_ESC),
  [CMB_SEMICORON] = COMBO(comb_keys_semicoron, JU_SCLN),
  [CMB_CTRL_SPACE] = COMBO(comb_keys_ctrl_space, C(KC_SPACE)),
  [CMB_SLASH] = COMBO(comb_keys_slash, KC_SLSH),
};

/* void process_combo_event(uint16_t combo_index, bool pressed) { */
/*   switch(combo_index) { */
/*     case CMB_CTRL_SPACE: */
/*       if (pressed) { */
/*         tap_code16(C(KC_SPACE)); */
/*       } */
/*       break; */
/*   } */
/* } */

/* // Alt-Q で alt-tab を送信する */
/* const key_override_t alt_tab = ko_make_basic(MOD_MASK_ALT, KC_Q, LALT(KC_TAB)); */
/*  */
/* const key_override_t **key_overrides = (const key_override_t *[]) { */
/*   &alt_tab, */
/*   NULL */
/* }; */

// Delete
const key_override_t shift_bspc_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DELETE);
// <
const key_override_t syounari = ko_make_basic(MOD_MASK_CTRL, KC_COMM, S(KC_COMM));
// >
const key_override_t dainari = ko_make_basic(MOD_MASK_CTRL, KC_DOT, S(KC_DOT));

const key_override_t **key_overrides = (const key_override_t *[]) {
  &shift_bspc_delete,
  &syounari,
  &dainari,
  NULL
};

// tap-dance
enum {
  TD_ALT_GUI,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // 1回のタップで ALT、2回のタップで GUI
  [TD_ALT_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3( \
         KC_TAB,  KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y, KC_U,  KC_I,    KC_O,    KC_BSPC, \
         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H, KC_J,  KC_K,    KC_L,    KC_P, \
  LSFT_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B,                          KC_N, KC_M,  KC_COMM, KC_DOT,  KC_Q, \
                    TD(TD_ALT_GUI),  LOWER,  LCTL_T(KC_SPACE),     SFT_T(KC_ENT), RAISE, KC_LALT  \
  ),
  [_LOWER] = LAYOUT_split_3x5_3( \
      KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  KC_PERC,              JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, \
      KC_LCTRL, XXXXXXX, S(KC_COMM), S(KC_DOT), JP_TILD,         JP_MINS, JP_EQL,  JP_LBRC, JP_RBRC, JP_COLN, \
      SWIN(KC_S), XXXXXXX, XXXXXXX, JP_BSLS, JP_PIPE,              JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, S(KC_SLSH),\
                        _______, _______, _______,              KC_SLSH, _______, _______ \
  ),
  [_RAISE] = LAYOUT_split_3x5_3( \
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                 KC_6,     KC_7,     KC_8,    KC_9,    KC_0,     \
      KC_LCTRL, JU_QUOT, JU_QUOT, JU_QUOT, JP_GRV,               KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, JP_COLN, \
      _______, XXXXXXX, KC_SLSH, KC_SLSH, KC_SLSH,              KC_HOME,  KC_PGUP,  KC_PGDN, KC_END,  KC_SLSH,   \
                        _______, _______, _______,              _______, _______, _______  \
  ),
  [_ADJUST] =  LAYOUT_split_3x5_3( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,               KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,    \
      KC_LCTRL, JP_DQUO,   JP_DQUO, JP_DQUO, JP_GRV,             C(KC_PGUP), XXXXXXX, XXXXXXX, C(KC_PGDN), KC_F12,\
      KC_F11, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, \
                        _______, _______, _______,             _______, _______, RESET                           \
  )
};

static bool lower_pressed = false;
static bool raise_pressed = false;
static bool zshift_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

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
      lower_pressed = false;
      raise_pressed = false;
      return false;
      break;

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
      lower_pressed = false;
      raise_pressed = false;
      return false;
      break;

    case LSFT_T(KC_Z):
      if (record->event.pressed) {
        zshift_pressed = true;

        // LOWER でもRAISEでもない文字だった場合、戻しておく
        lower_pressed = false;
        raise_pressed = false;
      } else {
        zshift_pressed = false;
      }
      break;

    case KC_E:
      if (record->event.pressed) {
          if (zshift_pressed) {
            lower_pressed = false;
            raise_pressed = false;
            zshift_pressed = false;

            // もし、Shift が押されていると認識したら、はなして Z を送信する (Z を2回送信しないようにするための処理)
            lshift = keyboard_report->mods & MOD_BIT(KC_LSFT);
            if (lshift) {
              unregister_code(KC_LSFT);
              tap_code(KC_Z);
            }
            tap_code(KC_E);
            return false;
          }
      }
      break;

    default:
      if (record->event.pressed) {
          // LOWER でもRAISEでもない文字だった場合、戻しておく
        lower_pressed = false;
        raise_pressed = false;
        zshift_pressed = false;
      }

      break;
  }

  return true;
}

// https://docs.qmk.fm/#/tap_hold?id=tapping-term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_ALT_GUI):
            return TAPPING_TERM + 500;
            break;
        /* case LCTL_T(KC_A): */
        /*     return TAPPING_TERM + 5; */
        /*     break; */
        case LSFT_T(KC_Z):
            return TAPPING_TERM + 30;
            break;
        case SFT_T(KC_ENT):
            return TAPPING_TERM - 20;
            break;
        default:
            return TAPPING_TERM;
            break;
    }
}
