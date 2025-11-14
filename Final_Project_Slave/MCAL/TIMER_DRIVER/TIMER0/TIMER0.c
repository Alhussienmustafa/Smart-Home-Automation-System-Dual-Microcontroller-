#include "TIMER0.h"
#include "TIMER0_private.h"
#include "../../../LIB/bit_math.h"
#include "../../DIO_DRIVER/DIO_interface.h"
#include "../../EXT_INTERRUPT/INT_interface.h"
#include <avr/interrupt.h>

void (*TIMER_OF_cb)(void) =  NULL_PTR;
void (*TIMER_CTC_cb)(void) =  NULL_PTR;

static void TIMER0_clockSelect(TIMER0_CLOCK_SELECT clock);

/*
 * 	NO_CLOCK, NO_PRESCALER, PRESCALER_8, PRESCALER_64, PRESCALER_256,PRESCALER_1024
 *
 */
void TIMER0_clockSelect(TIMER0_CLOCK_SELECT clock){
	switch(clock){
	case T0_NO_CLOCK:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;
	case T0_NO_PRESCALER:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;

	case T0_PRESCALER_8:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case T0_PRESCALER_64:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;

	case T0_PRESCALER_256:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case T0_PRESCALER_1024:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;
	}
}

void TIMER0_OF_init(TIMER0_CLOCK_SELECT clock){
	TCNT0 = TIMER0_PRELOAD;
	SET_BIT(TCCR0, FOC0);
	CLEAR_BIT(TCCR0, WGM01);
	CLEAR_BIT(TCCR0, WGM00);

	TIMER0_clockSelect(clock);

#if (TIMER0_OF_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, TOIE0);
	EXT_interrupt_GIE_state(ENABLE);
#else
	while( BIT_IS_CLEAR(TIFR, TOV0) );
	SET_BIT(TIFR, TOV0);
	TCNT0 = 0;
#endif

}

void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT mode, TIMER0_CLOCK_SELECT clock, u8 compValue){

	TCNT0 = TIMER0_PRELOAD;
	OCR0 = compValue;

	SET_BIT(TCCR0, FOC0);
	SET_BIT(TCCR0, WGM01);
	CLEAR_BIT(TCCR0, WGM00);

	switch(mode){
	case OC0_CTC_NORTMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case TOGGLE_OC0:
		CLEAR_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	case CLEAR_OC0:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;
	case SET_OC0:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		break;
	}

	TIMER0_clockSelect(clock);

#if(TIMER0_CTC_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, OCIE0);
	EXT_interrupt_GIE_state(ENABLE);
#else
	while(BIT_IS_CLEAR(TIFR, OCF0));
	SET_BIT(TIFR, OCF0);
	TCCR0 = 0;
#endif
}

void TIMER0_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, TIMER0_CLOCK_SELECT clock){
    OCR0 = 0;  // start with 0% duty cycle

    // Fast PWM (WGM01=1, WGM00=1)
    SET_BIT(TCCR0, WGM00);
    SET_BIT(TCCR0, WGM01);

    // Clock select
    TIMER0_clockSelect(clock);

    // Compare Output Mode
    switch(mode){
    case FAST_PWM_NORMAL: // OC0 disconnected
        CLEAR_BIT(TCCR0, COM01);
        CLEAR_BIT(TCCR0, COM00);
        break;
    case NON_INVERTING_MODE:
        SET_BIT(TCCR0, COM01);
        CLEAR_BIT(TCCR0, COM00);
        break;
    case INVERTING_MODE:
        SET_BIT(TCCR0, COM01);
        SET_BIT(TCCR0, COM00);
        break;
    }
}

void TIMER0_PHASE_CORRECT_PWM_init(FAST_PWM_MODE_SELECT mode, TIMER0_CLOCK_SELECT clock){
    OCR0 = 0;  // start with 0% duty cycle

    // Phase Correct PWM (WGM01=0, WGM00=1)
    CLEAR_BIT(TCCR0, WGM01);
    SET_BIT(TCCR0, WGM00);

    // Clock select
    TIMER0_clockSelect(clock);

    // Compare Output Mode
    switch(mode){
    case FAST_PWM_NORMAL: // OC0 disconnected
        CLEAR_BIT(TCCR0, COM01);
        CLEAR_BIT(TCCR0, COM00);
        break;
    case NON_INVERTING_MODE:
        SET_BIT(TCCR0, COM01);
        CLEAR_BIT(TCCR0, COM00);
        break;
    case INVERTING_MODE:
        SET_BIT(TCCR0, COM01);
        SET_BIT(TCCR0, COM00);
        break;
    }
}

void TIMER0_FAST_PWM_set_dutyCycle(u8 dutyCycle){
	OCR0 = dutyCycle;
}

void TIMER0_PHASECORRECT_set_dutyCycle(u8 dutyCycle){
	OCR0 = dutyCycle;
}

void TIMER0_OF_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_OF_cb = cb;
}

void TIMER0_CTC_set_cb(void (*cb)(void)){
	if(cb != NULL_PTR) TIMER_CTC_cb = cb;
}

ISR(TIMER0_OVF_vect){
	if(TIMER_OF_cb != NULL_PTR) TIMER_OF_cb();
}

ISR(TIMER0_COMP_vect){
	if(TIMER_CTC_cb != NULL_PTR) TIMER_CTC_cb();
}
