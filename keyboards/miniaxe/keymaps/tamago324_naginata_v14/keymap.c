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
// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
// 薙刀式

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _LOWER,
  _RAISE,
  _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  EISU = NG_SAFE_RANGE,
  KANA2,
  QWERTY,
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
  CMB_MINUS1,
  CMB_DEL,
  CMB_ESCAPE2
};

// コンボ
// TODO: LOWER でも dash をできるようにする
const uint16_t PROGMEM comb_keys_Escape[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM comb_keys_Escape2[] = {NG_S, NG_D, COMBO_END};
const uint16_t PROGMEM comb_keys_semicoron[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM comb_keys_ctrl_space[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM comb_keys_dash[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM comb_keys_delete[] = {KC_O, KC_BSPC, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CMB_ESCAPE] = COMBO_ACTION(comb_keys_Escape),
  [CMB_ESCAPE2] = COMBO_ACTION(comb_keys_Escape2),
  [CMB_SEMICORON] = COMBO(comb_keys_semicoron, JU_SCLN),
  [CMB_CTRL_SPACE] = COMBO(comb_keys_ctrl_space, C(KC_SPACE)),
  [CMB_MINUS1] = COMBO(comb_keys_dash, JP_MINS),
  [CMB_DEL] = COMBO(comb_keys_delete, KC_DELETE),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CMB_ESCAPE:
    case CMB_ESCAPE2:
      if (pressed) {
        tap_code16(KC_ESC);
        naginata_off();
      }
      break;
  }
}

/* // Alt-Q で alt-tab を送信する */
/* const key_override_t alt_tab = ko_make_basic(MOD_MASK_ALT, KC_Q, LALT(KC_TAB)); */
/*  */
/* const key_override_t **key_overrides = (const key_override_t *[]) { */
/*   &alt_tab, */
/*   NULL */
/* }; */

// // Delete
// const key_override_t shift_bspc_delete = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DELETE);
// // <
// const key_override_t syounari = ko_make_basic(MOD_MASK_CTRL, KC_COMM, S(KC_COMM));
// // >
// const key_override_t dainari = ko_make_basic(MOD_MASK_CTRL, KC_DOT, S(KC_DOT));
//
// const key_override_t **key_overrides = (const key_override_t *[]) {
//   &shift_bspc_delete,
//   &syounari,
//   &dainari,
//   NULL
// };

// // tap-dance
// enum {
//   TD_ALT_GUI,
// };
//
// qk_tap_dance_action_t tap_dance_actions[] = {
//   // 1回のタップで ALT、2回のタップで GUI
//   [TD_ALT_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI)
// };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3( \
         KC_TAB,  KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y, KC_U,  KC_I,    KC_O,    KC_BSPC, \
         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H, KC_J,  KC_K,    KC_L,    KC_P, \
  LSFT_T(KC_Z),   KC_X,    KC_C,    KC_V,    KC_B,                          KC_N, KC_M,  KC_COMM, KC_DOT,  KC_Q, \
                    KC_LALT,  LOWER,  LCTL_T(KC_SPACE),     SFT_T(KC_ENT), RAISE, KC_LGUI  \
  ),
  [_LOWER] = LAYOUT_split_3x5_3( \
      KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  KC_PERC,              JP_CIRC, JP_AMPR, JP_ASTR, JP_LPRN, JP_RPRN, \
      KC_LCTRL, XXXXXXX, S(KC_COMM), S(KC_DOT), JP_TILD,         KC_SLSH, JP_EQL,  JP_LBRC, JP_RBRC, JP_COLN, \
      SWIN(KC_S), XXXXXXX, JP_PIPE, JP_BSLS, XXXXXXX,              JP_UNDS, JP_PLUS, JP_LCBR, JP_RCBR, S(KC_SLSH),\
                        _______, _______, _______,              _______, _______, _______ \
  ),
  [_RAISE] = LAYOUT_split_3x5_3( \
      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                 KC_6,     KC_7,     KC_8,    KC_9,    KC_0,     \
      KC_LCTRL, JU_QUOT, JU_QUOT, JU_QUOT, JP_GRV,               KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, JP_COLN, \
      _______, XXXXXXX, KC_SLSH, KC_SLSH, KC_SLSH,              KC_HOME,  KC_PGUP,  KC_PGDN, KC_END,  XXXXXXX,   \
                        _______, _______, _______,              _______, _______, _______  \
  ),
  [_ADJUST] =  LAYOUT_split_3x5_3( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,               KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,    \
      KC_LCTRL, JP_DQUO,   JP_DQUO, JP_DQUO, JP_GRV,             C(KC_PGUP), XXXXXXX, XXXXXXX, C(KC_PGDN), KC_F12,\
      KC_F11, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, \
                        _______, _______, _______,             _______, _______, RESET                           \
  ),
  // 薙刀式
  [_NAGINATA] = LAYOUT_split_3x5_3(
    NG_Q   ,NG_W   ,NG_E   ,NG_R   ,NG_T   ,                NG_Y   ,NG_U   ,NG_I   ,NG_O   ,NG_P   , \
    NG_A   ,NG_S   ,NG_D   ,NG_F   ,NG_G   ,                NG_H   ,NG_J   ,NG_K   ,NG_L   ,NG_SCLN, \
    NG_Z   ,NG_X   ,NG_C   ,NG_V   ,NG_B   ,                NG_N   ,NG_M   ,NG_COMM,NG_DOT ,NG_SLSH, \
                   _______,_______, NG_SHFT,                NG_SHFT2,_______,_______
  ),
  // 薙刀式
};

static bool lower_pressed = false;
static bool raise_pressed = false;
static bool zshift_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 薙刀式
    if (!process_naginata(keycode, record))
      return false;
  // 薙刀式

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
            // 薙刀式
            naginata_off();
            // 薙刀式
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
            // 薙刀式
            naginata_on();
            // 薙刀式
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

    case EISU:
      if (record->event.pressed) {
        // 薙刀式
        naginata_off();
        // 薙刀式
      }
      return false;
      break;
    case KANA2:
      if (record->event.pressed) {
        // 薙刀式
        naginata_on();
        // 薙刀式
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
        // case TD(TD_ALT_GUI):
        //     return TAPPING_TERM + 500;
        //     break;
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


// 薙刀式をデフォルトとする
void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
}
