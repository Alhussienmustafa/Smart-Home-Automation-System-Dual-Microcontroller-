#ifndef MCAL_TIMERS_DRIVER_TIMER0_H_
#define MCAL_TIMERS_DRIVER_TIMER0_H_

#include "../../../LIB/std_types.h"
#include "TIMER0_config.h"

#define TIMER0_PRELOAD 0
#define TIMER0_OF_INTERRUPT_ENABLE True
#define TIMER0_CTC_INTERRUPT_ENABLE True


typedef enum{
	OC0_CTC_NORTMAL, TOGGLE_OC0, CLEAR_OC0, SET_OC0
}TIMER0_CTC_MODE_SELECT;

void TIMER0_OF_init(TIMER0_CLOCK_SELECT clock);

void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT mode, TIMER0_CLOCK_SELECT clock, u8 compValue);

void TIMER0_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, TIMER0_CLOCK_SELECT clock);
void TIMER0_PHASE_CORRECT_PWM_init(FAST_PWM_MODE_SELECT mode, TIMER0_CLOCK_SELECT clock);
void TIMER0_FAST_PWM_set_dutyCycle(u8 dutyCycle);
void TIMER0_PHASECORRECT_set_dutyCycle(u8 dutyCycle);

void TIMER0_OF_set_cb(void (*cb)(void));
void TIMER0_CTC_set_cb(void (*cb)(void));

#endif /* MCAL_TIMERS_DRIVER_TIMER0_H_ */
