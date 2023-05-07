/*
 * HTimer.h
 *
 *  Created on: Apr 5, 2023
 *      Author: hp
 */

#ifndef HAL_HTIMER_HTIMER_H_
#define HAL_HTIMER_HTIMER_H_


/*************************************************************************************************************
 * 							User defined data type
 ************************************************************************************************************/
typedef enum
{
	HTIMER_NOK = 0,
	HTIMER_OK

}enu_HTimerError_t;



typedef void(*ptr_funcc)(void);

/*************************************************************************************************************
 * 							Function Prototype
 ************************************************************************************************************/
enu_HTimerError_t HTimer_enInit(void);

void HTimer_vidDelayMs( Uint32_t u32_delay );

enu_HTimerError_t HTimer_enStop(void);

enu_HTimerError_t HTimer_enCBF(ptr_funcc pFunc);



#endif /* HAL_HTIMER_HTIMER_H_ */
