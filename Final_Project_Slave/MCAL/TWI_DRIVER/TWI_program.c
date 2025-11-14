#include "TWI_interface.h"
#include "TWI_private.h"
#include "../../LIB/bit_math.h"
#include "../../MCAL/DIO_DRIVER/DIO_interface.h"

static TWI_ConfigType gl_TWI_config;

static u32 TWI_getPrescalerFactor(TWI_PrescalerType p) {
    switch (p) {
        case TWI_PRESCALER_1:  return 1UL;
        case TWI_PRESCALER_4:  return 4UL;
        case TWI_PRESCALER_16: return 16UL;
        case TWI_PRESCALER_64: return 64UL;
        default: return 1UL;
    }
}

static u8 TWI_calcTWBR(u32 cpu_freq, u32 scl_freq, TWI_PrescalerType prescaler) {
    u32 presFact = TWI_getPrescalerFactor(prescaler);
    if (scl_freq == 0) return 0;

    u32 tmp = (cpu_freq / scl_freq);
    if (tmp <= 16UL) return 0;

    tmp = (tmp - 16UL) / (2UL * presFact);
    if (tmp > 255UL) tmp = 255UL;

    return (u8)tmp;
}

void TWI_init(const TWI_ConfigType *config) {
    if (config == NULL) return;
    gl_TWI_config = *config;

    /* Configure prescaler */
    TWSR &= ~PRESCALER_MASK;
    switch (config->prescaler) {
        case TWI_PRESCALER_4:  TWSR |= (1 << TWPS0); break;
        case TWI_PRESCALER_16: TWSR |= (1 << TWPS1); break;
        case TWI_PRESCALER_64: TWSR |= (1 << TWPS1) | (1 << TWPS0); break;
        default: break;
    }

    if (config->mode == TWI_MODE_MASTER) {
        TWBR = TWI_calcTWBR(config->cpu_freq, config->scl_freq, config->prescaler);

        /* Configure SDA/SCL as input (external pull-ups required!) */
        DIO_voidSetPinDir(PORTC_ID, PIN0_ID, PIN_INPUT); // SDA
        DIO_voidSetPinDir(PORTC_ID, PIN1_ID, PIN_INPUT); // SCL
    }

    if (config->mode == TWI_MODE_SLAVE) {
        TWAR = (u8)((config->slave_address & 0x7F) << 1);
        DIO_voidSetPinDir(PORTC_ID, PIN0_ID, PIN_INPUT);
        DIO_voidSetPinDir(PORTC_ID, PIN1_ID, PIN_INPUT);
    }

    TWCR = (1 << TWEN);
}

/* Master Functions */
u8 TWI_start(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    return (TWSR & STATUS_MASK);
}

u8 TWI_repeatedStart(void) {
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    return (TWSR & STATUS_MASK);
}

void TWI_stop(void) {
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

u8 TWI_writeByte(u8 data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    return (TWSR & STATUS_MASK);
}

u8 TWI_readByteWithACK(u8 *data) {
    if (!data) return 0xFF;
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    *data = TWDR;
    return (TWSR & STATUS_MASK);
}

u8 TWI_readByteWithNACK(u8 *data) {
    if (!data) return 0xFF;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    *data = TWDR;
    return (TWSR & STATUS_MASK);
}

u8 TWI_getStatus(void) {
    return (TWSR & STATUS_MASK);
}

/* Slave Functions */
u8 TWI_slaveListen(void) {
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    return (TWSR & STATUS_MASK);
}

u8 TWI_slaveReceiveByte(u8 *data) {
    if (!data) return 0xFF;
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    *data = TWDR;
    return (TWSR & STATUS_MASK);
}

u8 TWI_slaveSendByte(u8 data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
    while (!GET_BIT(TWCR, TWINT));
    return (TWSR & STATUS_MASK);
}

