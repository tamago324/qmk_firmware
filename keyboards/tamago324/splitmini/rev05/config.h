/*
Copyright 2022 tamago324

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x1926
#define PRODUCT_ID   0x040A
#define DEVICE_VER   0x0002
/* #define MANUFACTURER tamago324 */
#define PRODUCT      splitmini

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DIRECT_PINS { \
    { B6, F7, F6, B0, B3 }, \
    { B5, C7, F5, B1, B7 }, \
    { B4, C6, F4, B2, D5 }, \
    { NO_PIN, NO_PIN, D7, D6, D4 } \
}

#define DIRECT_PINS_RIGHT {\
    { F4, F6, F7, B3, D7 }, \
    { F1, F5, B1, B7, B4 }, \
    { F0, B0, B2, D5, B5 }, \
    { NO_PIN, NO_PIN, C7, C6, B6 } \
}

#define DEBOUNCE 50

#define USE_SERIAL

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

#define MASTER_LEFT

// 分割のマスターとスレーブを検知するために必要
#define SPLIT_USB_DETECT
