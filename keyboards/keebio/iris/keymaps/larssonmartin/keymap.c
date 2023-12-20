#include <stdint.h>
#include "action_layer.h"
#include "keyboard.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include "process_combo.h"
#include QMK_KEYBOARD_H

enum custom_layer { MAC_TARMAK1, LIN_TARMAK1, RAISE, LOWER, NUM_LAYERS };

#define MT_CLEC LCTL_T(KC_ESC)
#define MT_CLTG RCTL_T(CW_TOGG)

#define MO_RAISE MO(RAISE)
#define MO_LOWER MO(LOWER)

uint16_t last_key_pressed = KC_NO;
bool is_mac = true;

enum combo_events {
    LEFT_OS,
    RIGHT_OS
};

const uint16_t PROGMEM CO_LOS[] = { KC_Z, KC_X, COMBO_END };
const uint16_t PROGMEM CO_ROS[] = { KC_DOT, KC_SLSH, COMBO_END };
combo_t key_combos[] = {
    [LEFT_OS] = COMBO_ACTION(CO_LOS),
    [RIGHT_OS] = COMBO_ACTION(CO_ROS)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [MAC_TARMAK1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_J,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_L,    KC_SCLN, MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,            KC_NO, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCMD, MO_RAISE,KC_SPC,                    KC_ENT,  MO_LOWER,KC_RCMD
  ),

  [LIN_TARMAK1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_J,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_L,    KC_SCLN, MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,            KC_NO, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
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
    } else if (leader_sequence_two_keys(KC_L, KC_M)) {
        default_layer_set(1UL << MAC_TARMAK1);
        is_mac = true;
    } else if (leader_sequence_two_keys(KC_L, KC_L)) {
        default_layer_set(1UL << LIN_TARMAK1);
        is_mac = false;
    } else if (leader_sequence_two_keys(KC_E, KC_L)) {
        SEND_STRING("larssonmartin1998@gmail.com");
    } else if (leader_sequence_two_keys(KC_E, KC_Q)) {
        SEND_STRING("qvantry@gmail.com");
    } else if (leader_sequence_two_keys(KC_E, KC_W)) {
        SEND_STRING("martin.larsson@fasttravelgames.com");
    }
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    uint16_t keycode = KC_NO;
    switch (combo_index) {
        case LEFT_OS:
            keycode = is_mac ? KC_LOPT : KC_LWIN;
        break;
        case RIGHT_OS:
            keycode = is_mac ? KC_ROPT : KC_RWIN;
        break;
    }

    if (pressed) {
        register_code(keycode);
    } else {
        unregister_code(keycode);
    }
}

