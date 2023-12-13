#include <stdint.h>
#include "action_layer.h"
#include "keyboard.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include QMK_KEYBOARD_H

enum custom_layer { MAC_COLEMAK, MAC_QWERTY, LIN_COLEMAK, LIN_QWERTY, MAIN_LIN, RAISE, LOWER, NUM_LAYERS };

#define MT_CLEC LCTL_T(KC_ESC)
#define MT_CLTG RCTL_T(CW_TOGG)

#define MO_RAISE MO(RAISE)
#define MO_LOWER MO(LOWER)

#define TG_LIN TG(MAIN_LIN)

uint16_t last_key_pressed = KC_NO;
bool is_mac = true;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [MAC_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LALT,          KC_RALT, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, MO_RAISE,KC_SPC,                    KC_ENT,  MO_LOWER,KC_RGUI
  ),

  [MAC_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LALT,          KC_RALT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI, MO_RAISE,KC_SPC,                    KC_ENT,  MO_LOWER,KC_RGUI
  ),

  [LIN_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LGUI,          KC_RGUI, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT, MO_RAISE,KC_SPC,                    KC_ENT,  MO_LOWER,KC_RALT
  ),

  [LIN_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,          KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT, MO_RAISE,KC_SPC,                    KC_ENT,  MO_LOWER,KC_RALT
  ),

  [RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F12,  _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_F11,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, KC_NO,   _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_HOME, KC_END,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LBRC, KC_LT,   KC_LPRN, KC_LCBR, KC_TILD,                            KC_GRV,  KC_RCBR, KC_RPRN, KC_GT,   KC_RBRC, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_QUOT, KC_BSLS, KC_MINS, KC_PLUS, _______, _______,          _______, _______, KC_EQL,  KC_UNDS, KC_PIPE, KC_DQUO, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, KC_NO,   QK_LEAD,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};
// clang-format on

void set_rgb(const uint8_t index) {
    const uint8_t h[NUM_LAYERS] = {
        170,
        170,
        170,
        170,
        82,
        15,
    };
    const uint8_t s[NUM_LAYERS] = {
        124,
        124,
        124,
        124,
        255,
        255
    };
    const uint8_t v[NUM_LAYERS] = {
        150,
        150,
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

    is_mac = true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    const uint16_t curr_layer = get_highest_layer(state);
    set_rgb(curr_layer);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Custom mod-tap since QMK MT doesnt support the CW_TOGG key in MT.
    if (record->event.pressed) {
        last_key_pressed = keycode;

        if (keycode == MT_CLTG) {
            register_code(KC_RCTL);
        }
    } else {
        if (keycode == MT_CLTG) {
            unregister_code(KC_RCTL);

            if (last_key_pressed == MT_CLTG) {
                caps_word_toggle();
            }

            return false;
        }
    }

    return true;
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_B)) {
        reset_keyboard();
    } else if (leader_sequence_three_keys(KC_L, KC_M, KC_Q)) {
        default_layer_set(1UL << MAC_QWERTY);
        is_mac = true;
    } else if (leader_sequence_three_keys(KC_L, KC_M, KC_C)) {
        default_layer_set(1UL << MAC_COLEMAK);
        is_mac = true;
    } else if (leader_sequence_three_keys(KC_L, KC_L, KC_Q)) {
        default_layer_set(1UL << LIN_QWERTY);
        is_mac = false;
    } else if (leader_sequence_three_keys(KC_L, KC_L, KC_C)) {
        default_layer_set(1UL << LIN_COLEMAK);
        is_mac = false;
    } else if (leader_sequence_two_keys(KC_E, KC_L)) {
        SEND_STRING("larssonmartin1998@gmail.com");
    } else if (leader_sequence_two_keys(KC_E, KC_Q)) {
        SEND_STRING("qvantry@gmail.com");
    } else if (leader_sequence_two_keys(KC_E, KC_W)) {
        SEND_STRING("martin.larsson@fasttravelgames.com");
    }

}
