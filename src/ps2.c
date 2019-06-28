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
#include "spi.h"

uint8_t _TrasferByte(uint8_t data)
{
    while (!LL_SPI_IsActiveFlag_TXE(SPI2)) {
      osThreadYield();
    }
    LL_SPI_TransmitData8(SPI2, data);
    while (!LL_SPI_IsActiveFlag_RXNE(SPI2)){
      osThreadYield();
    }
    return (uint8_t)LL_SPI_ReceiveData8(SPI2);
}

void PS2_Init() {
  // TODO
  // LL_SPI_Enable(SPI2);
}