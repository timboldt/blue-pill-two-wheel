#include "wheel.h"

Wheel Wheel::wheels[] = {Wheel(Wheel::LEFT_WHEEL), Wheel(Wheel::RIGHT_WHEEL)};

Wheel::Wheel(WheelId wheel_id) : motor_(wheel_id), encoder_(wheel_id) {
  // TODO: Specify actual pins instead of assuming the ids match.
  wheel_id_ = wheel_id;
  target_speed_ = 0;
  actual_speed_ = 0;
}

Wheel::WheelId Wheel::wheel_id() const { return wheel_id_; }

void Wheel::set_target_speed(q15_t speed) { target_speed_ = speed; }

q15_t Wheel::target_speed() const { return target_speed_; }
q15_t Wheel::actual_speed() const { return actual_speed_; }

void Wheel::init_hardware() {
  Motor::init_hardware();
  Encoder::init_hardware;
}

Wheel* Wheel::get_wheel(uint8_t wheel_id) { return &wheels[wheel_id]; }
