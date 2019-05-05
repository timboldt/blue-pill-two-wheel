//
// Created by tim on 4/17/19.
//

extern "C" {
#include "SEGGER_RTT.h"
#include "stm32f1xx.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
}

#include <cstring>

#include "balance_main.h"
#include "tilt_sensor.h"
#include "wheel.h"

// extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

//static TiltSensor imu;

static uint8_t rtt_channel1_buffer[128];

void BALANCE_setup() {
  SEGGER_RTT_Init();
  SEGGER_RTT_ConfigUpBuffer(1, "DATA1", rtt_channel1_buffer,
                            sizeof(rtt_channel1_buffer),
                            SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

  // Enable GPIO port clocks.
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);

  // Enable the timer peripherals.
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

  // Board LED is on PC13.
  LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
  LL_GPIO_InitTypeDef gpio_init = {0};
  gpio_init.Pin = LL_GPIO_PIN_13;
  gpio_init.Mode = LL_GPIO_MODE_OUTPUT;
  gpio_init.Speed = LL_GPIO_SPEED_FREQ_LOW;
  gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOC, &gpio_init);

  Wheel::init_hardware();

  // const uint16_t MPU9250_DEVICE_ADDRESS = 0x68;
  //    for (;;) {
  //        int status = imu.init(&hi2c2, MPU9250_DEVICE_ADDRESS);
  //        if (status >= 0) {
  //            break;
  //        }
  //        printf("imu init failed, err: %d\n", status);
  //        HAL_Delay(100);
  //    }
}

void BALANCE_loop() {
  //        int angle = imu.tilt_angle();
  //        printf("angle: %d\n", angle);

  // int ch = SEGGER_RTT_WaitKey();
  Wheel *left_wheel = Wheel::get_wheel(Wheel::LEFT_WHEEL);
  Wheel *right_wheel = Wheel::get_wheel(Wheel::RIGHT_WHEEL);
  // if (ch == 'q' && left_wheel->target_speed() < INT16_MAX - 0x0FFF) {
  //   left_wheel->set_target_speed(left_wheel->target_speed() + 0x0FFF);
  // }
  // left_wheel->set_target_speed(0x1fff);
  // right_wheel->set_target_speed(0x1fff);
  left_wheel->set_target_speed(0xB000);
  right_wheel->set_target_speed(0xB000);
  left_wheel->update();
  right_wheel->update();
  // if (ch == 'a' && left_motor->power() > INT16_MIN + 0x0FFF) {
  //   left_motor->set_power(left_motor->power() - 0x0FFF);
  // }
  // if (ch == 'w' && right_motor->power() < INT16_MAX - 0x0FFF) {
  //   right_motor->set_power(right_motor->power() + 0x0FFF);
  // }
  // if (ch == 's' && right_motor->power() > INT16_MIN + 0x0FFF) {
  //   right_motor->set_power(right_motor->power() - 0x0FFF);
  // }
  // SEGGER_RTT_printf(0, "%d %d %d %d\n", left_wheel->target_speed(),
  //                   left_wheel->actual_speed(), right_wheel->target_speed(),
  //                   right_wheel->actual_speed());
  LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
  HAL_Delay(10);
}
