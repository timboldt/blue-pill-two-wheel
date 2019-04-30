#ifndef BLUEPILL2WHEEL_TILT_SENSOR_H
#define BLUEPILL2WHEEL_TILT_SENSOR_H

//#include "main.h"

class TiltSensor {
public:
    int init(I2C_HandleTypeDef *i2c, uint16_t address);

    // Returns the tilt angle, in degrees.
    // Straight up is zero.
    int tilt_angle();

private:
    I2C_HandleTypeDef *i2c;  // Does not own.
};


#endif //BLUEPILL2WHEEL_TILT_SENSOR_H
