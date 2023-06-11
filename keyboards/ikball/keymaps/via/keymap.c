// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keymap_japanese.h"

#include "quantum.h"
#include "print.h"

#include "paw3204.h"
#include "pointing_device.h"


enum layer_names {
    _BASE,
    _L1,
    _L2,
    _L3,
    _L4,
    _L5
};
enum encoder_number {
    _1ST_ENC = 0,
    _2ND_ENC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC, KC_Q,   KC_W,   KC_E,  KC_R,  KC_T,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I,

        KC_Y,   KC_U,   KC_X,   KC_I,  KC_I,  KC_I,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I
     ),

    [_L1] = LAYOUT(
        KC_ESC, KC_Q,   KC_W,   KC_E,  KC_R,  KC_T,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I,

        KC_Y,   KC_U,   KC_X,   KC_I,  KC_I,  KC_I,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I
     ),
    [_L2] = LAYOUT(
        KC_ESC, KC_Q,   KC_W,   KC_E,  KC_R,  KC_T,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I,

        KC_Y,   KC_U,   KC_X,   KC_I,  KC_I,  KC_I,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I
     ),

    [_L3] = LAYOUT(
        KC_ESC, KC_Q,   KC_W,   KC_E,  KC_R,  KC_T,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I,

        KC_Y,   KC_U,   KC_X,   KC_I,  KC_I,  KC_I,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I
     ),

    [_L4] = LAYOUT(
        KC_ESC, KC_Q,   KC_W,   KC_E,  KC_R,  KC_T,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I,

        KC_Y,   KC_U,   KC_X,   KC_I,  KC_I,  KC_I,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I
     ),

    [_L5] = LAYOUT(
        KC_ESC, KC_Q,   KC_W,   KC_E,  KC_R,  KC_T,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I,

        KC_Y,   KC_U,   KC_X,   KC_I,  KC_I,  KC_I,
        KC_A,   KC_X,   KC_S,   KC_O,  KC_I,  KC_I,
        KC_B,   KC_Z,   KC_X,   KC_P,  KC_I,  KC_I,
        KC_C,   KC_Q,   KC_W,   KC_E,  KC_I,  KC_I
     )
};
//////////////////////////////////////////////////////////////////////////////
// OLED表示用

/* static const char *format_4d(int8_t d) {
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
} */

//////////////////////////////////////////////////////////////////////////////
// trackball

report_mouse_t mouse_rep;
bool           mouse_mode_scroll = false;

void matrix_init_user(void) {
    init_paw3204();
}

#define SCROLL_THRESHOLD 10
bool is_scrolling = false;
int  cnt_mouse_v  = 0;

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;
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

        read_paw3204(&stat, &x, &y);
        mouse_rep.buttons = 0;

        if (mouse_mode_scroll) {
            cnt_mouse_v += x;
            int scrolling_v = 0;

            if (cnt_mouse_v > SCROLL_THRESHOLD) {
                scrolling_v = 1;
                cnt_mouse_v = 0;
            } else if (cnt_mouse_v < SCROLL_THRESHOLD * (-1)) {
                scrolling_v = -1;
                cnt_mouse_v = 0;
            }

            mouse_rep.h = 0;
            mouse_rep.v = -scrolling_v;
            mouse_rep.x = 0;
            mouse_rep.y = 0;

        } else {
            // mouse mode
            mouse_rep.h = 0;
            mouse_rep.v = 0;
            mouse_rep.x = -y;
            mouse_rep.y = x;
        }

        if (cnt % 100 == 0) {
         //   dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);

     /*        static char type_count_str[7];
            itoa(stat, type_count_str, 10);
            oled_write_P(PSTR("Ball:"), false);
            oled_write(type_count_str, false);
            oled_write(format_4d(mouse_rep.x), false);
            oled_write(format_4d(mouse_rep.y), false); */
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
      oled_write_P(PSTR("test ok:"), false);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // コンソールが有効化されている場合、マトリックス上の位置とキー押下状態を出力します
#ifdef CONSOLE_ENABLE
    dprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n",
     keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
     
#endif
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// OLED utility

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
    return rotation;
}

/* #define L_BASE 0
#define L_LOWER 1
#define L_RAISE 2
#define L_ADJUST 3 */

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case _BASE:
            oled_write_ln_P(PSTR("0"), false);
            break;
        case _L1:
            oled_write_ln_P(PSTR("1"), false);
            break;
        case _L2:
            oled_write_ln_P(PSTR("2"), false);
            break;
        case _L3:
            oled_write_ln_P(PSTR("3"), false);
            break;
    }
}

bool oled_task_user(void) {
    oled_render_layer_state();
    return false;
}



//////////////////////////////////////////////////////////////////////////////
//encoder
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
            layer_off(_BASE);
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
//change layer
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _BASE:
        dprint("layer 0\n");
        mouse_mode_scroll  = false;
         oled_write_ln_P(PSTR("0"), false);
        break;
    case _L1:
        dprint("layer 1\n");
         mouse_mode_scroll  = false;
          oled_write_ln_P(PSTR("1"), false);
        break;
    case _L2:
        dprint("layer 2\n");
         mouse_mode_scroll  = false;
          oled_write_ln_P(PSTR("2"), false);
        break;
    case _L3:
        dprint("layer 3\n");
         mouse_mode_scroll  = true;
        break;
    case _L4:
        dprint("layer 4\n");
         mouse_mode_scroll  = false;
        break;
    case _L5:
        dprint("layer 5\n");
         mouse_mode_scroll  = false;
        break;



    default:

        break;
    }
  return state;
}

/*
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case _1ST_ENC:
            if (clockwise) {
                tap_code(KC_VOLU);
                // tap_code(KC_PGDN);
                dprint("_1ST_ENC cw\n");
            } else {
                tap_code(KC_VOLD);
                // tap_code(KC_PGUP);
                dprint("_1ST_ENC ccw\n");
            }
            break;
        case _2ND_ENC:
            if (clockwise) {
                tap_code(KC_VOLU);
                dprint("_2ST_ENC cw\n");
            } else {
                tap_code(KC_VOLD);
                dprint("_2ST_ENC ccw\n");
            }
            break;
    }
    return false;
}
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case _1ST_ENC:
            if (clockwise) {
                tap_code(KC_VOLU);
                // tap_code(KC_PGDN);
                dprint("_1ST_ENC cw\n");
            } else {
                tap_code(KC_VOLD);
                // tap_code(KC_PGUP);
                dprint("_1ST_ENC ccw\n");
            }
            break;
        case _2ND_ENC:
            if (clockwise) {
                tap_code(KC_VOLU);
                dprint("_2ST_ENC cw\n");
            } else {
                tap_code(KC_VOLD);
                dprint("_2ST_ENC ccw\n");
            }
            break;
    }
    return false;
}
c
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (index) {
        case _1ST_ENC:
            if (clockwise) {
                tap_code(KC_VOLU);
                // tap_code(KC_PGDN);
                dprint("_1ST_ENC cw\n");
            } else {
                tap_code(KC_VOLD);
                // tap_code(KC_PGUP);
                dprint("_1ST_ENC ccw\n");
            }
            break;
        case _2ND_ENC:
            if (clockwise) {
                tap_code(KC_VOLU);
                dprint("_2ST_ENC cw\n");
            } else {
                tap_code(KC_VOLD);
                dprint("_2ST_ENC ccw\n");
            }
            break;
    }
    return false;
} */
