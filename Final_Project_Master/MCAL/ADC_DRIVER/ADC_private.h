#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#include "../../LIB/std_types.h"

// ADC Multiplexer Selection Register
#define ADMUX   (*(volatile u8*)0x27)

// ADC Control and Status Register A
#define ADCSRA  (*(volatile u8*)0x26)

// ADC Data Registers
#define ADCH    (*(volatile u8*)0x25)
#define ADCL    (*(volatile u16*)0x24)
#define ADC     (*(volatile u16*)0x24)   // Combined 16-bit result

// Special Function IO Register
#define SFIOR   (*(volatile u8*)0x50)


#define MUX0    0
#define MUX1    1
#define MUX2    2
#define MUX3    3
#define MUX4    4
#define ADLAR   5   // Left adjust result
#define REFS0   6   // Reference Selection Bit 0
#define REFS1   7   // Reference Selection Bit 1
/*
// Reference Voltage Options
#define AREF_EXTERNAL      0
#define AVCC_WITH_CAP      (1<<REFS0)
#define INTERNAL_2V56      ((1<<REFS0) | (1<<REFS1))
*/

#define ADPS0   0  // Prescaler Select Bit 0
#define ADPS1   1
#define ADPS2   2
#define ADIE    3   // Interrupt Enable
#define ADIF    4   // Interrupt Flag
#define ADATE   5   // Auto Trigger Enable
#define ADSC    6   // Start Conversion
#define ADEN    7   // ADC Enable


#define ADTS0   5
#define ADTS1   6
#define ADTS2   7

#endif
