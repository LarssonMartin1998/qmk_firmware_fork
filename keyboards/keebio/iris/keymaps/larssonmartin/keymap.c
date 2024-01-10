#include <stdint.h>
#include "action_layer.h"
#include "keyboard.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include "process_combo.h"
#include QMK_KEYBOARD_H

enum rgb_modes { RGB_MAC, RGB_LIN, RGB_LEADER_ACTIVE, NUM_RGB_MODES };
enum custom_layer { MAC_TARMAK4, LIN_TARMAK4, RAISE, LOWER, NUM_LAYERS };

#define MT_CLEC LCTL_T(KC_ESC)
#define MT_CLTG RCTL_T(CW_TOGG)

#define MO_RAISE MO(RAISE)
#define MO_LOWER MO(LOWER)

uint16_t last_key_pressed = KC_NO;
bool is_mac = true;
bool is_leader_active = false;

enum combo_events {
    LEFT_OS, // Opt / Super
    RIGHT_OS, // Opt / Super
    LEFT_CA, // Cmd / Alt
    RIGHT_CA, // Cmd / Alt
};

const uint16_t PROGMEM CO_LOS[] = { KC_Z, KC_X, COMBO_END };
const uint16_t PROGMEM CO_ROS[] = { KC_DOT, KC_SLSH, COMBO_END };
const uint16_t PROGMEM CO_LCA[] = { KC_X, KC_C, COMBO_END };
const uint16_t PROGMEM CO_RCA[] = { KC_COMM, KC_DOT, COMBO_END };
const uint16_t PROGMEM CO_LEAD[] = { KC_TAB, KC_BSPC, COMBO_END };
combo_t key_combos[] = {
    [LEFT_OS] = COMBO_ACTION(CO_LOS),
    [RIGHT_OS] = COMBO_ACTION(CO_ROS),
    [LEFT_CA] = COMBO_ACTION(CO_LCA),
    [RIGHT_CA] = COMBO_ACTION(CO_RCA),
    COMBO(CO_LEAD, QK_LEAD),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [MAC_TARMAK4] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_U,    KC_I,    KC_Y,    KC_SCLN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_L,    KC_O,    MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_NO,            KC_NO,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LCMD, MO_RAISE,KC_SPC,                    KC_ENT,  MO_LOWER,KC_RCMD
  ),

  [LIN_TARMAK4] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_U,    KC_I,    KC_Y,    KC_SCLN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     MT_CLEC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                               KC_M,    KC_N,    KC_E,    KC_L,    KC_O,    MT_CLTG,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_NO,            KC_NO,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
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
                                    _______, KC_NO,   _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};
// clang-format on

uint8_t get_rgb_state(void) {
    if (is_leader_active) {
        return RGB_LEADER_ACTIVE;
    } else if (is_mac) {
        return RGB_MAC;
    } else {
        return RGB_LIN;
    }
}

void set_rgb(void) {
    const uint8_t index = get_rgb_state();
    const uint8_t h[NUM_RGB_MODES] = {
        170,
        170,
        15,
    };
    const uint8_t s[NUM_RGB_MODES] = {
        80,
        160,
        255
    };
    const uint8_t v[NUM_RGB_MODES] = {
        100,
        170,
        155
    };

    rgblight_sethsv_noeeprom(h[index], s[index], v[index]);
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    const uint8_t mode_static_lighting = 1;
    rgblight_mode_noeeprom(mode_static_lighting);
    set_rgb();

    is_mac = true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    set_rgb();
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
    is_leader_active = true;

    set_rgb();
}

void leader_end_user(void) {
    is_leader_active = false;

    // QMK
    if (leader_sequence_two_keys(KC_Q, KC_B)) {
        reset_keyboard();
    // Layers
    } else if (leader_sequence_two_keys(KC_L, KC_M)) {
        default_layer_set(1UL << MAC_TARMAK4);
        is_mac = true;
    } else if (leader_sequence_two_keys(KC_L, KC_L)) {
        default_layer_set(1UL << LIN_TARMAK4);
        is_mac = false;
    // Emails
    } else if (leader_sequence_two_keys(KC_E, KC_L)) {
        SEND_STRING("larssonmartin1998@gmail.com");
    } else if (leader_sequence_two_keys(KC_E, KC_Q)) {
        SEND_STRING("qvantry@gmail.com");
    } else if (leader_sequence_two_keys(KC_E, KC_W)) {
        SEND_STRING("martin.larsson@fasttravelgames.com");
    // Media
    } else if (leader_sequence_two_keys(KC_M, KC_SPC)) {
        tap_code(KC_MEDIA_PLAY_PAUSE);
    } else if (leader_sequence_two_keys(KC_M, KC_P)) {
        tap_code(KC_MEDIA_PREV_TRACK);
    } else if (leader_sequence_two_keys(KC_M, KC_N)) {
        tap_code(KC_MEDIA_NEXT_TRACK);
    }

    set_rgb();
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
        case LEFT_CA:
            keycode = is_mac ? KC_LCMD : KC_LALT;
        break;
        case RIGHT_CA:
            keycode = is_mac ? KC_RCMD : KC_RALT;
        break;
    }

    if (pressed) {
        register_code(keycode);
    } else {
        unregister_code(keycode);
    }
}

