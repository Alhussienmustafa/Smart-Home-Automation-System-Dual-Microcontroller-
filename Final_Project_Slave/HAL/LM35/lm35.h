#ifndef LM35_H_
#define LM35_H_

#include "../../LIB/std_types.h"

// Sensor Configuration
#define LM35_CHANNEL_ID      0      // ADC Channel 0 for LM35
#define ADC_REF_VOLT_VALUE   5000u  // in millivolts (5V)
#define LM35_MV_PER_DEG      10u    // 10 mV per °C

// Function Prototypes
u16 LM35_getTemperature(void);

#endif // LM35_H_
