#include <util/delay.h>
#include "../../MCAL/DIO_DRIVER/DIO_interface.h"
#include "../../LIB/bit_math.h"
#include "lcd.h"

/*
 * Description :
 * Initialize the LCD
 */
void LCD_Init(void)
{
	/* 1- Configure RS and E as output */
	DIO_voidSetPinDir(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDir(LCD_E_PORT_ID,  LCD_E_PIN_ID,  PIN_OUTPUT);
	_delay_ms(20);

#if (LCD_DATA_BITS_MODE == 8)
	/* Configure the data port as output */
	DIO_voidSetPortDir(LCD_DATA_PORT_ID, PORT_OUTPUT);
	_delay_ms(20);

	/* Function set: 2 lines, 8-bit */
	LCD_SendCommand(LCD_TWO_LINES_8_BITS_MODE);

#elif (LCD_DATA_BITS_MODE == 4)
	/* Configure DB4–DB7 pins as output */
	DIO_voidSetPinDir(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDir(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDir(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
	DIO_voidSetPinDir(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);
	_delay_ms(20);

	/* Initialization sequence */
	LCD_SendCommand(LCD_TWO_LINES_4_BITS_MODE_INIT1);
	LCD_SendCommand(LCD_TWO_LINES_4_BITS_MODE_INIT2);
	LCD_SendCommand(LCD_TWO_LINES_4_BITS_MODE);
#endif

	/* Cursor OFF */
	LCD_SendCommand(LCD_CURSOR_OFF);

	/* Clear screen */
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Description :
 * Send command to LCD
 */
void LCD_SendCommand(u8 Copy_u8Command)
{
	/* RS = 0 for command */
	DIO_voidSetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_LOW);
	_delay_us(1);

	/* Enable = 1 */
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_us(1);

#if (LCD_DATA_BITS_MODE == 8)
	DIO_voidSetPortValue(LCD_DATA_PORT_ID, Copy_u8Command);
	_delay_us(1);

#elif (LCD_DATA_BITS_MODE == 4)
	/* Send high nibble */
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(Copy_u8Command,4));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(Copy_u8Command,5));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(Copy_u8Command,6));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(Copy_u8Command,7));
	_delay_ms(1);

	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	_delay_us(1);

	/* Enable = 1 again */
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_us(1);

	/* Send low nibble */
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(Copy_u8Command,0));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(Copy_u8Command,1));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(Copy_u8Command,2));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(Copy_u8Command,3));
	_delay_ms(1);
#endif

	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	_delay_us(1);
}

/*
 * Display a single character
 */
void LCD_DisplayChar(u8 Copy_u8Char)
{
	/* RS = 1 for data */
	DIO_voidSetPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_HIGH);
	_delay_us(1);

	/* Enable = 1 */
	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_us(1);

#if (LCD_DATA_BITS_MODE == 8)
	DIO_voidSetPortValue(LCD_DATA_PORT_ID, Copy_u8Char);
	_delay_us(1);

#elif (LCD_DATA_BITS_MODE == 4)
	/* Send high nibble */
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(Copy_u8Char,4));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(Copy_u8Char,5));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(Copy_u8Char,6));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(Copy_u8Char,7));
	_delay_ms(1);

	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	_delay_us(1);

	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_HIGH);
	_delay_us(1);

	/* Send low nibble */
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(Copy_u8Char,0));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(Copy_u8Char,1));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(Copy_u8Char,2));
	DIO_voidSetPinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(Copy_u8Char,3));
	_delay_ms(1);
#endif

	DIO_voidSetPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_LOW);
	_delay_us(1);
}

/*
 * Display string
 */
void LCD_DisplayString(const u8 *Copy_pu8Str)
{
	u8 i = 0;
	while (Copy_pu8Str[i] != '\0')
	{
		LCD_DisplayChar(Copy_pu8Str[i]);
		i++;
	}
}

/*
 * Display integer as string
 */
void LCD_IntegerToString(u32 Copy_u32Data)
{
    char buff[16];
    snprintf(buff, sizeof(buff), "%lu", Copy_u32Data);
    LCD_DisplayString((u8*)buff);
}

/*
 * Move cursor
 */
void LCD_MoveCursor(u8 Copy_u8Row, u8 Copy_u8Col)
{
	u8 Address = 0;

	switch (Copy_u8Row)
	{
	case 0: Address = Copy_u8Col; break;
	case 1: Address = 0x40 + Copy_u8Col; break;
	case 2: Address = 0x10 + Copy_u8Col; break;
	case 3: Address = 0x50 + Copy_u8Col; break;
	}

	LCD_SendCommand(Address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Display string at row/col
 */
void LCD_DisplayStringRowColumn(u8 Copy_u8Row, u8 Copy_u8Col, const u8 *Copy_pu8Str)
{
	LCD_MoveCursor(Copy_u8Row, Copy_u8Col);
	LCD_DisplayString(Copy_pu8Str);
}

/*
 * Clear screen
 */
void LCD_ClearScreen(void)
{
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}



