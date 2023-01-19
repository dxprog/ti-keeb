#include "pico/stdlib.h"
#include "tusb.h"

#include "keyboard.h"

int main() {
  const uint LED_PIN = PICO_DEFAULT_LED_PIN;
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, false);

  initKeyboard();
  setKey(KEY_MAP[0x04], true);

  while (true);
}
