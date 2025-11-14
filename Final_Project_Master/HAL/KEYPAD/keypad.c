#include "keypad.h"
#include <util/delay.h>
#include "../../MCAL/DIO_DRIVER/DIO_Interface.h"

// Keypad layout (4x4)
static u8 BUTTON[4][4] = {
    {'7', '8', '9', 'A'},
    {'4', '5', '6', 'B'},
    {'1', '2', '3', 'C'},
    {'*', '0', '#', 'D'}
};

u8 KEYPAD_getPressedKey(void) {
    u8 row, col;

    // Configure all column pins as input with pull-up
    for (col = 0; col < KEYPAD_COL_NUM; col++) {
        DIO_voidSetPinDir(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col, PIN_INPUT);
        DIO_voidSetPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col, PIN_HIGH); // enable pull-up
    }

    // Configure all row pins as output and drive them HIGH
    for (row = 0; row < KEYPAD_ROW_NUM; row++) {
        DIO_voidSetPinDir(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID + row, PIN_OUTPUT);
        DIO_voidSetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID + row, PIN_HIGH);
    }

    while (1) {
        for (row = 0; row < KEYPAD_ROW_NUM; row++) {
            // Activate current row (drive LOW)
            DIO_voidSetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID + row, KEYPAD_BUTTON_PRESSED);

            for (col = 0; col < KEYPAD_COL_NUM; col++) {
                if (DIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col) == KEYPAD_BUTTON_PRESSED) {
                    _delay_ms(10);
                    return BUTTON[row][col];
                }
            }

            // Deactivate row (drive HIGH again)
            DIO_voidSetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROWS_PIN_ID + row, KEYPAD_BUTTON_RELEASED);
        }
    }
}
