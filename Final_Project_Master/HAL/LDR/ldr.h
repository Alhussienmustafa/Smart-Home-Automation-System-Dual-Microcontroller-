#ifndef LDR_H_
#define LDR_H_

#include "../../MCAL/ADC_DRIVER/ADC_interface.h"
#include "../../LIB/std_types.h"

// Define your LDR connection
#define LDR_CHANNEL     1     // ADC channel where LDR is connected
#define LDR_VCC_MV      5000  // Supply voltage in millivolts

// Function Prototypes
u16 LDR_getVoltage(void);         // returns LDR voltage in mV
u32 LDR_getResistance(void);      // returns LDR resistance in ohms
u8  LDR_getLightIntensity(void);  // returns intensity in %

#endif // LDR_H_
