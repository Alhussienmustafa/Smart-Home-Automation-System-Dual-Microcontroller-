/*
 * leds.c
 *
 *  Created on: Sep 14, 2025
 *      Author: user
 */
#include"leds.h"
#include"../../MCAL/DIO_DRIVER/DIO_interface.h"
#include"../../APP/config.h"

void LED_voidInit()
{
    DIO_voidSetPinDir(LEDS_PORT, LED1_PIN, PIN_OUTPUT);
    DIO_voidSetPinDir(LEDS_PORT, LED2_PIN, PIN_OUTPUT);
}

void LED_voidON(u8 led_num)
{
	if (led_num == LED1)
	{
    DIO_voidSetPinValue(LEDS_PORT, LED1_PIN, LED_ON);
    return ;
	}
	if(led_num == LED2)
	{
    DIO_voidSetPinValue(LEDS_PORT, LED2_PIN, LED_ON);
	return ;
	}
	else
		return ;
}

void LED_voidOFF(u8 led_num)
{
	if (led_num == LED1)
		{
	    DIO_voidSetPinValue(LEDS_PORT, LED1_PIN, LED_OFF);
	    return ;
		}
		if(led_num == LED2)
		{
	    DIO_voidSetPinValue(LEDS_PORT, LED2_PIN, LED_OFF);
		return ;
		}
		else
			return ;
}
