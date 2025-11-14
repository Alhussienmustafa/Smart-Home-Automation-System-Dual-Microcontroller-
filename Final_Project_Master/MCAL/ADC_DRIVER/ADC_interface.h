#ifndef ADC_H_
#define ADC_H_

#include "../../LIB/std_types.h"

// Reference Voltage Options
#define AREF        0
#define AVCC        1
#define INT2_56     2

// Prescaler Options
#define ADC_PRESCALER_2     1
#define ADC_PRESCALER_4     2
#define ADC_PRESCALER_8     3
#define ADC_PRESCALER_16    4
#define ADC_PRESCALER_32    5
#define ADC_PRESCALER_64    6
#define ADC_PRESCALER_128   7

// Configuration Macros
//#define ADC_REF_VOLT_VALUE  5
#define ADC_MAX_VALUE       1023

#define ADC_VC_CONFIG       AVCC          // <-- choose reference here
#define ADC_PRESCALER_CFG   ADC_PRESCALER_128  // <-- choose prescaler here

// function prototypes
void ADC_init(u8 ref_voltage, u8 prescaler);
u16 ADC_readChannel(u8 channel_num);

#endif // ADC_H_
