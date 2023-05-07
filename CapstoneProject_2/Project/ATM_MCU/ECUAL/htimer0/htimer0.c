/*======================================== Includes =======================================*/
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"

#include "../../MCAL/timer0/tim0_interface.h"

#include "htimer0_private.h"
#include "htimer0.h"

/*==================================== Global Variables ====================================*/
/* prescaler options */
static Uint16_t arr_gs_prescalers[] = {1,8,64,265,1024};

extern Uchar8_t u8_g_TotalOVF;

/*================================= Function Implementation =================================*/

en_HTIMErrorState_t HTIM0_SyncDelay(Uint32_t u32_a_delay, en_timeUnits_t Copy_timeUnit)
{
	Uchar8_t u8_l_prescaler, Local_TotalOverFlows, Local_OverFlowCounter=0, u8_l_OverflowFlag, u8_l_TimState;
	Uint16_t Local_TotalTicks;
	float Local_TickTime;
	
	/* Get Value in micro seconds */
	if(Copy_timeUnit == Seconds)	{u32_a_delay *= SEC_TO_uSEC;}
	else if(Copy_timeUnit == mSeconds)	{u32_a_delay *= mSEC_TO_uSEC;}
	else if(Copy_timeUnit == uSeconds)	{/* Do Nothing */}
	else return TIM_NOK;
	
	/* Set prescaler according to delay time */
	if(u32_a_delay < MAX_CLK_DEV1_DELAY  )	{u8_l_prescaler = TIM_DIV_BY_1;}
	else if(u32_a_delay < MAX_CLK_DEV8_DELAY  ) {u8_l_prescaler = TIM_DIV_BY_8;}
	else if(u32_a_delay < MAX_CLK_DEV64_DELAY ) {u8_l_prescaler = TIM_DIV_BY_64;}
	else if(u32_a_delay < MAX_CLK_DEV256_DELAY) {u8_l_prescaler = TIM_DIV_BY_256;}
	else {u8_l_prescaler = TIM_DIV_BY_1024;}
	
	Local_TickTime = arr_gs_prescalers[u8_l_prescaler-1]/TIM0_PRESCALER;
	Local_TotalTicks = (Uint16_t)(u32_a_delay/Local_TickTime);
	Local_TotalOverFlows = Local_TotalTicks/TIM0_MAX_TICKS;
	
	/* Initialize timer in normal mode */
	TIM0_voidInit(NormalMode);
	
	/* Set timer start value */
	TIM0_SetValue(TIM0_MAX_TICKS-(Local_TotalTicks%TIM0_MAX_TICKS));
	
	/* Start Timer */
	TIM0_Start(u8_l_prescaler);
	
	while(Local_OverFlowCounter <= Local_TotalOverFlows)
	{
		/* Wait until the overflow flag is raised */
		do
		{
			TIM0_GetOVF(&u8_l_OverflowFlag);
			TIM0_GetState(&u8_l_TimState);
		}
		while(!u8_l_OverflowFlag && u8_l_TimState);
		
		/* Clear the overflow flag */
		TIM0_ClearOVF();
		
		Local_OverFlowCounter++;
	}
	
	TIM0_Stop();
	
	return TIM_OK;
}

en_HTIMErrorState_t HTIM0_AsyncDelay(Uint32_t u32_a_delay, en_timeUnits_t u8_a_timeUnit, void (*Copy_pvCallbackFn)(void))
{
	Uchar8_t u8_l_prescaler, u8_l_TimState;
	Uint16_t u8_l_TotalTicks;
	float Local_TickTime;
	
	/* Check whether timer is Idle or Busy */
	TIM0_GetState(&u8_l_TimState);
	if(u8_l_TimState == TIM0_RUNNING) return TIM_NOK;
	
	/* Get Value in micro seconds */
	if(u8_a_timeUnit == Seconds)	{u32_a_delay *= SEC_TO_uSEC;}
	else if(u8_a_timeUnit == mSeconds)	{u32_a_delay *= mSEC_TO_uSEC;}
	else if(u8_a_timeUnit == uSeconds)	{/* Do Nothing */}
	else return TIM_NOK;
	
	/* Set prescaler according to delay time */
	if(u32_a_delay < MAX_CLK_DEV1_DELAY  )	{u8_l_prescaler = TIM_DIV_BY_1;}
	else if(u32_a_delay < MAX_CLK_DEV8_DELAY  ) {u8_l_prescaler = TIM_DIV_BY_8;}
	else if(u32_a_delay < MAX_CLK_DEV64_DELAY ) {u8_l_prescaler = TIM_DIV_BY_64;}
	else if(u32_a_delay < MAX_CLK_DEV256_DELAY) {u8_l_prescaler = TIM_DIV_BY_256;}
	else {u8_l_prescaler = TIM_DIV_BY_1024;}
	
	Local_TickTime = arr_gs_prescalers[u8_l_prescaler-1]/TIM0_PRESCALER;
	u8_l_TotalTicks = (Uint16_t)(u32_a_delay/Local_TickTime);
	u8_g_TotalOVF = u8_l_TotalTicks/TIM0_MAX_TICKS;
	
	/*Set the callback function */
	TIM0_SetOVFCallback(Copy_pvCallbackFn);
	
	/* Set timer start value */
	TIM0_SetValue(TIM0_MAX_TICKS-(u8_l_TotalTicks%TIM0_MAX_TICKS));
	
	/* Enable Timer 0 overflow interrupt */
	//SET_BIT(TIMSK, TIMSK_TOIE0);
	TIM0_EnableOVFInterrupt();
	
	/* Start Timer */
	TIM0_Start(u8_l_prescaler);
	
	return TIM_OK;
}


/**
 * \brief Function to end a delay asynchronously 
 *		  (should only be called in an ISR/Callback function)
 * 
 * \return void
 */
void HTIM0_AsyncEndDelay()
{
	TIM0_Stop();
	TIM0_DisableOVFInterrupt();
}
