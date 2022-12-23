#include "pico/stdlib.h"
#include "tusb.h"

#include "keyboard.h"

int main() {
  const uint SOME_PIN = 5;
  gpio_init(SOME_PIN);
  gpio_set_dir(SOME_PIN, true);

  initKeyboard();
  setKey(KEY_MAP[0x04], true);

  while (true) {
    processKeys();
  }
}
