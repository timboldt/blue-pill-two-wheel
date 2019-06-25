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

#ifndef OLED_H
#define OLED_H

#include <stdint.h>

// Writes out one row of text.
// * If `text` contains more than 16 characters, it will be trucated.
// * If `text` is less than 16 characters (there is a null character within the
// first 16 characters), the output will be padded with space until the end of
// the line.
// * `row` must be between 0 and 7.
// * Returns true on success, and false if the device is busy.
bool OLED_SetText(uint8_t row, char *text);

// Writes out one column of a plot.
// TODO.
bool OLED_PlotData(uint8_t top_row, uint8_t rows, int8_t *values)

#endif  // OLED_H
