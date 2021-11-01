/* Copyright 2018 Salicylic_acid3
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

#pragma once

/* Select hand configuration */

//#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define USE_SERIAL

// #define TAPPING_FORCE_HOLD
// #define TAPPING_TERM 180

// SFT_T(KC_SPACE) としていたときに、 Space → Space長押し としたときに、 Spaceが連続で入力されてしまう問題の対処法
// https://docs.qmk.fm/#/ja/tap_hold?id=%e3%82%bf%e3%83%83%e3%83%94%e3%83%b3%e3%82%b0%e5%bc%b7%e5%88%b6%e3%83%9b%e3%83%bc%e3%83%ab%e3%83%89
// https://qiita.com/uodna/items/6d23581d26c1adb23377
#define TAPPING_FORCE_HOLD

// Mod Tap Key と通常キーを連続して拘束に押したときに両方のキーを Tap として扱う
#define IGNORE_MOD_TAP_INTERRUPT

// キーごとに タップとホールドの時間を設定する
//#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 150
// キーごとに TAPPING_TERM を設定できるようにする
#define TAPPING_TERM_PER_KEY

// コンボを使用する数を指定
#define COMBO_COUNT 1
