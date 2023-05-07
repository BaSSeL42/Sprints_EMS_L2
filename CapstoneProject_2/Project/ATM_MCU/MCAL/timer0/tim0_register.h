
#ifndef TIM_REGISTER_H_
#define TIM_REGISTER_H_



/******************* Timer 0 ***********************/
#define	 TCNT0					  *((volatile Uchar8_t*)0x52)	
#define  TCCR0                    *((volatile Uchar8_t*)0x53)			/* Timer/Counter Control Register */
#define  TCCR0_WGM00				6							/* Waveform generation mode bit 0 */
#define  TCCR0_WGM01				3							/* Waveform generation mode bit 1 */
#define  TCCR0_CS02					2			/* prescaler bit 2 */
#define  TCCR0_CS01					1
#define  TCCR0_CS00					0

#define  OCR0                     *((volatile Uchar8_t*)0x5c)			/* Output compare register */

#define	 TIFR					  *((volatile Uchar8_t*)0x58)	
#define  TIFR_TOV0					0
#define  TIMSK                    *((volatile Uchar8_t*)0x59)
#define  TIMSK_TOIE0				0
#define  TIMSK_OCIE0				1							/* Output compare 0 interrupt enable */
#define  TIMSK_TOIE1                2
#define  TIMSK_OCIE1B               3
#define  TIMSK_OCIE1A               4
#define  TIMSK_TICIE1				5							/* input capture interrupt enable */
#define  TIMSK_TOIE2                6
#define  TIMSK_OCIE2                7

#endif /* TIM_REGISTER_H_ */