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

#ifndef BLUEPILL2WHEEL_ENCODER_H
#define BLUEPILL2WHEEL_ENCODER_H

#include <arm_math.h>
#include <cstdint>

class Encoder {
 public:
  const static uint8_t LEFT_ENCODER = 0;
  const static uint8_t RIGHT_ENCODER = 1;

  // Encoder ID determines which timer is used.
  Encoder(uint8_t encoder_id);

  uint8_t encoder_id() const;

  q15_t counter_delta();

  static void init_hardware();

 private:
  uint8_t encoder_id_;
  q15_t last_counter_;
};

#endif  // BLUEPILL2WHEEL_ENCODER_H
