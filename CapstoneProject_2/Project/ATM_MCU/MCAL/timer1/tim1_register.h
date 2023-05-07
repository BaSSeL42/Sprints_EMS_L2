
#ifndef TIM1_REGISTER_H_
#define TIM1_REGISTER_H_

#define  TCCR1                     *((volatile Uint16_t*)0x4e)
#define  TCCR1A                    *((volatile Uchar8_t*)0x4f)
#define  TCCR1B                    *((volatile Uchar8_t*)0x4e)
#define  TCCR1A_WGM10				0			/* waveform generation mode bit 0 */
#define  TCCR1A_WGM11				1
#define  TCCR1A_COM1A0				6				/* prescaler bit 2 */
#define  TCCR1A_COM1A1				7

#define  TCCR1B_ICRS1				6				/* Input capture edge select */
#define  TCCR1B_WGM13				4
#define  TCCR1B_WGM12				3

#define  TCNT1					   *((volatile Uint16_t*)0x4c)
#define  TIMSK                    *((volatile Uchar8_t*)0x59)

#endif /* TIM_REGISTER_H_ */