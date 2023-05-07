
#ifndef TIM1_INTERFACE_H_
#define TIM1_INTERFACE_H_

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define TIM1_PRESCALER		TIM1_CLK_DIV_BY_1024
#define TIM1_CLK_MUL		8

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
	TIM1_CLK_DIV_BY_1=1 ,
	TIM1_CLK_DIV_BY_8   ,
	TIM1_CLK_DIV_BY_64  ,
	TIM1_CLK_DIV_BY_256 ,
	TIM1_CLK_DIV_BY_1024
}en_ICU_Prescaler_t;


/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * \brief Initialize timer 1 in normal mode
 * 
 * \return EN_TIMErrorState_t
 */
en_TIMErrorState_t TIM1_Init(void);

/**
 * \brief Start the timer clock after prescaling it with given value 
 * 
 * \param u8_a_prescaler
 * 
 * \return EN_TIMErrorState_t
 */
en_TIMErrorState_t TIM1_Start(en_ICU_Prescaler_t u8_a_prescaler);

/**
 * \brief Stop the timer
 * 
 * \return void
 */
void TIM1_Stop();

/**
 * \brief Set the timer to start from the given value
 * 
 * \param Copy_Value
 * 
 * \return void
 */
void TIM1_SetValue(Uint16_t u16_a_startValue);
Uint16_t TIM1_GetValue(void);
float32_t TIM1_GetTickTime(void);


#endif