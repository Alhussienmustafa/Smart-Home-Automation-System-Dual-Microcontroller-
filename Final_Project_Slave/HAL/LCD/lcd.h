#ifndef LCD_H_
#define LCD_H_

#include "../../LIB/std_types.h"

/* ============================
   LCD Configuration
   ============================ */
#define LCD_DATA_BITS_MODE 4

/* Control Pins */
#define LCD_RS_PORT_ID PORTB_ID
#define LCD_RS_PIN_ID  PIN2_ID

#define LCD_E_PORT_ID  PORTB_ID
#define LCD_E_PIN_ID   PIN3_ID

/* Data Port */
#define LCD_DATA_PORT_ID PORTB_ID

#if (LCD_DATA_BITS_MODE == 4)
#define LCD_DB4_PIN_ID PIN4_ID
#define LCD_DB5_PIN_ID PIN5_ID
#define LCD_DB6_PIN_ID PIN6_ID
#define LCD_DB7_PIN_ID PIN7_ID
#endif

/* ============================
   LCD Commands
   ============================ */
#define LCD_CLEAR_COMMAND               0x01
#define LCD_GO_TO_HOME                  0x02
#define LCD_CURSOR_ON                   0x0E
#define LCD_CURSOR_OFF                  0x0C
#define LCD_CURSOR_BLINKING             0x0F
#define LCD_SET_CURSOR_LOCATION         0x80
#define LCD_TWO_LINES_8_BITS_MODE       0x38
#define LCD_TWO_LINES_4_BITS_MODE       0x28
#define LCD_TWO_LINES_4_BITS_MODE_INIT1 0x33
#define LCD_TWO_LINES_4_BITS_MODE_INIT2 0x32

/* ============================
   LCD Function Prototypes
   ============================ */

/* Initialize LCD in selected mode */
void LCD_Init(void);

/* Send command to LCD */
void LCD_SendCommand(u8 Copy_u8Command);

/* Display a single character */
void LCD_DisplayChar(u8 Copy_u8Char);

/* Display a null-terminated string */
void LCD_DisplayString(const u8 *Copy_pu8Str);

/* Move cursor to specific row and column */
void LCD_MoveCursor(u8 Copy_u8Row, u8 Copy_u8Col);

/* Display string at a specific location */
void LCD_DisplayStringRowColumn(u8 Copy_u8Row, u8 Copy_u8Col, const u8 *Copy_pu8Str);

/* Display an integer number as string */
void LCD_IntegerToString(u32 Copy_u32Data);

/* Clear the LCD display */
void LCD_ClearScreen(void);

#endif /* LCD_H_ */
