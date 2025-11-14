#ifndef MCAL_TWI_DRIVER_TWI_INTERFACE_H_
#define MCAL_TWI_DRIVER_TWI_INTERFACE_H_

#include "../../LIB/std_types.h"

/* Status Codes */
#define TWI_START           0x08
#define TWI_REP_START       0x10
#define TWI_MT_SLA_W_ACK    0x18
#define TWI_MT_SLA_R_ACK    0x40
#define TWI_MT_DATA_ACK     0x28
#define TWI_MR_DATA_ACK     0x50
#define TWI_MR_DATA_NACK    0x58
#define TWI_SR_SLA_ACK      0x60
#define TWI_SR_DATA_ACK     0x80
#define TWI_ST_SLA_ACK      0xA8
#define TWI_ST_DATA_ACK     0xB8

/* Prescaler Options */
typedef enum {
    TWI_PRESCALER_1 = 0,
    TWI_PRESCALER_4,
    TWI_PRESCALER_16,
    TWI_PRESCALER_64
} TWI_PrescalerType;

/* Operation Modes */
typedef enum {
    TWI_MODE_MASTER = 0,
    TWI_MODE_SLAVE
} TWI_ModeType;

/* Config Structure */
typedef struct {
    u32 cpu_freq;       /* e.g. 8000000UL */
    u32 scl_freq;       /* e.g. 100000UL */
    TWI_PrescalerType prescaler;
    TWI_ModeType mode;
    u8 slave_address;   /* valid if SLAVE */
} TWI_ConfigType;

/* Function Prototypes */
void TWI_init(const TWI_ConfigType *config);

/* Master APIs */
u8 TWI_start(void);
u8 TWI_repeatedStart(void);
u8 TWI_writeByte(u8 data);
u8 TWI_readByteWithACK(u8 *data);
u8 TWI_readByteWithNACK(u8 *data);
void TWI_stop(void);

/* Slave APIs */
u8 TWI_slaveListen(void);
u8 TWI_slaveReceiveByte(u8 *data);
u8 TWI_slaveSendByte(u8 data);

/* Utility */
u8 TWI_getStatus(void);

#endif /* MCAL_TWI_DRIVER_TWI_INTERFACE_H_ */
