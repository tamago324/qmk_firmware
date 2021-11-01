#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

/*
 * MIDI options
 */

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

// #define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
// #define ENCODER_RESOLUTION 4

//#define PERMISSIVE_HOLD
//#define RETRO_TAPPING

// SFT_T(KC_SPACE) としていたときに、 Space → Space長押し としたときに、 Spaceが連続で入力されてしまう問題の対処法
// https://docs.qmk.fm/#/ja/tap_hold?id=%e3%82%bf%e3%83%83%e3%83%94%e3%83%b3%e3%82%b0%e5%bc%b7%e5%88%b6%e3%83%9b%e3%83%bc%e3%83%ab%e3%83%89
// https://qiita.com/uodna/items/6d23581d26c1adb23377
#define TAPPING_FORCE_HOLD

// Mod Tap Key と通常キーを連続して拘束に押したときに両方のキーを Tap として扱う
#define IGNORE_MOD_TAP_INTERRUPT

// キーごとに タップとホールドの時間を設定する
//#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 150


// // AUTO_SHIFT

// // 175 がデフォルト
// #define AUTO_SHIFT_TIMEOUT 133
// // -_, =+, [{, ]}, ;:, ‘“, ,<, .> および /? を含む特殊キーを自動シフトしない
// #define NO_AUTO_SHIFT_SPECIAL
// // 数字は自動シフトしない
// #define NO_AUTO_SHIFT_NUMERIC

// すべてのアニメーションを有効化する
#define RGBLIGHT_ANIMATIONS
