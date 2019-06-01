#include "led.h"

#include <libopencm3/stm32/gpio.h>

void LED_init(void) {
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
                GPIO13);
}

void LED_on(void) { gpio_clear(GPIOC, GPIO13); }

void LED_off(void) { gpio_set(GPIOC, GPIO13); }