/*
 * leds.h
 *
 *  Created on: Sep 14, 2025
 *      Author: user
 */

#ifndef HAL_LEDS_LEDS_H_
#define HAL_LEDS_LEDS_H_
#include"../../LIB/std_types.h"

typedef enum
{
	LED_OFF,LED_ON
}LED_STATE;

typedef enum {
	LED1=1,LED2
}LED_NUM;

void LED_voidInit() ;
void LED_voidON(u8 led_num) ;
void LED_voidOFF(u8 led_num) ;


#endif /* HAL_LEDS_LEDS_H_ */
