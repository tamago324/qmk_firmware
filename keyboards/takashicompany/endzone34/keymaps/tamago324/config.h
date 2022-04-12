#pragma once

// #define RGB_DI_PIN D3
// #ifdef RGB_DI_PIN
//   #define RGBLED_NUM 9
//   #define RGBLIGHT_HUE_STEP 16
//   #define RGBLIGHT_SAT_STEP 16
//   #define RGBLIGHT_VAL_STEP 16
//   #define RGBLIGHT_LIMIT_VAL 255
//   #define RGBLIGHT_SLEEP
// // /*== all animations enable ==*/
//   #define RGBLIGHT_ANIMATIONS
// #endif

// SFT_T(KC_SPACE) としていたときに、 Space → Space長押し としたときに、 Spaceが連続で入力されてしまう問題の対処法
// https://docs.qmk.fm/#/ja/tap_hold?id=%e3%82%bf%e3%83%83%e3%83%94%e3%83%b3%e3%82%b0%e5%bc%b7%e5%88%b6%e3%83%9b%e3%83%bc%e3%83%ab%e3%83%89
// https://qiita.com/uodna/items/6d23581d26c1adb23377
#define TAPPING_FORCE_HOLD

// Mod Tap Key と通常キーを連続して拘束に押したときに両方のキーを Tap として扱う
#define IGNORE_MOD_TAP_INTERRUPT

// キーごとに タップとホールドの時間を設定する
//#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 145

// キーごとに TAPPING_TERM を設定できるようにする
#define TAPPING_TERM_PER_KEY

// コンボを使用する数を指定
#define COMBO_COUNT 8
#define COMBO_TERM 100

// // たたんって打たれたときに、ホールドとして認識させる？
// // これは、 LCTL_T(KC_A) と H 用 (C-H)
// #define PERMISSIVE_HOLD

// // どのレイヤでも、コンボはすべて _QWERTY のキーマップをチェックするようになる
// #define COMBO_ONLY_FROM_LAYER 0

// // キーごとに設定する
// #define COMBO_TERM_PER_COMBO



// サイズを小さくするためのもの https://zenn.dev/koron/articles/98324ab760e83a
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

/* #undef NO_ACTION_ONESHOT // ワンショットキーの無効化 */

#define LAYER_STATE_8BIT    // レイヤーの上限を8にする
