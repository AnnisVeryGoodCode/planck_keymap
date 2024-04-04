#include QMK_KEYBOARD_H

// #include "muse.h" // TODO: Remove? Music?
#include "keymap_extras/keymap_german.h"

enum a_board_layers {
  // Layer
  _BASE,
  _PNCT,
  _PNCT_MAC,
  _FUNC,
  _NUMS,
  _LEADER,
  _ADJUST,
  _GAMING,
  _GAMING_SHOOTER,
};

enum a_board_keycodes {
  // Layer
  LR_BASE = SAFE_RANGE,
  LR_GMNG,
  LR_SHTR,
  LR_ADJT,

  // OS selection. 
  OS_COS, // Chrome OS.
  OS_LNX, // Linux.
  OS_WIN, // Windows.
  OS_MAC, // MAC OS.

  // App Mode Selection.
  AP_RSLV,

  // Macros
  MC_EXIT,
  MC_FIND, // Find selection in page (Ctrl+C Ctrl+F Ctrl+V).
  MC_GGLE, // Google for current selection (Ctrl+C Ctrl+L Ctrl+V Enter).
  MC_LINK, // Link what is currently highlighted (Ctrl+C Ctrl+K Ctrl+V Enter).
  MC_DKLF, // Dock window left.
  MC_DKRG, // Dock window right.
  MC_DLFT, // Go to virtual desktop left.
  MC_DRGT, // Go to virtual desktop right.
  MC_MSCT, // Mission Control / Show all windows
  // MC_MVLF, // Move window to virtual desktop on the left.
  // MC_MVRG, // Move window to virtual desktop on the right.
  MC_BACK, // CTRL Z
  MC_FWD,  // CTRL Y

  MC_GRV,  // `
  MC_DACH,  // ^

  MC_PNCT,
  // MC_LCTL,  // WIN/MAC Control/Command.
};

// TODO: Create custom unicode map; use XP(0x0142, 0x0141) for upper/lower case.
#define UC_LSTR UC(0x0142) // Polish l with a stroke.
#define UC_BKTK UC(0x0060) // Backtick (non-dead key).
#define UC_SHRG UC(0x30C4) // Shruggie face

// Remaps (similar to macros)
// #define MC_EXIT LALT(KC_F4)      // Close window, ALT + F4.
// #define MC_NTRM LCTL(LSFT(KC_N)) // Open new Terminal.

static enum operating_systems {
  LINUX,
  CHROME_OS,
  WINDOWS,
  MAC_OS,
} os;

static enum application_mode {
  DEFAULT,
  RESOLVE,
  NUMBER_OF_OPTIONS,
} app_mode;

// Layers
#define LR_PNCT  MO(_PNCT)
#define LR_PNCT_MAC  MO(_PNCT_MAC)
#define LR_FUNC  MO(_FUNC)
#define LR_FNCR  MO(_FUNC_CR)
#define LR_NUMS  LT(_NUMS, DE_F)
#define LR_LEAD OSL(_LEADER)

// Mac DE
// #define DM_LBRC A(DE_5)    // [	
// #define DM_RBRC A(DE_6)    // ]	
// #define DM_LCBR A(DE_8)    // {	
// #define DM_RCBR A(DE_9)    // }	
// #define DM_PIPE A(DE_7)    // |	
// #define DM_TILD A(DE_N)    // ~ (dead)
// #define DM_AT   A(DE_L)    // @
// #define DM_BSLS S(A(DE_7)) // (backslash)

// We send LCMD when we should normally send A(key) (= OPT, ALT): This is because on Karabiner, I've
// bound the LCMD key to OPT. If we send A(key), the symbols do not work since Karabiner registers
// CTRL(key), as I've bound OPT/ALT to CTRL.
#define DM_LBRC LCMD(DE_5)    // [
#define DM_RBRC LCMD(DE_6)    // ]	
#define DM_LCBR LCMD(DE_8)    // {	
#define DM_RCBR LCMD(DE_9)    // }	
#define DM_PIPE LCMD(DE_7)    // |	
#define DM_TILD LCMD(DE_N)    // ~ (dead)
#define DM_AT   LCMD(DE_L)    // @
#define DM_BSLS S(LCMD(DE_7)) // (backslash)
// Weird ones - the two buttons on the german layout are switched out?? I.e.:
// <  <->  ^
// >  <->  °
#define DM_DACH KC_NUBS       // ^ (not dead on Mac)
#define DM_DEG  S(KC_NUBS)    // °
#define DM_LABK KC_GRV        // <
#define DM_RABK S(KC_GRV)     // >
 


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//
// Base Layer
//

[_BASE] = LAYOUT_planck_2x2u(
  KC_ESC , DE_Q   , DE_W   , DE_E   , DE_R   , DE_T   , DE_Z   , DE_U   , DE_I   , DE_O   , DE_P   , KC_BSPC,
  KC_TAB , DE_A   , DE_S   , DE_D   , LR_NUMS, DE_G   , DE_H   , DE_J   , DE_K   , DE_L   , LR_LEAD, KC_ENT ,
  KC_LSFT, DE_Y   , DE_X   , DE_C   , DE_V   , DE_B   , DE_N   , DE_M   , DE_COMM, DE_DOT , DE_SS  , KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, LR_FUNC,     MC_PNCT     ,     KC_SPC      , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT
),

//
// Symbols Layer
//

// TODO: Utilize page up/down, R_Shift keys better.
// TODO: Bottom left key.
[_PNCT] = LAYOUT_planck_2x2u(
  KC_ENT , DE_EXLM, DE_AT,   DE_HASH, DE_DLR,  DE_EURO, MC_GRV , DE_LCBR, DE_RCBR, DE_UNDS, DE_PLUS, KC_DEL ,
  _______, DE_TILD, DE_BSLS, DE_DQUO, DE_QUOT, DE_DEG , DE_ASTR, DE_LPRN, DE_RPRN, DE_MINS, DE_EQL , _______,
  _______, _______, DE_AMPR, DE_LBRC, DE_RBRC, MC_DACH, DE_PIPE, DE_LABK, DE_RABK, DE_PERC, DE_SLSH, _______,
  _______, _______, _______, _______,     _______     ,     KC_DEL      , KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

[_PNCT_MAC] = LAYOUT_planck_2x2u(
  KC_ENT , DE_EXLM, DM_AT,   DE_HASH, DE_DLR,  DE_EURO, MC_GRV , DM_LCBR, DM_RCBR, DE_UNDS, DE_PLUS, KC_DEL ,
  _______, DM_TILD, DM_BSLS, DE_DQUO, DE_QUOT, DM_DEG , DE_ASTR, DE_LPRN, DE_RPRN, DE_MINS, DE_EQL , _______,
  _______, _______, DE_AMPR, DM_LBRC, DM_RBRC, DM_DACH, DM_PIPE, DM_LABK, DM_RABK, DE_PERC, DE_SLSH, _______,
  _______, _______, _______, _______,     _______     ,     KC_DEL      , KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

//
// Macro Layer
//

// TODO: Use right-hand side for dynamic macros?
[_FUNC] = LAYOUT_planck_2x2u(
  MC_EXIT, MC_FIND, MC_GGLE, MC_MSCT, MC_LINK, _______, _______, _______, _______, _______, _______, _______,
  KC_DEL , MC_DKLF, MC_DKRG, MC_DLFT, MC_DRGT, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______,
  KC_BSPC, KC_PGDN, KC_PGUP, MC_BACK, MC_FWD , _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,     _______     ,     KC_MPLY     , KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
),

//
// Numbers/F-key Layer
//

[_NUMS] = LAYOUT_planck_2x2u(
  _______, KC_F1  , KC_F2  , KC_F3  , _______, _______, _______, KC_7   , KC_8   , KC_9   , _______, _______,
  _______, KC_F4  , KC_F5  , KC_F6  , _______, _______, _______, KC_4   , KC_5   , KC_6   , _______, _______,
  _______, KC_F7  , KC_F8  , KC_F9  , _______, _______, _______, KC_1   , KC_2   , KC_3   , _______, _______,
  _______, KC_F10 , KC_F11 , KC_F12 ,     _______     ,     KC_0        , KC_COMM, KC_DOT , _______, _______
),

//
// Specials
//

[_LEADER] = LAYOUT_planck_2x2u(
  _______, _______, _______, _______, _______, _______, _______, DE_UDIA, _______, DE_ODIA, _______, _______,
  _______, DE_ADIA, DE_SS  , _______, _______, _______, _______, _______, _______, UC_LSTR, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______,     _______     ,     _______     , _______, _______, _______, _______
),

[_GAMING] = LAYOUT_planck_2x2u(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, DE_F   , _______, _______, _______, _______, _______, LR_NUMS, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LR_BASE,
  _______, _______, _______, KC_LALT,     KC_SPC      ,     _______     , _______, _______, _______, _______
),

[_GAMING_SHOOTER] = LAYOUT_planck_2x2u(
  _______, _______, DE_Q   , DE_W   , DE_E   , DE_R   , DE_T   , KC_7   , KC_8   , KC_9   , _______, _______,
  _______, _______, DE_A   , DE_S   , DE_D   , DE_F   , DE_G   , KC_4   , KC_5   , KC_6   , _______, _______,
  KC_LCTL, KC_LSFT, DE_Z   , DE_X   , DE_C   , DE_V   , DE_B   , KC_1   , KC_2   , KC_3   , _______, LR_BASE,
  _______, _______, _______, KC_LALT,     KC_SPC      ,     _______     , _______, _______, _______, _______
),

[_ADJUST] = LAYOUT_planck_2x2u(
  _______, _______, OS_WIN , _______, AP_RSLV, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, LR_SHTR, _______, _______, LR_GMNG, _______, _______, _______, OS_LNX , _______, _______,
  _______, _______, _______, OS_COS , _______, LR_BASE, _______, OS_MAC , _______, _______, _______, _______,
  _______, _______, _______, _______,     _______     ,     _______     , _______, _______, _______, _______
),

};

layer_state_t layer_state_set_user(layer_state_t state) {
  // Note: For layers that don't expose the FUNC and PNCT layer keys, we need
  // to provide a layer-specific way to switch back to the BASE layer.

  // update_tri_layer_state(state, x, y, z) checks if layers x and y are currently on. If so, it
  // turns on layer z.

  // TODO: Doesn't work :(
  // state = update_tri_layer_state(state, _FUNC, _PNCT, _ADJUST);
  // state = update_tri_layer_state(state, _FUNC, _PNCT_MAC, _ADJUST);
  // return state;

  return update_tri_layer_state(state, _FUNC, _PNCT, _ADJUST);
}

// Executes before usual QMK key event handling. On returning false, QMK will
// skip the normal key event handling.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Macros 

    case MC_EXIT:
      if (record->event.pressed) {
        switch (os) {
          // Karabiner maps Ctrl to Cmd, so use Ctrl here to get Cmd+Q shortcut.
          case MAC_OS:    SEND_STRING(SS_LCTL("q")); break;
          case LINUX:     
          case WINDOWS:   
          case CHROME_OS: SEND_STRING(SS_LALT(SS_TAP(X_F4))); break;
          default: return false;
        }
      }
      return false;

    // Go to desktop left/right.
    case MC_DLFT:
      if (record->event.pressed) {
        switch (os) {
          case LINUX:     SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_LEFT)))); break;
          case MAC_OS:    SEND_STRING(SS_LALT(SS_TAP(X_LEFT))); break;
          case WINDOWS:   SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_LEFT)))); break;
          case CHROME_OS: SEND_STRING(SS_LCTL(SS_LSFT(" ")) SS_DELAY(5) SS_LGUI("[") SS_DELAY(5) SS_LCTL(SS_LSFT(" "))); break;
          default: return false;
        }
      }
      return false;
    case MC_DRGT:
      if (record->event.pressed) {
        switch (os) {
          case LINUX:     SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_RGHT)))); break;
          case MAC_OS:    SEND_STRING(SS_LALT(SS_TAP(X_RGHT))); break;
          case WINDOWS:   SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_RGHT)))); break;
          case CHROME_OS: SEND_STRING(SS_LCTL(SS_LSFT(" ")) SS_DELAY(5) SS_LGUI("]") SS_DELAY(5) SS_LCTL(SS_LSFT(" "))); break;
          default: return false;
        }
      }
      return false;

    // For some reason, I need to switch out y and z???
    case MC_BACK:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("y"));
      }
      return false;
    case MC_FWD:
      if (record->event.pressed) {
        if (app_mode == RESOLVE || os == MAC_OS) {
          SEND_STRING(SS_LCTL(SS_LSFT("y")));
        } else {
          SEND_STRING(SS_LCTL("z"));
        }
      }
      return false;

    // Mission Control
    case MC_MSCT:
      if (record->event.pressed) {
        switch (os) {
          case LINUX:
          case MAC_OS:    SEND_STRING(SS_LCTL(SS_TAP(X_UP))); break;
          case CHROME_OS: // TODO
          case WINDOWS:   SEND_STRING(SS_LGUI(SS_TAP(X_TAB))); break;
          default: return false;
        }
      }
      return false;

    // Dock windows left/right.
    case MC_DKLF:
      if (record->event.pressed) {
        switch (os) {
          case LINUX:
          case MAC_OS:
          case WINDOWS:   SEND_STRING(SS_LGUI(SS_TAP(X_LEFT))); break;
          case CHROME_OS: SEND_STRING(SS_LCTL(SS_LSFT(" ")) SS_DELAY(5) SS_LALT("[") SS_DELAY(5) SS_LCTL(SS_LSFT(" "))); break;
          default: return false;
        }
      }
      return false;
    case MC_DKRG:
      if (record->event.pressed) {
        switch (os) {
          case LINUX:
          case MAC_OS:
          case WINDOWS:   SEND_STRING(SS_LGUI(SS_TAP(X_RGHT))); break;
          case CHROME_OS: SEND_STRING(SS_LCTL(SS_LSFT(" ")) SS_DELAY(5) SS_LALT("]") SS_DELAY(5) SS_LCTL(SS_LSFT(" "))); break;
          default: return false;
        }
      }
      return false;

    // TODO: Cont here: Use MO(layer) instead?
    case MC_PNCT:
      if (record->event.pressed) {
        switch (os) {
          case LINUX: case WINDOWS: case CHROME_OS: layer_on(_PNCT); break;
          case MAC_OS: layer_on(_PNCT_MAC); break;
          default:
              return false;
        }
      } else {
        switch (os) {
          case LINUX: case WINDOWS: case CHROME_OS: layer_off(_PNCT_MAC); layer_off(_PNCT); break;
          case MAC_OS: layer_off(_PNCT_MAC); layer_off(_PNCT); break;
          default:
              return false;
        }
      }
      return false;

    // + in US layout is where ` is on German keyboard (upper right corner, left to backspace).
    // ` in US layout is where ^ is on German keyboard (upper left corner, right to number row). 
    // Append <space> to avoid dead key behavior.
    case MC_GRV:
      if (record->event.pressed) {
        SEND_STRING("+ ");
      }
      return false;
    case MC_DACH:
      if (record->event.pressed) {
        SEND_STRING("` ");
      }
      return false;

    // Custom actions
    // TODO: Revisit whether delays help for MC_FIND.
    case MC_GGLE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c") SS_DELAY(25) SS_LCTL("t") SS_DELAY(25) SS_LCTL("v") SS_TAP(X_ENTER));
      }
      return false;
    case MC_FIND:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c") SS_DELAY(25) SS_LCTL("f") SS_DELAY(25) SS_LCTL("v"));
      }
      return false;
    case MC_LINK:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTL("c") SS_DELAY(25) SS_LCTL("k") SS_DELAY(25) SS_LCTL("v"));
      }
      return false;

    // Layers
    case LR_BASE:
      if (record->event.pressed) {
        layer_off(_FUNC);
        layer_off(_PNCT);
        layer_off(_ADJUST);
        set_single_persistent_default_layer(_BASE);
      }
      return false;
    case LR_GMNG:
      if (record->event.pressed) {
        layer_off(_FUNC);
        layer_off(_PNCT);
        layer_off(_ADJUST);
        set_single_persistent_default_layer(_GAMING);
      }
      return false;
    case LR_SHTR:
      if (record->event.pressed) {
        layer_off(_FUNC);
        layer_off(_PNCT);
        layer_off(_ADJUST);
        set_single_persistent_default_layer(_GAMING_SHOOTER);
      }
      return false;

    // OS selection
    case OS_LNX:
      if (record->event.pressed) {
        os = LINUX;
        set_unicode_input_mode(UNICODE_MODE_LINUX);
      }
      return false;
    case OS_WIN:
      if (record->event.pressed) {
        os = WINDOWS;
        // Note: Requires WinCompose.
        set_unicode_input_mode(UNICODE_MODE_WINDOWS);
      }
      return false;
    case OS_COS:
      if (record->event.pressed) {
        os = CHROME_OS;
        set_unicode_input_mode(UNICODE_MODE_LINUX);
      }
      return false;
    case OS_MAC:
      if (record->event.pressed) {
        os = MAC_OS;
        set_unicode_input_mode(UNICODE_MODE_MACOS);
      }
      return false;

    // App selection.
    case AP_RSLV:
      // Cycle through the options. For many app modes in the future, might want to use individual buttons.
      if (record->event.pressed) {
        app_mode = (app_mode + 1) % NUMBER_OF_OPTIONS;
      }
      return false;
  }

  return true;
}

// Templates

/*
[TODO] = LAYOUT_planck_2x2u(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),
*/

/*
    case TODO:
      if (record->event.pressed) {
        switch (os) {
          case LINUX:     TODO
          case WINDOWS:   TODO
          case CHROME_OS: TODO
          default: return false;
        }
      }
      return false;

    // Move window to desktop on the left/right (Chrome OS only).
    case MC_MVLF:
      if (record->event.pressed) {
        if (os == CHROME_OS) {
          SEND_STRING(SS_LCTL(SS_LSFT(" ")) SS_DELAY(5) SS_LSFT(SS_LGUI("[")) SS_DELAY(5) SS_LCTL(SS_LSFT(" ")));
        }
      }
      return false;
    case MC_MVRG:
      if (record->event.pressed) {
        if (os == CHROME_OS) {
          SEND_STRING(SS_LCTL(SS_LSFT(" ")) SS_DELAY(5) SS_LSFT(SS_LGUI("]")) SS_DELAY(5) SS_LCTL(SS_LSFT(" ")));
        }
      }
      return false;

*/

// // ! #$€`|≠_+
// !@#$€`{}_+
//  ^    ^^

// ±¿"'°*()-=
// ~\"'°*()-=
// ^^      

// °&{}^≤<>%/
// °&[]^|<>%/
//   ^^ ^
