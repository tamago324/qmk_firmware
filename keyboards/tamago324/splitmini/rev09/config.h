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
#define DEVICE_VER   0x0003
/* #define MANUFACTURER tamago324 */
#define PRODUCT      splitmini

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DIRECT_PINS { \
    { F4, F7, F6, F5, C7 }, \
    { F1, B1, B2, B3, B7 }, \
    { F0, B0, D1, D2, D3 }, \
    { NO_PIN, NO_PIN, B5, B6, C6 } \
}

#define DIRECT_PINS_RIGHT {\
    { F1, F0, E6, B2, B3 }, \
    { F6, F5, F4, B1, B7 }, \
    { B6, C6, C7, B0, D1 }, \
    { NO_PIN, NO_PIN, D7, B4, B5 } \
}

#define DEBOUNCE 50

#define USE_SERIAL

/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D0

#define MASTER_LEFT

// 分割のマスターとスレーブを検知するために必要
#define SPLIT_USB_DETECT
