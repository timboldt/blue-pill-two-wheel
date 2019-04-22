//
// Created by tim on 4/17/19.
//

#include "main.h"

#include <string.h>

#include "balance_main.h"
#include "motor.h"
#include "tilt_sensor.h"

extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

static TiltSensor imu;

void BALANCE_init_hardware() {
    // Enable GPIO port clocks.
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);

    // Board LED is on PC13.
    LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
    LL_GPIO_InitTypeDef gpio_init = {0};
    gpio_init.Pin = LL_GPIO_PIN_13;
    gpio_init.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_LOW;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOC, &gpio_init);

    Motor::init_hardware();
}


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void BALANCE_do_work(void const * argument) {
    const uint16_t MPU9250_DEVICE_ADDRESS = 0x68;
//    for (;;) {
//        int status = imu.init(&hi2c2, MPU9250_DEVICE_ADDRESS);
//        if (status >= 0) {
//            break;
//        }
//        printf("imu init failed, err: %d\n", status);
//        HAL_Delay(100);
//    }
//    HAL_GPIO_TogglePin(Motor1Ch2_GPIO_Port, Motor1Ch2_Pin);
//    HAL_GPIO_TogglePin(Motor2Ch2_GPIO_Port, Motor2Ch2_Pin);

    while (1) {
//        int angle = imu.tilt_angle();
//        printf("angle: %d\n", angle);
        printf("%d %d\n", __HAL_TIM_GET_COUNTER(&htim2), __HAL_TIM_GET_COUNTER(&htim3));
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
//        HAL_GPIO_TogglePin(Motor1Ch1_GPIO_Port, Motor1Ch1_Pin);
//        HAL_GPIO_TogglePin(Motor1Ch2_GPIO_Port, Motor1Ch2_Pin);
//        HAL_GPIO_TogglePin(Motor2Ch1_GPIO_Port, Motor2Ch1_Pin);
//        HAL_GPIO_TogglePin(Motor2Ch2_GPIO_Port, Motor2Ch2_Pin);
        HAL_Delay(1000);
    }
}
#pragma clang diagnostic pop