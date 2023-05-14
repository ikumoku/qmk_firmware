// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"

#include "keycode.h"   //補完ができる？
#include "keymap_extras/keymap_jp.h"//補完ができる？



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     *
     *     "matrix_pins": {
        "cols": ["C2", "C2", "C2", "C2"],
        "rows": ["D1", "D1", "D1", "D1"]
    },　

    [0] = LAYOUT_ortho_4x4(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS
    ) */

      // keymap for default
     [0] = LAYOUT_ortho_4x4(
    KC_ESC   , KC_Q     , KC_W     , KC_E ,
    KC_TAB   , KC_A     , KC_S     , KC_D  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C ,
    KC_ESC   , KC_Q     , KC_W     , KC_E
     ),


};
