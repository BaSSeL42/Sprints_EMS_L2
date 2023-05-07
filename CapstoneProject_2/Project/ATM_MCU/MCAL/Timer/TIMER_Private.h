/*
 * TIMER_Private.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

/********************************* TIMER0 REGISTERS ******************************************/
#define TCCR0_REG 	(*(volatile Uchar8_t*)(0x53))
#define TCNT0_REG 	(*(volatile Uchar8_t*)(0x52))
#define OCR0_REG 	(*(volatile Uchar8_t*)(0x5C))

/********************************* TIMER1 REGISTERS ******************************************/
#define TCCR1A_REG 	(*(volatile Uchar8_t*)(0x4F))
#define TCCR1B_REG 	(*(volatile Uchar8_t*)(0x4E))
#define TCNT1H_REG 	(*(volatile Uchar8_t*)(0x4D))
#define TCNT1L_REG 	(*(volatile Uchar8_t*)(0x4C))
#define TCNT1_REG 	(*(volatile Uint16_t*)(0x4C))
#define OCR1AH_REG 	(*(volatile Uchar8_t*)(0x4B))
#define OCR1AL_REG 	(*(volatile Uchar8_t*)(0x4A))
#define OCR1A_REG 	(*(volatile Uint16_t*)(0x4A))

#define OCR1BH_REG 	(*(volatile Uchar8_t*)(0x49))
#define OCR1BL_REG 	(*(volatile Uchar8_t*)(0x48))
#define ICR1H_REG 	(*(volatile Uchar8_t*)(0x47))
#define ICR1L_REG 	(*(volatile Uchar8_t*)(0x46))
#define ICR1_REG 	(*(volatile Uint16_t*)(0x46))



/********************************* TIMER2 REGISTERS ******************************************/
#define TCCR2_REG 	(*(volatile Uchar8_t*)(0x45))
#define TCNT2_REG 	(*(volatile Uchar8_t*)(0x44))
#define OCR2_REG 	(*(volatile Uchar8_t*)(0x43))

/********************************* TIMER_ALL REGISTERS ******************************************/
#define TIFR_REG 	(*(volatile Uchar8_t*)(0x58))
#define TIMSK_REG 	(*(volatile Uchar8_t*)(0x59))
#define SREG_REG 	(*(volatile Uchar8_t*)(0x5F)) // for global interrupt






/* TCCRO REG */
#define CS00		0
#define CS01		1
#define CS02		2
#define WGM01		3
#define COM00		4
#define COM01		5
#define WGM00		6
#define FOC0		7

/* TIMSK REG */
#define TOIE0		0
#define OCIE0		1
#define TOIE1		2
#define OCIE1A		3
#define OCIE1B		4
#define TICIE1		5
#define TOIE2		6
#define OCIE2		7

/* TIFR REG */
#define TOV0		0
#define OCF0		1
#define TOV1		2
#define OCF1A		3
#define OCF1B		4
#define ICF1		5
#define TOV2		6
#define OCF2		7


/* SREG REG */
#define timer_I		7


#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
