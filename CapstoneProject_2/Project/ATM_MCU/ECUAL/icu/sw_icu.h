/*
 * sw_icu.h
 *
 * Created: 5/2/2023 2:02:20 PM
 *  Author: ME
 */ 


#ifndef SW_ICU_H_
#define SW_ICU_H_


void SwICU_Init(void);
Uint16_t SwICU_GetTime(Uint16_t u16_a_TimCount);
void EXTI2_RisingEdgeNotification(void);
void EXTI2_FallingEdgeNotification(void);


#endif /* SW_ICU_H_ */