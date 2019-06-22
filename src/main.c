// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "main.h"

#include <string.h>

#include "SEGGER_RTT.h"
#include "balance_main.h"
#include "cmsis_os.h"

I2C_HandleTypeDef hi2c2;
SPI_HandleTypeDef hspi2;
UART_HandleTypeDef huart1;

osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[128];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId balanceTaskHandle;
uint32_t balanceTaskBuffer[128];
osStaticThreadDef_t balanceTaskControlBlock;

void SystemClock_Config(void);
void SetupRTT(void);
void TILT_InitHardware(void);
void WHEEL_InitHardware(void);
void StartDefaultTask(void const *argument);
extern void BALANCE_main(void const *argument);

int main(void) {
  HAL_Init();
  SystemClock_Config();
  SetupRTT();
  TILT_InitHardware();
  WHEEL_InitHardware();

  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128,
                    defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  osThreadStaticDef(balanceTask, BALANCE_main, osPriorityAboveNormal, 0, 128,
                    balanceTaskBuffer, &balanceTaskControlBlock);
  balanceTaskHandle = osThreadCreate(osThread(balanceTask), NULL);

  osKernelStart();

  while (1) {
  }
}

void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

void SetupRTT(void) {
  static uint8_t rtt_channel1_buffer[128];
  SEGGER_RTT_Init();
  SEGGER_RTT_ConfigUpBuffer(1, "DATA1", rtt_channel1_buffer,
                            sizeof(rtt_channel1_buffer),
                            SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
}

int __io_putchar(int ch) {
  // uint8_t ch8=ch;
  // HAL_UART_Transmit(&huart1,(uint8_t *)&ch8,1,HAL_MAX_DELAY);
  SEGGER_RTT_PutChar(0, ch);
  return ch;
}

int __io_getchar() {
  // uint8_t ch8;
  // HAL_UART_Receive(&huart1,&ch8,1,HAL_MAX_DELAY);
  // return 0;
  return SEGGER_RTT_GetKey();
}

void StartDefaultTask(void const *argument) {
  // Board LED is on PC13.
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
  LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13);
  LL_GPIO_InitTypeDef gpio_init = {0};
  gpio_init.Pin = LL_GPIO_PIN_13;
  gpio_init.Mode = LL_GPIO_MODE_OUTPUT;
  gpio_init.Speed = LL_GPIO_SPEED_FREQ_LOW;
  gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOC, &gpio_init);

  for (;;) {
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
    osDelay(1000);
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
}

void Error_Handler(void) {
  while (1) {
  }
}
