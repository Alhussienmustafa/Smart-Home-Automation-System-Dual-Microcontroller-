/*
 * private.h
 *
 *  Created on: 17 Sep 2025
 *      Author: AlHussien Mustafa
 */

#ifndef MCAL_EEPROM_PRIVATE_H_
#define MCAL_EEPROM_PRIVATE_H_

#include "../../LIB/std_types.h"

/* EEPROM Control Register */
#define EECR    (*(volatile u8*)0x3C)
#define EERE    0   // EEPROM Read Enable
#define EEWE    1   // EEPROM Write Enable
#define EEMWE   2   // EEPROM Master Write Enable

/* EEPROM Data Register */
#define EEDR    (*(volatile u8*)0x3D)

/* EEPROM Address Register */
#define EEAR    (*(volatile u16*)0x3E)

#endif /* MCAL_EEPROM_PRIVATE_H_ */
