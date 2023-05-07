/*
 * HEEPROM_Interface.h
 *
 *  Created on: Feb 3, 2023
 *      Author: hp
 */

#ifndef HAL_EEPROM_HEEPROM_INTERFACE_H_
#define HAL_EEPROM_HEEPROM_INTERFACE_H_

#include <string.h>
#include <util/delay.h>
#include "../../MCAL/i2c/MI2C_Interface.h"
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"

//#define EEPROM_ADDRESS 			0xA0
#define EEPROM_PAGE_SIZE 		64
#define PAGE_ADDRESS			0x0000


void eeprom_init(void);
void eeprom_write_byte(Uint16_t address, Uchar8_t data);
void eeprom_write_string(Uint16_t Copy_u8Address, const Uchar8_t* str);
void eeprom_read_string(Uint16_t Copy_u8Address, Uchar8_t* str);
Uchar8_t eeprom_read_byte(Uint16_t address);
void EEPROM_readPage(Uint16_t u16_a_pageAddress , Uchar8_t *str);


#endif /* HAL_EEPROM_HEEPROM_INTERFACE_H_ */
