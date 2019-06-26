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

#include <stdbool.h>
#include <stdint.h>

#include "arm_math.h"

// Initializes and clears the display.
void OLED_Init();

// Writes out one row of text.
// - If `text` contains more than 16 characters, it will be trucated.
// - If `text` is less than 16 characters (there is a null character within the
// first 16 characters), the output will be padded with space until the end of
// the line.
// - `row` must be between 0 and 7.
void OLED_SetText(uint8_t row, char *text);

// Writes out one column of a plot.
// - Internally, it maintains a column counter associated with `top_row` which
// is incremented after every call to `OLED_PlotData`.
// - If `reset` is true, the column is reset to zero.
// - `top_row` must be between 0 and 7. (Each row is 8 pixels high - 64 pixels
// in total.)
// - The height of the graph will be `8 * rows` pixels.
// - `top_row + rows` should be never be greater than 8.
// - `rows` must be a multiple of 2, i.e. 1, 2, 4 or 8.
// - `col` should be a value between 0 and 127.
// - `value` is a 8-bit signed value representing a number in the range [-1, 1).
// Visually -1 is at the bottom and 1 is at the top.
void OLED_PlotData(bool reset, uint8_t top_row, uint8_t num_rows, uint8_t col,
                   q7_t value);

#endif  // OLED_H
