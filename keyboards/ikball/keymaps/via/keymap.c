// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "print.h"

enum layer_names {
    _BASE,
    _L1,
    _L2,
    _L3,
};

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
*/

    [_BASE] = LAYOUT(
    KC_D   , KC_Q     , KC_W     , KC_I ,
    KC_A   , KC_X     , KC_S     , KC_O ,
    KC_B  , KC_Z     , KC_X     , KC_P,
    KC_C   , KC_Q     , KC_W     , KC_E
     ),

    [_L1] = LAYOUT(
    KC_D   , KC_Q     , KC_W     , KC_I ,
    KC_A   , KC_X     , KC_S     , KC_O ,
    KC_B  , KC_Z     , KC_X     , KC_P,
    KC_C   , KC_Q     , KC_W     , KC_E
     ),

    [_L2] = LAYOUT(
    KC_D   , KC_Q     , KC_W     , KC_I ,
    KC_A   , KC_X     , KC_S     , KC_O ,
    KC_B  , KC_Z     , KC_X     , KC_P,
    KC_C   , KC_Q     , KC_W     , KC_E
     ),

    [_L3] = LAYOUT(
    KC_D   , KC_Q     , KC_W     , KC_I ,
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
 