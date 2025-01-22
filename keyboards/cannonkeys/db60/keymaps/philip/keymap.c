//
#include QMK_KEYBOARD_H
#include "common.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_ansi(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
        KC_LGUI, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NAV_SCLN,KC_QUOT,           KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,
        FKEYS,   KC_LCTL, KC_LALT,                            KC_SPC,                             KC_RCTL, KC_RALT, KC_MEH,   ADJ
    ),
    [_NAV] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, WORD_R,  _______, _______, _______, _______, KC_PGUP, LINE_L,  LINE_R,  _______, _______, _______, _______,
        _______, _______, _______, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, CUT    , COPY   , PASTE  , WORD_L,  _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [_FKEYS] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_U, _______, _______, _______, _______, _______,
        _______, _______, _______, KC_BTN1, KC_BTN2, _______, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_60_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MPRV, KC_MNXT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          CAP_IMG,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   CAP_SRN,
        QK_BOOT, _______, _______,                            _______,                            _______, _______, _______, _______
    )
};
// clang-format on

static uint16_t last_key_code;
static uint32_t last_key_time;

static int semicolon_nav_activated;

void unregister_nav_scln_down_state(void) {
    unregister_code16(KC_SCLN);
    semicolon_nav_activated = 0;
}

bool process_nav_scln(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NAV_SCLN:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LSFT) || (get_mods() == 0 && timer_elapsed(last_key_time) < 100)) {
                    register_code16(KC_SCLN);
                    semicolon_nav_activated = 2;
                    return true;
                } else {
                    semicolon_nav_activated = 1;
                    layer_on(_NAV);
                    return false;
                }
            } else {
                switch (semicolon_nav_activated) {
                    case 1:
                        if (timer_elapsed(last_key_time) < 250) {
                            clear_mods();
                            tap_code16(KC_SCLN);
                        }
                        break;
                }
                unregister_nav_scln_down_state();
                layer_off(_NAV);
                return false;
            }
    }

    if (!record->event.pressed && semicolon_nav_activated < 1) {
        return true;
    }

    switch (keycode) {
        case KC_UP:
        case KC_DOWN:
        case KC_PGUP:
        case KC_PGDN:
        case WORD_L:
        case WORD_R:
        case LINE_L:
        case LINE_R:
        case KC_LEFT:
        case KC_RGHT:
            unregister_nav_scln_down_state();
            semicolon_nav_activated = 2;
            return true;
        case KC_LGUI:
        case KC_LSFT:
        case KC_RSFT:
            return true;
    }

    return true;
}

bool process_all_custom(uint16_t keycode, keyrecord_t *record) {
    if (!process_nav_scln(keycode, record)) {
        return false;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool retval = process_all_custom(keycode, record);

    if (record->event.pressed) {
        last_key_time = timer_read();
        last_key_code = keycode;
    }

    return retval;
}
