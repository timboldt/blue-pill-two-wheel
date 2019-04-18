//
// Created by tim on 4/17/19.
//

#include "main.h"
#include "cmsis_os.h"

#include <cstring>

#include "balance_main.h"

extern I2C_HandleTypeDef hi2c2;

void BALANCE_do_work(void const * argument) {
    while (1) {
        const uint16_t MPU9250_DEVICE_ADDRESS = 0xD0;
        const uint16_t MPU9250_RA_WHO_AM_I = 0x75;
        static uint8_t buffer[100];
        memset(buffer, 0, sizeof(buffer));
        HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c2, MPU9250_DEVICE_ADDRESS, MPU9250_RA_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, buffer, 1, 100);

        osDelay(10);
    }
}