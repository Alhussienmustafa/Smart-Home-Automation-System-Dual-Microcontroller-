#include "ADC_interface.h"
#include "ADC_private.h"
#include "../../LIB/bit_math.h"

void ADC_init(u8 ref_voltage, u8 prescaler){
    // Choose VREF
    switch(ref_voltage){
        case AREF:
            CLEAR_BIT(ADMUX, REFS0);
            CLEAR_BIT(ADMUX, REFS1);
            break;
        case AVCC:
            SET_BIT(ADMUX, REFS0);
            CLEAR_BIT(ADMUX, REFS1);
            break;
        case INT2_56:
            SET_BIT(ADMUX, REFS0);
            SET_BIT(ADMUX, REFS1);
            break;
        default:
            break;
    }

    // Adjust Result: Right Adjust (ADLAR = 0)
    CLEAR_BIT(ADMUX, ADLAR);

    // Enable ADC
    SET_BIT(ADCSRA, ADEN);

    // Disable ADC Interrupt (polling mode)
    CLEAR_BIT(ADCSRA, ADIE);

    // Choose Prescaler
    switch(prescaler){
        case ADC_PRESCALER_2:
            SET_BIT(ADCSRA, ADPS0);
            CLEAR_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS2);
            break;
        case ADC_PRESCALER_4:
            CLEAR_BIT(ADCSRA, ADPS0);
            SET_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS2);
            break;
        case ADC_PRESCALER_8:
            SET_BIT(ADCSRA, ADPS0);
            SET_BIT(ADCSRA, ADPS1);
            CLEAR_BIT(ADCSRA, ADPS2);
            break;
        case ADC_PRESCALER_16:
            CLEAR_BIT(ADCSRA, ADPS0);
            CLEAR_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS2);
            break;
        case ADC_PRESCALER_32:
            SET_BIT(ADCSRA, ADPS0);
            CLEAR_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS2);
            break;
        case ADC_PRESCALER_64:
            CLEAR_BIT(ADCSRA, ADPS0);
            SET_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS2);
            break;
        case ADC_PRESCALER_128:
            SET_BIT(ADCSRA, ADPS0);
            SET_BIT(ADCSRA, ADPS1);
            SET_BIT(ADCSRA, ADPS2);
            break;
        default:
            break;
    }
}

u16 ADC_readChannel(u8 channel_num){
    // Select channel (0 → 7)
    channel_num &= 0x07;        // mask to keep only 3 bits
    ADMUX = (ADMUX & 0xE0) | channel_num;  // keep REFS1:0 + ADLAR bits, set MUX4:0

    // Start conversion
    SET_BIT(ADCSRA, ADSC);

    // Wait for conversion to finish (ADIF = 1)
    while(BIT_IS_CLEAR(ADCSRA, ADIF));

    // Clear ADIF by writing 1
    SET_BIT(ADCSRA, ADIF);

    // Return result (10-bit, right adjusted)
    return ADC;
}
