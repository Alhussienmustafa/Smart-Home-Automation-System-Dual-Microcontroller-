#include "DIO_interface.h"
#include "DIO_private.h"
#include "../../LIB/bit_math.h"


void DIO_voidSetPortDir(u8 Copy_u8PortNum, u8 Copy_u8PortDirection) {
	if (Copy_u8PortNum >= NUM_OF_PORTS) {
		return;
	}

	switch (Copy_u8PortNum) {
	case PORTA_ID:
		DDRA = Copy_u8PortDirection;
		break;
	case PORTB_ID:
		DDRB = Copy_u8PortDirection;
		break;
	case PORTC_ID:
		DDRC = Copy_u8PortDirection;
		break;
	case PORTD_ID:
		DDRD = Copy_u8PortDirection;
		break;
	}
}
void DIO_voidSetPortValue(u8 Copy_u8PortNum, u8 Copy_u8PortValue) {
	if (Copy_u8PortNum >= NUM_OF_PORTS) {
		return;
	}

	switch (Copy_u8PortNum) {
	case PORTA_ID:
		PORTA = Copy_u8PortValue;
		break;
	case PORTB_ID:
		PORTB = Copy_u8PortValue;
		break;
	case PORTC_ID:
		PORTC = Copy_u8PortValue;
		break;
	case PORTD_ID:
		PORTD = Copy_u8PortValue;
		break;
	}
}


void DIO_voidSetPinDir(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8PinDirection) {
	if ((Copy_u8PinNum >= NUM_OF_PINS_PER_PORT) || (Copy_u8PortNum >= NUM_OF_PORTS)) {
		/* Do nothing */
		return;
	}

	switch (Copy_u8PortNum) {
	case PORTA_ID:
		if (Copy_u8PinDirection == PIN_OUTPUT) SET_BIT(DDRA, Copy_u8PinNum);
		else CLEAR_BIT(DDRA, Copy_u8PinNum);
		break;
	case PORTB_ID:
		if (Copy_u8PinDirection == PIN_OUTPUT) SET_BIT(DDRB, Copy_u8PinNum);
		else CLEAR_BIT(DDRB, Copy_u8PinNum);
		break;
	case PORTC_ID:
		if (Copy_u8PinDirection == PIN_OUTPUT) SET_BIT(DDRC, Copy_u8PinNum);
		else CLEAR_BIT(DDRC, Copy_u8PinNum);
		break;
	case PORTD_ID:
		if (Copy_u8PinDirection == PIN_OUTPUT) SET_BIT(DDRD, Copy_u8PinNum);
		else CLEAR_BIT(DDRD, Copy_u8PinNum);
		break;
	}
}
void DIO_voidSetPinValue(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8PinValue) {
	if ((Copy_u8PinNum >= NUM_OF_PINS_PER_PORT) || (Copy_u8PortNum >= NUM_OF_PORTS)) {
		/* Do nothing */
		return;
	}

	switch (Copy_u8PortNum) {
	case PORTA_ID:
		if (Copy_u8PinValue == PIN_HIGH) SET_BIT(PORTA, Copy_u8PinNum);
		else CLEAR_BIT(PORTA, Copy_u8PinNum);
		break;
	case PORTB_ID:
		if (Copy_u8PinValue == PIN_HIGH) SET_BIT(PORTB, Copy_u8PinNum);
		else CLEAR_BIT(PORTB, Copy_u8PinNum);
		break;
	case PORTC_ID:
		if (Copy_u8PinValue == PIN_HIGH) SET_BIT(PORTC, Copy_u8PinNum);
		else CLEAR_BIT(PORTC, Copy_u8PinNum);
		break;
	case PORTD_ID:
		if (Copy_u8PinValue == PIN_HIGH) SET_BIT(PORTD, Copy_u8PinNum);
		else CLEAR_BIT(PORTD, Copy_u8PinNum);
		break;
	}
}


void DIO_voidTogglePin(u8 Copy_u8PortNum, u8 Copy_u8PinNum) {
	if ((Copy_u8PinNum >= NUM_OF_PINS_PER_PORT) || (Copy_u8PortNum >= NUM_OF_PORTS)) {
		return;
	}

	switch (Copy_u8PortNum) {
	case PORTA_ID:
		TOGGLE_BIT(PORTA, Copy_u8PinNum);
		break;
	case PORTB_ID:
		TOGGLE_BIT(PORTB, Copy_u8PinNum);
		break;
	case PORTC_ID:
		TOGGLE_BIT(PORTC, Copy_u8PinNum);
		break;
	case PORTD_ID:
		TOGGLE_BIT(PORTD, Copy_u8PinNum);
		break;
	}
}

Logical_Value DIO_readPin(u8 Copy_u8PortNum, u8 Copy_u8PinNum) {
	if ((Copy_u8PinNum >= NUM_OF_PINS_PER_PORT) || (Copy_u8PortNum >= NUM_OF_PORTS)) {
		return PIN_LOW;
	}

	switch (Copy_u8PortNum) {
	case PORTA_ID:
		return BIT_IS_SET(PINA, Copy_u8PinNum) ? PIN_HIGH : PIN_LOW;
	case PORTB_ID:
		return BIT_IS_SET(PINB, Copy_u8PinNum) ? PIN_HIGH : PIN_LOW;
	case PORTC_ID:
		return BIT_IS_SET(PINC, Copy_u8PinNum) ? PIN_HIGH : PIN_LOW;
	case PORTD_ID:
		return BIT_IS_SET(PIND, Copy_u8PinNum) ? PIN_HIGH : PIN_LOW;
	}

	return PIN_LOW;
}

u8 DIO_readPort(u8 Copy_u8PortNum) {
	if (Copy_u8PortNum >= NUM_OF_PORTS) {
		return 0;
	}

	switch (Copy_u8PortNum) {
	case PORTA_ID: return PINA;
	case PORTB_ID: return PINB;
	case PORTC_ID: return PINC;
	case PORTD_ID: return PIND;
	}

	return 0;
}

