#ifndef BLUEPILL2WHEEL_MOTOR_H
#define BLUEPILL2WHEEL_MOTOR_H

#include <arm_math.h>
#include <cstdint>

class Motor {
 public:
  const static uint8_t LEFT_MOTOR = 1;
  const static uint8_t RIGHT_MOTOR = 2;

  // Motor ID determines which timer channel is used for PWM.
  Motor(uint8_t motor_id);

  uint8_t motor_id() const;

  // Power is a value between -1 and +1 exclusive.
  void set_power(q15_t power);
  q15_t power() const;

  static void init_hardware();
  static Motor* get_motor(uint8_t motor_id);

 private:
  uint8_t motor_id_;
  q15_t power_;

  static Motor motors[];
};

#endif  // BLUEPILL2WHEEL_MOTOR_H
