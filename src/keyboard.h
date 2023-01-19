#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

// TI-99 Keyboard Connector
// -------------------------------
//  - R: matrix row
//  - C: column, driven by low pulses by the TI when it reads the keyboard state
//
// 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00
// ------------------------------------------------------------------------
//  R |  R |  R |  R |  R |  C |  R |  C |  C |  R |  R |  C |  C |  C |  C

#define KEY_NONE  0

// A list of column lookup numbers as stored in the key map to the
// column pin on the keyboard connector
#define COL_0       0
#define COL_0_GPIO 28
#define COL_1       1
#define COL_1_GPIO 27
#define COL_2       2
#define COL_2_GPIO 26
#define COL_3      3
#define COL_3_GPIO 22
#define COL_6      4
#define COL_6_GPIO 28
#define COL_7      5
#define COL_7_GPIO 20
#define COL_9      6
#define COL_9_GPIO 19
#define COL_COUNT  7
#define COL_NOT_FOUND 255
#define KEY_MAP_COLUMN_OFFSET 3
const uint8_t COLUMN_LOOKUP[COL_COUNT] = {
  COL_0_GPIO,
  COL_1_GPIO,
  COL_2_GPIO,
  COL_3_GPIO,
  COL_6_GPIO,
  COL_7_GPIO,
  COL_9_GPIO,
};

// A list of row lookup numbers as stored in the key map to the
// ropw pin on the keyboard connector
#define ROW_4      0
#define ROW_5      1
#define ROW_8      2
#define ROW_10     3
#define ROW_11     4
#define ROW_12     5
#define ROW_13     6
#define ROW_14     7
#define ROW_COUNT  8
const uint8_t ROW_LOOKUP[ROW_COUNT] = {
  2, // ROW_4
  3, // ROW_5
  4, // ROW_8
  5, // ROW_10
  6, // ROW_11
  7, // ROW_12
  8, // ROW_13
  9, // ROW_14
};

// Modifier keys to press for certain key codes
#define MODIFIER_NONE  0
#define MODIFIER_CTRL  1
#define MODIFIER_FCTN  2
#define MODIFIER_SHIFT 3
#define KEY_MAP_MODIFIER_OFFSET 6
const uint8_t MODIFIER_LOOKUP[] = {
  KEY_NONE,
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_5,  // CTRL
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_8,  // FCTN
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_12, // SHIFT
};

// Map of HID key codes to the key presses to
// send back to the TI, including any modifiers
// required (shift, etc.)
// --
// https://github.com/adafruit/Adafruit_TinyUSB_ArduinoCore/blob/master/tinyusb/src/class/hid/hid.h#L303
//
// Key format: 0xAABBBCCC
//  - AA:  modifer key
//  - BBB: column lookup number
//  - CCC: row lookup number
#define KEY_SHIFT (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_12
#define KEY_FCTN  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_8
#define KEY_CTRL  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_5
#define KEY_MAP_MODIFIER_MASK   0b11000000
#define KEY_MAP_COLUMN_MASK     0b00111000
#define KEY_MAP_ROW_MASK        0b00000111
const uint8_t KEY_MAP[] = {
  KEY_NONE,                                                                                 // 0x00
  KEY_NONE,                                                                                 // 0x01
  KEY_NONE,                                                                                 // 0x02
  KEY_NONE,                                                                                 // 0x03
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                // 0x04 A
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 // 0x05 B
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 // 0x06 C
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                // 0x07 D
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 // 0x08 E
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                // 0x09 F
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                // 0x0A G
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                // 0x0B H
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                // 0x0C I
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                // 0x0D J
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                // 0x0E K
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                // 0x0F L
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                // 0x10 M
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                // 0x11 N
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                // 0x12 O
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                // 0x13 P
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 // 0x14 Q
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 // 0x15 R
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                // 0x16 S
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 // 0x17 T
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                // 0x18 U
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 // 0x19 V
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 // 0x1A W
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 // 0x1B X
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                // 0x1C Y
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 // 0x1D Z
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 // 0x1E 1
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 // 0x1F 2
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 // 0x20 3
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 // 0x21 4
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 // 0x22 5
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                // 0x23 6
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                // 0x24 7
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                // 0x25 8
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                // 0x26 9
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                // 0x27 0
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                // 0x28 Enter
  KEY_NONE,                                                                                 // 0x29 Escape
  KEY_NONE,                                                                                 // 0x2A Backspace
  KEY_NONE,                                                                                 // 0x2B Tab
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                // 0x2C Space
  (MODIFIER_SHIFT << KEY_MAP_MODIFIER_OFFSET) | (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_10,  // 0x2D Minus
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                // 0x2E Equal
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_5,    // 0x2F Left Bracket
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_5,    // 0x30 Right Bracket
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_4,    // 0x31 Backslash
  KEY_NONE,                                                                                 // 0x32 "EUROPE 1"
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                // 0x33 Semi-colon
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_14,   // 0x34 Apostrophe
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_4,    // 0x35 Back tick
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                // 0x36 Comma
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                // 0x37 Period
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                // 0x38 Slash
  (COL_9 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 // 0x39 Caps lock
  KEY_NONE,                                                                                 // 0x3A F1
  KEY_NONE,                                                                                 // 0x3B F2
  KEY_NONE,                                                                                 // 0x3C F3
  KEY_NONE,                                                                                 // 0x3D F4
  KEY_NONE,                                                                                 // 0x3E F5
  KEY_NONE,                                                                                 // 0x3F F6
  KEY_NONE,                                                                                 // 0x40 F7
  KEY_NONE,                                                                                 // 0x41 F8
  KEY_NONE,                                                                                 // 0x42 F9
  KEY_NONE,                                                                                 // 0x43 F10
  KEY_NONE,                                                                                 // 0x44 F11
  KEY_NONE,                                                                                 // 0x45 F12
  KEY_NONE,                                                                                 // 0x46 Print screen
  KEY_NONE,                                                                                 // 0x47 Scroll lock
  KEY_NONE,                                                                                 // 0x48 Pause
  KEY_NONE,                                                                                 // 0x49 Insert
  KEY_NONE,                                                                                 // 0x4A Home
  KEY_NONE,                                                                                 // 0x4B Page up
  KEY_NONE,                                                                                 // 0x4C Delete
  KEY_NONE,                                                                                 // 0x4D End
  KEY_NONE,                                                                                 // 0x4E Page down
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_12,   // 0x4F Right arrow
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_12,   // 0x50 Left arrow
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_4,    // 0x51 Down arrow
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_5,    // 0x52 Up arrow
};

void initKeyboard();
void setKey(uint8_t keymapCode, bool pressed);
void processKeys();

#endif
