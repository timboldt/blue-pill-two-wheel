//
// Created by tim on 4/17/19.
//

#include "main.h"

#include <cstring>

#include "SEGGER_RTT.h"

#include "balance_main.h"
#include "motor.h"
#include "tilt_sensor.h"

extern I2C_HandleTypeDef hi2c2;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

static TiltSensor imu;

static  uint8_t rtt_channel1_buffer[128];

void BALANCE_init_hardware() {
    SEGGER_RTT_Init();
    SEGGER_RTT_ConfigUpBuffer(1, "DATA1", rtt_channel1_buffer, sizeof(rtt_channel1_buffer), SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);

    // Enable GPIO port clocks.
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);

    // Enable the TIM4 peripheral.
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

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

void BALANCE_do_work(void const *) {
    //const uint16_t MPU9250_DEVICE_ADDRESS = 0x68;
//    for (;;) {
//        int status = imu.init(&hi2c2, MPU9250_DEVICE_ADDRESS);
//        if (status >= 0) {
//            break;
//        }
//        printf("imu init failed, err: %d\n", status);
//        HAL_Delay(100);
//    }


    while (true) {
//        int angle = imu.tilt_angle();
//        printf("angle: %d\n", angle);
//        int ch = SEGGER_RTT_GetKey();
//        if (ch > 0)
//            printf("I saw a %c!", ch);
        puts("This goes to channel 0.");
        SEGGER_RTT_printf(1, "%d %d\n",
               __HAL_TIM_GET_COUNTER(&htim2),
               __HAL_TIM_GET_COUNTER(&htim3));
        LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
        HAL_Delay(1000);
    }
}

#pragma clang diagnostic pop