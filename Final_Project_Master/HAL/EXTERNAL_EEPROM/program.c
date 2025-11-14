/*
 * EEPROM.c
 *
 *  Created on: 17 Sep 2025
 *      Author: AlHussien Mustafa
 */


#include "interface.h"

void EEPROM_writeByte(u16 addr, u8 data) {
    TWI_start();
    TWI_writeByte((u8)((EEPROM_FIXED_ADDRESS << 1) | ((addr & 0x0700) >> 7)) | 0); // SLA+W
    TWI_writeByte((u8)addr);   // Low address
    TWI_writeByte(data);
    TWI_stop();
    _delay_ms(10);
}

void EEPROM_readByte(u16 addr, u8 *data) {
    TWI_start();
    TWI_writeByte((u8)((EEPROM_FIXED_ADDRESS << 1) | ((addr & 0x0700) >> 7)) | 0); // SLA+W
    TWI_writeByte((u8)addr);
    TWI_repeatedStart();
    TWI_writeByte((u8)((EEPROM_FIXED_ADDRESS << 1) | ((addr & 0x0700) >> 7)) | 1); // SLA+R
    TWI_readByteWithNACK(data);
    TWI_stop();
}
