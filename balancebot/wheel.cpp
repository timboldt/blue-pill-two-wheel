#include "wheel.h"

extern "C" {
#include "SEGGER_RTT.h"
}

const uint16_t UPDATES_PER_SECOND = 100;
const uint16_t PID_KP = 100;
const uint16_t PID_KI = 0;
const uint16_t PID_KD = 0;
const uint16_t ENCODER_SCALE_FACTOR = 512;

Wheel Wheel::wheels[] = {Wheel(Wheel::LEFT_WHEEL), Wheel(Wheel::RIGHT_WHEEL)};

Wheel::Wheel(WheelId wheel_id) : motor_(wheel_id), encoder_(wheel_id) {
  // TODO: Specify actual pins instead of assuming the ids match.
  wheel_id_ = wheel_id;
  target_speed_ = 0;
  actual_speed_ = 0;
  pid_.Kp = PID_KP << 24;
  pid_.Ki = (PID_KI << 24) / UPDATES_PER_SECOND;
  pid_.Kd = (PID_KD << 24) * UPDATES_PER_SECOND;
  arm_pid_init_q31(&pid_, 1);
}

Wheel::WheelId Wheel::wheel_id() const { return wheel_id_; }

void Wheel::set_target_speed(q15_t speed) { target_speed_ = speed; }

q15_t Wheel::target_speed() const { return target_speed_; }
q15_t Wheel::actual_speed() const { return actual_speed_; }

void Wheel::update() {
  if (wheel_id_ == RIGHT_WHEEL) {
    actual_speed_ = (q31_t)encoder_.counter_delta() * ENCODER_SCALE_FACTOR;
    q31_t pid_output = arm_pid_q31(&pid_, (q31_t)target_speed_ - actual_speed_);
    q15_t power = (q15_t)__SSAT(pid_output, 16);
    SEGGER_RTT_printf(0, "%d %ld %d %d\n", target_speed_, actual_speed_,
                      motor_.power(), power);
    motor_.set_power(power);
  }
}

void Wheel::init_hardware() {
  Motor::init_hardware();
  Encoder::init_hardware();
}

Wheel* Wheel::get_wheel(uint8_t wheel_id) { return &wheels[wheel_id]; }
