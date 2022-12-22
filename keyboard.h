#include "pico/stdlib.h"

// TI-99 Keyboard Connector
// -------------------------------
//  - R: matrix row
//  - C: column, driven by low pulses by the TI when it reads the keyboard state
//
// 14 | 13 | 12 | 11 | 10 | 09 | 08 | 07 | 06 | 05 | 04 | 03 | 02 | 01 | 00
// ------------------------------------------------------------------------
//  R |  R |  R |  R |  R |  C |  R |  C |  C |  R |  R |  C |  C |  C |  C

// Modifier keys to press for certain key codes
#define MODIFIER_CTRL  1
#define MODIFIER_FCTN  2
#define MODIFIER_SHIFT 3
#define KEY_MAP_MODIFIER_OFFSET 6

// A list of column lookup numbers as stored in the key map to the
// column pin on the keyboard connector
#define COL_0  0
#define COL_1  1
#define COL_2  2
#define COL_3  3
#define COL_6  4
#define COL_7  5
#define COL_9  6
#define KEY_MAP_COLUMN_OFFSET 3
#define COLUMN_LOOKUP { \
  0, /* COL_0   */ \
  1, /* COL_1   */ \
  2, /* COL_2   */ \
  3, /* COL_3   */ \
  6, /* COL_6   */ \
  7, /* COL_7   */ \
  9, /* COL_9 */
}

// A list of row lookup numbers as stored in the key map to the
// ropw pin on the keyboard connector
#define ROW_4  0
#define ROW_5  1
#define ROW_8  2
#define ROW_10 3
#define ROW_11 4
#define ROW_12 5
#define ROW_13 6
#define ROW_14 7
#define ROW_LOOKUP { \
  4,  /* ROW_4    */ \
  5,  /* ROW_5    */ \
  8,  /* ROW_8    */ \
  10, /* ROW_10   */ \
  11, /* ROW_11   */ \
  12, /* ROW_12   */ \
  13, /* ROW_13   */ \
  14, /* ROW_14   */ \
}

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
#define KEY_NA 0
#define KEY_MAP[] = {
  KEY_NA,                                                                                   /* 0x00               */ \
  KEY_NA,                                                                                   /* 0x01               */ \
  KEY_NA,                                                                                   /* 0x02               */ \
  KEY_NA,                                                                                   /* 0x03               */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                /* 0x04 A             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 /* 0x05 B             */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 /* 0x06 C             */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                /* 0x07 D             */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 /* 0x08 E             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                /* 0x09 F             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                /* 0x0A G             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                /* 0x0B H             */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                /* 0x0C I             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                /* 0x0D J             */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                /* 0x0E K             */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                /* 0x0F L             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                /* 0x10 M             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                /* 0x11 N             */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                /* 0x12 O             */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                /* 0x13 P             */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 /* 0x14 Q             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 /* 0x15 R             */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_12,                                                /* 0x16 S             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 /* 0x17 T             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                /* 0x18 U             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 /* 0x19 V             */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_5,                                                 /* 0x1A W             */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 /* 0x1B X             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                /* 0x1C Y             */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_4,                                                 /* 0x1D Z             */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 /* 0x1E 1             */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 /* 0x1F 2             */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 /* 0x20 3             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 /* 0x21 4             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 /* 0x22 5             */ \
  (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                /* 0x23 6             */ \
  (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                /* 0x24 7             */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                /* 0x25 8             */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                /* 0x26 9             */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                /* 0x27 0             */ \
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_14,                                                /* 0x28 Enter         */ \
  KEY_NA,                                                                                   /* 0x29 Escape        */ \
  KEY_NA,                                                                                   /* 0x2A Backspace     */ \
  KEY_NA,                                                                                   /* 0x2B Tab           */ \
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_11,                                                /* 0x2C Space         */ \
  (MODIFIER_SHIFT << KEY_MAP_MODIFIER_OFFSET) | (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_10,  /* 0x2D Minus         */ \
  (COL_3 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                /* 0x2E Equal         */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_0 << KEY_MAP_COLUMN_OFFSET) | ROW_5,    /* 0x2F Left Bracket  */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_6 << KEY_MAP_COLUMN_OFFSET) | ROW_5,    /* 0x30 Right Bracket */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_4,    /* 0x31 Backslash     */ \
  KEY_NA,                                                                                   /* 0x32 "EUROPE 1"    */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_13,                                                /* 0x33 Semi-colon    */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_14,   /* 0x34 Apostrophe    */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_4,    /* 0x35 Back tick     */ \
  (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                /* 0x36 Comma         */ \
  (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                /* 0x37 Period        */ \
  (COL_7 << KEY_MAP_COLUMN_OFFSET) | ROW_10,                                                /* 0x38 Slash         */ \
  (COL_9 << KEY_MAP_COLUMN_OFFSET) | ROW_8,                                                 /* 0x39 Caps lock     */ \
  KEY_NA,                                                                                   /* 0x3A F1            */ \
  KEY_NA,                                                                                   /* 0x3B F2            */ \
  KEY_NA,                                                                                   /* 0x3C F3            */ \
  KEY_NA,                                                                                   /* 0x3D F4            */ \
  KEY_NA,                                                                                   /* 0x3E F5            */ \
  KEY_NA,                                                                                   /* 0x3F F6            */ \
  KEY_NA,                                                                                   /* 0x40 F7            */ \
  KEY_NA,                                                                                   /* 0x41 F8            */ \
  KEY_NA,                                                                                   /* 0x42 F9            */ \
  KEY_NA,                                                                                   /* 0x43 F10           */ \
  KEY_NA,                                                                                   /* 0x44 F11           */ \
  KEY_NA,                                                                                   /* 0x45 F12           */ \
  KEY_NA,                                                                                   /* 0x46 Print screen  */ \
  KEY_NA,                                                                                   /* 0x47 Scroll lock   */ \
  KEY_NA,                                                                                   /* 0x48 Pause         */ \
  KEY_NA,                                                                                   /* 0x49 Insert        */ \
  KEY_NA,                                                                                   /* 0x4A Home          */ \
  KEY_NA,                                                                                   /* 0x4B Page up       */ \
  KEY_NA,                                                                                   /* 0x4C Delete        */ \
  KEY_NA,                                                                                   /* 0x4D End           */ \
  KEY_NA,                                                                                   /* 0x4E Page down     */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_12,   /* 0x4F Right arrow   */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_12,   /* 0x50 Left arrow    */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_2 << KEY_MAP_COLUMN_OFFSET) | ROW_4,    /* 0x51 Down arrow    */ \
  (MODIFIER_FCTN << KEY_MAP_MODIFIER_OFFSET) | (COL_1 << KEY_MAP_COLUMN_OFFSET) | ROW_5,    /* 0x52 Up arrow      */ \
};
