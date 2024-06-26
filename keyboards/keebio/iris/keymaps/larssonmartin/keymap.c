#include <stdint.h>
#include "action_layer.h"
#include "unicode/unicode.h"
#include "keyboard.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "quantum_keycodes.h"
#include "rgb_matrix.h"
#include "process_combo.h"
#include "unicode/unicode.h"
#include QMK_KEYBOARD_H

enum custom_keycodes {
    UC_AA = SAFE_RANGE,
    UC_AE,
    UC_OE,
};

enum rgb_modes { RGB_BASE, RGB_LEADER_ACTIVE, NUM_RGB_MODES };
enum custom_layer { LIN_COLEMAK_DH, MAC_COLEMAK_DH, WIN_COLEMAK_DH, RAISE, LOWER, GAMING, NUM_LAYERS };

#define GUI_A LGUI_T(KC_A)
#define ALT_A LALT_T(KC_A)
#define GUI_R LGUI_T(KC_R)
#define ALT_R LALT_T(KC_R)
#define CTL_S LCTL_T(KC_S)
#define SFT_t LSFT_T(KC_T)

#define SFT_N RSFT_T(KC_N)
#define CTL_E RCTL_T(KC_E)
#define ALT_I RALT_T(KC_I)
#define GUI_I RGUI_T(KC_I)
#define ALT_O RALT_T(KC_O)
#define GUI_O RGUI_T(KC_O)

#define RSE_TAB LT(RAISE, KC_TAB)
#define LWR_BSPC LT(LOWER, KC_BSPC)

enum custom_layer current_base_layer = LIN_COLEMAK_DH;
bool              is_leader_active   = false;

bool is_in_numbers_mode = false;

const uint16_t PROGMEM CO_LEAD[] = {KC_Z, KC_SLSH, COMBO_END};
const uint16_t PROGMEM CO_AA[]   = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM CO_AE[]   = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM CO_OE[]   = {KC_Y, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    COMBO(CO_LEAD, QK_LEAD),
    COMBO(CO_AA, UC_AA),
    COMBO(CO_AE, UC_AE),
    COMBO(CO_OE, UC_OE),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [LIN_COLEMAK_DH] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   GUI_A,   ALT_R,   CTL_S,   SFT_t,   KC_G,                               KC_M,    SFT_N,   CTL_E,   ALT_I,   GUI_O,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_NO,            KC_NO,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_NO,   RSE_TAB, KC_SPC,                    KC_ENT,  LWR_BSPC,KC_NO
  ),

  [MAC_COLEMAK_DH] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   ALT_A,   GUI_R,   CTL_S,   SFT_t,   KC_G,                               KC_M,    SFT_N,   CTL_E,   GUI_I,   ALT_O,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_NO,            KC_NO,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_NO,   RSE_TAB, KC_SPC,                    KC_ENT,  LWR_BSPC,KC_NO
  ),

  [WIN_COLEMAK_DH] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   GUI_A,   ALT_R,   CTL_S,   SFT_t,   KC_G,                               KC_M,    SFT_N,   CTL_E,   ALT_I,   GUI_O,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_NO,            KC_NO,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_NO,   RSE_TAB, KC_SPC,                    KC_ENT,  LWR_BSPC,KC_NO
  ),

  [GAMING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_A,   KC_R,   KC_S,   KC_T,   KC_G,                               KC_M,    KC_N,   KC_E,   KC_I,   KC_O,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_NO,            KC_NO,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_NO,   KC_TAB, KC_SPC,                    KC_ENT,  KC_BSPC,KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [RAISE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F11,  _______, _______, _______, _______,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_F12,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,          _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   KC_ENT,  KC_DEL,  _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [LOWER] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_HOME, KC_END,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LBRC, KC_LT,   KC_LPRN, KC_LCBR, KC_TILD,                            KC_GRV,  KC_RCBR, KC_RPRN, KC_GT,   KC_RBRC, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_QUOT, KC_BSLS, KC_MINS, KC_PLUS, _______, _______,          _______, _______, KC_EQL,  KC_UNDS, KC_PIPE, KC_DQUO, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, KC_ESC,  KC_SPC,                    _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
};
// clang-format on

uint8_t get_rgb_state(void) {
    if (is_leader_active) {
        return RGB_LEADER_ACTIVE;
    } else {
        return RGB_BASE;
    }
}

void set_rgb(void) {
    const uint8_t index            = get_rgb_state();
    const uint8_t h[NUM_RGB_MODES] = {170, 15};
    const uint8_t s[NUM_RGB_MODES] = {160, 255};
    const uint8_t v[NUM_RGB_MODES] = {170, 155};

    rgblight_sethsv_noeeprom(h[index], s[index], v[index]);
}

void set_operating_system(enum custom_layer layer, uint8_t unicode_input_mode) {
    default_layer_set(1UL << layer);
    current_base_layer = layer;
    set_unicode_input_mode(unicode_input_mode);
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    const uint8_t mode_static_lighting = 1;
    rgblight_mode_noeeprom(mode_static_lighting);
    set_rgb();

    set_operating_system(LIN_COLEMAK_DH, UNICODE_MODE_LINUX);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    set_rgb();
    is_in_numbers_mode = false;

    return state;
}

void leader_start_user(void) {
    is_leader_active = true;

    set_rgb();
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_t:
        case SFT_N:
            return TAPPING_TERM - 20;
        case CTL_S:
        case CTL_E:
            return TAPPING_TERM - 15;
        case ALT_A:
        case GUI_A:
        case ALT_O:
        case GUI_O:
            return TAPPING_TERM + 5;
        default:
            return TAPPING_TERM;
    }
}

void leader_end_user(void) {
    is_leader_active = false;

    // QMK
    if (leader_sequence_two_keys(KC_Q, KC_B)) {
        reset_keyboard();
        // Layers
    } else if (leader_sequence_two_keys(KC_L, KC_L)) {
        set_operating_system(LIN_COLEMAK_DH, UNICODE_MODE_LINUX);
    } else if (leader_sequence_two_keys(KC_L, KC_M)) {
        set_operating_system(MAC_COLEMAK_DH, UNICODE_MODE_MACOS);
    } else if (leader_sequence_two_keys(KC_L, KC_W)) {
        set_operating_system(WIN_COLEMAK_DH, UNICODE_MODE_WINCOMPOSE);
    } else if (leader_sequence_two_keys(KC_L, KC_G)) {
        default_layer_set(1UL << GAMING);
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
        // Typing
    } else if (leader_sequence_one_key(KC_C)) {
        caps_word_toggle();
    }

    set_rgb();
}

void try_activate_numbers_mode(uint16_t keycode) {
    switch (keycode) {
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
        case KC_0:
            is_in_numbers_mode = true;
            break;
    }
}

uint16_t get_converted_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_F8:
            return KC_COMM;
        case KC_F9:
            return KC_DOT;
        case KC_DEL:
            return KC_BSPC;
    }

    return KC_NO;
}

bool handle_numbers_mode(uint16_t keycode, keyrecord_t *record) {
    try_activate_numbers_mode(keycode);

    if (!is_in_numbers_mode) {
        return true;
    }

    const uint16_t converted_keycode = get_converted_keycode(keycode);
    if (converted_keycode == KC_NO) {
        return true;
    }

    if (record->event.pressed) {
        register_code(converted_keycode);
    } else {
        unregister_code(converted_keycode);
    }

    return false;
}

bool is_shift_held(void) {
    return (get_mods() & MOD_MASK_SHIFT) != 0;
}

void register_unicode_letter(uint16_t lower, uint16_t upper) {
    if (is_shift_held()) {
        register_unicode(upper);
    } else {
        register_unicode(lower);
    }
}

bool handle_swedish_unicode_chars(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case UC_AA:
            register_unicode_letter(0x00E5, 0x00C5);
            return false;
        case UC_AE:
            register_unicode_letter(0x00E4, 0x00C4);
            return false;
        case UC_OE:
            register_unicode_letter(0x00F6, 0x00D6);
            return false;
        default:
            return true;
    }
}

void try_unregister_numbers_mode(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        return;
    }

    switch (keycode) {
        case KC_F8:
            unregister_code(KC_COMM);
            break;
        case KC_F9:
            unregister_code(KC_DOT);
            break;
        case KC_DEL:
            unregister_code(KC_BSPC);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    try_unregister_numbers_mode(keycode, record);

    if (layer_state_is(RAISE)) {
        return handle_numbers_mode(keycode, record);
    }

    return handle_swedish_unicode_chars(keycode, record);
}
