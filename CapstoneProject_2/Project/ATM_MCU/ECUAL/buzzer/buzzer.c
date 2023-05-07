/*
 * buzzer.c
 *
 * Created: 4/17/2023 5:47:13 AM
 *  Author: ME
 */ 
/*************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "../../Common/STD_Types.h"

#include "../../MCAL/dio/dio_interface.h"

#include "buzzer.h"
/*************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/
//static ST_pin_config_t st_gs_BuzzerPin = {BUZZER_PORT, BUZZER_PIN, GPIO_DIRECTION_OUTPUT, GPIO_LOGIC_LOW};
st_Buzzer_t st_g_Buzzer = {BUZZER_PIN};

/*************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/
void BUZ_Init(st_Buzzer_t* pst_a_buzzer)
{
	DIO_s8SETPinDir(pst_a_buzzer->BuzzerPin, OUTPUT);
	DIO_s8SETPinVal(pst_a_buzzer->BuzzerPin, LOW);
}

en_BuzzerErrorState_t BUZ_Enable(st_Buzzer_t* pst_a_buzzer);
en_BuzzerErrorState_t BUZ_SetState(st_Buzzer_t* pst_a_buzzer, en_BuzzerState_t u16_a_state)
{
	if(pst_a_buzzer != NULL)
	{
		DIO_s8SETPinVal(pst_a_buzzer->BuzzerPin, u16_a_state);
	}
	else
	{
		return BUZ_NOK;
	}
	
	return BUZ_OK;
}