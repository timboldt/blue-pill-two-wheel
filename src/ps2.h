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

#ifndef PS2_H
#define PS2_H

#include <stdbool.h>
#include <stdint.h>

#include "arm_math.h"

// Initializes the PS2 joystick device.
void PS2_Init();

void PS2_GetJoy(uint8_t* jx, uint8_t* jy);

#endif  // PS2_H
