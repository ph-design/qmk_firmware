// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H



enum custom_layers {
    _BASE_WIN,
    _BASE_MAC,
    _FN1,
};


os_variant_t current_os = OS_UNSURE;

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) return false;
    
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            current_os = OS_MACOS;
            set_single_persistent_default_layer(_BASE_MAC);
            break;
        default: // Windows/Linux/Uncertain
            current_os = OS_WINDOWS;
            set_single_persistent_default_layer(_BASE_WIN);
    }
    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Windows Base Layer
    [_BASE_WIN] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,  MO(_FN1)，KC_RGUI,KC_RCTL
    ),
    // Mac Base Layer
    [_BASE_MAC] = LAYOUT_60_ansi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(_FN1),KC_RALT,KC_RCTL
    ),
    // Fn1 Layer
    [_FN1] = LAYOUT_60_ansi(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, KC_UP,   _______, _______, _______, _______, _______, KC_INS,  _______, KC_PSCR, KC_SCRL, KC_PAUS, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP,          _______,
        _______,          RM_ON, RM_NEXT, RGB_HUI, RGB_HUD, RGB_SAI, RM_VALU, RM_VALD, _______, KC_END,  KC_PGDN,          _______,
        _______, GU_TOGG, _______,                            _______,                            _______, _______, _______, _______
    ),
};

led_config_t g_led_config = {
        {
            { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 },
            { 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14 },
            { 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, NO_LED, 40 },
            { 52, NO_LED, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, NO_LED, 41 },
            { 53, 54, 55, NO_LED, NO_LED, NO_LED, 56, NO_LED, NO_LED, NO_LED, 57, 58, 59, 60 }
        },
        {
            // 行 0
            {0,0},   {18,0},  {36,0},  {54,0},  {72,0},  {90,0},  {108,0}, {126,0}, {144,0}, {162,0}, {180,0}, {198,0}, {216,0}, {234,0},
            // 行 1
            {0,16},  {18,16}, {36,16}, {54,16}, {72,16}, {90,16}, {108,16}, {126,16}, {144,16}, {162,16}, {180,16}, {198,16}, {216,16}, {234,16},
            // 行 2
            {0,32},  {18,32}, {36,32}, {54,32}, {72,32}, {90,32}, {108,32}, {126,32}, {144,32}, {162,32}, {180,32}, {198,32},          {234,32},
            // 行 3
            {0,48},          {24,48}, {48,48}, {72,48}, {96,48}, {120,48}, {144,48}, {168,48}, {192,48}, {216,48}, {240,48},          {234,48},
            // 行 4
            {0,64},  {24,64}, {48,64},                            {120,64},                            {192,64}, {210,64}, {228,64}, {246,64}
        },
        // LED标志（4表示每个按键LED）
        {
                4,4,4,4,4,4,4,4,4,4,4,4,4,4,
                4,4,4,4,4,4,4,4,4,4,4,4,4,4,
                4,4,4,4,4,4,4,4,4,4,4,4,   4,
                4,  4,4,4,4,4,4,4,4,4,4,   4,
                4,4,4,          4,       4,4,4,4
        }
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        if (current_os == OS_MACOS) {
            rgb_matrix_set_color(28, 0x00, 0xFF, 0x00); // MacOS下CapsLock亮绿色
        } else {
            rgb_matrix_set_color(28, 0xFF, 0x00, 0x00); // Windows下CapsLock亮红色
        }
    }

    if (get_highest_layer(layer_state) == _FN1) {
        // Row 0
        rgb_matrix_set_color(0, 0xFF, 0xFF, 0xFF);  // KC_GRV
        for (int i = 1; i <= 12; i++) {             // F1-F12
            rgb_matrix_set_color(i, 0xFF, 0xFF, 0xFF);
        }
        rgb_matrix_set_color(13, 0xFF, 0xFF, 0xFF); // KC_DEL

        // Row 1
        rgb_matrix_set_color(25, 0xFF, 0xFF, 0xFF); // KC_UP
        rgb_matrix_set_color(19, 0xFF, 0xFF, 0xFF); // KC_INS
        rgb_matrix_set_color(17, 0xFF, 0xFF, 0xFF); // KC_PSCR
        rgb_matrix_set_color(16, 0xFF, 0xFF, 0xFF); // KC_SCRL
        rgb_matrix_set_color(15, 0xFF, 0xFF, 0xFF); // KC_PAUS

        // Row 2
        rgb_matrix_set_color(29, 0xFF, 0xFF, 0xFF); // KC_LEFT
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF); // KC_DOWN
        rgb_matrix_set_color(31, 0xFF, 0xFF, 0xFF); // KC_RGHT
        rgb_matrix_set_color(38, 0xFF, 0xFF, 0xFF); // KC_HOME
        rgb_matrix_set_color(39, 0xFF, 0xFF, 0xFF); // KC_PGUP

        // Row 3
        rgb_matrix_set_color(51, 0xFF, 0xFF, 0xFF); // RM_ON
        rgb_matrix_set_color(50, 0xFF, 0xFF, 0xFF); // RM_NEXT
        rgb_matrix_set_color(49, 0xFF, 0xFF, 0xFF); // RGB_HUI
        rgb_matrix_set_color(48, 0xFF, 0xFF, 0xFF); // RGB_HUD
        rgb_matrix_set_color(47, 0xFF, 0xFF, 0xFF); // RGB_SAI
        rgb_matrix_set_color(46, 0xFF, 0xFF, 0xFF); // RM_VALU
        rgb_matrix_set_color(45, 0xFF, 0xFF, 0xFF); // RM_VALD
        rgb_matrix_set_color(43, 0xFF, 0xFF, 0xFF); // KC_END
        rgb_matrix_set_color(42, 0xFF, 0xFF, 0xFF); // KC_PGDN

        // Row 4
        rgb_matrix_set_color(54, 0xFF, 0xFF, 0xFF); // GU_TOGG
    }

    return false;
}
