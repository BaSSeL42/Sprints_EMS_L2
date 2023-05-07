/*
 * DIO_Private.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_DIO_DIO_PRIVATE_H_
#define MCAL_DIO_DIO_PRIVATE_H_

#define PORTA_REG	(volatile Uchar8_t*)(0x3B)
#define DDRA_REG	(volatile Uchar8_t*)(0x3A)
#define PINA_REG	(volatile Uchar8_t*)(0x39)

#define PORTB_REG	(volatile Uchar8_t*)(0x38)
#define DDRB_REG	(volatile Uchar8_t*)(0x37)
#define PINB_REG	(volatile Uchar8_t*)(0x36)

#define PORTC_REG	(volatile Uchar8_t*)(0x35)
#define DDRC_REG	(volatile Uchar8_t*)(0x34)
#define PINC_REG	(volatile Uchar8_t*)(0x33)

#define PORTD_REG	(volatile Uchar8_t*)(0x32)
#define DDRD_REG	(volatile Uchar8_t*)(0x31)
#define PIND_REG	(volatile Uchar8_t*)(0x30)

#endif /* 04_MCAL_DIO_DIO_PRIVATE_H_ */