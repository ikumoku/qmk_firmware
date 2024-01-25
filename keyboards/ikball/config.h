// Copyright 2023 ikumoku (@ikumoku)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER    //エラーが起きる
// #define NO_ACTION_TAPPING  //エラーが起きる

// #undef LOCKING_SUPPORT_ENABLE
// #undef LOCKING_RESYNC_ENABLE

#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE

#define LAYER_STATE_8BIT
#define LAYER_STATE_16BIT

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN C6
#    define NO_MUSIC_MODE // Save 2000 bytes  変化なし
#endif

//////////////////////////////////////////////////////////////////////////////////
// pin Assignments
//   D3 TX   RGB_DI ←　　ROW4
//   D2 RX   SERIAL
//   GND
//   GND
//   X1 D1 SDA  OLED_SDA           F4 X9   ROW0
//   X2 D0 SCL  OLED_SCL           F5 X10  ROW1
//   X3 D4      COL0               F6 Y1   ROW2
//   X4 C6      COL1               F7 Y2   ROW3
//   X5 D7      COL2               B1 Y3   ENCODERS_PAD_A
//   X6 E6      COL3               B3 Y4   ENCODERS_PAD_B
//   X7 B4      COL4               B2 Y5   PAW3204_SCLK　
//   X8 B5      COL5               B6 Y6 　PAW3204_DATA

//      D5  TX_LED
//      B0  RX_LED
//////////////////////////////////////////////////////////////////////////////////

// Key matrix parameters
// #define MATRIX_ROWS         4 * 2
#define MATRIX_ROWS 5 * 2
#define MATRIX_COLS 6

// #define MATRIX_ROW_PINS     { F4, F5, F6, F7 }          //F4 enc push sw
#define MATRIX_ROW_PINS \
    { F4, F5, F6, F7, D3 } // F4 enc push sw
#define MATRIX_COL_PINS \
    { D4, C6, D7, E6, B4, B5 } // B5 enc push sw only
// #define MATRIX_MASKED
// #define DEBOUNCE            5
#define DIODE_DIRECTION COL2ROW
// #define DIODE_DIRECTION     ROW2COLjkj

#define SOFT_SERIAL_PIN D2 // Split Keyboard specific options
// #define SELECT_SOFT_SERIAL_SPEED 5
#define MASTER_RIGHT

//////////////////////////////////////////////////////////////////////////////////
// trackball
// B2　　PAW3204_SCLK　　　右下一つ上
// B6  　PAW3204_DATA　　　　右下

// PCB
//  CN2
// 1  3.3v
// 2  SDIO  ----  B6
// 3  SCL   ----  B2
// 4  GND

// #define PAW3204_SCLK B2
// #define PAW3204_DATA B6

#define PAW3204_SCLK_PIN B2
#define PAW3204_SDIO_PIN B6

//////////////////////////////////////////////////////////////////////////////////////
// Rotary encoder
#define ENCODERS_PAD_A \
    { B1 }
#define ENCODERS_PAD_B \
    { B3 }
// #define ENCODER_RESOLUTION 2
#define ENCODER_RESOLUTION 4

// RGB LED settings
// #define RGB_DI_PIN       D3
// #define RGBLED_NUM       8
// #define RGBLIGHT_EFFECT_BREATHING

// OLED
//  D0 SCL
//  D1 SDA

#define RGBLIGHT_LIMIT_VAL 200
#define RGBLIGHT_VAL_STEP 15
#define RGBLIGHT_HUE_STEP 17
#define RGBLIGHT_SAT_STEP 17

// add test
