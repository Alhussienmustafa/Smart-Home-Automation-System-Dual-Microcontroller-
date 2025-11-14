/*
 * config.h
 *
 *  Created on: Sep 14, 2025
 *      Author: user
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

// 	SWITCH
#define SWITCH_PORT  	PORTD_ID
#define SWITCH1_PIN		PIN2_ID
#define SWITCH2_PIN		PIN3_ID

//  LED
#define LEDS_PORT  	 	PORTA_ID
#define LED1_PIN		 PIN6_ID
#define LED2_PIN		 PIN7_ID

//// FAN OF TEMPRATURE SENSOR
#define FAN_ONE_PORT		PORTB_ID
#define FAN_ONE_IN1_PIN		PIN0_ID
#define FAN_ONE_IN2_PIN		PIN1_ID
#define FAN_ONE_PWM			PIN3_ID
//#define FAN_TEMP_BUZZER			PIN2_ID

#define TEMP_SENSOR_PORT	PORTA_ID
#define TEMP_SENSOR_PIN		PIN0_ID

//// FAN OF FLAME SENSOR
#define FAN_TWO_PORT		PORTD_ID
#define FAN_TWO_IN3_PIN		PIN5_ID
#define FAN_TWO_IN4_PIN		PIN6_ID
#define FAN_TWO_PWM			PIN7_ID // added
//#define FAN_FLAME_BUZZER	PIN4_ID //changed

#define FLAME_SENSOR_PORT	PORTA_ID
#define FLAME_SENSOR_PIN	PIN1_ID
#define FAN2_LEVEL			170

#define ACTION_BUZZER_PORT	PORTD_ID
#define ACTION_BUZZER_PIN	PIN4_ID
#define ACTION_BUZZER_TIME  200

// password config
#define PASS_ADDR     0x10
#define PASS_LEN      4
#define MAX_TRIES     3

#define DISPLAY_TIME		2000

#endif /* APP_CONFIG_H_ */
