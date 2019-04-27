//
// Created by tim on 4/17/19.
//

#include "main.h"

#include "tilt_sensor.h"

#include <cstring>

int TiltSensor::init(I2C_HandleTypeDef *i2c, const uint16_t address) {
    const uint16_t MPU9250_RA_WHO_AM_I = 0x75;
    static uint8_t buffer[100];
    memset(buffer, 0, sizeof(buffer));
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(i2c, address<<1, MPU9250_RA_WHO_AM_I, I2C_MEMADD_SIZE_8BIT, buffer, 1, 100);

    if (status != HAL_OK) {
        // Hardware error.
        return -1;
    }
    if (buffer[0] != 0x71) {
        // Unexpected WHOAMI value.
        return -2;
    }
    return 0;
}

int TiltSensor::tilt_angle() {
    return 91;
}
