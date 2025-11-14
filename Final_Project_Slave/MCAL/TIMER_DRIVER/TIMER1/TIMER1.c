#include "TIMER1.h"
#include "TIMER1_private.h"
#include <avr/interrupt.h>
#include "../../../LIB/bit_math.h"

// global callback interrupt
static void (*TIMER1_OF_cb)(void)   = 0;
static void (*TIMER1_OC_A_cb)(void) = 0;
static void (*TIMER1_OC_B_cb)(void) = 0;

static void TIMER1_clockSelect(TIMER1_CLOCK_SELECT clk){
	switch(clk){
	case T1_NO_CLOCK:
		CLEAR_BIT(TCCR1B,CS12);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS10); break;

	case T1_NO_PRESCALER:
		CLEAR_BIT(TCCR1B,CS12);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS10); break;

	case T1_PRESCALER_8:
		CLEAR_BIT(TCCR1B,CS12);
		SET_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS10); break;

	case T1_PRESCALER_64:
		CLEAR_BIT(TCCR1B,CS12);
		SET_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS10); break;

	case T1_PRESCALER_256:
		SET_BIT(TCCR1B,CS12);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS10); break;

	case T1_PRESCALER_1024:
		SET_BIT(TCCR1B,CS12);
		CLEAR_BIT(TCCR1B,CS11);
		SET_BIT(TCCR1B,CS10); break;
	}
}

void TIMER1_initNormal(TIMER1_CLOCK_SELECT clk){
    // Normal mode (WGM13:0 = 0000)
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    SET_BIT(TIMSK, TOIE1); // Enable overflow interrupt
    TIMER1_clockSelect(clk);
}

void TIMER1_initCTC(TIMER1_CTC_MODE_SELECT mode, TIMER1_CLOCK_SELECT clk, u16 compValue){
    // CTC using OCR1A as TOP (WGM12=1, others=0)
    TCCR1A = 0;
    TCCR1B = (1<<WGM12);
    TCNT1 = 0;
    OCR1A = compValue;

    switch(mode){
    case OC1_DISCONNECTED:
    	CLEAR_BIT(TCCR1A,COM1A1);
    	CLEAR_BIT(TCCR1A,COM1A0); break;

    case TOGGLE_OC1:
    	CLEAR_BIT(TCCR1A,COM1A1);
    	SET_BIT(TCCR1A,COM1A0); break;

    case CLEAR_OC1:
    	SET_BIT(TCCR1A,COM1A1);
    	CLEAR_BIT(TCCR1A,COM1A0); break;

    case SET_OC1:
    	SET_BIT(TCCR1A,COM1A1);
    	SET_BIT(TCCR1A,COM1A0); break;
    }

    SET_BIT(TIMSK, OCIE1A); // Enable compare A interrupt
    TIMER1_clockSelect(clk);
}

void TIMER1_initFastPWM_ICR1(TIMER1_PWM_MODE_SELECT mode, TIMER1_CLOCK_SELECT clk, u16 top){
    // Fast PWM, ICR1 as TOP (WGM13:0 = 1110)
    TCCR1A = (1<<WGM11);
    TCCR1B = (1<<WGM12) | (1<<WGM13);

    ICR1 = top;
    OCR1A = 0;
    OCR1B = 0;

    switch(mode){
    case T1_NON_INVERTING:
        SET_BIT(TCCR1A, COM1A1);
        CLEAR_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1B1);
        CLEAR_BIT(TCCR1A, COM1B0);  break;

    case T1_INVERTING:
        SET_BIT(TCCR1A, COM1A1);
        SET_BIT(TCCR1A, COM1A0);
        SET_BIT(TCCR1A, COM1B1);
        SET_BIT(TCCR1A, COM1B0);    break;
    }

    TIMER1_clockSelect(clk);
}

void TIMER1_setDutyCycleA(u16 duty){
    OCR1A = duty;
}

void TIMER1_setDutyCycleB(u16 duty){
    OCR1B = duty;
}

// Callback setters
void TIMER1_OF_setCallback(void (*cb)(void)){
	TIMER1_OF_cb = cb;
}

void TIMER1_OC_A_setCallback(void (*cb)(void)){
	TIMER1_OC_A_cb = cb;
}

void TIMER1_OC_B_setCallback(void (*cb)(void)){
	TIMER1_OC_B_cb = cb;
}

// ISR
ISR(TIMER1_OVF_vect){
	if(TIMER1_OF_cb) TIMER1_OF_cb();
}

ISR(TIMER1_COMPA_vect){
	if(TIMER1_OC_A_cb) TIMER1_OC_A_cb();
}

ISR(TIMER1_COMPB_vect){
	if(TIMER1_OC_B_cb) TIMER1_OC_B_cb();
}
