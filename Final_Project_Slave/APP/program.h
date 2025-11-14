///*
// * program.h
// *
// *  Created on: 14 Sep 2025
// *      Author: AlHussien Mustafa
// */
//
#ifndef APP_PROGRAM_H_
#define APP_PROGRAM_H_
//
#include"../LIB/std_types.h"
#include "config.h"
#include "../MCAL/DIO_DRIVER/DIO_interface.h"
#include "../MCAL/UART_DRIVER/UART_interface.h"
#include "../MCAL/TIMER_DRIVER/TIMER0/TIMER0.h"
#include "../MCAL/TIMER_DRIVER/TIMER2/TIMER2.h"
#include "../MCAL/SPI_DRIVER/SPI_INTERFACE.h"
#include "../MCAL/ADC_DRIVER/ADC_interface.h"
#include "../HAL/LEDS/leds.h"
#include "../HAL/FAN/fan.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/KEYPAD/keypad.h"
#include <util/delay.h>

void Slave_Init();
void UART_LedCntrl(u8 led_num) ;
void UART_FanSpeedCntrl(u8 fan_num) ;
void Buzz_Action();
void Wel3a();
void vManual_LEDMenu(u8 choice);
void vManual_FanMenu(u8 speed);

#endif /* APP_PROGRAM_H_ */
