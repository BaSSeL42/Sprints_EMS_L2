
#ifndef APP_H_
#define APP_H_

#include "../ATM_MODULE/atm.h"
/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define		PIN_LENGTH			5


/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/


typedef enum
{
	TRIGGER,
	N_TRIGGER,
    CHECKING,
	IDLE
}EN_TriggerState;


/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/
///*
 //* AUTHOR			: Bassel Yasser Mahmoud
 //* FUNCTION			: timer_ovfCount
 //* DESCRIPTION		: Countiong OVF times
 //* RETURN			: void
 //*/
//void timer_ovfCount(void);
///*
 //* AUTHOR			: Bassel Yasser Mahmoud
 //* FUNCTION			: Button_enStatus
 //* DESCRIPTION		: check button press {Zero if less than 2 sec otherwise it will be Enter}
 //* RETURN			: en_buttonStatus {ZERO or ENTER}
 //*/
//en_buttonStatus Button_enStatus(void);
//
///**
 //* \brief Function to implement logic after approved transaction
 //* 
 //* \param f32_a_NewBalance: balance after transaction which will be
 //*							displayed on LCD
 //* \return void
 //*/
//void ATM_ApprovedCard(float32_t f32_a_NewBalance) /* Get account data and transaction or just balance after transaction */
//
//
///**
 //* \brief Function to get the card pin from the card MCU
 //* 
 //* \param pu8_a_CardPIN: reference to character array to
 //*						 store the PIN
 //* \return void
 //*/
 
//void ATM_GetCardPIN(Uchar8_t *pu8_a_CardPIN);


void APP_Init(void);
void APP_Start(void);
 

#endif /* APP_H_ */
