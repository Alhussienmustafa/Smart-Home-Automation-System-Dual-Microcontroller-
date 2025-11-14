/*
 * fan.h
 *
 *  Created on: Sep 15, 2025
 *      Author: user
 */

#ifndef HAL_FAN_FAN_H_
#define HAL_FAN_FAN_H_

#define LEVEL_0		0
#define LEVEL_1		85
#define LEVEL_2		170
#define LEVEL_3		255

typedef enum {
	FAN1 = 1 ,FAN2
}FAN_NUM;

void FAN_Off(u8 fan_num ) ;
void FAN_RevModeOn(u8 fan_num) ;
void FAN_ModeOn(u8 fan_num) ;

#endif /* HAL_FAN_FAN_H_ */
