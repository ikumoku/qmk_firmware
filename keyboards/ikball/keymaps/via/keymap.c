// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keymap_japanese.h"

#include "quantum.h"
#include "print.h"
// #include <stdio.h>

#include "paw3204.h"
#include "pointing_device.h"

enum layer_names { _BASE, _L1, _L2, _L3, _L4, _L5 };
enum encoder_number {
    _1ST_ENC = 0,
    _2ND_ENC,
};

enum my_keycodes { MSCROLL = SAFE_RANGE, SCROLL_L, SCROLL_R };

enum mouse_mode { BALL_MODE_MOUSE, BALL_MODE_SCROLL_V, BALL_MODE_L_KEY, BALL_MODE_R_KEY };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I,

                     KC_Y, KC_U, KC_X, KC_I, KC_I, KC_I, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I),

    [_L1] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I,

                   KC_Y, KC_U, KC_X, KC_I, KC_I, KC_I, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I),
    [_L2] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I,

                   KC_Y, KC_U, KC_X, KC_I, KC_I, KC_I, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I),

    [_L3] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I,

                   KC_Y, KC_U, KC_X, KC_I, KC_I, KC_I, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I),

    [_L4] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I,

                   KC_Y, KC_U, KC_X, KC_I, KC_I, KC_I, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I),

    [_L5] = LAYOUT(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I,

                   KC_Y, KC_U, KC_X, KC_I, KC_I, KC_I, KC_A, KC_X, KC_S, KC_O, KC_I, KC_I, KC_B, KC_Z, KC_X, KC_P, KC_I, KC_I, KC_C, KC_Q, KC_W, KC_E, KC_I, KC_I)};

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
// bool    mouse_mode_scroll = false; // 上下スクロールモード

unsigned char ball_mode = BALL_MODE_MOUSE;

void matrix_init_user(void) {
    init_paw3204();
}

#define SCROLL_THRESHOLD_V 10
#define SCROLL_THRESHOLD_H 50

int cnt_mouse_v = 0;
int cnt_mouse_h = 0;

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;
    keypos_t    key;

    if (cnt++ % 50000 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            //   dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t  x, y;

        read_paw3204(&stat, &y, &x);
        mouse_rep.buttons = 0;

        if (ball_mode == BALL_MODE_SCROLL_V) {
            cnt_mouse_v += y;
            int scrolling_v = 0;

            if (cnt_mouse_v > SCROLL_THRESHOLD_V) {
                scrolling_v = 1;
                cnt_mouse_v = 0;
            } else if (cnt_mouse_v < SCROLL_THRESHOLD_V * (-1)) {
                scrolling_v = -1;
                cnt_mouse_v = 0;
            }

            mouse_rep.h = 0;
            mouse_rep.v = -scrolling_v;
            mouse_rep.x = 0;
            mouse_rep.y = 0;
        }

        if (ball_mode == BALL_MODE_L_KEY) {
            cnt_mouse_h += x;

            // uprintf("BALL_MODE_L_KEY:%d\n", cnt_mouse_h);

            if (cnt_mouse_h > SCROLL_THRESHOLD_H) {
                print("left!\n");
                cnt_mouse_h = 0;

                key.row = 3;
                key.col = 5;
                layer_move(_L1);
                action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
                action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
                layer_move(_L4);

            } else if (cnt_mouse_h < SCROLL_THRESHOLD_H * (-1)) {
                print("right!\n");

                cnt_mouse_h = 0;

                key.row = 7;
                key.col = 5;
                action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
                action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
            }
        }

        if (ball_mode == BALL_MODE_MOUSE) {
            // mouse mode
            mouse_rep.h = 0;
            mouse_rep.v = 0;
            mouse_rep.x = -x;
            mouse_rep.y = y;
        }

        if (cnt % 10 == 0) {
            // dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
            // uprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);

            static char type_count_str[7];
            itoa(stat, type_count_str, 10);
            oled_set_cursor(0, 8);
            //  oled_write_P(PSTR("Ball"), false);
            // oled_write(type_count_str, false);
            oled_set_cursor(0, 11);
            oled_write(format_4d(mouse_rep.x), false);
            oled_set_cursor(0, 13);
            oled_write(format_4d(mouse_rep.y), false);
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
    // joled_write_P(PSTR("test ok:"), false);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // print("process_record_user\n");

    // コンソールが有効化されている場合、マトリックス上の位置とキー押下状態を出力します
#ifdef CONSOLE_ENABLE
    //  dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);

#endif

    oled_set_cursor(0, 9);
    oled_write(format_4d(keycode), false);

    switch (keycode) {
        case MSCROLL: // custom(64) via

            if (record->event.pressed) {
                // 押された時に何かをします
                print("MSCROLL  pressed 2\n");
                //   mouse_mode_scroll = true;
                ball_mode = BALL_MODE_SCROLL_V;
            } else {
                // 放された時に何かをします
                print("MSCROLL  release\n");
                //  mouse_mode_scroll = false;
                ball_mode = BALL_MODE_MOUSE;
            }
            return false; // このキーの以降の処理をスキップします

        case SCROLL_L: // custom(65) via
            if (record->event.pressed) {
                print("SCROLL_L  pressed\n");
                ball_mode = BALL_MODE_L_KEY;
                // layer_move(_L5);

            } else {
                print("SCROLL_L  release\n");
                ball_mode = BALL_MODE_MOUSE;
               // layer_off(_L4);
            }
            return false;

        case SCROLL_R: // custom(66) via
            if (record->event.pressed) {
                print("SCROLL_R  pressed\n");

            } else {
                print("SCROLL_R  release\n");
            }
            return false;

        default:
            return true; // 他の全てのキーコードを通常通りに処理します
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////
// OLED utility

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
    return rotation;
}

//////////////////////////////////////////////////////////////////////////////
// encoder
bool encoder_update_kb(uint8_t index, bool clockwise) {
    keypos_t key;
    bool     encoder_layer_locked = false;

    if (index == 0) {
        if (clockwise) {
            key.row = 2;
            key.col = 5;
        } else {
            key.row = 1;
            key.col = 5;
        }
        if (get_highest_layer(layer_state) < _L3) {
            layer_on(_BASE);
            encoder_layer_locked = true;
        }
        action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
        action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
        if (encoder_layer_locked) {
           // layer_off(_BASE);
        }
    }

    if (index == 1) {
        if (clockwise) {
            key.row = 6;
            key.col = 5;
        } else {
            key.row = 5;
            key.col = 5;
        }
        if (get_highest_layer(layer_state) < _L3) {
            layer_on(_BASE);
            encoder_layer_locked = true;
        }
        action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
        action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
        if (encoder_layer_locked) {
            layer_off(_BASE);
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// change layer
layer_state_t layer_state_set_user(layer_state_t state) {
    oled_set_cursor(0, 0);
    //  oled_write_P(PSTR("Layer"), false);
    oled_set_cursor(2, 3);
    switch (get_highest_layer(state)) {
        case _BASE:
            print("layer 0\n");
            //  mouse_mode_scroll = false;
            ball_mode = BALL_MODE_MOUSE;

            oled_set_cursor(0, 2);
            oled_write_ln_P(PSTR("--0--"), false);
            oled_set_cursor(0, 3);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 4);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 5);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 6);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 7);
            oled_write_ln_P(PSTR("-   -"), false);

            break;

        case _L1:
            print("layer 1\n");
            // mouse_mode_scroll = false;
            ball_mode = BALL_MODE_MOUSE;

            oled_set_cursor(0, 2);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 3);
            oled_write_ln_P(PSTR("--1--"), false);
            oled_set_cursor(0, 4);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 5);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 6);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 7);
            oled_write_ln_P(PSTR("-   -"), false);

            break;

        case _L2:
            print("layer 2\n");
            // mouse_mode_scroll = false;
            ball_mode = BALL_MODE_MOUSE;

            oled_set_cursor(0, 2);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 3);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 4);
            oled_write_ln_P(PSTR("--2--"), false);
            oled_set_cursor(0, 5);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 6);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 7);
            oled_write_ln_P(PSTR("-   -"), false);
            break;

        case _L3:
            print("layer 3\n");
            // mouse_mode_scroll = true;
            ball_mode = BALL_MODE_SCROLL_V;
            oled_set_cursor(0, 2);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 3);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 4);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 5);
            oled_write_ln_P(PSTR("--3--"), false);
            oled_set_cursor(0, 6);
            oled_write_ln_P(PSTR("-   -"), false);
            oled_set_cursor(0, 7);
            oled_write_ln_P(PSTR("-   -"), false);
            break;

        case _L4:
            print("layer 4\n");
            //  mouse_mode_scroll = false;
            ball_mode = BALL_MODE_MOUSE;

            oled_set_cursor(0, 2);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 3);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 4);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 5);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 6);
            oled_write_ln_P(PSTR("--4--"), false);
            oled_set_cursor(0, 7);
            oled_write_ln_P(PSTR("-   -"), false);
            break;

        case _L5:
            print("layer 5\n");
            //  mouse_mode_scroll = false;
            ball_mode = BALL_MODE_MOUSE;

            oled_set_cursor(0, 2);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 3);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 4);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 5);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 6);
            oled_write_ln_P(PSTR("-- --"), false);
            oled_set_cursor(0, 7);
            oled_write_ln_P(PSTR("--5--"), false);
            break;

        default:

            break;
    }
    return state;
}
