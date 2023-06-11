// Copyright 2023 ikumoku (@ikumoku)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT



// Key matrix parameters
#define MATRIX_ROWS         4 * 2
#define MATRIX_COLS         6
#define MATRIX_ROW_PINS     { F4, F5, F6, F7 }          //F4 enc push sw
#define MATRIX_COL_PINS     { D4, C6, D7, E6, B4, B5 }  //B5 enc push sw only
//#define MATRIX_MASKED
//#define DEBOUNCE            5
#define DIODE_DIRECTION     COL2ROW
//#define DIODE_DIRECTION     ROW2COL

#define SOFT_SERIAL_PIN D2 //Split Keyboard specific options
#define MASTER_RIGHT

//////////////////////////////////////////////////////////////////////////////////////
//trackball
//B2　　PAW3204_SCLK　　　右下一つ上
//B6  　PAW3204_DATA　　　　右下

// PCB
//  CN2
// 1  3.3v
// 2  SDIO  ----  B6
// 3  SCL   ----  B2
// 4  GND
//////////////////////////////////////////////////////////////////////////////////////
// Rotary encoder
#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B3 }
#define ENCODER_RESOLUTION 2

// RGB LED settings
#define RGB_DI_PIN          D3
#define RGBLED_NUM      3

#define RGBLIGHT_LIMIT_VAL 200
#define RGBLIGHT_VAL_STEP   15
#define RGBLIGHT_HUE_STEP   17
#define RGBLIGHT_SAT_STEP   17
