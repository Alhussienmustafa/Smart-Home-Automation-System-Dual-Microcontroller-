#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIB/std_types.h"

/* Configuration */
#define KEYPAD_COL_NUM 4
#define KEYPAD_ROW_NUM 4

/* Port/Pin assignments */
#define KEYPAD_ROW_PORT_ID PORTA_ID
#define KEYPAD_FIRST_ROWS_PIN_ID PIN0_ID

#define KEYPAD_COL_PORT_ID PORTA_ID
#define KEYPAD_FIRST_COL_PIN_ID PIN4_ID

/* Logic levels */
#define KEYPAD_BUTTON_PRESSED PIN_LOW
#define KEYPAD_BUTTON_RELEASED PIN_HIGH

/* API */
u8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
