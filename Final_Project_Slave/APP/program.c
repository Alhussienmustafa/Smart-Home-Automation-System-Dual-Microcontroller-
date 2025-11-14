#include "program.h"

void Slave_Init() {
	// Sensors & Actuators
	DIO_voidSetPinDir(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN, PIN_INPUT);
	DIO_voidSetPinDir(TEMP_SENSOR_PORT, TEMP_SENSOR_CHANNEL, PIN_INPUT);
	DIO_voidSetPinDir(ACTION_BUZZER_PORT, ACTION_BUZZER_PIN, PIN_OUTPUT);
	DIO_voidSetPinDir(PORTB_ID, PIN4_ID, PIN_INPUT); // SS Input

	// Fans
	DIO_voidSetPinDir(FAN_ONE_PORT, FAN_ONE_IN1_PIN, PIN_OUTPUT);
	DIO_voidSetPinDir(FAN_ONE_PORT, FAN_ONE_IN2_PIN, PIN_OUTPUT);
	DIO_voidSetPinDir(FAN_ONE_PORT, FAN_ONE_PWM, PIN_OUTPUT);
	DIO_voidSetPinDir(FAN_TWO_PORT, FAN_TWO_IN3_PIN, PIN_OUTPUT);
	DIO_voidSetPinDir(FAN_TWO_PORT, FAN_TWO_IN4_PIN, PIN_OUTPUT);
	DIO_voidSetPinDir(FAN_TWO_PORT, FAN_TWO_PWM, PIN_OUTPUT);
	DIO_voidSetPinDir(FAN_LED_PORT, FAN_ONE_LED, PIN_OUTPUT);
	DIO_voidSetPinDir(FAN_LED_PORT, FAN_TWO_LED, PIN_OUTPUT);

	// Init Modules
	LED_voidInit();
	ADC_init(AVCC, ADC_PRESCALER_CFG);
	TIMER0_FAST_PWM_init(NON_INVERTING_MODE, T0_PRESCALER_64);
	TIMER2_initFastPWM(T2_NON_INVERTING, T2_PRESCALER_64);
	SPI_slaveInit(SPI_MODE3);
}

void Buzz_Action() {
	DIO_voidSetPinValue(ACTION_BUZZER_PORT, ACTION_BUZZER_PIN, PIN_HIGH);
	_delay_ms(ACTION_BUZZER_TIME);
	DIO_voidSetPinValue(ACTION_BUZZER_PORT, ACTION_BUZZER_PIN, PIN_LOW);
}

void FAN1_TemperatureControl(void) {
	u16 adc_value;
	u32 temperature;

	adc_value = ADC_readChannel(TEMP_SENSOR_CHANNEL);
	temperature = (adc_value * 500) / 1024;

	if (temperature > 26) {
		TIMER2_setDutyCycle(FAN_Wel3a_LEVEL);
		FAN_ModeOn(FAN2);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_TWO_LED, PIN_HIGH);
		Buzz_Action() ;
	} else {
		TIMER0_FAST_PWM_set_dutyCycle(LEVEL_0);
		FAN_Off(FAN1);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_ONE_LED, PIN_LOW);
	}
}

void Wel3a(){
	if(DIO_readPin(FLAME_SENSOR_PORT, FLAME_SENSOR_PIN) == 1){
		FAN_RevModeOn(FAN1);
		FAN_RevModeOn(FAN2);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_ONE_LED, PIN_HIGH);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_TWO_LED, PIN_HIGH);
		TIMER2_setDutyCycle(FAN_Wel3a_LEVEL);
		TIMER0_FAST_PWM_set_dutyCycle(FAN_Wel3a_LEVEL);
	}
	else{
		FAN_Off(FAN1);
		FAN_Off(FAN2);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_ONE_LED, PIN_LOW);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_TWO_LED, PIN_LOW);
	}
}

void vManual_LEDMenu(u8 choice) {
	switch(choice) {
	case '0':
		LED_voidON(LED1);
		break;
	case '1':
		LED_voidOFF(LED1);
		break;
	case '2':
		LED_voidON(LED2);
		break;
	case '3':
		LED_voidOFF(LED2);
		break;
	default: break;
	}
	Buzz_Action();
}

void vManual_FanMenu(u8 speed) {
	switch(speed) {
	case '4':
		FAN_Off(FAN1);
		TIMER0_FAST_PWM_set_dutyCycle(LEVEL_0);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_ONE_LED, PIN_LOW);
		break;
	case '5':
		FAN_ModeOn(FAN1);
		TIMER0_FAST_PWM_set_dutyCycle(LEVEL_1);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_ONE_LED, PIN_HIGH);
		break;
	case '6':
		FAN_ModeOn(FAN1);
		TIMER0_FAST_PWM_set_dutyCycle(LEVEL_2);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_ONE_LED, PIN_HIGH);
		break;
	case '7':
		FAN_ModeOn(FAN1);
		TIMER0_FAST_PWM_set_dutyCycle(LEVEL_3);
		DIO_voidSetPinValue(FAN_LED_PORT, FAN_ONE_LED, PIN_HIGH);
		break;
	case '8':
		Wel3a();
		break;
	case '9':
		FAN1_TemperatureControl();
		break;
	default: break;
	}
	Buzz_Action();
}
