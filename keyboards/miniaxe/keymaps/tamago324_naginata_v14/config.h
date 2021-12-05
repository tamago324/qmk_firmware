#pragma once

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
#define COMBO_TERM 35

// // たたんって打たれたときに、ホールドとして認識させる？
// // これは、 LCTL_T(KC_A) と H 用 (C-H)
// #define PERMISSIVE_HOLD


// どのレイヤでも、コンボはすべて _QWERTY のキーマップをチェックするようになる
// #define COMBO_ONLY_FROM_LAYER 0

// 薙刀式
// #define NAGINATA_TATEGAKI
#define NAGINATA_YOKOGAKI

// #define NAGINATA_EDIT_WIN // JP106
// #define UNICODE_SELECTED_MODES UC_WINC

// #define NAGINATA_EDIT_MAC // US101
// Macはunicode入力を使わない
// #define MAC_LIVE_CONVERSION // Macでライブ変換をオンにしている場合

#define NAGINATA_EDIT_LINUX
#define UNICODE_SELECTED_MODES UC_LNX

// #define NAGINATA_KOUCHI_SHIFT // シフトを後置でも有効にする
// 薙刀式

// // サイズを小さくする
// #ifndef NO_DEBUG
// #define NO_DEBUG
// #endif // !NO_DEBUG
// #if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
// #define NO_PRINT
// #endif // !NO_PRINT

// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION
//
// #define DISABLE_LEADER
