#include "pico/stdlib.h"

#include "keyboard.h"

int main() {
  const uint SOME_PIN = 5;
  gpio_init(SOME_PIN);
  gpio_set_dir(SOME_PIN, true);
  while (true) {
    gpio_put(SOME_PIN, false);
    sleep_ms(1000);
    gpio_put(SOME_PIN, true);
  }
}
