//
// Created by tim on 4/17/19.
//

#ifndef BLUEPILL2WHEEL_BALANCE_MAIN_H
#define BLUEPILL2WHEEL_BALANCE_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
    void BALANCE_init_hardware();
    void BALANCE_do_work(void const * argument);
#ifdef __cplusplus
};
#endif

#endif //BLUEPILL2WHEEL_BALANCE_MAIN_H
