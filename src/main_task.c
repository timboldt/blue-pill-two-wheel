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

#include "cmsis_os.h"

#include "main.h"
#include "oled.h"
#include "ps2.h"

void MainTask(void const *argument) {
  // Wait for device to power up.
  osDelay(100);
  OLED_Init();
  OLED_SetText(0, "OLED Ready");
  PS2_Init();
  OLED_SetText(0, "PS2 Ready");
  uint8_t col = 0;
  OLED_SetText(0, "Init Done");
  for (;;) {
    // Board LED is on PC13.
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
    if (LL_GPIO_IsOutputPinSet(GPIOC, LL_GPIO_PIN_13)) {
      OLED_SetText(1, "LED Off");
    } else {
      OLED_SetText(1, "LED On");
    }
    uint8_t jx = 0, jy = 0;
    PS2_GetJoy(&jx, &jy);
    OLED_PlotData(4, 2, col & 0x7f, ((int)jx) - 128);
    OLED_PlotData(6, 2, col & 0x7f, ((int)jy) - 128);
    col++;
    osDelay(200);
  }
}