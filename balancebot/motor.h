//
// Created by tim on 4/21/19.
//

#ifndef BLUEPILL2WHEEL_MOTOR_H
#define BLUEPILL2WHEEL_MOTOR_H

#include <cstdint>

class Motor {
public:
    void set_speed(int16_t speed);

public:
    static void init_hardware();
    static Motor* get_motor(uint8_t motor_id);
};

#endif //BLUEPILL2WHEEL_MOTOR_H
