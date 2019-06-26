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

#include "oled.h"

#include "cmsis_os.h"
#include "i2c.h"

/** Set Lower Column Start Address for Page Addressing Mode. */
#define SSD1306_SETLOWCOLUMN 0x00
/** Set Higher Column Start Address for Page Addressing Mode. */
#define SSD1306_SETHIGHCOLUMN 0x10
/** Set Memory Addressing Mode. */
#define SSD1306_MEMORYMODE 0x20
/** Set display RAM display start line register from 0 - 63. */
#define SSD1306_SETSTARTLINE 0x40
/** Set Display Contrast to one of 256 steps. */
#define SSD1306_SETCONTRAST 0x81
/** Enable or disable charge pump.  Follow with 0X14 enable, 0X10 disable. */
#define SSD1306_CHARGEPUMP 0x8D
/** Set Segment Re-map between data column and the segment driver. */
#define SSD1306_SEGREMAP 0xA0
/** Resume display from GRAM content. */
#define SSD1306_DISPLAYALLON_RESUME 0xA4
/** Force display on regardless of GRAM content. */
#define SSD1306_DISPLAYALLON 0xA5
/** Set Normal Display. */
#define SSD1306_NORMALDISPLAY 0xA6
/** Set Inverse Display. */
#define SSD1306_INVERTDISPLAY 0xA7
/** Set Multiplex Ratio from 16 to 63. */
#define SSD1306_SETMULTIPLEX 0xA8
/** Set Display off. */
#define SSD1306_DISPLAYOFF 0xAE
/** Set Display on. */
#define SSD1306_DISPLAYON 0xAF
/**Set GDDRAM Page Start Address. */
#define SSD1306_SETSTARTPAGE 0XB0
/** Set COM output scan direction normal. */
#define SSD1306_COMSCANINC 0xC0
/** Set COM output scan direction reversed. */
#define SSD1306_COMSCANDEC 0xC8
/** Set Display Offset. */
#define SSD1306_SETDISPLAYOFFSET 0xD3
/** Sets COM signals pin configuration to match the OLED panel layout. */
#define SSD1306_SETCOMPINS 0xDA
/** This command adjusts the VCOMH regulator output. */
#define SSD1306_SETVCOMDETECT 0xDB
/** Set Display Clock Divide Ratio/ Oscillator Frequency. */
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
/** Set Pre-charge Period */
#define SSD1306_SETPRECHARGE 0xD9
/** Deactivate scroll */
#define SSD1306_DEACTIVATE_SCROLL 0x2E
/** No Operation Command. */
#define SSD1306_NOP 0XE3
//------------------------------------------------------------------------------
/** Set Pump voltage value: (30H~33H) 6.4, 7.4, 8.0 (POR), 9.0. */
#define SH1106_SET_PUMP_VOLTAGE 0X30
/** First byte of set charge pump mode */
#define SH1106_SET_PUMP_MODE 0XAD
/** Second byte charge pump on. */
#define SH1106_PUMP_ON 0X8B
/** Second byte charge pump off. */
#define SH1106_PUMP_OFF 0X8A

const uint8_t kSlaveAddress = 0x3c << 1;

//--------------------------------------------------------------------------
// ASCII 7x7 font values with first byte equal to first column, LSB at top.
//--------------------------------------------------------------------------

static uint8_t symbol_font[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // Blank
};

static uint8_t digit_font[] = {
    0x1C, 0x3E, 0x61, 0x41, 0x43, 0x3E, 0x1C, 0x00,  // 0
    0x40, 0x42, 0x7F, 0x7F, 0x40, 0x40, 0x00, 0x00,  // 1
    0x62, 0x73, 0x79, 0x59, 0x5D, 0x4F, 0x46, 0x00,  // 2
    0x20, 0x61, 0x49, 0x4D, 0x4F, 0x7B, 0x31, 0x00,  // 3
    0x18, 0x1C, 0x16, 0x13, 0x7F, 0x7F, 0x10, 0x00,  // 4
    0x27, 0x67, 0x45, 0x45, 0x45, 0x7D, 0x38, 0x00,  // 5
    0x3C, 0x7E, 0x4B, 0x49, 0x49, 0x79, 0x30, 0x00,  // 6
    0x03, 0x03, 0x71, 0x79, 0x0D, 0x07, 0x03, 0x00,  // 7
    0x36, 0x7F, 0x49, 0x49, 0x49, 0x7F, 0x36, 0x00,  // 8
    0x06, 0x4F, 0x49, 0x49, 0x69, 0x3F, 0x1E, 0x00,  // 9
};

static uint8_t alpha_font[] = {
    0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00, 0x00, 0x00,  // A
    0x7F, 0x49, 0x49, 0x49, 0x36, 0x00, 0x00, 0x00,  // B
    0x3E, 0x41, 0x41, 0x41, 0x22, 0x00, 0x00, 0x00,  // C
    0x7F, 0x7F, 0x41, 0x41, 0x63, 0x3E, 0x1C, 0x00,  // D
    0x7F, 0x49, 0x49, 0x49, 0x41, 0x00, 0x00, 0x00,  // E
    0x7F, 0x09, 0x09, 0x01, 0x01, 0x00, 0x00, 0x00,  // F
    0x3E, 0x41, 0x41, 0x51, 0x32, 0x00, 0x00, 0x00,  // G
    0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00, 0x00, 0x00,  // H
    0x00, 0x41, 0x7F, 0x41, 0x00, 0x00, 0x00, 0x00,  // I
    0x20, 0x40, 0x41, 0x3F, 0x01, 0x00, 0x00, 0x00,  // J
    0x7F, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00,  // K
    0x7F, 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00,  // L
    0x7F, 0x02, 0x04, 0x02, 0x7F, 0x00, 0x00, 0x00,  // M
    0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00, 0x00, 0x00,  // N
    0x3E, 0x7F, 0x41, 0x41, 0x41, 0x7F, 0x3E, 0x00,  // O
    0x7F, 0x09, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00,  // P
    0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00, 0x00, 0x00,  // Q
    0x7F, 0x7F, 0x11, 0x31, 0x79, 0x6F, 0x4E, 0x00,  // R
    0x46, 0x49, 0x49, 0x49, 0x31, 0x00, 0x00, 0x00,  // S
    0x01, 0x01, 0x7F, 0x01, 0x01, 0x00, 0x00, 0x00,  // T
    0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00, 0x00, 0x00,  // U
    0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00, 0x00, 0x00,  // V
    0x7F, 0x7F, 0x38, 0x1C, 0x38, 0x7F, 0x7F, 0x00,  // W
    0x63, 0x14, 0x08, 0x14, 0x63, 0x00, 0x00, 0x00,  // X
    0x03, 0x04, 0x78, 0x04, 0x03, 0x00, 0x00, 0x00,  // Y
    0x61, 0x51, 0x49, 0x45, 0x43, 0x00, 0x00, 0x00   // Z
};

static uint8_t *_GetBytesForChar(char c) {
  if (c >= '0' && c <= '9') {
    return &digit_font[8*(c - '0')];
  } else if (c >= 'A' && c <= 'Z') {
    return &alpha_font[8*(c - 'A')];
  } else if (c >= 'a' && c <= 'z') {
    return &alpha_font[8*(c - 'a')];
  }
  return &symbol_font[0];
}

static void _WriteBytes(bool command_mode, uint8_t *bytes, uint8_t len) {
  while (LL_I2C_IsActiveFlag_BUSY(I2C2)) {
    osThreadYield();
  }

  LL_I2C_GenerateStartCondition(I2C2);
  while (!LL_I2C_IsActiveFlag_SB(I2C2)) {
    osThreadYield();
  }

  // Send  device address
  LL_I2C_TransmitData8(I2C2, kSlaveAddress);
  while (!LL_I2C_IsActiveFlag_ADDR(I2C2)) {
    osThreadYield();
  }
  LL_I2C_ClearFlag_ADDR(I2C2);

  uint8_t lead_byte = (command_mode ? 0x00 : 0x40);
  while (!LL_I2C_IsActiveFlag_TXE(I2C2)) {
    osThreadYield();
  }
  LL_I2C_TransmitData8(I2C2, lead_byte);

  for (uint8_t i = 0; i < len; i++) {
    while (!LL_I2C_IsActiveFlag_TXE(I2C2)) {
      osThreadYield();
    }
    LL_I2C_TransmitData8(I2C2, bytes[i]);
  }

  while (!LL_I2C_IsActiveFlag_BTF(I2C2)) {
    osThreadYield();
  }
  LL_I2C_GenerateStopCondition(I2C2);
}

static void _MoveToRowCol(uint8_t row, uint8_t col) {
  // TODO: implement me.
  unsigned char cmd[] = {// Set row
                         SSD1306_SETSTARTPAGE | (row & 0x07),
                         // Set column
                         SSD1306_SETLOWCOLUMN | (col & 0x0f),
                         SSD1306_SETHIGHCOLUMN | (col >> 4)};
  _WriteBytes(true, cmd, sizeof(cmd));
}

void OLED_Init() {
  uint8_t cmd[] = {// display off
                   SSD1306_DISPLAYOFF,
                   // the suggested ratio 0x80
                   SSD1306_SETDISPLAYCLOCKDIV, 0x80,
                   // ratio 64
                   SSD1306_SETMULTIPLEX, 0x3F,
                   // no offset
                   SSD1306_SETDISPLAYOFFSET, 0x0,
                   // line #0
                   SSD1306_SETSTARTLINE | 0x0,
                   // internal vcc
                   SSD1306_CHARGEPUMP, 0x14,
                   // wrapping mode
                   SSD1306_MEMORYMODE, 0x00,
                   // column 127 mapped to SEG0
                   SSD1306_SEGREMAP | 0x1,
                   // column scan direction reversed
                   SSD1306_COMSCANDEC,
                   // alt COM pins, disable remap
                   SSD1306_SETCOMPINS, 0x12,
                   // contrast level 127
                   SSD1306_SETCONTRAST, 0x7F,
                   // pre-charge period (1, 15)
                   SSD1306_SETPRECHARGE, 0xF1,
                   // vcomh regulator level
                   SSD1306_SETVCOMDETECT, 0x40,
                   // display on with normal display
                   SSD1306_DISPLAYALLON_RESUME, SSD1306_NORMALDISPLAY};
  _WriteBytes(true, cmd, sizeof(cmd));

  // // Blank the display.
  // // This assumes wrapping mode right now.
  for (int i = 0; i < 64; i++) {
    unsigned char data[16] = {
        0x00,
    };
    _WriteBytes(false, data, sizeof(data));
  }

  uint8_t cmd2[] = {// page mode
                    SSD1306_MEMORYMODE, 0x02,
                    // display on
                    SSD1306_DISPLAYON};
  _WriteBytes(true, cmd2, sizeof(cmd2));
}

void OLED_SetText(uint8_t row, char *text) {
  _MoveToRowCol(row, 0);

  const int kMaxChars = 16;
  int index = 0;
  // Ouput characters until NUL or end of line.
  while (index < kMaxChars && text[index] != 0) {
    uint8_t *bytes = _GetBytesForChar(text[index]);
    _WriteBytes(false, bytes, 8);
    index++;
  }
  // Pad with blanks to end of line.
  while (index < kMaxChars) {
    uint8_t *bytes = _GetBytesForChar(' ');
    _WriteBytes(false, bytes, 8);
    index++;
  }
}

void OLED_PlotData(bool reset, uint8_t top_row, uint8_t num_rows, uint8_t col,
                   q7_t value) {
  // TODO: implement me.
}