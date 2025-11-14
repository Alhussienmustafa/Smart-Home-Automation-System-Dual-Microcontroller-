#ifndef MCAL_SPI_DRIVER_INCLUDE_SPI_PRIVATE_H_
#define MCAL_SPI_DRIVER_INCLUDE_SPI_PRIVATE_H_

#include "../../LIB/bit_math.h"
#include "../../LIB/std_types.h"

/* ----------- SPI Registers ----------- */
#define SPCR    (*(volatile u8*)0x2D)  /* SPI Control Register */
#define SPSR    (*(volatile u8*)0x2E)  /* SPI Status Register  */
#define SPDR    (*(volatile u8*)0x2F)  /* SPI Data Register    */

/* ----------- SPCR bits ----------- */
#define SPR0    0
#define SPR1    1
#define CPHA    2
#define CPOL    3
#define MSTR    4
#define DORD    5
#define SPE     6
#define SPIE    7

/* ----------- SPSR bits ----------- */
#define SPI2X   0
#define WCOL    6
#define SPIF    7

#endif /* MCAL_SPI_DRIVER_INCLUDE_SPI_PRIVATE_H_ */
