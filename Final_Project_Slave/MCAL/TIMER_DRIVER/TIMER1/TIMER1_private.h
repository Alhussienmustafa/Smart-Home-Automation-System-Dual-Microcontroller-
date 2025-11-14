#ifndef TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

#include "../../../LIB/std_types.h"

// Registers
#define TCCR1A   (*(volatile u8*)0x4F)
#define TCCR1B   (*(volatile u8*)0x4E)
#define TCNT1    (*(volatile u16*)0x4C)
#define OCR1A    (*(volatile u16*)0x4A)
#define OCR1B    (*(volatile u16*)0x48)
#define ICR1     (*(volatile u16*)0x46)
#define TIMSK    (*(volatile u8*)0x59)
#define TIFR     (*(volatile u8*)0x58)

// TCCR1A Bits
#define COM1A1   7
#define COM1A0   6
#define COM1B1   5
#define COM1B0   4
#define FOC1A    3
#define FOC1B    2
#define WGM11    1
#define WGM10    0

// TCCR1B Bits
#define ICNC1    7
#define ICES1    6
#define WGM13    4
#define WGM12    3
#define CS12     2
#define CS11     1
#define CS10     0

// TIMSK bits
#define TICIE1   5
#define OCIE1A   4
#define OCIE1B   3
#define TOIE1    2

// TIFR bits
#define ICF1     5
#define OCF1A    4
#define OCF1B    3
#define TOV1     2

#endif
