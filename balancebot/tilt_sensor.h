#ifndef BLUEPILL2WHEEL_TILT_SENSOR_H
#define BLUEPILL2WHEEL_TILT_SENSOR_H

extern "C" {
#include <arm_math.h>
}

class TiltSensor {
 public:
  // Returns the tilt angle as a fraction unit fraction
  // of the distance between +/-45 degrees (straight up is 0).
  q15_t tilt_angle();

  static void init_hardware();

 private:
  q15_t angle = 0;
  uint32_t prev_ticks = 0;
};

#endif  // BLUEPILL2WHEEL_TILT_SENSOR_H
