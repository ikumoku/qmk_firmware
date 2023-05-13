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
#define MATRIX_ROWS        4
#define MATRIX_COLS         4
#define MATRIX_ROW_PINS     { F4, F5, F6, F7 }
#define MATRIX_COL_PINS     { D4, C6, D7, E6 }
//#define MATRIX_MASKED
//#define DEBOUNCE            5
#define DIODE_DIRECTION     COL2ROW
