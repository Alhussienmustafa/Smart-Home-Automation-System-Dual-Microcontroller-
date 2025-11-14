#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H

#include "../../LIB/std_types.h"

/*  ATmega32 USART Registers  */

#define UDR     (*((volatile u8*)0x2C))
#define UCSRA   (*((volatile u8*)0x2B))
#define UCSRB   (*((volatile u8*)0x2A))
#define UBRRL   (*((volatile u8*)0x29))
#define UBRRH   (*((volatile u8*)0x40))
#define UCSRC   (*((volatile u8*)0x40))

/* UCSRA bits  */
#define RXC     7   /* Receive Complete */
#define TXC     6   /* Transmit Complete */
#define UDRE    5   /* Data Register Empty */
#define FE      4   /* Frame Error */
#define DOR     3   /* Data OverRun */
#define PE      2   /* Parity Error */
#define U2X     1   /* Double Speed (async) */
#define MPCM    0   /* Multi-processor Comm */

/*  UCSRB bits  */
#define RXCIE   7
#define TXCIE   6
#define UDRIE   5
#define RXEN    4
#define TXEN    3
#define UCSZ2   2
#define RXB8    1
#define TXB8    0

/*  UCSRC bits */
#define URSEL   7
#define UMSEL   6   /* 0=Async, 1=Sync */
#define UPM1    5   /* Parity Mode */
#define UPM0    4
#define USBS    3   /* Stop Bit Select: 0=1bit, 1=2bits */
#define UCSZ1   2   /* Char size */
#define UCSZ0   1
#define UCPOL   0   /* Clock Polarity (sync only) */

/* Character size used by this driver: fixed 8-bit (UCSZ2:0 = 011) */
#define UART_CHAR_SIZE_MASK   ((1<<UCSZ1)|(1<<UCSZ0))
#define UART_CHAR_SIZE_8BIT   ((1<<UCSZ1)|(1<<UCSZ0))

/* Frame format helpers */
#define UART_PARITY_DISABLED  0
#define UART_PARITY_EVEN      (1<<UPM1)
#define UART_PARITY_ODD       ((1<<UPM1)|(1<<UPM0))

#define UART_STOP_1BIT        0
#define UART_STOP_2BIT        (1<<USBS)

#endif
