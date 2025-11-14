#ifndef MCAL_EXT_INTERRUPT_DRIVER_INCLUDE_EXT_INTERRUPT_H_
#define MCAL_EXT_INTERRUPT_DRIVER_INCLUDE_EXT_INTERRUPT_H_

#include "../../LIB/std_types.h"

// External interrupt handler definition
#define EXT_INTERRUPT(INT,STATE,CONTROL) EXT_##INT##_init(STATE,CONTROL)

#define ALLOW_NESTING_INTERRUPT FALSE

// Interrupt state data type declaration ( USING MCUCR )
typedef enum{
	LOW_LEVEL, ANY_CHANGE, FALLING_EDGE, RISING_EDGE
}INT_CONTROL;


typedef enum{
	DISABLE, ENABLE
}INT_STATE;

// Enable/Disable GIE bit in SREG register
void EXT_interrupt_GIE_state(INT_STATE state);

// initialize interrupt 0
void EXT_INT0_init(INT_STATE state, INT_CONTROL ctrl);

// initialize interrupt 1
void EXT_INT1_init(INT_STATE state, INT_CONTROL ctrl);

// initialize interrupt 2
void EXT_INT2_init(INT_STATE state, INT_CONTROL ctrl);

// function set callback function to call in interrup0 ISR
void EXT_int0_set_cb( void (*cb)(void) );

// function set callback function to call in interrup1 ISR
void EXT_int1_set_cb( void (*cb)(void) );

// function set callback function to call in interrup2 ISR
void EXT_int2_set_cb( void (*cb)(void) );

#endif // MCAL_EXT_INTERRUPT_DRIVER_INCLUDE_EXT_INTERRUPT_H_ 
