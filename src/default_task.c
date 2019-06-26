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

void StartDefaultTask(void const *argument) {
  OLED_Init();
  OLED_SetText(1, "Hello world!");
  for (;;) {
    // Board LED is on PC13.
    LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
    osDelay(1000);
  }
}