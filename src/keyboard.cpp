#include "pico/stdlib.h"

#include "keyboard.h"

uint8_t pressedColumnRows[COL_COUNT];

/**
 * Initializes keyboard mapping memory and pins
 */
void initKeyboard() {
  // zero out the button press cache
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    pressedColumnRows[i] = 0;
  }

  // set all the pins
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    gpio_init(COLUMN_LOOKUP[i]);
    gpio_set_dir(COLUMN_LOOKUP[i], false);
  }

  for (uint8_t i = 0; i < ROW_COUNT; i++) {
    gpio_init(ROW_LOOKUP[i]);
    gpio_set_dir(ROW_LOOKUP[i], true);
  }
}

/**
 * Sets a key's pressed state from a key mapped code
 *
 * @param keymapCode The keymap code to set the state for
 * @param pressed The key's pressed state to set
 */
void setKey(uint8_t keymapCode, bool pressed) {
  uint8_t columnLookup = (keymapCode & KEY_MAP_COLUMN_MASK) >> KEY_MAP_COLUMN_OFFSET;
  uint8_t rowLookup = keymapCode & KEY_MAP_ROW_MASK;
  uint8_t modifierKey = (keymapCode & KEY_MAP_MODIFIER_MASK) >> KEY_MAP_MODIFIER_OFFSET;
  uint8_t rowPin = ROW_LOOKUP[rowLookup];

  if (modifierKey != MODIFIER_NONE) {
    setKey(MODIFIER_LOOKUP[modifierKey], pressed);
  }

  pressedColumnRows[columnLookup] = rowPin;
}

/**
 * Updates the pressed rows based on the state of the machine
 */
void processKeys() {
  bool colStatus;
  uint8_t rowPin;
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    colStatus = gpio_get(COLUMN_LOOKUP[i]);

    for (uint8_t j = 0; j < ROW_COUNT; j++) {
      // columns reads are active low, so if the line's gone low, process the pressed key
      gpio_put(pressedColumnRows[i], colStatus || rowPin != ROW_LOOKUP[i]);
    }
  }
}
