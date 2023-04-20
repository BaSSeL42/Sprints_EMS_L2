/*============================== Includes ==============================*/
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"
#include "../../Common/vect_table.h"

#include "tim0_register.h"
#include "tim0_private.h"
#include "tim0_interface.h"

/*========================= Global Variables ========================*/
Uchar8_t u8_g_TotalOVF = 0;
static Uchar8_t u8_gs_OVFCount = 0;

void (*TIM0_OVFCallbackFn)(void) = NULL;

/*========================= Function Implementation ========================*/
en_TIMErrorState_t TIM0_voidInit(en_TIMMode_t u8_a_Mode)
{
	Uchar8_t u8_l_T0Mode;
	
	switch(u8_a_Mode)
	{
		case NormalMode:   u8_l_T0Mode = TIM0_NORMAL;	 break;
		case PWM_Mode:     u8_l_T0Mode = TIM0_PWM;	     break;
		case CTC_Mode:	   u8_l_T0Mode = TIM0_CTC;		 break;
		case FastPWM_Mode: u8_l_T0Mode = TIM0_FAST_PWM; break;
		default: return TIM_NOK;
	}
	
	/* Clear the timer0 mode bit */
	TCCR0 &= TIMER0_MODE_MASK;
	/* Set the bits to the given value */
	TCCR0 |= u8_l_T0Mode;
	
	return TIM_OK;
}

en_TIMErrorState_t TIM0_Start(en_TIM_CLK_SELECT_t u8_a_prescaler)
{
	en_TIMErrorState_t u8_l_ErrorState = TIM_OK;
	
	/* Check that prescaler is valid */
	if(u8_a_prescaler > TIM_NO_CLOCK && u8_a_prescaler <= TIM_EXTERNAL_RISING_EDGE)
	{
		/* Clear the prescaler bits */
		TCCR0 &= TIM0_CLK_MASK;
		/* Set prescaler value */
		TCCR0 |= u8_a_prescaler;
	}
	else
	{
		u8_l_ErrorState = TIM_NOK;
	}
	
	return u8_l_ErrorState;
}

void TIM0_Stop()
{
	/* Clear the prescaler bits */
	TCCR0 &= TIM0_CLK_MASK;
	TCNT0 = 0;
	CLEAR_BIT(TIFR, TIFR_TOV0);
	u8_gs_OVFCount = 0;
}

void TIM0_SetValue(Uchar8_t u8_a_startValue)
{
	TCNT0 = u8_a_startValue;
}

/**
* \brief Function to get the value of the overflow flag
*		  of timer 0
* \param u8_a_FlagValue reference to a variable to store flag value
*
* \return en_TIMErrorState_t
*/
en_TIMErrorState_t TIM0_GetOVF(Uchar8_t* u8_a_FlagValue)
{
	if(u8_a_FlagValue != NULL)
	{
		*u8_a_FlagValue = GET_BIT(TIFR, TIFR_TOV0);
	}
	else
	{
		return TIM_NOK;
	}
	
	return TIM_OK;
}

/**
 * \brief Function to clear timer 0 overflow flag
 *
 * \return void
 */
void TIM0_ClearOVF(void)
{
	SET_BIT(TIFR, TIFR_TOV0);
}

/**
* \brief Function to get the timer state (running/stopped)
*
* \param u8_a_State reference to a variable to store timer state
*
* \return en_TIMErrorState_t
*/
en_TIMErrorState_t TIM0_GetState(en_TIMState_t* u8_a_State)
{
	if(u8_a_State != NULL)
	{
		if (TCCR0 & 0b00000111 != 0) 
		{
			*u8_a_State = TIM0_RUNNING;
		}
		else
		{
			*u8_a_State = TIM0_STOPPED;
		}
	}
	else
	{
		return TIM_NOK;
	}
	
	return TIM_OK;
}

void TIM0_EnableOVFInterrupt(void)
{
	SET_BIT(TIMSK, TIMSK_TOIE0);
}

void TIM0_DisableOVFInterrupt(void)
{
	CLEAR_BIT(TIMSK, TIMSK_TOIE0);
}

en_TIMErrorState_t TIM0_SetOVFCallback(void (*pv_a_CallbackFn)(void))
{
	TIM0_OVFCallbackFn = pv_a_CallbackFn;
}



/*========================== ISRs =============================*/

ISR(TIM0_OVF_INT)
{
	if(TIM0_OVFCallbackFn != NULL)
	{
		/* Delay is complete */
		if(u8_gs_OVFCount == u8_g_TotalOVF)
		{
			/* Stop the timer */
			TIM0_Stop();
			
			/* Reset the OVF counter */
			u8_gs_OVFCount = 0;
			
			/* Disable OVF interrupt */
			CLEAR_BIT(TIMSK, TIMSK_TOIE0);
			
			/* Call the Callback function */
			TIM0_OVFCallbackFn();
		}
		else
		{
			/* Increment the overflow count */
			u8_gs_OVFCount++;
		}
	}
}


