/*============================== Includes ==============================*/
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"
#include "../../Common/vect_table.h"

#include "tim1_register.h"
#include "tim1_private.h"
#include "tim1_interface.h"

/*========================= Global Variables ========================*/
/* prescaler options */
static Uint16_t arr_gs_prescalers[] = {1,8,64,265,1024};

/*========================= Function Implementation ========================*/
en_TIMErrorState_t TIM1_Init(void)
{
	/* Choose Normal Mode */
	TCCR1A &= ~(1 << TCCR1A_WGM10);
	TCCR1A &= ~(1 << TCCR1A_WGM11);
	TCCR1B &= ~(1 << TCCR1B_WGM12);
	TCCR1B &= ~(1 << TCCR1B_WGM13);

	TCNT1 = 0;
	
	return TIM_OK;
}

en_TIMErrorState_t TIM1_Start(en_ICU_Prescaler_t u8_a_prescaler)
{
	en_TIMErrorState_t u8_l_ErrorState = TIM_OK;
		
	/* Clear the prescaler bits */
	TCCR1B &= TIM1_CLK_MASK;
	/* Set prescaler value */
	TCCR1B |= TIM1_PRESCALER;
	
	
	return u8_l_ErrorState;
}

void TIM1_Stop(void)
{
	/* Clear the prescaler bits */
	TCCR1B &= TIM1_CLK_MASK;
	TCNT1 = 0;
}

void TIM1_SetValue(Uint16_t u16_a_startValue)
{
	TCNT1 = u16_a_startValue;
}

Uint16_t TIM1_GetValue(void)
{
	return TCNT1;
}


float32_t TIM1_GetTickTime(void)
{
	return ((float32_t)arr_gs_prescalers[TIM1_PRESCALER-1]/(TIM1_CLK_MUL*1000));
}


