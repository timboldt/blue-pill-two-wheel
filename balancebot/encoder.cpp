extern "C" {
#include <stm32f1xx_ll_tim.h>
#include "SEGGER_RTT.h"
#include "stm32f1xx.h"
#include "stm32f1xx_ll_gpio.h"
}

#include "encoder.h"

Encoder Encoder::encoders[] = {Encoder(Encoder::LEFT_ENCODER), Encoder(Encoder::RIGHT_ENCODER)};

Encoder::Encoder(uint8_t encoder_id) {
  encoder_id_ = encoder_id;
}

uint8_t Encoder::encoder_id() const { return encoder_id_; }

q15_t Encoder::speed() const { return 42; }

void Encoder::init_hardware() {
    // TODO XXX
}


Encoder* Encoder::get_encoder(uint8_t encoder_id) {
  for (Encoder& encoder : encoders) {
    if (encoder.encoder_id() == encoder_id) {
      return &encoder;
    }
  }
  return nullptr;
}
