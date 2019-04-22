//
// Created by tim on 4/21/19.
//

#ifndef BLUEPILL2WHEEL_MOTOR_H
#define BLUEPILL2WHEEL_MOTOR_H

#include <arm_math.h>
#include <cstdint>

class Motor {
public:
    void set_speed(q15_t speed);

private:
    uint8_t  channel_;

public:
    static void init_hardware();
    static Motor* get_motor(uint8_t motor_id);
};

#endif //BLUEPILL2WHEEL_MOTOR_H
