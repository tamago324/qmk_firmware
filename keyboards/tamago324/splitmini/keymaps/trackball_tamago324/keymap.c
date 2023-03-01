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
#include QMK_KEYBOARD_H
#include "keymap_japanese.h"
#include <stdio.h>
#include "quantum.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _SPECIAL,
  _WIN,
  _ALT_L,
  _MOUSE,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SPLITMINI_SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  JU_SCLN,
  JU_QUOT,
  // ALT_TAB,
  // ALT_SHIFT_TAB,
  SPECIAL,
  ALT_L,
  // L1,
  KEY_STAB,

  KC_MY_BTN1,
  KC_MY_BTN2,
  KC_MY_BTN3,
};

enum combo_events {
  CMB_EQ_LEFT_ARROW,
  CMB_MINUS_LEFT_ARROW,
  CMB_MINUS_MINUS,
};


// =>
const uint16_t PROGMEM comb_keys_eq_left_arrow[] = {JP_EQL, JP_LBRC, COMBO_END};
// ->
const uint16_t PROGMEM comb_keys_minus_left_arrow[] = {JP_MINS, JP_LPRN, COMBO_END};
// --
const uint16_t PROGMEM comb_keys_minus_minus[] = {JP_MINS, JP_LBRC, COMBO_END};
// // -
const uint16_t PROGMEM comb_keys_minus[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [CMB_EQ_LEFT_ARROW] = COMBO_ACTION(comb_keys_eq_left_arrow),
  [CMB_MINUS_LEFT_ARROW] = COMBO_ACTION(comb_keys_minus_left_arrow),
  [CMB_MINUS_MINUS] = COMBO_ACTION(comb_keys_minus_minus),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {

    case CMB_EQ_LEFT_ARROW:
      if (pressed) {
        tap_code16(JP_EQL);
        tap_code16(S(KC_DOT));
      }
      break;

    case CMB_MINUS_LEFT_ARROW:
      if (pressed) {
        tap_code16(JP_MINS);
        tap_code16(S(KC_DOT));
      }
      break;

    case CMB_MINUS_MINUS:
      if (pressed) {
        tap_code16(JP_MINS);
        tap_code16(JP_MINS);
      }
      break;
  }
}

//// <
//const key_override_t syounari = ko_make_basic(MOD_MASK_CTRL, KC_COMM, S(KC_COMM));
//// >
//const key_override_t dainari = ko_make_basic(MOD_MASK_CTRL, KC_DOT, S(KC_DOT));
//// // ALT_SHIFT_TAB
//// const key_override_t alt_shift_tab = ko_make_basic(MOD_MASK_ALT, KC_W, S(A(KC_TAB)));
//
//
//const key_override_t **key_overrides = (const key_override_t *[]) {
//  &syounari,
//  &dainari,
//  // &alt_shift_tab,
//  NULL
//};

////////////////////////////////////////
// トラックボールの機能を使うための設定
////////////////////////////////////////
// from cocot36plus

// #define MS_BTN1 KC_MS_BTN1
// #define MS_BTN2 KC_MS_BTN2
// #define MS_BTN3 KC_MS_BTN3

enum click_state {
    NONE = 0,
    WAITING,    // マウスレイヤーが有効になるのを待つ。 Wait for mouse layer to activate.
    CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる。 Mouse layer is enabled to take click input.
    CLICKING,   // クリック中。 Clicking.
    SCROLLING   // スクロール中。 Scrolling.
};

enum click_state state;     // 現在のクリック入力受付の状態 Current click input reception status
uint16_t click_timer;       // タイマー。状態に応じて時間で判定する。 Timer. Time to determine the state of the system.

uint16_t to_clickable_time = 100;   // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
uint16_t to_reset_time = 800; // この秒数(千分の一秒)、CLICKABLE状態ならクリックレイヤーが無効になる。 For this number of seconds (milliseconds), the click layer is disabled if in CLICKABLE state.

const uint16_t click_layer = _MOUSE;   // マウス入力が可能になった際に有効になるレイヤー。Layers enabled when mouse input is enabled

int16_t scroll_v_mouse_interval_counter;   // 垂直スクロールの入力をカウントする。　Counting Vertical Scroll Inputs
int16_t scroll_h_mouse_interval_counter;   // 水平スクロールの入力をカウントする。  Counts horizontal scrolling inputs.

int16_t scroll_v_threshold = 50;    // この閾値を超える度に垂直スクロールが実行される。 Vertical scrolling is performed each time this threshold is exceeded.
int16_t scroll_h_threshold = 50;    // この閾値を超える度に水平スクロールが実行される。 Each time this threshold is exceeded, horizontal scrolling is performed.

int16_t after_click_lock_movement = 0;      // クリック入力後の移動量を測定する変数。 Variable that measures the amount of movement after a click input.

int16_t mouse_record_threshold = 30;    // ポインターの動きを一時的に記録するフレーム数。 Number of frames in which the pointer movement is temporarily recorded.
int16_t mouse_move_count_ratio = 5;     // ポインターの動きを再生する際の移動フレームの係数。 The coefficient of the moving frame when replaying the pointer movement.


// layer_state_t layer_state_set_user(layer_state_t state) {
//     switch (get_highest_layer(state)) {
//     case 1:
//         splitmini_set_scroll_mode(true);
//         break;
//     case 2:
//         splitmini_set_scroll_mode(true);
//         break;
//     case 3:
//         splitmini_set_scroll_mode(false);
//         break;
//     case 4:
//         splitmini_set_scroll_mode(false);
//         break;
//     case 5:
//         splitmini_set_scroll_mode(false);
//         break;
//     case 6:
//         splitmini_set_scroll_mode(false);
//         break;
//     case 7:
//         splitmini_set_scroll_mode(false);
//         break;
//     default:
//         splitmini_set_scroll_mode(false);
//         break;
//     }
//   return state;
// };



// LCTL_T(KC_A) は Lower レイヤーのためのもの
// Lower の Ctrl をおそうとして、a が入力されるのを防ぐため
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
         KC_TAB,  KC_W,    KC_E, KC_R,        KC_T,    KC_Y, KC_U,  KC_I,    KC_O,    KC_BSPC,
  LCTL_T(KC_A),   KC_S,    KC_D, KC_F,        KC_G,    KC_H, KC_J,  KC_K,    KC_L,    KC_P,
  LSFT_T(KC_Z),   KC_X,    KC_C, ALT_T(KC_V), KC_B,    KC_N, KC_M,  KC_COMM, KC_DOT,  ALT_T(KC_Q),
                      ALT_L, LOWER,  LCTL_T(KC_SPACE),          SFT_T(KC_ENT), RAISE, SPECIAL
  ),
  [_LOWER] = LAYOUT(
      KC_EXLM, JP_AT,   KC_HASH, KC_DLR,  XXXXXXX,          JP_ASTR, JP_AMPR, JP_LPRN, JP_RPRN, S(KC_SLSH),
      KC_LCTRL, KC_ESC, KC_BSPC, KC_ENT, KC_DELETE,        KC_SLSH, JP_MINS,  JP_LBRC, JP_RBRC, XXXXXXX,
      OSL(_WIN), XXXXXXX, XXXXXXX, C(KC_Z),  JP_CIRC,   JP_UNDS, JP_EQL, JP_LCBR, JP_RCBR, XXXXXXX,
                       XXXXXXX , _______, _______,                   SFT_T(LALT(KC_ENT)), _______, XXXXXXX
  ),
  [_RAISE] = LAYOUT(
      KC_0, KC_4, KC_5, KC_6, XXXXXXX,             XXXXXXX,  XXXXXXX, JU_QUOT, JU_QUOT, KC_DELETE,
      KC_LSFT, KC_1, KC_2, KC_3, JP_COLN,             KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, KC_DOT,
      KC_LSFT, KC_7, KC_8, KC_9, JU_SCLN,             KC_HOME,  KC_PGDN,  KC_PGUP, KC_END,  XXXXXXX,
                        KC_LALT ,_______, CTL_T(KC_0),            _______, _______ , XXXXXXX
  ),
  [_ADJUST] =  LAYOUT(
      XXXXXXX, KC_F2, KC_PERC, XXXXXXX, XXXXXXX,     XXXXXXX, KC_F7, JP_DQUO, JP_DQUO, KC_F10,
      KC_LCTRL, JP_TILD, JP_PIPE, JP_BSLS, XXXXXXX,    C(KC_PGUP), C(KC_DOWN), C(KC_UP), C(KC_PGDN), XXXXXXX,
      XXXXXXX, C(KC_SPACE), XXXXXXX, JP_GRV,  XXXXXXX,     XXXXXXX, JP_PLUS,  XXXXXXX, XXXXXXX, XXXXXXX,
                        XXXXXXX ,_______, _______,             _______, _______, XXXXXXX
  ),
  [_SPECIAL] = LAYOUT(
    XXXXXXX, KC_F4, KC_F5, KC_F6, XXXXXXX,             XXXXXXX, XXXXXXX, CPI_DEC, CPI_INC,  XXXXXXX,
    KC_LCTRL, KC_F1, KC_F2, KC_F3, KC_F11,              XXXXXXX, XXXXXXX, SCRL_SW, XXXXXXX, XXXXXXX,
    KC_LSFT, KC_F7, KC_F8, KC_F9, XXXXXXX,             XXXXXXX, XXXXXXX, ROT_LEFT, ROT_RIGHT,  RESET,
                     XXXXXXX ,XXXXXXX, XXXXXXX,                _______, _______, _______
  ),
  [_WIN] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, G(KC_D), KC_F12, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, G(KC_L), XXXXXXX,
    XXXXXXX,  KC_LGUI, SWIN(KC_S), G(KC_V), XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                     XXXXXXX ,_______, XXXXXXX,                 G(KC_ENT), _______, XXXXXXX
  ),
  [_ALT_L] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, KEY_STAB, KC_TAB, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______ ,XXXXXXX, XXXXXXX,       XXXXXXX, _______, XXXXXXX
  ),
  [_MOUSE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    SCRL_MO, KC_MY_BTN2, KC_MY_BTN3, KC_MY_BTN1, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      ALT_L, LOWER, LCTL_T(KC_SPACE),       XXXXXXX, XXXXXXX, XXXXXXX
  ),
  // [_L1] = LAYOUT(
  //   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //   KC_LCTRL, C(JP_MINS), C(JP_PLUS), XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //   KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //                    _______ ,XXXXXXX, XXXXXXX,                 XXXXXXX, RAISE, XXXXXXX
  // ),
  // [_ALT_NUM] = LAYOUT(
  //     XXXXXXX, A(KC_4), A(KC_5), A(KC_6), XXXXXXX,             XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //     KC_LSFT, A(KC_1), A(KC_2), A(KC_3), A(KC_0),             XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //     KC_LSFT, A(KC_7), A(KC_8), A(KC_9), XXXXXXX,             XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //                       _______ ,_______, XXXXXXX,            _______, _______ , XXXXXXX
  // ),
};




////////////////////////////////////////
// トラックボールの機能を使うための設定
////////////////////////////////////////
// from cocot36plus
// クリック用のレイヤーを有効にする。　Enable layers for clicks
void enable_click_layer(void) {
    layer_on(click_layer);
    click_timer = timer_read();
    state = CLICKABLE;
}

// クリック用のレイヤーを無効にする。 Disable layers for clicks.
void disable_click_layer(void) {
    state = NONE;
    layer_off(click_layer);
    scroll_v_mouse_interval_counter = 0;
    scroll_h_mouse_interval_counter = 0;
}

// 自前の絶対数を返す関数。 Functions that return absolute numbers.
int16_t my_abs(int16_t num) {
    if (num < 0) {
        num = -num;
    }

    return num;
}

// 自前の符号を返す関数。 Function to return the sign.
int16_t mmouse_move_y_sign(int16_t num) {
    if (num < 0) {
        return -1;
    }

    return 1;
}

// 現在クリックが可能な状態か。 Is it currently clickable?
bool is_clickable_mode(void) {
    return state == CLICKABLE || state == CLICKING || state == SCROLLING;
}

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////




static bool lower_pressed = false;
static bool raise_pressed = false;
static bool zshift_pressed = false;
static bool alt_tab_pressed = false;
static bool alt_layer_on = false;
// static bool alt_tab_pressed = false;
// static bool alt_shift_tab_pressed = false;

// lower を長押ししたら単推しとしてみなさないようにするためのタイマー
static uint16_t lower_pressed_time = 0;
static uint16_t raise_pressed_time = 0;
static uint16_t alt_tab_pressed_time = 0;


void reset_pressed_state(void) {
  lower_pressed = false;
  raise_pressed = false;
}

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
        // LOWER を押した時間を保持しておく
        lower_pressed_time = record->event.time;

        layer_off(_MOUSE);
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);

        // if (alt_tab_pressed || alt_shift_tab_pressed) {
        //   // もし、Lower を離したときに、ALT が押しっぱになっていたら、離す
        //   unregister_code(KC_LALT);
        //   alt_tab_pressed = false;
        //   alt_shift_tab_pressed = false;
        //   // また、無変換は送信しない
        //   return false;
        // }

        if (lower_pressed && TIMER_DIFF_16(record->event.time, lower_pressed_time) < TAPPING_TERM) {
          // もし、長押しをしていなければ、無変換を送信する
            tap_code(KC_MHEN);
        }
        lower_pressed = false;
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        raise_pressed = true;
        raise_pressed_time = record->event.time;

        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        // update_tri_layer(_RAISE, _L1, _ALT_NUM);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        // update_tri_layer(_RAISE, _L1, _ALT_NUM);

        if (raise_pressed && TIMER_DIFF_16(record->event.time, raise_pressed_time) < TAPPING_TERM) {
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

    case SPECIAL:
      if (record->event.pressed) {
        layer_on(_SPECIAL);
      } else {
        layer_off(_SPECIAL);
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
      reset_pressed_state();
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
      reset_pressed_state();
      return false;
      break;

    case LSFT_T(KC_Z):
      if (record->event.pressed) {
        zshift_pressed = true;
        reset_pressed_state();
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
            zshift_pressed = false;

            reset_pressed_state();

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

    // ALT レイヤーに移動する
    case ALT_L:
      if (record->event.pressed) {
        // タイマースタート
        alt_tab_pressed = true;
        alt_tab_pressed_time = record->event.time;

        layer_off(_MOUSE);

        // LOWER でもRAISEでもない文字だった場合、戻しておく
        reset_pressed_state();
        zshift_pressed = false;
      } else {
        alt_tab_pressed = false;
        alt_tab_pressed_time = 0;

        if (alt_layer_on) {
          layer_off(_ALT_L);
          unregister_code(KC_LALT);
        } else {
          tap_code(KC_LALT);
        }

        alt_layer_on = false;
      }
      return false;
      break;

    case KEY_STAB:
      if (record->event.pressed) {
        tap_code16(S(KC_TAB));
      }
      return false;
      break;

    // case ALT_TAB:
    //   if (record->event.pressed) {
    //     // 初めて押したら、Altを押し続ける
    //     // また、TAB も送信する
    //     if (!alt_tab_pressed || !alt_shift_tab_pressed) {
    //       lower_pressed = false;
    //       raise_pressed = false;
    //       zshift_pressed = false;
    //
    //       alt_tab_pressed = true;
    //
    //       // ALT を押し続ける
    //       register_code(KC_LALT);
    //     }
    //     register_code(KC_TAB);
    //   } else {
    //     unregister_code(KC_TAB);
    //   }
    //   break;
    //
    // case ALT_SHIFT_TAB:
    //   if (record->event.pressed) {
    //     // 初めて押したら、Altを押し続ける
    //     // また、TAB も送信する
    //     if (!alt_tab_pressed || !alt_shift_tab_pressed) {
    //       lower_pressed = false;
    //       raise_pressed = false;
    //       zshift_pressed = false;
    //
    //       alt_shift_tab_pressed = true;
    //
    //       // ALT を押し続ける
    //       register_code(KC_LALT);
    //     }
    //     register_code16(S(KC_TAB));
    //   } else {
    //     unregister_code16(S(KC_TAB));
    //   }
    //   break;
    //
    // case L1:
    //   if (record->event.pressed) {
    //     layer_on(_L1);
    //     update_tri_layer(_RAISE, _L1, _ALT_NUM);
    //   } else {
    //     layer_off(_L1);
    //     update_tri_layer(_RAISE, _L1, _ALT_NUM);
    //   }
    //   return false;
    //   break;


    ////////////////////////////////////////
    // トラックボールの機能を使うための設定
    ////////////////////////////////////////
    // from cocot36plus
    case KC_MY_BTN1:
    case KC_MY_BTN2:
    case KC_MY_BTN3:
      {
        report_mouse_t currentReport = pointing_device_get_report();

        // どこのビットを対象にするか。 Which bits are to be targeted?
        uint8_t btn = 1 << (keycode - KC_MY_BTN1);

        if (record->event.pressed) {
            // ビットORは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットのどちらかが「1」の場合に「1」にします。
            // Bit OR compares bits in the same position on the left and right sides of the operator and sets them to "1" if either of both bits is "1".
            currentReport.buttons |= btn;
            state = CLICKING;
            after_click_lock_movement = 30;
        } else {
            // ビットANDは演算子の左辺と右辺の同じ位置にあるビットを比較して、両方のビットが共に「1」の場合だけ「1」にします。
            // Bit AND compares the bits in the same position on the left and right sides of the operator and sets them to "1" only if both bits are "1" together.
            currentReport.buttons &= ~btn;
            enable_click_layer();
        }

        // pointing_device_set_report(currentReport);
        // // これを読んでしまうとドラッグアンドドロップがうまくできないため、呼び出さないようにする
        // // https://qiita.com/TumoiYorozu/items/20979079f2896fae63d1
        // pointing_device_send();

        // extern void register_button(bool, enum mouse_buttons);
        // register_button(record->event.pressed, MOUSE_BTN_MASK(keycode - KC_MY_BTN1));

        return true;
      }
      break;

    case SCRL_MO:
      if (record->event.pressed) {
          state = SCROLLING;
      } else {
          enable_click_layer();   // スクロールキーを離した時に再度クリックレイヤーを有効にする。 Enable click layer again when the scroll key is released.
      }
      return false;
    ////////////////////////////////////////
    ////////////////////////////////////////
    ////////////////////////////////////////

    default:
      if (record->event.pressed) {
        reset_pressed_state();

        zshift_pressed = false;

        disable_click_layer();
      }

      break;
  }

  return true;
}

void matrix_scan_user(void) {
  // もし、500ms 押していたら、レイヤー移動
  if (alt_tab_pressed) {
    if (timer_elapsed(alt_tab_pressed_time) > 50) {
      layer_on(_ALT_L);
      register_code(KC_LALT);
      alt_layer_on = true;
    }
  }
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
        case ALT_T(KC_V):
            return TAPPING_TERM + 30;
            break;
        case LCTL_T(KC_SPACE):
            return TAPPING_TERM + 20;
            break;
        case LCTL_T(KC_A):
            return TAPPING_TERM + 50;
            break;
        case CTL_T(KC_0):
            return TAPPING_TERM + 10;
            break;
        default:
            return TAPPING_TERM;
            break;
    }
}




////////////////////////////////////////
// トラックボールの機能を使うための設定
////////////////////////////////////////
// from cocot36plus
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {

    int16_t current_x = mouse_report.x;
    int16_t current_y = mouse_report.y;
    int16_t current_h = 0;
    int16_t current_v = 0;

    if (current_x != 0 || current_y != 0) {

        switch (state) {
            case CLICKABLE:
                click_timer = timer_read();
                break;

            case CLICKING:
                after_click_lock_movement -= my_abs(current_x) + my_abs(current_y);

                if (after_click_lock_movement > 0) {
                    current_x = 0;
                    current_y = 0;
                }

                break;

            case SCROLLING:
            {
                int8_t rep_v = 0;
                int8_t rep_h = 0;

                // 垂直スクロールの方の感度を高める。 Increase sensitivity toward vertical scrolling.
                if (my_abs(current_y) * 2 > my_abs(current_x)) {

                    scroll_v_mouse_interval_counter += current_y;
                    while (my_abs(scroll_v_mouse_interval_counter) > scroll_v_threshold) {
                        if (scroll_v_mouse_interval_counter < 0) {
                            scroll_v_mouse_interval_counter += scroll_v_threshold;
                            rep_v += scroll_v_threshold;
                        } else {
                            scroll_v_mouse_interval_counter -= scroll_v_threshold;
                            rep_v -= scroll_v_threshold;
                        }

                    }
                } else {

                    scroll_h_mouse_interval_counter += current_x;

                    while (my_abs(scroll_h_mouse_interval_counter) > scroll_h_threshold) {
                        if (scroll_h_mouse_interval_counter < 0) {
                            scroll_h_mouse_interval_counter += scroll_h_threshold;
                            rep_h += scroll_h_threshold;
                        } else {
                            scroll_h_mouse_interval_counter -= scroll_h_threshold;
                            rep_h -= scroll_h_threshold;
                        }
                    }
                }

                current_h = rep_h / scroll_h_threshold;
                current_v = -rep_v / scroll_v_threshold;
                current_x = 0;
                current_y = 0;
            }
                break;

            case WAITING:
                if (timer_elapsed(click_timer) > to_clickable_time) {
                    enable_click_layer();
                }
                break;

            default:
                click_timer = timer_read();
                state = WAITING;
        }
    }
    else
    {
        switch (state) {
            case CLICKING:
            case SCROLLING:

                break;

            case CLICKABLE:
                if (timer_elapsed(click_timer) > to_reset_time) {
                    disable_click_layer();
                }
                break;

             case WAITING:
                if (timer_elapsed(click_timer) > 50) {
                    state = NONE;
                }
                break;

            default:
                state = NONE;
        }
    }

    mouse_report.x = current_x;
    mouse_report.y = current_y;
    mouse_report.h = current_h;
    mouse_report.v = current_v;

    return mouse_report;
}

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
