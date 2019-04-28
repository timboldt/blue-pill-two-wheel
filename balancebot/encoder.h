#ifndef BLUEPILL2WHEEL_ENCODER_H
#define BLUEPILL2WHEEL_ENCODER_H

#include <arm_math.h>
#include <cstdint>

class Encoder {
 public:
  const static uint8_t LEFT_ENCODER = 1;
  const static uint8_t RIGHT_ENCODER = 2;

  // Encoder ID determines which timer is used.
  Encoder(uint8_t encoder_id);

  uint8_t encoder_id() const;

  // TODO: Figure this out. Do we need both odometer (a 32-bit value) and
  // speed (a time-based 16-bit value)? Where does time come from here?
  q15_t speed() const;

  static void init_hardware();
  static Encoder* get_encoder(uint8_t encoder_id);

 private:
  uint8_t encoder_id_;

  static Encoder encoders[];
};

#endif  // BLUEPILL2WHEEL_ENCODER_H
