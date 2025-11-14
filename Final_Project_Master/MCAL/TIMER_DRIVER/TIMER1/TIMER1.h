#ifndef TIMER1_H_
#define TIMER1_H_

#include "TIMER1_config.h"

void TIMER1_initNormal(TIMER1_CLOCK_SELECT clk);

void TIMER1_initCTC(TIMER1_CTC_MODE_SELECT mode, TIMER1_CLOCK_SELECT clk, u16 compValue);

void TIMER1_initFastPWM_ICR1(TIMER1_PWM_MODE_SELECT mode, TIMER1_CLOCK_SELECT clk, u16 top);

void TIMER1_setDutyCycleA(u16 duty);

void TIMER1_setDutyCycleB(u16 duty);

void TIMER1_OF_setCallback(void (*cb)(void));

void TIMER1_OC_A_setCallback(void (*cb)(void));

void TIMER1_OC_B_setCallback(void (*cb)(void));

#endif /* TIMER1_H_ */
