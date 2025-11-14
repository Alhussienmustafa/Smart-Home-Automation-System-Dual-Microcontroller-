/*
 * uart_program.c
 *
 * Created to match provided headers:
 *   - LIB/std_types.h
 *   - MCAL/UART_DRIVER/include/UART.h
 *   - MCAL/UART_DRIVER/include/UART_private.h
 *
 * Features:
 *  - Blocking (polling) send/receive byte
 *  - send/receive string (receive stops on newline '\n', CR '\r' or when max length reached)
 *  - Configurable baud via UART_t.baudRate
 *  - ASYNC_DSM toggles U2X (double speed async)
 *  - Parity and stop bits are applied on init
 *  - Fixed 8-bit data frame
 */

#include "UART_interface.h"
#include "UART_private.h"

#ifndef F_CPU
 #error "F_CPU not defined. Define CPU frequency (e.g. #define F_CPU 8000000UL) before including uart_program.c"
#endif

/* Helper: compute UBRR value for given baud and U2X mode */
static u16 UART_compute_ubrr(u32 baud, bool use_double_speed)
{
    /* Formula:
       - Normal async (U2X=0): UBRR = F_CPU/(16*baud) - 1
       - Double speed (U2X=1) : UBRR = F_CPU/(8*baud)  - 1
    */
    if (baud == 0) return 0;
    if (use_double_speed)
    {
        return (u16)((F_CPU / (8UL * baud)) - 1UL);
    }
    else
    {
        return (u16)((F_CPU / (16UL * baud)) - 1UL);
    }
}

/* Initialize UART according to UART_t structure */
void UART_init(UART_t *uart)
{
    u8 ucsrc_val = 0;
    u16 ubrr_val = 0;

    if (uart == NULL) return;

    /* Set/clear U2X bit in UCSRA according to ASYNC_DSM */
    if (uart->ASYNC_DSM)
    {
        SET_BIT(UCSRA, U2X);
    }
    else
    {
        CLEAR_BIT(UCSRA, U2X);
    }

    /* Compute UBRR */
    ubrr_val = UART_compute_ubrr(uart->baudRate, uart->ASYNC_DSM);

    /* Write UBRR (low and high bytes). UBRRH and UCSRC share same IO address:
       writing to UBRRH should be done by writing the high byte to UBRRH macro (URSEL = 0).
       Our UBRRH macro maps to the same address, so writing it directly is fine. */
    UBRRL = (u8)(ubrr_val & 0xFF);
    UBRRH = (u8)((ubrr_val >> 8) & 0x0F);

    /* Build UCSRC value:
       - URSEL = 1 to select UCSRC (not UBRRH)
       - UMSEL = 0 (Async) [we assume async mode; could expand later]
       - Parity: according to uart->mode
       - Stop bits: according to uart->select
       - Character size: fixed 8-bit (UCSZ1:0 = 11) and UCSZ2 in UCSRB = 0
    */
    ucsrc_val |= (1 << URSEL); /* write to UCSRC */

    /* Parity */
    switch (uart->mode)
    {
        case DISABLED:
            /* nothing */
            break;
        case EVEN_PARITY:
            ucsrc_val |= UART_PARITY_EVEN;
            break;
        case ODD_PARITY:
            ucsrc_val |= UART_PARITY_ODD;
            break;
        default:
            break;
    }

    /* Stop bits */
    switch (uart->select)
    {
        case ONE_BIT:
            /* nothing */
            break;
        case TWO_BIT:
            ucsrc_val |= UART_STOP_2BIT;
            break;
        default:
            break;
    }

    /* Character size 8-bit: UCSZ1=1, UCSZ0=1 (and UCSZ2 in UCSRB = 0) */
    ucsrc_val |= UART_CHAR_SIZE_8BIT;

    /* Write UCSRC (URSEL=1 makes this write to UCSRC not UBRRH) */
    UCSRC = ucsrc_val;

    /* Ensure UCSZ2 (in UCSRB) = 0 for 8-bit mode */
    CLEAR_BIT(UCSRB, UCSZ2);

    /* Enable receiver and transmitter (polling mode) */
    SET_BIT(UCSRB, RXEN);
    SET_BIT(UCSRB, TXEN);

    /* Optionally disable interrupts (we're implementing polling). If you want to use interrupts later,
       set RXCIE/TXCIE/UDRIE here. */
}

/* Blocking send byte */
void UART_sendByte(const u8 data)
{
    /* Wait for empty transmit buffer (UDRE bit set) */
    while (!BIT_IS_SET(UCSRA, UDRE))
    {
        /* busy wait */
    }

    /* Put data into buffer, sends the data */
    UDR = data;

    /* Optionally wait for transmit complete (TXC) if you want to ensure shift register done:
       while (!BIT_IS_SET(UCSRA, TXC)) { }
       then clear TXC by writing 1 to it:
       SET_BIT(UCSRA, TXC);
       Not necessary for most uses. */
}

/* Blocking receive byte
   Returns True on success (byte placed in *data). If data == NULL returns False.
*/
bool UART_receiveByte(u8 *data)
{
    if (data == NULL) return False;

    /* Wait for data to be received (RXC bit set) */
    while (!BIT_IS_SET(UCSRA, RXC))
    {
        /* busy wait */
    }

    /* Read received data */
    *data = UDR;

    /* Some status bits like FE/DOR/PE can be checked in UCSRA if needed.
       For now we don't do explicit error handling, but you can check:
         if (BIT_IS_SET(UCSRA, FE)) -> frame error
         if (BIT_IS_SET(UCSRA, DOR)) -> data overrun
         if (BIT_IS_SET(UCSRA, PE)) -> parity error
    */

    return True;
}

/* Send null-terminated string (blocking) */
void UART_sendString(const u8 *str)
{
    if (str == NULL) return;

    const u8 *p = str;
    while (*p != '\0')
    {
        UART_sendByte(*p);
        p++;
    }
}

/* Receive string into buffer 'str'. Stops when:
   - newline '\n' is received
   - carriage return '\r' is received
   - max length reached (MAX_STRING_LENGTH - 1), then null-terminates
   The received string will be null-terminated.
*/
void UART_receiveString(u8 *str)
{
    if (str == NULL) return;

    u8 ch;
    u8 idx = 0;
    /* Reserve last byte for NUL */
    u8 limit = (MAX_STRING_LENGTH > 1) ? (MAX_STRING_LENGTH - 1) : 0;

    while (1)
    {
        if (!UART_receiveByte(&ch)) break; /* unexpected, but keep safe */

        /* stop conditions */
        if ((ch == '\n') || (ch == '\r')) break;

        if (idx < limit)
        {
            str[idx++] = ch;
        }
        else
        {
            /* buffer full: stop reading further characters to avoid overflow */
            break;
        }
    }

    /* null-terminate */
    str[idx] = '\0';
}
