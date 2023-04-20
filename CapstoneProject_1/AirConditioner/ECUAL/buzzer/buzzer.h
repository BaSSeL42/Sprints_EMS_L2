/*
 * buzzer.h
 *
 * Created: 4/17/2023 5:47:35 AM
 *  Author: ME
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_


/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
//#define BUZZER_PORT				GPIO_PORTB_INDEX
#define BUZZER_PIN				DIO_PINB_4

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef struct
{
	Uchar8_t BuzzerPin;	
}st_Buzzer_t;

typedef enum
{
	BUZ_OFF,
	BUZ_ON
}en_BuzzerState_t;

typedef enum
{
	BUZ_OK,
	BUZ_NOK
}en_BuzzerErrorState_t;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/
void BUZ_Init(st_Buzzer_t* pst_a_buzzer);
en_BuzzerErrorState_t BUZ_Enable(st_Buzzer_t* pst_a_buzzer);
en_BuzzerErrorState_t BUZ_SetState(st_Buzzer_t* pst_a_buzzer, en_BuzzerState_t u16_a_state);

#endif /* BUZZER_H_ */