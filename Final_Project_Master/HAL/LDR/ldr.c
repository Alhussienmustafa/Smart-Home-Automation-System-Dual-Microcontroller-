#include "ldr.h"

#define R_FIXED   10000UL   // fixed resistor value (10kohm)

u16 LDR_getVoltage(void)
{
    u16 adc_value = ADC_readChannel(LDR_CHANNEL);
    // Convert ADC value to mV
    u16 voltage = ((u32)adc_value * LDR_VCC_MV) / 1023;
    return voltage;
}

u32 LDR_getResistance(void)
{
    u16 v_out = LDR_getVoltage();

    if (v_out == 0) return 0;  // avoid division by zero

    // Voltage divider formula:
    // R_ldr = R_fixed * (Vcc - Vout) / Vout
    u32 r_ldr = ( (u32)R_FIXED * (LDR_VCC_MV - v_out) ) / v_out;
    return r_ldr;
}

u8 LDR_getLightIntensity(void)
{
    u16 v_out = LDR_getVoltage();

    // Simple linear mapping: 0V -> 0%, Vcc -> 100%
    u8 intensity = ((u32)v_out * 100) / LDR_VCC_MV;
    return intensity;
}
