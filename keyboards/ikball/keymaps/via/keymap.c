// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "print.h"

#include "paw3204.h"
#include "pointing_device.h"

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
        KC_D,   KC_Q,   KC_W,   KC_I, 
        KC_A,   KC_X,   KC_S,   KC_O,
        KC_B,   KC_Z,   KC_X,   KC_P, 
        KC_C,   KC_Q,   KC_W,   KC_E
     ),

    [_L1] = LAYOUT(KC_D, KC_Q, KC_W, KC_I, KC_A, KC_X, KC_S, KC_O, KC_B, KC_Z, KC_X, KC_P, KC_C, KC_Q, KC_W, KC_E),

    [_L2] = LAYOUT(KC_D, KC_Q, KC_W, KC_I, KC_A, KC_X, KC_S, KC_O, KC_B, KC_Z, KC_X, KC_P, KC_C, KC_Q, KC_W, KC_E),

    [_L3] = LAYOUT(KC_D, KC_Q, KC_W, KC_I, KC_A, KC_X, KC_S, KC_O, KC_B, KC_Z, KC_X, KC_P, KC_C, KC_Q, KC_W, KC_E),

};
//////////////////////////////////////////////////////////////////////////////
// OLED表示用
static const char *format_4d(int8_t d) {
    static char buf[5] = {0}; // max width (4) + NUL (1)
    char        lead   = ' ';
    if (d < 0) {
        d    = -d;
        lead = '-';
    }
    buf[3] = (d % 10) + '0';
    d /= 10;
    if (d == 0) {
        buf[2] = lead;
        lead   = ' ';
    } else {
        buf[2] = (d % 10) + '0';
        d /= 10;
    }
    if (d == 0) {
        buf[1] = lead;
        lead   = ' ';
    } else {
        buf[1] = (d % 10) + '0';
        d /= 10;
    }
    buf[0] = lead;
    return buf;
}

//////////////////////////////////////////////////////////////////////////////
// trackball

report_mouse_t mouse_rep;

void matrix_init_user(void) {
    init_paw3204();
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;
    if (cnt++ % 1000 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t  x, y;

        read_paw3204(&stat, &x, &y);
        mouse_rep.buttons = 0;
        mouse_rep.h       = 0;
        mouse_rep.v       = 0;
        //mouse_rep.x       = y;
       // mouse_rep.y       = -x;
        mouse_rep.x       = -y;
        mouse_rep.y       = x;

        if (cnt % 10 == 0) {
<<<<<<< Updated upstream
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);

            static char type_count_str[7];
            itoa(stat, type_count_str, 10);
            oled_write_P(PSTR("Ball:"), false);
          //  oled_write(type_count_str, false);
            oled_write(format_4d(mouse_rep.x), false);
            oled_write(format_4d(mouse_rep.y), false);
=======
             dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
>>>>>>> Stashed changes
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
// init

void keyboard_post_init_user(void) {
    // 希望する動作に合わせて値をカスタマイズします
    debug_enable = true;
    debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // コンソールが有効化されている場合、マトリックス上の位置とキー押下状態を出力します
#ifdef CONSOLE_ENABLE
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n",
     keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    dprint("debug OK\n");
#endif
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// OLED utility
/*
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
    return rotation;
}
*/

#define L_BASE 0
#define L_LOWER 1
#define L_RAISE 2
#define L_ADJUST 3

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("0"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("1"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("2"), false);
            break;
        case L_ADJUST:
            oled_write_ln_P(PSTR("3"), false);
            break;
    }
}

bool oled_task_user(void) {
    oled_render_layer_state();
    return false;
}
