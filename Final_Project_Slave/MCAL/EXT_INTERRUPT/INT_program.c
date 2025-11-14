#include "INT_interface.h"
#include "INT_private.h"
#include "../../LIB/bit_math.h"
#include "../../LIB/std_types.h"
#include "../DIO_DRIVER/DIO_interface.h"
#include <avr/interrupt.h>

// Global Callback pointers
static void (*INT0_callback)(void) = NULL;
static void (*INT1_callback)(void) = NULL;
static void (*INT2_callback)(void) = NULL;

// Enable or disable global interrupt flag (I-bit)
void EXT_interrupt_GIE_state(INT_STATE state) {
    if (state == ENABLE) {
        SET_BIT(SREG, I_BIT);
    } else {
        CLEAR_BIT(SREG, I_BIT);
    }
}

// ================= INT0 =================
void EXT_INT0_init(INT_STATE state, INT_CONTROL ctrl) {
    if (state == ENABLE) {
        SET_BIT(GICR, INT0);
    } else {
        CLEAR_BIT(GICR, INT0);
    }

    switch (ctrl) {
        case LOW_LEVEL:
            CLEAR_BIT(MCUCR, ISC00);
            CLEAR_BIT(MCUCR, ISC01);
            break;
        case ANY_CHANGE:
            SET_BIT(MCUCR, ISC00);
            CLEAR_BIT(MCUCR, ISC01);
            break;
        case FALLING_EDGE:
            CLEAR_BIT(MCUCR, ISC00);
            SET_BIT(MCUCR, ISC01);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, ISC00);
            SET_BIT(MCUCR, ISC01);
            break;
    }
}

void EXT_int0_set_cb(void (*cb)(void)) {
	if(cb != NULL )
    INT0_callback = cb;
}

ISR(INT0_vect) {
    if (INT0_callback != NULL) {
        INT0_callback();
    }
}

// ================= INT1 =================
void EXT_INT1_init(INT_STATE state, INT_CONTROL ctrl) {
    if (state == ENABLE) {
        SET_BIT(GICR, INT1);
    } else {
        CLEAR_BIT(GICR, INT1);
    }

    switch (ctrl) {
        case LOW_LEVEL:
            CLEAR_BIT(MCUCR, ISC10);
            CLEAR_BIT(MCUCR, ISC11);
            break;
        case ANY_CHANGE:
            SET_BIT(MCUCR, ISC10);
            CLEAR_BIT(MCUCR, ISC11);
            break;
        case FALLING_EDGE:
            CLEAR_BIT(MCUCR, ISC10);
            SET_BIT(MCUCR, ISC11);
            break;
        case RISING_EDGE:
            SET_BIT(MCUCR, ISC10);
            SET_BIT(MCUCR, ISC11);
            break;
    }
}

void EXT_int1_set_cb(void (*cb)(void)) {
    INT1_callback = cb;
}

ISR(INT1_vect) {
    if (INT1_callback != NULL) {
        INT1_callback();
    }
}

// ================= INT2 =================
void EXT_INT2_init(INT_STATE state, INT_CONTROL ctrl) {
    if (state == ENABLE) {
        SET_BIT(GICR, INT2);
    } else {
        CLEAR_BIT(GICR, INT2);
    }

    if (ctrl == FALLING_EDGE) {
        CLEAR_BIT(MCUCSR, ISC2);
    } else if (ctrl == RISING_EDGE) {
        SET_BIT(MCUCSR, ISC2);
    }
}

void EXT_int2_set_cb(void (*cb)(void)) {
    INT2_callback = cb;
}

ISR(INT2_vect) {
    if (INT2_callback != NULL) {
        INT2_callback();
    }
}
