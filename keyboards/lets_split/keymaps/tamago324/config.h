/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

 // place overrides here
#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                              SONG(COLEMAK_SOUND), \
                              SONG(DVORAK_SOUND) \
                            }

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// 左右のLEDの数を設定する
//#define RGBLED_SPLIT { 6, 6 }
// すべてのアニメーションを有効化する
#define RGBLIGHT_ANIMATIONS

// SFT_T(KC_SPACE) としていたときに、 Space → Space長押し としたときに、 Spaceが連続で入力されてしまう問題の対処法
// https://docs.qmk.fm/#/ja/tap_hold?id=%e3%82%bf%e3%83%83%e3%83%94%e3%83%b3%e3%82%b0%e5%bc%b7%e5%88%b6%e3%83%9b%e3%83%bc%e3%83%ab%e3%83%89
// https://qiita.com/uodna/items/6d23581d26c1adb23377
#define TAPPING_FORCE_HOLD

// Mod Tap Key と通常キーを連続して拘束に押したときに両方のキーを Tap として扱う
#define IGNORE_MOD_TAP_INTERRUPT

// キーごとに タップとホールドの時間を設定する
//#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 150
