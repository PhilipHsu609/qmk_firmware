// Insert lincense here
#include QMK_KEYBOARD_H

// clang-format off
enum layer_names {
    _BASE,
    _NAV,
    _FKEYS,
    _ADJUST,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    NAV_SCLN,
    F_FKEYS,
};

#define ADJ MO(_ADJUST)
#define F_FKEYS LT(_FKEYS, KC_F)

#define WORD_L LALT(KC_LEFT)
#define WORD_R LALT(KC_RGHT)

#define LINE_L LGUI(KC_LEFT)
#define LINE_R LGUI(KC_RGHT)