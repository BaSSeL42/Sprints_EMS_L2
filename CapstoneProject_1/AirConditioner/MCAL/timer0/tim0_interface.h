
#ifndef TIM_INTERFACE_H_
#define TIM_INTERFACE_H_

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define TIM0_PRESCALER		8

/* Asynchronous Delay Function States */
#define  DELAY_BUSY			0
#define  DELAY_IDLE			1

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/

typedef enum
{
	TIM_OK,
	TIM_NOK
}en_TIMErrorState_t;

typedef enum
{
	TIM0_STOPPED,
	TIM0_RUNNING
}en_TIMState_t;

typedef enum
{
	NormalMode,
	PWM_Mode,
	CTC_Mode,
	FastPWM_Mode
}en_TIMMode_t;

typedef enum
{
	TIM_NO_CLOCK             ,
	TIM_DIV_BY_1             ,
	TIM_DIV_BY_8             ,
	TIM_DIV_BY_64            ,
	TIM_DIV_BY_256           ,
	TIM_DIV_BY_1024          ,
	TIM_EXTERNAL_FALLING_EDGE,
	TIM_EXTERNAL_RISING_EDGE
}en_TIM_CLK_SELECT_t;


/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * \brief Initialize the timer with given mode
 * 
 * \param u8_a_Mode
 * 
 * \return EN_TIMErrorState_t
 */
en_TIMErrorState_t TIM0_voidInit(en_TIMMode_t u8_a_Mode);

/**
 * \brief Start the timer clock after prescaling it with given value 
 * 
 * \param u8_a_prescaler
 * 
 * \return EN_TIMErrorState_t
 */
en_TIMErrorState_t TIM0_Start(en_TIM_CLK_SELECT_t u8_a_prescaler);

/**
 * \brief Stop the timer
 * 
 * \return void
 */
void TIM0_Stop();

/**
 * \brief Set the timer to start from the given value
 * 
 * \param Copy_Value
 * 
 * \return void
 */
void TIM0_SetValue(Uchar8_t u8_a_startValue);

/**
 * \brief Function to get the value of the overflow flag
 *		  of timer 0
 * \param u8_a_FlagValue reference to a variable to store flag value
 * 
 * \return en_TIMErrorState_t
 */
en_TIMErrorState_t TIM0_GetOVF(Uchar8_t* u8_a_FlagValue);

/**
 * \brief Function to clear timer 0 overflow flag
 *
 * \return void
 */
void TIM0_ClearOVF(void);

/**
 * \brief Function to get the timer state (running/stopped)
 * 
 * \param u8_a_State reference to a variable to store timer state
 * 
 * \return en_TIMErrorState_t
 */
en_TIMErrorState_t TIM0_GetState(en_TIMState_t* u8_a_State);

void TIM0_EnableOVFInterrupt(void);

void TIM0_DisableOVFInterrupt(void);

/**
 * \brief Function to set a function to call when the timer0
 *	      Overflow Interrupt is triggered
 * \param pv_a_CallbackFn reference to the function to call
 * 
 * \return en_TIMErrorState_t
 */
en_TIMErrorState_t TIM0_SetOVFCallback(void (*pv_a_CallbackFn)(void));



#endif