/*
 * terminal_process.c
 *
 * Created: 02/05/2023 19:50:35
 *  Author: 20101
 */ 
/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include "card_database.h"

/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
Uchar8_t pin_arr[PIN_LENGTH] = "";
Uchar8_t pan_arr[MAX_PAN_LENGTH] = "";

/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/
/*
 * AUTHOR			: Bassel Yasser Mahmoud
 * FUNCTION			: APP_terminalPinGet
 * DESCRIPTION		: Get pin from User within terminal and doing some validation
 * RETURN			: en_terminalPinGetStatus_t {PINGET_NOK or PINGET_OK}
 */
en_terminalPinGetStatus_t APP_terminalPinGet(Uchar8_t* arr)
{
	en_terminalPinGetStatus_t errorStatus = PINGET_OK;

	Uchar8_t counter = 0, flag = 0;
	HUSART_receiveSTRING(arr, PIN_LENGTH);
	while(arr[counter] != null)
	{
		if(arr[counter] >= '0' && arr[counter] <= '9')
		{
			counter++;
		}
		else
		{
			HUSART_sendSTRING( (Uchar8_t*) "\rNot numeric ");
			flag = 1;
			errorStatus = PINGET_NOK;
			break;
		}
	}
	if(counter < PIN_LENGTH-1 && flag == 0)
	{
		HUSART_sendSTRING( (Uchar8_t*) "\rbelow 4 dig ");
		errorStatus = PINGET_NOK;
	}
	return errorStatus;
}

/*
 * AUTHOR			: Sharpel
 * FUNCTION			: APP_terminalPanGet
 * DESCRIPTION		: Get pan from User within terminal and doing some validation
 * RETURN			: en_terminalPanGetStatus_t {PANGET_NOK or PANGET_OK}
 */
en_terminalPanGetStatus_t APP_terminalPanGet(Uchar8_t* arr)
{
	Uchar8_t loc_counter=0;
	HUSART_sendSTRING((Uchar8_t*)"\n\rEnter Card Pan : ");
	HUSART_receiveSTRING(arr,20);
	while(arr[loc_counter] != null)
	{
		if(arr[loc_counter] >= '0' && arr[loc_counter] <= '9')
		{
			loc_counter++;
		}
		else
		{
			HUSART_sendSTRING((Uchar8_t*) "\n\rInvalid Pan Number - must contain Numbers only");
			return PANGET_NOK;
		}
	}
	if(loc_counter<16)
	{
	 HUSART_sendSTRING((Uchar8_t*) "\n\rInvalid Pan Number - must contain at least 16 numbers");
	 return PANGET_NOK;
	}
	return PANGET_OK;
}


/**
 * \brief : This Function Use To Save User Pan & User Pin In The EEPROM By Calling eeprom_write_string Function
 * 
 * \param Uchar8_t *CardPan :  Pointer From Uchar8_t Will Store The Address Of Array Of Char That Contain User Pan String
 * \param Uchar8_t *CardPin :  Pointer From Uchar8_t Will Store The Address Of Array Of Char That Contain User Pin String
 * \return EN_TerminalDataState : This Is Enum For Terminal Data State
 */
EN_TerminalDataState SaveCardData(Uchar8_t *CardPan,Uchar8_t *CardPin)
{
	EN_TerminalDataState ret = DATA_NSAVED; 
	if(CardPan == null || CardPin == null) // Check If The Pointers Is Equal Null Or Not Equal
	{
		ret = DATA_NSAVED; // If Equal Null Then Return DATA_NSAVED From Terminal Data State Enum
	}
	else
	{
		_delay_ms(200);
		eeprom_write_string(PAN_PAGE,CardPan);// Call This Function To Write In The EEPROM And Give To It The Address & Pointer Point To The Pan Array 
		_delay_ms(200);
		eeprom_write_string(PIN_PAGE,CardPin);// Call This Function To Write In The EEPROM And Give To It The Address & Pointer Point To The Pin Array
		_delay_ms(200);
		eeprom_write_string(FLAG_PAGE, (Uchar8_t*)"1");// Call This Function To Write In The EEPROM And Give To It The Address & The Data 
		_delay_ms(200);
		ret = DATA_SAVED;//Return DATA_NSAVED From Terminal Data State 
	}
	
	return ret;
}

/**
 * \brief : This Function Use To Read User Pan & User Pin From The EEPROM By Calling eeprom_read_string Function
 * 
 * \param Uchar8_t *CardPan :  Pointer From Uchar8_t Will Store The Address Of Array Of Char That Function Will Return User Pan String In It
 * \param Uchar8_t *CardPin :  Pointer From Uchar8_t Will Store The Address Of Array Of Char That Function Will Return User Pin String In It
 * \return EN_TerminalDataState : This Is Enum For Terminal Data State 
 */
EN_TerminalDataState ReadCardData(Uchar8_t *CardPan,Uchar8_t *CardPin)
{
		EN_TerminalDataState ret = DATA_NREAD;
		
		if(CardPan == null || CardPin == null)// Check If The Pointers Is Equal Null Or Not Equal
		{
			ret = DATA_NREAD;// If Equal Null Then Return DATA_NREAD From Terminal Data State Enum
		}
		else
		{			
			eeprom_read_string(PAN_PAGE , CardPan);// Call This Function To Read From The EEPROM And Give To It The Address & Pointer Point To The Pan Array 
			_delay_ms(200);
			eeprom_read_string(PIN_PAGE , CardPin);// Call This Function To Read From The EEPROM And Give To It The Address & Pointer Point To The Pin Array
			_delay_ms(200);
			ret = DATA_READ;//Return DATA_READ From Terminal Data State 
		}
		return ret;
}


en_CardPinMatchError_t CARD_MatchPINs(Uchar8_t *pu8_a_pin)
{
	Uchar8_t PIN_Confirm[PIN_LENGTH], u8_l_PINiterator;
	Uchar8_t u8_l_ValidatePIN, u8_l_ValidateConfirmPIN;
	
	/* Get PIN from user */
	HUSART_sendSTRING( (Uchar8_t*) "\n\rEnter your PIN : ");
	u8_l_ValidatePIN = APP_terminalPinGet(pu8_a_pin);
	if(u8_l_ValidatePIN == PINGET_NOK) return PIN_Match_NOK;
	
	/* Get PIN again for Confirmation */
	HUSART_sendSTRING((Uchar8_t *)"\n\rConfirm Your PIN : ");
	u8_l_ValidateConfirmPIN = APP_terminalPinGet(PIN_Confirm);
	
	if((PINGET_OK == u8_l_ValidatePIN) && (PINGET_OK == u8_l_ValidateConfirmPIN))
	{
		/* Check if the user entered same PIN both times */
		for(u8_l_PINiterator=0; u8_l_PINiterator<PIN_LENGTH; u8_l_PINiterator++)
		{
			if(pu8_a_pin[u8_l_PINiterator] != PIN_Confirm[u8_l_PINiterator])
			{
				HUSART_sendSTRING((Uchar8_t *)"\n\rPin Not Matched");
				return PIN_Match_NOK;
			}
		}
		
		HUSART_sendSTRING((Uchar8_t *)"\n\rPin Matched");
		return PIN_Match_OK;
	}
	
	return PIN_Match_NOK;
}

