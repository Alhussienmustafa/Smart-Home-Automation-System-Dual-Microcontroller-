/*
 * fan.c
 *
 *  Created on: Sep 15, 2025
 *      Author: user
 */
#include"../../APP/config.h"
#include "../../MCAL/DIO_DRIVER/DIO_interface.h"
#include"fan.h"

void FAN_ModeOn(u8 fan_num)
{
	switch (fan_num)
	{
	case FAN1 :
		DIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_IN1_PIN ,PIN_HIGH) ;
		DIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_IN2_PIN,PIN_LOW) ;
		break ;
	case FAN2 :
		DIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_IN3_PIN,PIN_HIGH) ;
		DIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_IN4_PIN,PIN_LOW) ;
		break ;
	default :
		break ;
	}
}

void FAN_RevModeOn(u8 fan_num)
{
	switch (fan_num)
	{
	case FAN1 :
		DIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_IN1_PIN ,PIN_LOW) ;
		DIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_IN2_PIN,PIN_HIGH) ;
		break ;
	case FAN2 :
		DIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_IN3_PIN,PIN_LOW) ;
		DIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_IN4_PIN,PIN_HIGH) ;
		break ;
	default :
		break ;
	}
}


void FAN_Off(u8 fan_num )
{
	switch (fan_num)
	{
	case FAN1 :
		DIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_IN1_PIN ,PIN_LOW) ;
		DIO_voidSetPinValue(FAN_ONE_PORT,FAN_ONE_IN2_PIN,PIN_LOW) ;
		break ;
	case FAN2 :
		DIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_IN3_PIN,PIN_LOW) ;
		DIO_voidSetPinValue(FAN_TWO_PORT,FAN_TWO_IN4_PIN,PIN_LOW) ;
		break ;
	default :
		break ;
	}
}


