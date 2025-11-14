#include "SPI_private.h""
#include "SPI_INTERFACE.h"
#include "../DIO_DRIVER/DIO_interface.h"

/*  SPI Master Init  */
void SPI_masterInit(SPI_CLOCK_RATE clock, SPI_MODE mode)
{
    /* Set MOSI(PB5), SCK(PB7), SS(PB4) as output */
    DIO_voidSetPinDir(PORTB_ID, PIN5_ID, PIN_OUTPUT);
    DIO_voidSetPinDir(PORTB_ID, PIN7_ID, PIN_OUTPUT);
    DIO_voidSetPinDir(PORTB_ID, PIN4_ID, PIN_OUTPUT);

    /* Set MISO(PB6) as input */
    DIO_voidSetPinDir(PORTB_ID, PIN6_ID, PIN_INPUT);

    /* Enable SPI, set as Master */
    SPCR = (1 << SPE) | (1 << MSTR);

    /* Configure SPI Mode (CPOL/CPHA) */
    switch(mode) {
        case SPI_MODE0: SPCR &= ~((1<<CPOL)|(1<<CPHA)); break;
        case SPI_MODE1: SPCR = (SPCR & ~(1<<CPOL)) | (1<<CPHA); break;
        case SPI_MODE2: SPCR = (SPCR & ~(1<<CPHA)) | (1<<CPOL); break;
        case SPI_MODE3: SPCR |= (1<<CPOL) | (1<<CPHA); break;
    }

    /* Configure Clock rate */
    switch(clock)
    {
        case CLOCK_2:
            SPSR |= (1 << SPI2X);
            SPCR &= ~((1 << SPR0) | (1 << SPR1));
            break;
        case CLOCK_4:
            SPSR &= ~(1 << SPI2X);
            SPCR &= ~((1 << SPR0) | (1 << SPR1));
            break;
        case CLOCK_8:
            SPSR |= (1 << SPI2X);
            SPCR = (SPCR & ~((1 << SPR0) | (1 << SPR1))) | (1 << SPR0);
            break;
        case CLOCK_16:
            SPSR &= ~(1 << SPI2X);
            SPCR = (SPCR & ~((1 << SPR0) | (1 << SPR1))) | (1 << SPR0);
            break;
        case CLOCK_32:
            SPSR |= (1 << SPI2X);
            SPCR = (SPCR & ~((1 << SPR0) | (1 << SPR1))) | (1 << SPR1);
            break;
        case CLOCK_64:
            SPSR &= ~(1 << SPI2X);
            SPCR = (SPCR & ~((1 << SPR0) | (1 << SPR1))) | (1 << SPR1);
            break;
        case CLOCK_128:
            SPSR &= ~(1 << SPI2X);
            SPCR |= (1 << SPR0) | (1 << SPR1);
            break;
    }
}

/*  SPI Slave Init  */
void SPI_slaveInit(SPI_MODE mode)
{
    /* Set MISO(PB6) as output */
    DIO_voidSetPinDir(PORTB_ID, PIN6_ID, PIN_OUTPUT);

    /* Set MOSI, SCK, SS as input */
    DIO_voidSetPinDir(PORTB_ID, PIN5_ID, PIN_INPUT);
    DIO_voidSetPinDir(PORTB_ID, PIN7_ID, PIN_INPUT);
    DIO_voidSetPinDir(PORTB_ID, PIN4_ID, PIN_INPUT);

    /* Enable SPI (slave mode by default when MSTR=0) */
    SPCR = (1 << SPE);

    /* Configure SPI Mode (CPOL/CPHA) */
    switch(mode) {
        case SPI_MODE0: SPCR &= ~((1<<CPOL)|(1<<CPHA)); break;
        case SPI_MODE1: SPCR = (SPCR & ~(1<<CPOL)) | (1<<CPHA); break;
        case SPI_MODE2: SPCR = (SPCR & ~(1<<CPHA)) | (1<<CPOL); break;
        case SPI_MODE3: SPCR |= (1<<CPOL) | (1<<CPHA); break;
    }
}

/*  Send & Receive Byte  */
u8 SPI_sendReceiveByte(u8 data)
{
    SPDR = data;                       /* Start transmission */
    while (!(SPSR & (1 << SPIF)));     /* Wait for transmission complete */
    return SPDR;                       /* Return received data */
}

/*  Send & Receive Daisy Mode  */
u8 SPI_sendReceiveByteDaisy(void)
{
    SPDR = SPI_DEFAULT_VALUE;          /* Send dummy byte */
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

/*  Send String  */
void SPI_sendString(u8 *str)
{
    u8 i = 0;
    while (str[i] != '\0' && i < MAX_STRING_LENGTH)
    {
        SPI_sendReceiveByte(str[i]);
        i++;
    }
    /* Send string terminator */
    SPI_sendReceiveByte('#');
}

/*  Receive String  */
void SPI_receiveString(u8 *str)
{
    u8 i = 0;
    u8 data;

    do {
        data = SPI_sendReceiveByteDaisy();
        str[i] = data;
        i++;
    } while (data != '#' && i < MAX_STRING_LENGTH - 1);

    str[i-1] = '\0';   /* Replace '#' with null terminator */
}
