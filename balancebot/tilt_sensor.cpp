#include "tilt_sensor.h"

extern "C" {
#include <arm_math.h>
#include "SEGGER_RTT.h"
#include "main.h"
}

#include <cstring>

extern I2C_HandleTypeDef hi2c2;

const uint16_t MPU9250_DEVICE_ADDRESS = 0x68;
const uint16_t MPU9250_WHOAMI_ID = 0x71;
const uint32_t MPU9250_IO_TIMEOUT = 100;
const uint32_t MPU9250_IO_SHORT_TIMEOUT = 5;

const uint16_t MPU9250_RA_SMPLRT_DIV = 0x19;
const uint16_t MPU9250_RA_CONFIG = 0x1A;
const uint16_t MPU9250_RA_GYRO_CONFIG = 0x1B;
const uint16_t MPU9250_RA_ACCEL_CONFIG = 0x1C;
const uint16_t MPU9250_RA_WHO_AM_I = 0x75;
const uint16_t MPU9250_RA_PWR_MGMT_1 = 0x6B;
const uint16_t MPU9250_RA_ACCEL_XOUT_H = 0x3B;

void TiltSensor::init_hardware() {
  // I2C2 GPIO Configuration:
  //    PB10   ------> I2C2_SCL
  //    PB11   ------> I2C2_SDA
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK) {
    Error_Handler();
  }

  for (;;) {
    HAL_StatusTypeDef status;
    uint8_t byte_data = 0x00;
    status = HAL_I2C_Mem_Write(&hi2c2, MPU9250_DEVICE_ADDRESS << 1,
                               MPU9250_RA_SMPLRT_DIV, I2C_MEMADD_SIZE_8BIT,
                               &byte_data, 1, MPU9250_IO_TIMEOUT);
    if (status != HAL_OK) {
      SEGGER_RTT_printf(0, "Error setting MPU9250_RA_SMPLRT_DIV, err: %d\n",
                        status);
      HAL_Delay(100);
      continue;
    }
    byte_data = 0x00;
    status = HAL_I2C_Mem_Write(&hi2c2, MPU9250_DEVICE_ADDRESS << 1,
                               MPU9250_RA_CONFIG, I2C_MEMADD_SIZE_8BIT,
                               &byte_data, 1, MPU9250_IO_TIMEOUT);
    if (status != HAL_OK) {
      SEGGER_RTT_printf(0, "Error setting MPU9250_RA_CONFIG, err: %d\n",
                        status);
      HAL_Delay(100);
      continue;
    }
    byte_data = 0x08;
    status = HAL_I2C_Mem_Write(&hi2c2, MPU9250_DEVICE_ADDRESS << 1,
                               MPU9250_RA_GYRO_CONFIG, I2C_MEMADD_SIZE_8BIT,
                               &byte_data, 1, MPU9250_IO_TIMEOUT);
    if (status != HAL_OK) {
      SEGGER_RTT_printf(0, "Error setting MPU9250_RA_GYRO_CONFIG, err: %d\n",
                        status);
      HAL_Delay(100);
      continue;
    }
    byte_data = 0x00;
    status = HAL_I2C_Mem_Write(&hi2c2, MPU9250_DEVICE_ADDRESS << 1,
                               MPU9250_RA_ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT,
                               &byte_data, 1, MPU9250_IO_TIMEOUT);
    if (status != HAL_OK) {
      SEGGER_RTT_printf(0, "Error setting MPU9250_RA_ACCEL_CONFIG, err: %d\n",
                        status);
      HAL_Delay(100);
      continue;
    }
    byte_data = 0x01;
    status = HAL_I2C_Mem_Write(&hi2c2, MPU9250_DEVICE_ADDRESS << 1,
                               MPU9250_RA_PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT,
                               &byte_data, 1, MPU9250_IO_TIMEOUT);
    if (status != HAL_OK) {
      SEGGER_RTT_printf(0, "Error setting MPU9250_RA_PWR_MGMT_1, err: %d\n",
                        status);
      HAL_Delay(100);
      continue;
    }
    break;
  }

  for (;;) {
    uint8_t who_am_i;
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
        &hi2c2, MPU9250_DEVICE_ADDRESS << 1, MPU9250_RA_WHO_AM_I,
        I2C_MEMADD_SIZE_8BIT, &who_am_i, 1, MPU9250_IO_TIMEOUT);
    if (status == HAL_OK) {
      if (who_am_i != MPU9250_WHOAMI_ID) {
        // Unexpected WHOAMI value.
        SEGGER_RTT_printf(
            0, "FATAL ERROR: Unexpected MPU9250_RA_WHO_AM_I value: %d\n",
            who_am_i);
        Error_Handler();
      }
      break;
    }
    SEGGER_RTT_printf(0, "Imu init failed, err: %d\n", status);
    HAL_Delay(100);
  }
}

q15_t TiltSensor::tilt_angle() {
  uint8_t buffer[14];
  HAL_StatusTypeDef status = HAL_I2C_Mem_Read(
      &hi2c2, MPU9250_DEVICE_ADDRESS << 1, MPU9250_RA_ACCEL_XOUT_H,
      I2C_MEMADD_SIZE_8BIT, buffer, sizeof(buffer), MPU9250_IO_SHORT_TIMEOUT);
  if (status != HAL_OK) {
    SEGGER_RTT_printf(0, "Error reading IMU data: %d\n", status);
  } else {
    // The buffer contains 16-bit values in big-endian format. The order
    // is Accel X/Y/Z, Temperature, Gyro X/Y/Z. To compute tilt, we need
    // the two accelerometer axes pointing up/down and forward/backward, and
    // the one gyro axes that is perpendicular to those. In the current
    // orientation on this bot, this is Accel X/Z and Gyro Y.
    q15_t raw_accel_1 = (buffer[0] << 8 | buffer[1]);
    q15_t raw_accel_2 = -(buffer[4] << 8 | buffer[5]);
    q15_t raw_gyro = (buffer[10] << 8 | buffer[11]);

    // The accelerometer gives us an absolute frame of reference, because
    // gravity is always down. The angle can be computed from the ratio of
    // the forward/backward acceleration compared to the force of gravity.
    // Specifically, we can compute ATAN2(horiz_accel/vertical_accel). What
    // follows is a bunch of tricks to use integer arithmetic with an implied
    // decimal place between binary digits, that is moved around to avoid
    // overflow/underflow.

    // Ratio is a Q1.15 representing a fraction between -1 (at -45 degrees)
    // and 1 (at +45 degrees).
    q15_t ratio;
    if (raw_accel_1 >= raw_accel_2 || raw_accel_2 < 1) {
      ratio = INT16_MAX;
    } else if (raw_accel_1 <= -raw_accel_2) {
      ratio = INT16_MIN;
    } else {
      ratio = __SSAT(((q31_t)raw_accel_1 << 15) / raw_accel_2, 16);
    }

    // Per https://www.dsprelated.com/showarticle/1052.php, a reasonable
    // approximation of atan2(a,b) is 0.9724 * (b/a) - 0.1919 * x^3
    q31_t factor1 = ((q31_t)ratio * 0x0000F8EF) >> 16;  // 0.9724 * ratio
    q31_t factor2 = ((q31_t)ratio * ratio) >> 16;       // ratio^2
    q31_t factor3 = ((q31_t)ratio * 0x00003120) >> 16;  // 0.1919 * ratio
    q31_t factor4 = (factor2 * factor3) >> 16;          // 0.1919 * ratio^3
    q31_t angle_accel = factor1 - factor4;  // 0.9724 * ratio - 0.1919 * ratio^3

    // The gyroscope measures angular speed, so we need to multiply it by
    // the elapsed time and add it to the last known angle from last iteration.
    uint32_t ticks = HAL_GetTick();
    uint32_t elapsed_time = ticks - prev_ticks_;
    q31_t delta_gyro = (q31_t)raw_gyro * elapsed_time;
    q31_t prev_angle = ((q31_t)angle_) << 7;
    q31_t angle_gyro = (prev_angle + delta_gyro) >> 7;
    prev_ticks_ = ticks;

    // The gyroscope is less succeptible to disturbances, compared to
    // the accelerometers. The gyroscopes' weakness is that it drifts
    // over the long run. Hence, we setup a complimentary filter such
    // that we trust the gyro in the short run and the accelerometer in
    // the long run.
    const uint16_t GYRO_WEIGHT = 64225;
    const uint16_t ACCEL_WEIGHT = 65536 - 64225;
    angle_ = __SSAT(
        (angle_gyro * GYRO_WEIGHT + angle_accel * ACCEL_WEIGHT) >> 16, 16);

    //SEGGER_RTT_printf(0, "%d %d %d\n", angle_accel, angle_gyro, angle_);

    // static int debug_count = 0;
    // debug_count++;
    // if (debug_count % 100 == 0) {
    //   SEGGER_RTT_printf(
    //       0,
    //       "IMU data:\n  Raw: %d %d %d\n  Ratio: %d\n  Angle accel: "
    //       "%d\n  Angle gyro: (%d %d) %d\n  Net angle: %d\n",
    //       raw_accel_1, raw_accel_2, raw_gyro, ratio, angle_accel, delta_gyro,
    //       prev_angle, angle_gyro, angle_);
    // }
  }
  return angle_;
}
