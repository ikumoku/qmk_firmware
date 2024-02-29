// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "print.h"

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
    KC_ESC   , KC_Q     , KC_W     , KC_I ,
    KC_A   , KC_X     , KC_S     , KC_O ,
    KC_B  , KC_Z     , KC_X     , KC_P,
    KC_C   , KC_Q     , KC_W     , KC_E
     ),

};

void keyboard_post_init_user(void) {
  // 希望する動作に合わせて値をカスタマイズします
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // コンソールが有効化されている場合、マトリックス上の位置とキー押下状態を出力します
#ifdef CONSOLE_ENABLE
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, 
         record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
 dprint("debug OK\n");
#endif
  return true;
}
 