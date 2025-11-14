#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include "../../LIB/std_types.h"

/* define number of ports and pins in AVR ATmega32 GPIO registers*/
#define NUM_OF_PINS_PER_PORT 8
#define NUM_OF_PORTS 4

/* define port ID */
#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

/* Define pins ID */
#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

/* Pin direction declaration */
typedef enum{
	PIN_INPUT, PIN_OUTPUT
}DIO_PinDirectionType;

/* Port direction declaration */
typedef enum{
	PORT_INPUT, PORT_OUTPUT = 0xff
}DIO_PortDirectionType;

typedef enum {
	PIN_LOW,PIN_HIGH
}DIO_PinValue;

typedef enum {
PORT_LOW,PORT_HIGH=0xff
}DIO_PortValue;


void DIO_voidSetPortDir(u8 Copy_u8PortNum,u8 Copy_u8PortDirection);
void DIO_voidSetPortValue(u8 Copy_u8PortNum,u8 Copy_u8PortValue);


void DIO_voidSetPinDir(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinDirection);
void DIO_voidSetPinValue(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 Copy_u8PinValue);


void DIO_voidTogglePin(u8 Copy_u8PortNum,u8 Copy_u8PinNum);

Logical_Value DIO_readPin(u8 Copy_u8PortNum,u8 Copy_u8PinNum);

u8 DIO_readPort(u8 Copy_u8PortNum);


#endif /* MCAL_DIO_DRIVER_DIO_INTERFACE_H_ */


