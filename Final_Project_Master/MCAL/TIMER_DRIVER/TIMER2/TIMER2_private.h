#ifndef TIMER2_PRIVATE_H
#define TIMER2_PRIVATE_H

#include "../../../LIB/std_types.h"

// Registers
#define TCCR2   (*(volatile u8*)0x45)
#define TCNT2   (*(volatile u8*)0x44)
#define OCR2    (*(volatile u8*)0x43)
#define TIMSK   (*(volatile u8*)0x59)
#define TIFR    (*(volatile u8*)0x58)

// TCCR2 Bits
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

// TIMSK Bits
#define OCIE2   7
#define TOIE2   6

// TIFR Bits
#define OCF2    7
#define TOV2    6

#endif
