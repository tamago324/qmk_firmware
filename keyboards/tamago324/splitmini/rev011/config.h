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
#define DEVICE_VER   0x0001
/* #define MANUFACTURER tamago324 */
#define PRODUCT      splitmini

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
// 改良二条マトリクスの場合、同じ値を指定する
#define MATRIX_ROW_PINS { GP26, GP27, GP28, GP29, GP6 }
#define MATRIX_COL_PINS { GP26, GP27, GP28, GP29, GP6 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

// https://github.com/qmk/qmk_firmware/blob/master/docs/serial_driver.md#the-pio-driver
// RP2040専用の機能
// PIO ペリフェラルの柔軟な性質により、任意のGPIO ピンをTXまたはRXピンとして使用できます。
#define SERIAL_PIO_USE_PIO1
#define SERIAL_USART_TX_PIN GP1

#define DEBOUNCE 50
