#include <stdint.h>
#include "action_layer.h"
#include "action_tapping.h"
#include "config.h"
#include "keyboard.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "pico/types.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

enum custom_layer { MAIN, MAIN_LIN, NUMBERS, SYMBOLS, NUM_LAYERS };

#define MT_CLEC LCTL_T(KC_ESC)
#define MT_CLQT RCTL_T(KC_QUOT)

#define MT_LSTG LSFT_T(CW_TOGG)
#define MT_RSTG RSFT_T(CW_TOGG)

#define MO_NUM MO(NUMBERS)
#define MO_SYM MO(SYMBOLS)

#define TG_LIN TG(MAIN_LIN)

// These doesn't work, need to implement them specially.
// There is a limitation in QMK's Mod-Tap: https://docs.qmk.fm/#/mod_tap
// #define LGUI_TOG LGUI_T(CW_TOGG)
// #define RGUI_TOG RGUI_T(CW_TOGG)
// #define LALT_TOG LALT_T(CW_TOGG)
// #define RALT_TOG RALT_T(CW_TOGG)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [MAIN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    CW_TOGG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT_CLQT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LALT,          KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, MO_NUM,  KC_SPC,                    KC_ENT,  MO_SYM,  KC_RGUI
  ),

  [MAIN_LIN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    CW_TOGG,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT_CLQT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,          KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT, KC_LALT, KC_SPC,                    KC_ENT, KC_RALT,  KC_RALT
  ),

  [NUMBERS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,          _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TG_LIN,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [SYMBOLS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_QUOT, KC_BSLS, KC_MINS, KC_PLUS, _______,                            _______, KC_EQL,  KC_UNDS, KC_PIPE, KC_DQUO, KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TILD, KC_LBRC, KC_LT,   KC_LPRN, KC_LCBR, _______,                            _______, KC_RCBR, KC_RPRN, KC_GT,   KC_RBRC, KC_GRV,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,          _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_HOME, KC_END,  QK_BOOT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};
// clang-format on

void set_rgb(const uint8_t index) {
    const uint8_t h[NUM_LAYERS] = {
        170,
        170,
        82,
        15,
    };
    const uint8_t s[NUM_LAYERS] = {
        124,
        124,
        255,
        255
    };
    const uint8_t v[NUM_LAYERS] = {
        150,
        150,
        155,
        155
    };

    rgblight_sethsv_noeeprom(h[index], s[index], v[index]);
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    const uint8_t mode_static_lighting = 1;
    rgblight_mode_noeeprom(mode_static_lighting);
    set_rgb(0);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    const uint16_t curr_layer = get_highest_layer(state);
    set_rgb(curr_layer);
    return state;
}
