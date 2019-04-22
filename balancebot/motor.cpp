//
// Created by tim on 4/21/19.
//

#include "motor.h"

#include "main.h"

void Motor::init_hardware() {
    // Direction control pins:
    //    PA2  - Motor 1 Forward
    //    PA3  - Motor 1 Reverse
    //    PA4  - Motor 2 Forward
    //    PA5  - Motor 2 Reverse
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5);
    LL_GPIO_InitTypeDef gpio_init = {0};
    gpio_init.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_5;
    gpio_init.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_LOW;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOA, &gpio_init);

    //xxxx
    //    HAL_TIM_Base_Start(&htim4);
    //    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
    //    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);
}
