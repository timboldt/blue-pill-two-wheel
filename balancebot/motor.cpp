//
// Created by tim on 4/21/19.
//

extern "C" {
#include "stm32f1xx.h"
#include "stm32f1xx_ll_gpio.h"
#include <stm32f1xx_ll_tim.h>
#include "SEGGER_RTT.h"
}

#include "motor.h"

void Motor::init_hardware() {
    // Initialize timer.
    //
    // Frequency = ClockFreq / ((PSC + 1) * (ARR + 1))
    // 2008 Hz = 72 MHz / ((34+1)*(1023+1))
    LL_TIM_InitTypeDef timer_init = {0};
    timer_init.Prescaler = 34;
    timer_init.CounterMode = LL_TIM_COUNTERMODE_UP;
    timer_init.Autoreload = 1023;
    timer_init.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    LL_TIM_Init(TIM4, &timer_init);
    LL_TIM_DisableARRPreload(TIM4);

    // Initialize timer output compare for channels 1 and 2.
    LL_TIM_OC_InitTypeDef timer_oc_init = {0};
    timer_oc_init.OCMode = LL_TIM_OCMODE_PWM1;
    timer_oc_init.CompareValue = 0;
    timer_oc_init.OCPolarity = LL_TIM_OCPOLARITY_HIGH;

    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH1);
    timer_oc_init.OCState = LL_TIM_OCSTATE_DISABLE;
    timer_oc_init.OCNState = LL_TIM_OCSTATE_DISABLE;
    LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH1, &timer_oc_init);
    LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH1);

    LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH2);
    timer_oc_init.OCState = LL_TIM_OCSTATE_DISABLE;
    timer_oc_init.OCNState = LL_TIM_OCSTATE_DISABLE;
    LL_TIM_OC_Init(TIM4, LL_TIM_CHANNEL_CH2, &timer_oc_init);
    LL_TIM_OC_DisableFast(TIM4, LL_TIM_CHANNEL_CH2);

    LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_RESET);
    LL_TIM_DisableMasterSlaveMode(TIM4);

    // Direction control GPIO pins:
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

    // PWM GPIO pins:
    //    PB6 - Motor 1 PWM
    //    PB7 - Motor 2 PWM
    LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_6|LL_GPIO_PIN_7);
    gpio_init = {0};
    gpio_init.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_7;
    gpio_init.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_LOW;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOB, &gpio_init);

    // Enable the PWM channels, enable the counter, and force an update event.
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH2);
    LL_TIM_EnableCounter(TIM4);
    LL_TIM_GenerateEvent_UPDATE(TIM4);
}


void Motor::set_speed(q15_t speed) {
    // Compute absolute value, and saturating 0x8000 to 0x7ffff.
    q15_t abs_speed = (speed > 0) ? speed : (q15_t)__QSUB16(0, speed);

    // Convert from 15-bit fractional value to 10-bit duty cycle value.
    int16_t pwm_value = abs_speed >> 5;
    if (channel_ == 1) {
        LL_TIM_OC_SetCompareCH1(TIM4, pwm_value);
    } else {
        LL_TIM_OC_SetCompareCH2(TIM4, pwm_value);
    }
}

