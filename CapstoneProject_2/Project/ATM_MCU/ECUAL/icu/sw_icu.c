/*
 * sw_icu.c
 *
 * Created: 5/2/2023 2:02:01 PM
 *  Author: ME
 */ 

#include "../../Common/STD_Types.h"

#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/timer1/tim1_interface.h"
#include "../../MCAL/extint/extinterrupt.h"

#include "sw_icu.h"

Uint16_t u16_g_TimerCount, u16_g_msTime;
Uchar8_t EnterCheck;
Uchar8_t ZeroCheck;

void (*RisingEdge_CBF)(void) = NULL; 
void (*FallingEdge_CBF)(void) = NULL; 


void SwICU_Init(void)
{
	DIO_s8SETPinDir(DIO_PINB_2, INPUT);
	/* Set extint to be triggered on rising edge at first (button is pulled down) */
	EXTINT_init(EXTINT2, RISING_EDGE);
	
// 	RisingEdge_CBF = EXTI2_RisingEdgeNotification;
// 	FallingEdge_CBF = EXTI2_FallingEdgeNotification;
		
	EXTINT_CallBack(EXTINT2, EXTI2_RisingEdgeNotification);
}

Uint16_t SwICU_GetTime(Uint16_t u16_a_TimCount)
{
	Uint16_t u16_l_msTime;
	float32_t f32_l_TickTime;
	
	f32_l_TickTime = TIM1_GetTickTime();
	u16_l_msTime = (Uint16_t)(f32_l_TickTime * u16_a_TimCount);

	return u16_l_msTime;
}



void EXTI2_RisingEdgeNotification(void)
{
	/* Start Timer */
	TIM1_Start(TIM1_CLK_DIV_BY_1024);
	
	/* Set the interrupt to be triggered on a falling edge */
	EXTINT_init(EXTINT2, FALLING_EDGE);
	EXTINT_CallBack(EXTINT2, EXTI2_FallingEdgeNotification);
}


void EXTI2_FallingEdgeNotification(void)
{		
	/* Get timer value */
	u16_g_TimerCount = TIM1_GetValue();
	
	/* Stop the timer */
	TIM1_Stop();
	
	u16_g_msTime = SwICU_GetTime(u16_g_TimerCount);

	/* Set the interrupt to be triggered on a falling edge */
	EXTINT_init(EXTINT2, RISING_EDGE);
	EXTINT_CallBack(EXTINT2, EXTI2_RisingEdgeNotification);
	
	/* Check Enter or Zero */
	if(u16_g_msTime >= (Uint16_t)2000) EnterCheck = 1;
	else ZeroCheck = 1;
}


