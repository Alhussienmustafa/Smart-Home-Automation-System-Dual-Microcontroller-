#include "../../MCAL/ADC_DRIVER/ADC_interface.h"
#include "lm35.h"

// Function to get temperature reading from LM35
u16 LM35_getTemperature(void)
{
    u16 adc_value = ADC_readChannel(LM35_CHANNEL_ID);

    // Temperature = (ADC_value * Vref) / (ADC_max * 10mV)
    u16 temperature = ((u32)adc_value * ADC_REF_VOLT_VALUE) / (ADC_MAX_VALUE * LM35_MV_PER_DEG);
    return temperature;   // returns °C
}
