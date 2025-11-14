#include "TIMER2.h"
#include "TIMER2_private.h"
#include <avr/interrupt.h>
#include "../../../LIB/bit_math.h"


static void (*TIMER2_OF_cb)(void) = 0;
static void (*TIMER2_OC_cb)(void) = 0;

// Select clock
static void TIMER2_clockSelect(TIMER2_CLOCK_SELECT clk){
    switch(clk){
    case T2_NO_CLOCK:
    	CLEAR_BIT(TCCR2,CS22);
    	CLEAR_BIT(TCCR2,CS21);
    	CLEAR_BIT(TCCR2,CS20); break;

    case T2_NO_PRESCALER:
    	CLEAR_BIT(TCCR2,CS22);
    	CLEAR_BIT(TCCR2,CS21);
    	SET_BIT(TCCR2,CS20); break;

    case T2_PRESCALER_8:
    	CLEAR_BIT(TCCR2,CS22);
    	SET_BIT(TCCR2,CS21);
    	CLEAR_BIT(TCCR2,CS20); break;

    case T2_PRESCALER_32:
    	CLEAR_BIT(TCCR2,CS22);
    	SET_BIT(TCCR2,CS21);
    	SET_BIT(TCCR2,CS20); break;

    case T2_PRESCALER_64:
    	SET_BIT(TCCR2,CS22);
    	CLEAR_BIT(TCCR2,CS21);
    	CLEAR_BIT(TCCR2,CS20); break;

    case T2_PRESCALER_128:
    	SET_BIT(TCCR2,CS22);
    	CLEAR_BIT(TCCR2,CS21);
    	SET_BIT(TCCR2,CS20); break;

    case T2_PRESCALER_256:
    	SET_BIT(TCCR2,CS22);
    	SET_BIT(TCCR2,CS21);
    	CLEAR_BIT(TCCR2,CS20); break;

    case T2_PRESCALER_1024:
    	SET_BIT(TCCR2,CS22);
    	SET_BIT(TCCR2,CS21);
    	SET_BIT(TCCR2,CS20); break;

    }
}

void TIMER2_initNormal(TIMER2_CLOCK_SELECT clk){
    // Normal Mode
    CLEAR_BIT(TCCR2,WGM20);
    CLEAR_BIT(TCCR2,WGM21);
    TCNT2 = 0;

    SET_BIT(TIMSK,TOIE2); // Enable overflow interrupt
    TIMER2_clockSelect(clk);
}

void TIMER2_initCTC(TIMER2_CTC_MODE_SELECT mode, TIMER2_CLOCK_SELECT clk, u8 compValue){
    // CTC Mode
    CLEAR_BIT(TCCR2,WGM20);
    SET_BIT(TCCR2,WGM21);
    OCR2 = compValue;

    switch(mode){
    case OC2_DISCONNECTED:
    	CLEAR_BIT(TCCR2,COM21);
    	CLEAR_BIT(TCCR2,COM20); break;

    case TOGGLE_OC2:
    	CLEAR_BIT(TCCR2,COM21);
    	SET_BIT(TCCR2,COM20); break;

    case CLEAR_OC2:
    	SET_BIT(TCCR2,COM21);
    	CLEAR_BIT(TCCR2,COM20); break;

    case SET_OC2:
    	SET_BIT(TCCR2,COM21);
    	SET_BIT(TCCR2,COM20); break;

    }

    SET_BIT(TIMSK,OCIE2); // Enable compare interrupt
    TIMER2_clockSelect(clk);
}

void TIMER2_initFastPWM(TIMER2_PWM_MODE_SELECT mode, TIMER2_CLOCK_SELECT clk){
    // Fast PWM
    SET_BIT(TCCR2,WGM20);
    SET_BIT(TCCR2,WGM21);

    switch(mode){
    case T2_NON_INVERTING:
    	SET_BIT(TCCR2,COM21);
    	CLEAR_BIT(TCCR2,COM20); break;

    case T2_INVERTING:
    	SET_BIT(TCCR2,COM21);
    	SET_BIT(TCCR2,COM20); break;

    }

    TIMER2_clockSelect(clk);
}

void TIMER2_initPhaseCorrectPWM(TIMER2_PWM_MODE_SELECT mode, TIMER2_CLOCK_SELECT clk){
    // Phase Correct PWM
    SET_BIT(TCCR2,WGM20);
    CLEAR_BIT(TCCR2,WGM21);

    switch(mode){
    case T2_NON_INVERTING:
    	SET_BIT(TCCR2,COM21);
    	CLEAR_BIT(TCCR2,COM20); break;

    case T2_INVERTING:
    	SET_BIT(TCCR2,COM21);
    	SET_BIT(TCCR2,COM20); break;

    }

    TIMER2_clockSelect(clk);
}

void TIMER2_setDutyCycle(u8 duty){
    OCR2 = duty;
}

// Callbacks
void TIMER2_OF_setCallback(void (*cb)(void)){
	TIMER2_OF_cb = cb;
}

void TIMER2_OC_setCallback(void (*cb)(void)){
	TIMER2_OC_cb = cb;
}

// ISR
ISR(TIMER2_OVF_vect){
	if(TIMER2_OF_cb) TIMER2_OF_cb();
}

ISR(TIMER2_COMP_vect){
	if(TIMER2_OC_cb) TIMER2_OC_cb();
}
