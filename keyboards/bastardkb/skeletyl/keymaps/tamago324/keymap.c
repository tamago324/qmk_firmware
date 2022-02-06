/* 
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
  _ADJUST,
  // _OPENING_BRACKET,
  // _CLOSING_BRACKET,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  JU_SCLN,
  JU_QUOT,
  ALT_TAB,
  ALT_SHIFT_TAB
};

enum combo_events {
  CMB_ESCAPE,
  CMB_SEMICORON,
  CMB_CTRL_SPACE,
  // CMB_MINUS1,
  // CMB_MINUS2,
  // CMB_OPENING_BRACKET_LAYER,
  // CMB_CLOSING_BRACKET_LAYER,
  CMB_BACKSPACE,
  CMB_WIN_ENTER,
  CMB_WIN,
};

// コンボ
const uint16_t PROGMEM comb_keys_Escape[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM comb_keys_semicoron[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM comb_keys_ctrl_space[] = {KC_X, KC_C, COMBO_END};
// const uint16_t PROGMEM comb_keys_dash[] = {KC_J, KC_K, COMBO_END};
// const uint16_t PROGMEM comb_keys_dash2[] = {JP_EQL, JP_LBRC, COMBO_END};
const uint16_t PROGMEM comb_keys_opening_bracket_layer[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM comb_keys_closing_bracket_layer[] = {KC_C, KC_V, COMBO_END};
// const uint16_t PROGMEM comb_keys_back_space[] = {KC_COMM, KC_DOT, COMBO_END};
// Lower の SD
const uint16_t PROGMEM comb_keys_win_enter[] = {JP_PIPE, S(KC_COMM), COMBO_END};
const uint16_t PROGMEM comb_keys_win[] = {JP_AT, KC_HASH, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CMB_ESCAPE] = COMBO(comb_keys_Escape, KC_ESC),
  [CMB_SEMICORON] = COMBO(comb_keys_semicoron, JU_SCLN),
  [CMB_CTRL_SPACE] = COMBO(comb_keys_ctrl_space, C(KC_SPACE)),
  // [CMB_MINUS1] = COMBO(comb_keys_dash, JP_MINS),
  // [CMB_MINUS2] = COMBO(comb_keys_dash2, JP_MINS),
  // [CMB_OPENING_BRACKET_LAYER] = COMBO(comb_keys_opening_bracket_layer, MO(_OPENING_BRACKET)),
  // [CMB_CLOSING_BRACKET_LAYER] = COMBO(comb_keys_closing_bracket_layer, MO(_CLOSING_BRACKET)),
  // [CMB_BACKSPACE] = COMBO(comb_keys_back_space, KC_BSPC),
  [CMB_WIN_ENTER] = COMBO(comb_keys_win_enter, LWIN(KC_ENT)),
  [CMB_WIN] = COMBO(comb_keys_win, KC_LGUI),
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
// // // Alt+Shift+Tab
// // const key_override_t alt_shift_tab = ko_make_basic(MOD_MASK_ALT, KC_W, S(LALT(KC_TAB)));
// // Alt+Shift+Tab
// const key_override_t alt_shift_tab2 = ko_make_basic(MOD_MASK_ALT, KC_B, S(LALT(KC_TAB)));
// // Alt+Tab
// const key_override_t alt_tab = ko_make_basic(MOD_MASK_ALT, KC_G, LALT(KC_TAB));

const key_override_t **key_overrides = (const key_override_t *[]) {
  &shift_bspc_delete,
  &syounari,
  &dainari,
  // &alt_shift_tab,
  // &alt_shift_tab2,
  // &alt_tab,
  NULL
};

// tap-dance
enum {
  TD_ALT_GUI,
};

qk_tap_dance_action_t tap_dance_actions[] = {
  // 1回のタップで ALT、2回のタップで GUI
  [TD_ALT_GUI] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3( \
         KC_TAB,  KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y, KC_U,  KC_I,    KC_O,    KC_BSPC, \
         KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                          KC_H, KC_J,  KC_K,    KC_L,    KC_P, \
  LSFT_T(KC_Z),   KC_X,    KC_C,    ALT_T(KC_V),    KC_B,                   KC_N, KC_M,  KC_COMM, KC_DOT,  ALT_T(KC_Q), \
                    LOWER,  LCTL_T(KC_SPACE), XXXXXXX,                XXXXXXX,  SFT_T(KC_ENT), RAISE \
  ),
  [_LOWER] = LAYOUT_split_3x5_3( \
      KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  KC_PERC,              JP_ASTR, JP_AMPR, JP_LPRN, JP_RPRN, JP_CIRC,  \
      KC_LCTRL, JP_PIPE, S(KC_COMM), S(KC_DOT), JP_TILD,        KC_SLSH, JP_MINS,  JP_LBRC, JP_RBRC, JP_COLN, \
      C(KC_Z), SWIN(KC_S), ALT_SHIFT_TAB, ALT_TAB, KC_ENT,          JP_UNDS, JP_EQL, JP_LCBR, JP_RCBR, S(KC_SLSH),\
                        _______, _______, _______,              _______, LALT(KC_ENT), _______ \
  ),
  [_RAISE] = LAYOUT_split_3x5_3( \
      XXXXXXX,  KC_4, KC_5, KC_6, XXXXXXX,               XXXXXXX,  XXXXXXX, JU_QUOT, JU_QUOT, XXXXXXX,     \
      XXXXXXX, KC_1, KC_2, KC_3, JP_BSLS,              KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, XXXXXXX, \
      KC_LSFT,  KC_7, KC_8, KC_9, XXXXXXX,             KC_HOME,  KC_PGUP,  KC_PGDN, KC_END,  KC_DELETE,   \
                        _______, CTL_T(KC_0), _______,              _______, _______, _______  \
  ),
  [_ADJUST] =  LAYOUT_split_3x5_3( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,               KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,    \
      KC_LCTRL, JP_DQUO, JP_DQUO, JP_DQUO, XXXXXXX,             C(KC_PGUP), XXXXXXX, XXXXXXX, C(KC_PGDN), KC_F12,\
      KC_F11, XXXXXXX, JP_GRV, JP_GRV, XXXXXXX,             XXXXXXX,  JP_PLUS,  XXXXXXX, XXXXXXX, XXXXXXX, \
                        _______, _______, _______,             _______, _______, XXXXXXX                           \
  ),
};

static bool lower_pressed = false;
static bool raise_pressed = false;
static bool zshift_pressed = false;
static bool alt_tab_pressed = false;
static bool alt_shift_tab_pressed = false;

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

        if (alt_tab_pressed || alt_shift_tab_pressed) {
          // もし、Lower を離したときに、ALT が押しっぱになっていたら、離す
          unregister_code(KC_LALT);
          alt_tab_pressed = false;
          alt_shift_tab_pressed = false;
          // また、無変換は送信しない
          return false;
        }

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
    // case KC_O:
    // case KC_U:
    // case KC_I:
      // z と同時に押したら、zX にする
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
            tap_code(keycode);
            return false;
          }
      }
      break;

    case ALT_TAB:
      if (record->event.pressed) {
        // 初めて押したら、Altを押し続ける
        // また、TAB も送信する
        if (!alt_tab_pressed || !alt_shift_tab_pressed) {
          lower_pressed = false;
          raise_pressed = false;
          zshift_pressed = false;
        
          alt_tab_pressed = true;

          // ALT を押し続ける
          register_code(KC_LALT);
        }
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;

    case ALT_SHIFT_TAB:
      if (record->event.pressed) {
        // 初めて押したら、Altを押し続ける
        // また、TAB も送信する
        if (!alt_tab_pressed || !alt_shift_tab_pressed) {
          lower_pressed = false;
          raise_pressed = false;
          zshift_pressed = false;
        
          alt_shift_tab_pressed = true;

          // ALT を押し続ける
          register_code(KC_LALT);
        }
        register_code16(S(KC_TAB));
      } else {
        unregister_code16(S(KC_TAB));
      }
      break;

    default:
      if (record->event.pressed) {
          // LOWER でもRAISEでもない文字だった場合、戻しておく
        lower_pressed = false;
        raise_pressed = false;
        zshift_pressed = false;

        // if (IS_LAYER_ON(_OPENING_BRACKET)) {
        //   // [
        //   tap_code(JP_LBRC);
        // } else if (IS_LAYER_ON(_CLOSING_BRACKET)) {
        //   // ]
        //   tap_code(JP_RBRC);
        // }
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
        case ALT_T(KC_V):
            return TAPPING_TERM + 30;
            break;
        // case LCTL_T(KC_SPACE):
        //     return TAPPING_TERM + 20;
        //     break;
        default:
            return TAPPING_TERM;
            break;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    // switch (combo->keycode) {
    //     case KC_F:
    //         return COMBO_TERM + 50;
    // }

    // or with combo index, i.e. its name from enum.
    switch (index) {
        // case CMB_MINUS1:
        // case CMB_MINUS2:
        //     return COMBO_TERM + 30;
        case CMB_ESCAPE:
            return COMBO_TERM + 30;
    }

    // // And if you're feeling adventurous, you can even decide by the keys in the chord,
    // // i.e. the exact array of keys you defined for the combo.
    // // This can be useful if your combos have a common key and you want to apply the
    // // same combo term for all of them.
    // if (combo->keys[0] == KC_ENTER) { // if first key in the array is KC_ENTER
    //     return 150;
    // }

    return COMBO_TERM;
}
