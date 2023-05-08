/*
* HEEPROM_Program.c
*
*  Created on: Feb 3, 2023
*      Author: hp
*/

#include "HEEPROM_Interface.h"

Uchar8_t arr_g_ReadBuffer[EEPROM_PAGE_SIZE];



/**
* \brief : This Function Just Call To Initialize I2C as Master
*
* \param : Void
*
* \return void
*/
void eeprom_init(void)
{
	i2c_init_master(); // call function that init I2c Master
}

/**
* \brief : This Function Call To Make The Sequence Of I2C Frame To Write Byte On A Device
*
* \param : Uint16_t address : This Is Device Address
*		 : Uchar8_t data : This Is Data That Will Be Write
*
* \return void
*/
void eeprom_write_byte(Uint16_t address, Uchar8_t data)
{
	
	i2c_start(); // Send Start Bit On I2c
	i2c_send_slave_address_with_write_req(0x50);// Send Slave Address With Write Bit On I2c
	i2c_write_byte(address >> 8); // Write Byte Contain Device Address Shifted By 8 On I2c
	i2c_write_byte(address); // Write Byte Contain Device Address On I2c
	i2c_write_byte(data); // Write Byte Contain Data On I2c
	i2c_stop(); // Send Stop Bit On I2c
}

/**
* \brief : This Function Call To Make The Sequence Of I2C Frame To Read Byte On A Device
*
* \param : Uint16_t address : This Is Device Address
*
* \return Uchar8_t : Function Will Return Uchar8_t Contain The Data
*/
Uchar8_t eeprom_read_byte(Uint16_t address)
{
	Uchar8_t data = 0;
	i2c_start();// Send Start Bit On I2c
	i2c_send_slave_address_with_write_req(0x50);// Send Slave Address With Write Bit On I2c
	i2c_write_byte(address >> 8);// Write Byte Contain Device Address Shifted By 8 On I2c
	i2c_write_byte(address & 0xFF);// Write Byte Contain Device Address On I2c
	i2c_repeated_start();// Send Repeated Start Bit On I2c
	i2c_send_slave_address_with_read_req(0x50);// Send Slave Address With Read Bit On I2c
	data = i2c_read_byte_nack();// Read Byte Contain Data On I2c With No Ack
	i2c_stop();// Send Stop Bit On I2c
	return data;//Return The Data That Been Read
}



/**
* \brief : This Function Call When You Need To Write A String In The EEPROM
*
* \param : Uint16_t address : This Is Device Address
*		 : Uchar8_t *str	: This Pointer Will Store The Address Of The Array Of The Chars
* \return  Void
*/
void eeprom_write_string(Uint16_t Copy_u8Address, const Uchar8_t* str)
{
	Uchar8_t i = 0;
	
	i2c_start();// Send Start Bit On I2c
	i2c_send_slave_address_with_write_req(0x50);// Send Slave Address With Write Bit On I2c
	i2c_write_byte(Copy_u8Address >> 8);// Write Byte Contain Device Address Shifted By 8 On I2c
	i2c_write_byte(Copy_u8Address & 0xFF);// Write Byte Contain Device Address On I2c
	
	while(str[i] != '\0') // Loop Until The End Of The String
	{
		//_delay_ms(50);
		i2c_write_byte(str[i++]);//Call This Function To Write Char In EEPROM And Increment The Address And Index
	}
	_delay_ms(50);
	i2c_write_byte('\0');//Call This Function To Write Null After The Last Char Of The String To Know Where The String Is End
	i2c_stop();// Send Stop Bit On I2c
}

/**
* \brief : This Function Call When You Need To Read A String From The EEPROM
*
* \param : Uint16_t address : This Is Device Address
*		 : Uchar8_t *str	: This Pointer Will Store The Address Of The Array Of The Chars That Will Return String In It
* \return  Void
*/
void eeprom_read_string(Uint16_t Copy_u8Address, Uchar8_t* str)
{
	Uchar8_t len = 0;
	do
	{
		//_delay_ms(50);
		str[len] = eeprom_read_byte(Copy_u8Address++);//Call This Function To Read Char From EEPROM And Increment The Address And Index
	}
	while(str[len++] != '\0');// Loop Until The End Of The String
}

