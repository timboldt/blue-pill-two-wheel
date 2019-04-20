//
// Created by tim on 4/17/19.
//

#include "main.h"

#include <string.h>

#include "balance_main.h"
#include "tilt_sensor.h"

extern I2C_HandleTypeDef hi2c2;

static TiltSensor imu;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void BALANCE_do_work(void const * argument) {
    const uint16_t MPU9250_DEVICE_ADDRESS = 0x68;
    for (;;) {
        int status = imu.init(&hi2c2, MPU9250_DEVICE_ADDRESS);
        if (status >= 0) {
            break;
        }
        printf("imu init failed, err: %d\n", status);
        HAL_Delay(100);
    }

    while (1) {
        int angle = imu.tilt_angle();
        puts("hi");
        printf("angle: %d\n", angle);
        HAL_Delay(1000);
    }
}
#pragma clang diagnostic pop