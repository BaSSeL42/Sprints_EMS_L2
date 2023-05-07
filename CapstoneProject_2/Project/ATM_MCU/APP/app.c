/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
//#include <util/delay.h>
#include "app.h"
#include "../ECUAL/Button/button.h"
#include "../ATM_MODULE/database_check.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/


extern Uchar8_t  ATMpin[5] ;
extern Uchar8_t  CARDpin[5] ;
extern Uchar8_t  CARDpan[20] ;
Uchar8_t global_u8OVFCounter = 0;

extern VUchar8_t keys_arr [10];
extern en_buttonStatus myState;
extern st_Buzzer_t st_g_Buzzer;
extern Uchar8_t Entered_amount [8];

Uchar8_t Default_Entered_amount [8] = "0000.00";
EN_TriggerState TriggerState = N_TRIGGER; 

Uchar8_t welcomeFlag = 0;
Uchar8_t trialsFlag = 0;
EN_dataError_t DB_CHECK;
float32_t newAMOUNT ;

/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/


void TriggerCallBack(void)
{
	TriggerState = TRIGGER;
}


/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: timer_ovfCount
 * DESCRIPTION		: Countiong OVF times
 * RETURN			: void
 */

void timer_ovfCount(void)
{
	global_u8OVFCounter++;

}
void APP_Init(void)
{
	
	
	(void)KEYPAD_init();
	(void)HTimer_enInit();
	(void)HTimer_enCBF(timer_ovfCount);
	(void)HLCD_vidInit();
	(void)HSPI_MasterInit();
	(void)H_EXTINT_create(EXTINT0,RISING_EDGE,TriggerCallBack);
	(void)BUZ_Init(&st_g_Buzzer);
	(void)HButton_ExtIntInit(DIO_PINB_2);
	(void)H_EXTINT_create(EXTINT2, RISING_EDGE,EXTINT_FUNC);
}


void APP_Start(void)
{
			
	switch(TriggerState)
	{
		case TRIGGER:
		{
			welcomeFlag = 0;
			if(Get_pin(ATMpin)==PIN_NOT_OK)break;
			if(ATM_ValidatePIN() == PIN_MATCHED)
			{
				TriggerState = CHECKING;
                  
			}
			else
			{
				trialsFlag++;
				/* Lock system if max tries exceeded */
				if(trialsFlag == 3)
				{
					HLCD_ClrDisplay();
					HLCD_gotoXY(0,4);
					HLCD_WriteString("LOCKED");
					deinitAtm(&st_g_Buzzer);
					TriggerState = IDLE;
					
				}
			}
			//_delay_ms(1000);
			//TriggerState = N_TRIGGER;
			break;
		}
		case N_TRIGGER:
		{
			if(welcomeFlag == 0)
			{
				Welcome();
				welcomeFlag = 1;
			}
			break;
		}
		case IDLE:
		{
			
			break;
		}
        case CHECKING:
       {

		get_amount_left(Entered_amount);
		if(!strcmp(Entered_amount,Default_Entered_amount))break;
		HLCD_ClrDisplay();
		DB_CHECK = DATABASE_checking(CARDpan,Entered_amount,&newAMOUNT);
		switch(DB_CHECK){
			case APPROVED:
			{
				ATM_ApprovedCard(newAMOUNT);
				HSPI_SendChar(ATM_REQUEST_EJECTED);
				strcpy(Entered_amount,Default_Entered_amount);
				TriggerState = N_TRIGGER;
				break;
			}
			case FRAUD_CARD:
			{
				deinitAtm(&st_g_Buzzer);
				HLCD_gotoXY(0, 4);
				HLCD_WriteString("This is a");
				HLCD_gotoXY(1, 2);
				HLCD_WriteString("Fraud Card");
				HTIM0_SyncDelay(1, Seconds);
				TriggerState = IDLE;
				break;
			}
			case CARD_STOLEN:
			{
				deinitAtm(&st_g_Buzzer);
				HLCD_gotoXY(0, 4);
				HLCD_WriteString("This Card ");
				HLCD_gotoXY(1, 2);
				HLCD_WriteString("is Stolen");
				HTIM0_SyncDelay(1, Seconds);
				TriggerState = IDLE;
				break;
			}
			case EXCEED_MAX_DAILY_AMOUNT:
			{
				
				HLCD_gotoXY(0, 4);
				HLCD_WriteString("Max Limit ");
				HLCD_gotoXY(1, 2);
				HLCD_WriteString("is Exceeded");
				HTIM0_SyncDelay(1, Seconds);
				HLCD_ClrDisplay();
				strcpy(Entered_amount,Default_Entered_amount);
				TriggerState = CHECKING;
				break;
			}
			case INSUFFICIENT_FUND:
			{
				
				HLCD_gotoXY(0, 4);
				HLCD_WriteString("INSUFFICIENT ");
				HLCD_gotoXY(1, 5);
				HLCD_WriteString("FUND");
				HTIM0_SyncDelay(1, Seconds);
				strcpy(Entered_amount,Default_Entered_amount);
				TriggerState = CHECKING;
				break;
			}	
		}
		break;
        }	

	
	}
	
	
}




















/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: timer_ovfCount
 * DESCRIPTION		: Countiong OVF times
 * RETURN			: void
 */

//void timer_ovfCount(void)
//{
	//global_u8OVFCounter++;
//
//}


// 
// 
// 
 
// 
// 
// /**
//  * \brief Function to implement logic after approved transaction
//  * 
//  * \param f32_a_NewBalance: balance after transaction which will be
//  *							displayed on LCD
//  * \return void
//  */
// void ATM_ApprovedCard(/* Get account data and transaction or just balance after transaction */float32_t f32_a_NewBalance)
// {
// 	HLCD_gotoXY(0, 4);
// 	HLCD_WriteString("Approved");
// 	HLCD_gotoXY(1, 2);
// 	HLCD_WriteString("Transaction");
// 	
// 	HTIM0_SyncDelay(1, Seconds);
// 	HLCD_ClrDisplay();
// 	
// 	/* Todo: remaining balance */
// 	HLCD_gotoXY(0, 4);
// 	HLCD_WriteString("Remaining");
// 	HLCD_gotoXY(1, 0);
// 	HLCD_WriteString("Balance  ");
// 	HLCD_DisplayFloat(f32_a_NewBalance);
// 	
// 	HTIM0_SyncDelay(1, Seconds);
// 	HLCD_ClrDisplay();
// 	
// 	HLCD_gotoXY(0, 1);
// 	HLCD_WriteString("Ejecting Card");
// 	HTIM0_SyncDelay(1, Seconds);
// 	HLCD_ClrDisplay();
// }
// 
// 
// /**
//  * \brief Function to get the card pin from the card MCU
//  * 
//  * \param pu8_a_CardPIN: reference to character array to
//  *						 store the PIN
//  * \return void
//  */
// void ATM_GetCardPIN(Uchar8_t *pu8_a_CardPIN)
// {
// 	/* Receive PIN from Card */
// 	HSPI_ReceiveData(pu8_a_CardPIN, PIN_LENGTH);
// }
// 


