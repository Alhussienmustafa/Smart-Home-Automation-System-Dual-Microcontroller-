#ifndef MCAL_SPI_DRIVER_INCLUDE_SPI_H_
#define MCAL_SPI_DRIVER_INCLUDE_SPI_H_

#include "../../LIB/std_types.h"

#define SPI_DEFAULT_VALUE 0xFF
#define MAX_STRING_LENGTH 50

/* Clock rate options */
typedef enum {
    CLOCK_2 , CLOCK_4, CLOCK_8, CLOCK_16,
    CLOCK_32, CLOCK_64, CLOCK_128
} SPI_CLOCK_RATE;

/* SPI modes (CPOL/CPHA) */
typedef enum {
    SPI_MODE0,  // CPOL=0, CPHA=0
    SPI_MODE1,  // CPOL=0, CPHA=1
    SPI_MODE2,  // CPOL=1, CPHA=0
    SPI_MODE3   // CPOL=1, CPHA=1
} SPI_MODE;

/* Initialize SPI in master mode */
void SPI_masterInit(SPI_CLOCK_RATE clock, SPI_MODE mode);

/* Initialize SPI in slave mode */
void SPI_slaveInit(SPI_MODE mode);

/* Send & receive single byte */
u8 SPI_sendReceiveByte(u8 data);

/* Send & receive (dummy for reading only) */
u8 SPI_sendReceiveByteDaisy(void);

/* Send a string (null-terminated) */
void SPI_sendString(u8 *str);

/* Receive a string (until '#') */
void SPI_receiveString(u8 *str);

#endif /* MCAL_SPI_DRIVER_INCLUDE_SPI_H_ */
