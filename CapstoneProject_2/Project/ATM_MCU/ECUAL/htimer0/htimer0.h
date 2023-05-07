
#ifndef HTIMER0_H_
#define HTIMER0_H_

typedef enum
{
	uSeconds,
	mSeconds,
	Seconds
}en_timeUnits_t;

typedef enum
{
	HTIM_OK,
	HTIM_NOK
}en_HTIMErrorState_t;

/**
 * \brief Generate Synchronous delay (busy waiting)
 * 
 * \param Copy_delayTime 
 * \param Copy_timeUnit
 * 
 * \return EN_TIMErrorState_t
 */
en_HTIMErrorState_t HTIM0_SyncDelay(Uint32_t u32_a_delay, en_timeUnits_t u8_a_timeUnit);


/**
 * \brief Generate an asynchronous delay using the timer0
 *		  OVF interrupt
 * \param u32_a_delay
 * \param u8_a_timeUnit
 * \param Copy_pvCallbackFn
 * 
 * \return en_TIMErrorState_t
 */
en_HTIMErrorState_t HTIM0_AsyncDelay(Uint32_t u32_a_delay, en_timeUnits_t u8_a_timeUnit, void (*Copy_pvCallbackFn)(void));

/**
 * \brief Function to end a delay asynchronously 
 *		  (should only be called in an ISR/Callback function)
 * 
 * \return void
 */
void HTIM0_AsyncEndDelay();


#endif /* HTIMER0_H_ */