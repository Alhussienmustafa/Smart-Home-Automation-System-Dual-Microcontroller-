/*
 * program.h (Master)
 *
 *  Created on: Sep 16, 2025
 *      Author: user
 */

#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_

#include "../LIB/std_types.h"
#include "../MCAL/UART_DRIVER/UART_interface.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/KEYPAD/keypad.h"
#include "../MCAL/DIO_DRIVER/DIO_interface.h"
#include "../MCAL/SPI_DRIVER/SPI_INTERFACE.h"
#include "../HAL/EXTERNAL_EEPROM/interface.h"
#include "config.h"
#include <util/delay.h>

/* ------------ Master Functions ------------ */
void Master_Init();
void Master_SendCommand(u8 cmd);
void vManual_System();
void vManual_LEDMenu();
void vManual_FanMenu();
void vBluetooth_Mode();
// pass func
void Password_init();
u8   Password_check();
void Password_change();

#endif /* APP_INTERFACE_H_ */
