/*************************************************************************************************************
* 													Includes
************************************************************************************************************/

#include "../Common/BIT_Math.h"
#include "../Common/vect_table.h"
#include "../Common/STD_Types.h"
//#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/husart/husart.h"
#include "../ECUAL/hspi/hspi_interface.h"
#include "../ECUAL/eeprom/HEEPROM_Interface.h"

#include "../card_database/card_database.h"
#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
extern Uchar8_t pin_arr[PIN_LENGTH];
extern Uchar8_t pan_arr[MAX_PAN_LENGTH];
extern Uchar8_t u8_g_SlaveReceive;

Uchar8_t u8_g_EepromFlag, u8_g_CardState = CardGetMode , u8_g_PanValid, u8_gs_ModeSelect;
/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/

void APP_Init(void)
{
	(void)HUSART_enInit();
	HSPI_SlaveInit();
	eeprom_init();
	sei();
}


void APP_Start(void)
{
	switch(u8_g_CardState)
	{
		case CardGetMode:
		{
			/* Check whether the card is already programmed */
			u8_g_EepromFlag = eeprom_read_byte(FLAG_PAGE);
			if(u8_g_EepromFlag == 0xFF) u8_g_CardState = CardProgMode_GetPan;
			else
			{
				HUSART_sendSTRING((Uchar8_t*) "\n\rPlease press 1 for entering user mode and 2 for programming mode:");
				while(HUSART_enRecieveData(&u8_gs_ModeSelect));
				HUSART_enSendData(u8_gs_ModeSelect);
				HUSART_sendSTRING((Uchar8_t*) "\n\r");
				if('1' == u8_gs_ModeSelect)	u8_g_CardState = CardUserMode;
				else if('2' == u8_gs_ModeSelect) u8_g_CardState = CardProgMode_GetPan;
				else HUSART_sendSTRING((Uchar8_t*) "Invalid Choice, ");
			}
			break;
		}
		case CardProgMode_GetPan:
		{
			/* Get and validate PAN number from user */
			u8_g_PanValid = APP_terminalPanGet(pan_arr);
			if(PANGET_OK == u8_g_PanValid) u8_g_CardState = CardProgMode_GetPin;
			break;
		}
		case CardProgMode_GetPin:
		{
			if(CARD_MatchPINs(pin_arr) == PIN_Match_OK)
			{
				SaveCardData(pan_arr,pin_arr);
				u8_g_CardState = CardUserMode;
			}
			else u8_g_CardState = CardProgMode_GetPin;
			break;
		}
		case CardUserMode:
		{
			HUSART_sendSTRING((Uchar8_t*) "\n\r------------- User Mode -------------\n");

			/* Get PIN from EEPROM to prepare data in SPI buffer */
			ReadCardData(pan_arr,pin_arr);
			
			/* Trigger the ATM */
			HSPI_SlaveRequest(pin_arr, PIN_LENGTH);
			u8_g_CardState = CardCommMode;
			break;
		}
		case CardCommMode:
		{
			if(CARD_PIN_REQUEST == u8_g_SlaveReceive)
			{
				u8_g_SlaveReceive = 0;
				HSPI_SlaveSetData(pin_arr, PIN_LENGTH);
			}
			else if(CARD_PAN_REQUEST == u8_g_SlaveReceive)
			{
				u8_g_SlaveReceive = 0;
				HSPI_SlaveSetData(pan_arr, MAX_PAN_LENGTH);
			}
			else if(ATM_REQUEST_EJECTED == u8_g_SlaveReceive)
			{
				u8_g_SlaveReceive = 0;
				u8_g_CardState = CardGetMode;
			}
			break;
		}

	}
}
