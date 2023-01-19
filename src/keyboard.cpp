#include "pico/stdlib.h"

#include "keyboard.h"

uint8_t pressedColumnRows[COL_COUNT];

/**
 * Looks up the column index from a GPIO pin number
 */
uint8_t lookupColumnIndexFromGpio(uint gpio) {
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    if (COLUMN_LOOKUP[i] == gpio) {
      return i;
    }
  }

  return COL_NOT_FOUND;
}

/**
 * Enables the correct row outputs for whichever column scan triggered an IRQ
 */
void handleColumnIrq(uint gpio, uint32_t events) {
  uint8_t columnIndex = lookupColumnIndexFromGpio(gpio);

  if (columnIndex == COL_NOT_FOUND) {
    return;
  }

  gpio_put(PICO_DEFAULT_LED_PIN, true);

  uint8_t rowPin = pressedColumnRows[columnIndex];
  for (uint8_t j = 0; j < ROW_COUNT; j++) {
    gpio_put(rowPin, rowPin != ROW_LOOKUP[j]);
  }
}

/**
 * Initializes keyboard mapping memory and pins
 */
void initKeyboard() {
  // zero out the button press cache
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    pressedColumnRows[i] = 0;
  }

  // set up the IRQ handler for the keyboard columns
  gpio_set_irq_callback(&handleColumnIrq);
  for (uint8_t i = 0; i < COL_COUNT; i++) {
    gpio_set_irq_enabled(COLUMN_LOOKUP[i], GPIO_IRQ_EDGE_FALL, true);
  }
  irq_set_enabled(IO_IRQ_BANK0, true);

  for (uint8_t i = 0; i < ROW_COUNT; i++) {
    gpio_init(ROW_LOOKUP[i]);
    gpio_set_dir(ROW_LOOKUP[i], GPIO_OUT);
    gpio_put(ROW_LOOKUP[i], true);
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
