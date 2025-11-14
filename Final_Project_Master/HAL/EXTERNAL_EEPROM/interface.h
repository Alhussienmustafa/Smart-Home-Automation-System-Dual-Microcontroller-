/*
 * EEPROM.h
 *
 *  Created on: 17 Sep 2025
 *      Author: AlHussien Mustafa
 */

#ifndef MCAL_EEPROM_INTERFACE_H_
#define MCAL_EEPROM_INTERFACE_H_

#include "private.h"
#include "../../LIB/std_types.h"
#include "../../MCAL/TWI_DRIVER/TWI_interface.h"
#include <util/delay.h>

#define EEPROM_FIXED_ADDRESS 0x50   // 24C02/04 address (A2,A1,A0=0)

void EEPROM_writeByte(u16 addr, u8 data);
void EEPROM_readByte(u16 addr, u8 *data);

#endif /* MCAL_EEPROM_INTERFACE_H_ */
