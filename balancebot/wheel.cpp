#include "wheel.h"

const uint16_t UPDATES_PER_SECOND = 100;
const uint16_t PID_SCALE_FACTOR = 256;
const uint16_t PID_KP = 10;
const uint16_t PID_KI = 0;
const uint16_t PID_KD = 0;
const uint16_t ENCODER_SCALE_FACTOR = 1;

Wheel Wheel::wheels[] = {Wheel(Wheel::LEFT_WHEEL), Wheel(Wheel::RIGHT_WHEEL)};

Wheel::Wheel(WheelId wheel_id) : motor_(wheel_id), encoder_(wheel_id) {
  // TODO: Specify actual pins instead of assuming the ids match.
  wheel_id_ = wheel_id;
  target_speed_ = 0;
  actual_speed_ = 0;
  pid_.Kp = INT16_MAX / PID_SCALE_FACTOR * PID_KP;
  pid_.Ki = INT16_MAX / PID_SCALE_FACTOR / UPDATES_PER_SECOND * PID_KI;
  pid_.Kd = INT16_MAX / PID_SCALE_FACTOR * UPDATES_PER_SECOND * PID_KD;
  arm_pid_init_q15(&pid_, 1);
}

Wheel::WheelId Wheel::wheel_id() const { return wheel_id_; }

void Wheel::set_target_speed(q15_t speed) { target_speed_ = speed; }

q15_t Wheel::target_speed() const { return target_speed_; }
q15_t Wheel::actual_speed() const { return actual_speed_; }

void Wheel::update() {
  actual_speed_ = (q15_t)__SSAT(
      ((q31_t)encoder_.counter_delta() * ENCODER_SCALE_FACTOR), 16);
  q15_t pid_output = arm_pid_q15(&pid_, target_speed_ - actual_speed_);
  q15_t power = (q15_t)__SSAT(((q31_t)pid_output * PID_SCALE_FACTOR), 16);
  motor_.set_power(power);
}

void Wheel::init_hardware() {
  Motor::init_hardware();
  Encoder::init_hardware();
}

Wheel* Wheel::get_wheel(uint8_t wheel_id) { return &wheels[wheel_id]; }
