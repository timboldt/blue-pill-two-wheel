#ifndef BLUEPILL2WHEEL_WHEEL_H
#define BLUEPILL2WHEEL_WHEEL_H

extern "C" {
#include <arm_math.h>
}

#include <cstdint>

#include "encoder.h"
#include "motor.h"

class Wheel {
 public:
  enum WheelId { LEFT_WHEEL, RIGHT_WHEEL };

  // Wheel ID determines which hardware devices to use.
  Wheel(WheelId wheel_id);

  WheelId wheel_id() const;

  void set_target_speed(q15_t speed);
  q15_t target_speed() const;
  q15_t actual_speed() const;

  void update();

  static void init_hardware();
  static Wheel* get_wheel(uint8_t wheel_id);

 private:
  WheelId wheel_id_;
  q15_t target_speed_;
  q15_t actual_speed_;
  arm_pid_instance_q15 pid_;
  Motor motor_;
  Encoder encoder_;

  static Wheel wheels[];
};

#endif  // BLUEPILL2WHEEL_WHEEL_H
