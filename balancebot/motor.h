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

#ifndef BLUEPILL2WHEEL_MOTOR_H
#define BLUEPILL2WHEEL_MOTOR_H

#include <arm_math.h>
#include <cstdint>

class Motor {
 public:
  const static uint8_t LEFT_MOTOR = 0;
  const static uint8_t RIGHT_MOTOR = 1;

  // Motor ID determines which timer channel is used for PWM.
  Motor(uint8_t motor_id);

  uint8_t motor_id() const;

  // Power is a value between -1 and +1 exclusive.
  void set_power(q15_t power);
  q15_t power() const;

  static void init_hardware();

 private:
  uint8_t motor_id_;
  q15_t power_;
};

#endif  // BLUEPILL2WHEEL_MOTOR_H
