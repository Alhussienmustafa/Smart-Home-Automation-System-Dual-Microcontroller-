#ifndef TIMER2_H_
#define TIMER2_H_

#include "TIMER2_config.h"

void TIMER2_initNormal(TIMER2_CLOCK_SELECT clk);

void TIMER2_initCTC(TIMER2_CTC_MODE_SELECT mode, TIMER2_CLOCK_SELECT clk, u8 compValue);

void TIMER2_initFastPWM(TIMER2_PWM_MODE_SELECT mode, TIMER2_CLOCK_SELECT clk);

void TIMER2_initPhaseCorrectPWM(TIMER2_PWM_MODE_SELECT mode, TIMER2_CLOCK_SELECT clk);

void TIMER2_setDutyCycle(u8 duty);

void TIMER2_OF_setCallback(void (*cb)(void));

void TIMER2_OC_setCallback(void (*cb)(void));

#endif /* TIMER2_H_ */
