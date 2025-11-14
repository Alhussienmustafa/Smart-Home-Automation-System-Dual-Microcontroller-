#ifndef MCAL_TWI_DRIVER_TWI_PRIVATE_H_
#define MCAL_TWI_DRIVER_TWI_PRIVATE_H_

#include "../../LIB/std_types.h"

/* TWI Registers (ATmega32) */
#define TWBR    (*(volatile u8*)0x20)
#define TWSR    (*(volatile u8*)0x21)
#define TWAR    (*(volatile u8*)0x22)
#define TWDR    (*(volatile u8*)0x23)
#define TWCR    (*(volatile u8*)0x56)

/* TWI Control Register (TWCR) Bits */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
#define TWIE    0

/* TWI Status Register (TWSR) Bits */
#define TWPS0   0
#define TWPS1   1

/* TWI Address Register (TWAR) Bits */
#define TWGCE   0

/* Useful Masks */
#define STATUS_MASK     0xF8
#define PRESCALER_MASK  0x03

#endif /* MCAL_TWI_DRIVER_TWI_PRIVATE_H_ */
