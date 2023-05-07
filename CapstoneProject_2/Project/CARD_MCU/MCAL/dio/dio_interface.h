/*
 * DIO_interface.h
 *
 *  Created on: 5 Apr 2023
 *      Author: 20101
 */

#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_


#define E_OK	0
#define E_NOK	-1

#define PORT_INPUT		0x00
#define PORT_OUTPUT		0xff

typedef enum
{
	DIO_PINA_0 = 0,
	DIO_PINA_1,
	DIO_PINA_2,
	DIO_PINA_3,
	DIO_PINA_4,
	DIO_PINA_5,
	DIO_PINA_6,
	DIO_PINA_7,

	DIO_PINB_0,
	DIO_PINB_1,
	DIO_PINB_2,
	DIO_PINB_3,
	DIO_PINB_4,
	DIO_PINB_5,
	DIO_PINB_6,
	DIO_PINB_7,

	DIO_PINC_0,
	DIO_PINC_1,
	DIO_PINC_2,
	DIO_PINC_3,
	DIO_PINC_4,
	DIO_PINC_5,
	DIO_PINC_6,
	DIO_PINC_7,

	DIO_PIND_0,
	DIO_PIND_1,
	DIO_PIND_2,
	DIO_PIND_3,
	DIO_PIND_4,
	DIO_PIND_5,
	DIO_PIND_6,
	DIO_PIND_7,

	PIN_INVALID,

}enu_pin;


typedef enum
{
	DIO_PORTA=0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD,
	PORT_INVALID,
}enu_port;

typedef enum
{
	INPUT = 0,
	OUTPUT,
	DIR_INVALID,

}enu_dir;

typedef enum
{
	LOW = 0,
	HIGH,
	VAL_INVALID,

}enu_val;


Uchar8_t DIO_s8SETPortDir(enu_port enPortCopy,  enu_dir enPortDir);
Uchar8_t DIO_s8SETPortVal(enu_port enPortCopy,  Uchar8_t u8PortVal);
Uchar8_t DIO_s8GETPortVal(enu_port enPortCopy,  Uchar8_t* pu8Val);

Uchar8_t DIO_s8SETPinDir (enu_pin enPinCopy, enu_dir enPortDir);
Uchar8_t DIO_s8SETPinVal (enu_pin enPinCopy, enu_val enPortVal);
Uchar8_t DIO_s8TOGPinVal (enu_pin enPinCopy);
Uchar8_t DIO_s8GETPinVal (enu_pin enPinCopy, Uchar8_t* pu8Val);


#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
