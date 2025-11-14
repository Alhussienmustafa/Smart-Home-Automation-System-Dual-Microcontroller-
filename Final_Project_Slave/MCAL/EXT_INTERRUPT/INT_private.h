#ifndef _EXTI_PRIVATE_H_
#define _EXTI_PRIVATE_H_

#define SREG    (*(volatile u8*)0x5F)

#define GICR     (*(volatile u8*)0x5B)

#define GIFR     (*(volatile u8*)0x5A)

#define MCUCR    (*(volatile u8*)0x55)

#define MCUCSR   (*(volatile u8*)0x54)

  // Bit Positions in GICR ( external interrupts enable)
#define INT1    7
#define INT0    6
#define INT2    5

  // Bit Positions in GIFR (Flags)
#define INTF1   7
#define INTF0   6
#define INTF2   5

  // Bit Positions in MCUCR (INT0/INT1 ISC bits)
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

   //Bit Position in MCUCSR (INT2)
#define ISC2    6
//bit postion in SREG
#define I_BIT   7



#endif /* _EXTI_PRIVATE_H_ */
