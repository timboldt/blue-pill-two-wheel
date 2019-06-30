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

#include "ps2.h"

#include "cmsis_os.h"
#include "gpio.h"
#include "spi.h"

static uint8_t data_[32];

uint8_t _TrasferByte(uint8_t data) {
  while (!LL_SPI_IsActiveFlag_TXE(SPI2)) {
    osThreadYield();
  }
  LL_SPI_TransmitData8(SPI2, data);
  while (!LL_SPI_IsActiveFlag_RXNE(SPI2)) {
    osThreadYield();
  }
  return (uint8_t)LL_SPI_ReceiveData8(SPI2);
}

void _TrasferBytes(const uint8_t* txbuf, uint8_t* rxbuf, uint8_t len) {
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_12);
  for (uint8_t i = 0; i < len; i++) {
    rxbuf[i] = _TrasferByte(txbuf[i]);
    // Since the ACK line isn't connected, just delay a few us between bytes.
    for (int j = 0; j < 500; j++) {
      asm("NOP");
    }
  }
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
}

void _CmdInitialPoll() {
  uint8_t cmd[] = {0x01, 0x42, 0x00, 0xFF, 0xFF};
  _TrasferBytes(cmd, data_, sizeof(cmd));
}

void _CmdEnterConfigMode() {
  uint8_t cmd[] = {0x01, 0x43, 0x00, 0x01, 0x00};
  _TrasferBytes(cmd, data_, sizeof(cmd));
}

void _CmdExitConfigMode() {
  uint8_t cmd[] = {0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A};
  _TrasferBytes(cmd, data_, sizeof(cmd));
}

void _CmdAnalogMode() {
  uint8_t cmd[] = {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};
  _TrasferBytes(cmd, data_, sizeof(cmd));
}

void _CmdPoll() {
  uint8_t cmd[] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  _TrasferBytes(cmd, data_, sizeof(cmd));
}

void PS2_Init() {
  LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_12);
  LL_SPI_Enable(SPI2);
  _CmdInitialPoll();
  _CmdEnterConfigMode();
  _CmdAnalogMode();
  _CmdExitConfigMode();
  _CmdPoll();
}

void PS2_GetJoy(uint8_t* jx, uint8_t* jy) {
  _CmdPoll();
  // TEST: read right joystick
  *jx = data_[5];
  *jy = data_[6];
}