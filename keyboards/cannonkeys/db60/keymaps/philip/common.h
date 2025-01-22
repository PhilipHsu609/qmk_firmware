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
#define FKEYS MO(_FKEYS)

#define WORD_L LALT(KC_LEFT)
#define WORD_R LALT(KC_RGHT)

#define LINE_L LGUI(KC_LEFT)
#define LINE_R LGUI(KC_RGHT)

#define CAP_SRN LGUI(LSFT(KC_3))
#define CAP_IMG LGUI(LSFT(KC_4))

#define COPY LGUI(KC_C)
#define PASTE LGUI(KC_V)
#define CUT LGUI(KC_X)
