#include <libopencm3/stm32/rcc.h>

#include "led.h"

static void clock_setup(void) {
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  rcc_periph_clock_enable(RCC_AFIO);

  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOC);
  // rcc_periph_clock_enable(RCC_GPIOD);

  rcc_periph_clock_enable(RCC_TIM1);
  rcc_periph_clock_enable(RCC_TIM2);
  rcc_periph_clock_enable(RCC_TIM3);
  rcc_periph_clock_enable(RCC_TIM4);

  rcc_periph_clock_enable(RCC_I2C2);
}

static void i2c_bus_setup(void) {
  // I2C2 SCL=PB10 SDA=PB11
  // gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
  //               GPIO10 | GPIO11);
  // gpio_set(GPIOB, GPIO10 | GPIO11);

  //     let i2c = BlockingI2c::i2c2(
  //         dp.I2C2,
  //         (scl, sda),
  //         hal::i2c::Mode::Fast {
  //             frequency: 400_000,
  //             duty_cycle: hal::i2c::DutyCycle::Ratio2to1,
  //         },
  //         clocks,
  //         &mut rcc.apb1,
  //         1_000,
  //         2,
  //         1_000,
  //         1_000,
  //     );
}

int main(void) {
  clock_setup();
  i2c_bus_setup();

  LED_init();

  int i = 0;
  for (;;) {
    LED_on();
    for (i = 0; i < 1500000; i++) /* Wait a bit. */
      __asm__("nop");

    LED_off();
    for (i = 0; i < 500000; i++) /* Wait a bit. */
      __asm__("nop");
  }

  return 0;
}
