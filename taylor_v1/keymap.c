#include QMK_KEYBOARD_H

enum {
	Vim_O = SAFE_RANGE,
	Vim_C,
	Vim_V,
	Vim_D
};

bool is_visual_mode = false;

void toggle_visual_mode(void) {
	if (is_visual_mode){
		unregister_code(KC_LSFT);
		is_visual_mode = false;
	} else {
		register_code(KC_LSFT);
		is_visual_mode = true;
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case Vim_O:
			if (record->event.pressed) {
				SEND_STRING(SS_TAP(X_END)"\n");
			}
			break;
		case Vim_C:
			if (record->event.pressed) {
				if (is_visual_mode) {
					toggle_visual_mode();
				}
				SEND_STRING(SS_LCTL("x"));
			}
			break;
		case Vim_V:
			if (record->event.pressed) {
				toggle_visual_mode();
			}
			break;
		case KC_UP:
			if (record->event.pressed) {
				if(is_visual_mode) {
					tap_code(KC_HOME);
				}
			}
			break;
		case KC_DOWN:
			if (record->event.pressed) {
				if(is_visual_mode) {
					tap_code(KC_END);
				}
			}
			break;
		case Vim_D:
			if (record->event.pressed) {
				if (is_visual_mode) {
					toggle_visual_mode();
				}
				SEND_STRING(SS_LCTL("x"));
			}
			break;
	}
	return true;
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case Vim_O:
		case Vim_C:
			if(!record->event.pressed) {
				layer_off(5);
			}
			break;
	}
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ortho_4x12(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, LSFT_T(KC_QUOT), KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_DEL, OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, MO(3), KC_LCTL, KC_LGUI, KC_LALT, TT(1), KC_BSPC, KC_SPC, MO(2), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
	[1] = LAYOUT_ortho_4x12(KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_INS, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, MO(4), KC_HOME, KC_WH_D, KC_WH_U, KC_END),
	[2] = LAYOUT_ortho_4x12(KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_UNDS, KC_PLUS, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_PIPE, TO(5), KC_LT, KC_LPRN, KC_LBRC, KC_LCBR, KC_MINS, KC_EQL, KC_RCBR, KC_RBRC, KC_RPRN, KC_GT, KC_BSLS, KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, OSM(MOD_LCTL|MOD_LALT), KC_DEL, KC_INS, KC_NO, MO(4), KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO),
	[3] = LAYOUT_ortho_4x12(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_NO),
	[4] = LAYOUT_ortho_4x12(RESET, DEBUG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_WH_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, TO(0)),
	[5] = LAYOUT_ortho_4x12(KC_TRNS, KC_NO, LCTL(KC_RGHT), KC_NO, KC_NO, KC_NO, LCTL(KC_C), LCTL(KC_Z), TG(5), Vim_O, LCTL(KC_V), KC_NO, KC_TRNS, KC_NO, KC_NO, Vim_D, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_DEL, Vim_C, Vim_V, LCTL(KC_LEFT), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)
};

//void dance_fs (qk_tap_dance_state_t *state, void *user_data) {
//  register_code (KC_LCTL);
//  if (state->count == 1) {
//    tap_code (KC_F);
//  } else {
//    tap_code (KC_P);
//  }
//  unregister_code (KC_LCTL);
//}

//void dance_d (qk_tap_dance_state_t *state, void *user_data) {
//	if (state->count == 1) {
//		register_code(KC_LCTL);
//		tap_code(KC_X);
//		unregister_code(KC_LCTL);
//	}
//	if (state->count == 2) {
//		tap_code(KC_HOME);
//		register_code(KC_LSFT);
//		tap_code(KC_END);
//		unregister_code(KC_LSFT);
//		register_code(KC_LCTL);
//		tap_code(KC_X);
//		unregister_code(KC_LCTL);
//		tap_code(KC_BSPC);
//	}
//}

//void dance_c (qk_tap_dance_state_t *state, void *user_data) {
//	if (state->count == 1) {
//		register_code(KC_LCTL);
//		tap_code(KC_X);
//		unregister_code(KC_LCTL);
//	}
//	if (state->count == 2) {
//		tap_code(KC_HOME);
//		register_code(KC_LSFT);
//		tap_code(KC_END);
//		unregister_code(KC_LSFT);
//		register_code(KC_LCTL);
//		tap_code(KC_X);
//		unregister_code(KC_LCTL);
//	}
//}

//qk_tap_dance_action_t tap_dance_actions[] = {
//	[TD_TAB_GRV] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_GRV),
//	[TD_CTLF_CTLP] = ACTION_TAP_DANCE_FN(dance_fs),
//	[TD_D] = ACTION_TAP_DANCE_FN(dance_d),
//	[TD_C] = ACTION_TAP_DANCE_FN(dance_c)
//};
