
#ifndef APP_H_
#define APP_H_

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define DEFAULT_TEMP			20
#define MIN_TEMP				18
#define MAX_TEMP				35

#define TIME_OUT_SEC			5

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/


/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/
/**
 * \brief Initialize all modules and execute welcome routine
 * 
 * \return void
 */
void APP_Init(void);


/**
 * \brief Application main logic
 * 
 * \param 
 * 
 * \return void
 */
void APP_Start(void);

/**
 * \brief Initialize temperature adjustment process
 * 
 * \param 
 * 
 * \return void
 */
void APP_AdjustInit(void);


/**
 * \brief timeout callback function
 * 
 * \return void
 */
void timeout(void);  

#endif /* APP_H_ */