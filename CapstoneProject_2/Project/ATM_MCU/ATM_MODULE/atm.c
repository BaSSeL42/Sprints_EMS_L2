/*
* atm.c
*
* Created: 02/05/2023 19:03:32
*  Author: 20101
*/
/*************************************************************************************************************
* 													Includes
************************************************************************************************************/

#include "atm.h"

#include "../ECUAL/Button/button.h"
#include "../ECUAL/HTimer/HTimer.h"

/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/

extern Uchar8_t keys_arr [10];
extern Uchar8_t global_u8OVFCounter;
extern Uchar8_t EnterCheck;
extern Uchar8_t ZeroCheck;

Uchar8_t buttonPressed;
en_buttonStatus myState;
Uchar8_t  arr_g_ATMpin[PIN_LENGTH] = "";
Uchar8_t  arr_g_CARDpin[PIN_LENGTH], arr_g_CARDpan[MAX_PAN_LENGTH];
Uchar8_t Entered_amount [8] = "0000.00";
en_buttonStatus myState = NOTHING;

/************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/

/**
* \brief Displays welcome routine
* \return void
*/
void Welcome(void)
{
	HLCD_ClrDisplay();
	HLCD_gotoXY(0,0);
	HLCD_WriteString((char*)"Welcome To Atm");
	HTIM0_SyncDelay(1,Seconds);
	HLCD_ClrDisplay();
	HLCD_gotoXY(0,0);
	HLCD_WriteString((char*)"Insert Your Card");
}

/**
* (Author: Alaa Hisham)
* \brief Carries out the routine for approved card
* \param f32_a_NewBalance: the balance to display after transaction
* \return void
*/
void ATM_ApprovedCard(float32_t f32_a_NewBalance)
{
	/* Display "Approved Transaction" for one second */
	HLCD_gotoXY(0, 4);
	HLCD_WriteString("Approved");
	HLCD_gotoXY(1, 2);
	HLCD_WriteString("Transaction");
	HTIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
	
	/* Display the remaining balance for one second */
	HLCD_gotoXY(0, 4);
	HLCD_WriteString("Remaining");
	HLCD_gotoXY(1, 0);
	HLCD_WriteString("Balance  ");
	HLCD_DisplayFloat(f32_a_NewBalance);
	HTIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
	
	/* Display "Ejecting Card" for one second */
	HLCD_gotoXY(0, 1);
	HLCD_WriteString("Ejecting Card");
	HTIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
}



/*
* AUTHOR			: Sharpel
* FUNCTION			: Get_pin
* DESCRIPTION		: get pin from user (on the atm )
* ARGS		        : pointer to array (the size of array must be 5 or more) to store entered pin by user
* RETURN			: PIN_OK if user enters 4 numbers , PIN_NOT_OK otherwise
*/
EN_PinState Get_pin(Uchar8_t *enteredpin)
{
	
	/* Clear Display and display enter your pin */
	HLCD_ClrDisplay();
	HLCD_gotoXY(LCD_LINE_ZERO,LCD_COL_ZERO);
	HLCD_WriteString("Enter Your pin");
	/* change cursor position to next line for user input */
	HLCD_gotoXY(LCD_LINE_ONE,LCD_COL_ZERO);
	
	/* clear global (ENTER-ZERO) variable --> myState*/
	myState =NOTHING;
	Uchar8_t BTN = KEY_NOTHING , loc_counter=ZERO;
	
	/* loop terminates if the counter exceed pin length or enter button pressed */
	while (loc_counter < PIN_LENGTH-1 && myState != ENTER)
	{
		/* Get Button from keypad*/
		BTN = KEYPAD_GetButton();
		
		/* case nothing pressed on keypad*/
		if(BTN == KEY_NOTHING)
		{
			
			/* check if zero pressed*/
			if(myState == ZERO)
			{
				
				/* clear global (ENTER-ZERO) variable --> myState*/
				myState = NOTHING;
				
				/* store zero in the array at counter position */
				enteredpin[loc_counter] = ZERO_CHAR;
				
				/* Update cursor position and increament counter*/
				HLCD_gotoXY(LCD_LINE_ONE,loc_counter++);
				HLCD_vidWriteChar('*');
				
			}
			
			/* repeat while */
			continue;
		}
			
		/* case Button pressed on keypad*/
		else
		{
			/* store Button in the array at counter position */
			enteredpin[loc_counter] = keys_arr[BTN-1];
			
			/* Update cursor position and increment counter*/
			HLCD_gotoXY(LCD_LINE_ONE,loc_counter++);
			HLCD_vidWriteChar('*');
			
		}
	}
	
	
	/* check if user types less than pin length and press enter*/
	if(loc_counter<PIN_LENGTH-1)
	{
		/* clear global (ENTER-ZERO) variable --> myState*/
		myState = NOTHING;
		
		/* Clear Display and display short pin */
		HLCD_ClrDisplay();
		HLCD_gotoXY(LCD_LINE_ZERO,LCD_COL_ZERO);
		HLCD_WriteString("Short Pin");
		HTIM0_SyncDelay(LCD_LINE_ONE,Seconds);
		
		return PIN_NOT_OK;
	}
	
	return PIN_OK;
	
}

/**
* \brief : ThiS Function Compare Pin User Enter It On Atm With The Pin Saved In The EEPROM On Card
*
* \param : Uchar8_t *pinFromAtm : Pointer From Uchar8_t Data Type Point On The Array Contain The Pin User Enter From Atm
* \param : Uchar8_t *pinFromServer : Pointer From Uchar8_t Data Type Point On The Array Contain The Pin Saved EEPROM Of The Card
*
* \return EN_PinState This Is Enum Contain pin State
*/
EN_PinState PIN_checkPinMatching(Uchar8_t *pinFromAtm,Uchar8_t *pinFromServer)
{
	EN_PinState ret = PIN_NOT_MATCHED;
	if(pinFromAtm == NULL || pinFromServer == NULL) // Check If The Pointers Is Equal Null Or Not Equal
	{
		ret = NULL_POINTER;//Return NULL_POINTER From PinState Enum
	}
	else
	{
		if(!strcmp((char*)pinFromAtm, (char*)pinFromServer)) // Compare This Two Array Equal Or Not
		{
			ret = PIN_MATCHED;//Return PIN_MATCHED From PinState Enum
			HLCD_ClrDisplay();// Clear Screen
			HLCD_WriteString("PIN_MATCHED");//Print PIN_MATCHED On Lcd
			HTIM0_SyncDelay(1, Seconds);
		}
		else
		{
			ret = PIN_NOT_MATCHED;//Return PIN_NOT_MATCHED From PinState Enum
			HLCD_ClrDisplay();// Clear Screen
			HLCD_WriteString("PIN_NOT_MATCHED");//Print PIN_NOT_MATCHED On Lcd
			HTIM0_SyncDelay(1, Seconds);
		}
	}
	return ret;
}

/**
* \brief : This Function Call To Locked The Atm System
*
* \param : st_Buzzer_t *pst_a_buzzer Thi sIs Struct Contain The Buzzer CFG
*
* \return en_BuzzerErrorState_t This Is Enum Return Buzzer State
*/
en_BuzzerErrorState_t deinitAtm(st_Buzzer_t* pst_a_buzzer)
{
	en_BuzzerErrorState_t ret = BUZ_NOK;
	
	ret = BUZ_SetState(pst_a_buzzer,BUZ_ON);//Call This Function To Change Buzzer State To On
	
	return ret;
}

/**
* (Author: Alaa Hisham)
* \brief Get the card pan and pin
* \param pu8_a_pan: reference to buffer to receive pan from card
* \param pu8_a_pin: reference to buffer to receive pin from card
* \return en_CardDataErrorState_t
*/
en_CardDataErrorState_t ATM_GetCardData(Uchar8_t *pu8_a_pan, Uchar8_t *pu8_a_pin)
{
	en_CardDataErrorState_t en_l_DataErrorState = DATA_OK;
	
	if((pu8_a_pin != NULL) && (pu8_a_pan != NULL))
	{
		/* Request PIN From Card */
		HSPI_SendChar(ATM_REQUEST_PIN);
		HTIM0_SyncDelay(5, mSeconds);
		HSPI_ReceiveData(arr_g_CARDpin, PIN_LENGTH);
		HTIM0_SyncDelay(10, mSeconds);
		
		/* Request PAN From Card */
		HSPI_SendChar(ATM_REQUEST_PAN);
		HTIM0_SyncDelay(5, mSeconds);
		HSPI_ReceiveData(arr_g_CARDpan, MAX_PAN_LENGTH);
		
		if(arr_g_CARDpan[ZERO] == DATA_END || arr_g_CARDpin[ZERO] == DATA_END)
		{
			en_l_DataErrorState = DATA_NOT_RECEIVED;
		}
	}
	else
	{
		en_l_DataErrorState = NULL_DATA_PTR;
	}
	
	return en_l_DataErrorState;	
}

/*
* AUTHOR			: Sharpel
* FUNCTION			: get_amount_left
* DESCRIPTION		: get amount from user ( on the atm )
* ARGS		        : pointer to array (the size of array must be 8 or more and equal "0000.00" initial value) to store entered pin by user
* RETURN			: void
*/
void get_amount_left (Uchar8_t * amount)
{
	/* Clear Display and display ENTER amount at first line */
	HLCD_ClrDisplay();
	HLCD_gotoXY(LCD_LINE_ZERO,LCD_COL_ZERO);
	HLCD_WriteString("ENTER amount");
	
	/* display amount at second line initially "0000.00" */
	HLCD_gotoXY(LCD_LINE_ONE,LCD_COL_ZERO);
	HLCD_WriteString((char*)amount);
	
	/* clear global (ENTER-ZERO) variable --> myState*/
	myState =NOTHING;
	/* display amount at second line initially "0000.00" */
	Uchar8_t BTN = KEY_NOTHING,loc_counter=ZERO,i=ZERO;
	while(loc_counter<AMOUNT_LENGTH && myState !=ENTER)
	{
		
		/* Get Button from keypad*/
		BTN = KEYPAD_GetButton();
		
		/* Case Nothing pressed on keypad*/
		if(BTN == KEY_NOTHING)
		{
			/* check if zero pressed*/
			if(myState == ZERO)
			{
				
				/* clear global (ENTER-ZERO) variable --> myState*/
				myState =NOTHING;
				
				/* loop to shift numbers left*/
				for(i=ZERO;i<AMOUNT_LENGTH;i++)
				{
					
					/* check if index is before decimal*/
					if(i==3)
					{
						/* shift the number before decimal left to after decimal at index 3*/
						amount[i]=amount[i+2];
						HLCD_gotoXY(1,i);
						HLCD_vidWriteChar(amount[i]);
						/* skip decimal iteration and move after it*/
						i=5;
					};
					/* shift the number left*/
					amount[i]=amount[i+1];
					HLCD_gotoXY(1,i);
					HLCD_vidWriteChar(amount[i]);
				}
				
				/* store zero in the array at least position */
				amount[6] = '0';
				HLCD_gotoXY(1,AMOUNT_LENGTH);
				HLCD_vidWriteChar(amount[6]);
				loc_counter++;
			}
			
			/* repeat while*/
			continue;
		}
		
		
		/* case Button pressed on keypad*/
		else
		{
			
			/* loop to shift numbers left*/
			for(i=ZERO;i<AMOUNT_LENGTH;i++)
			{
				
				/* check if index is before decimal*/
				if(i==3)
				{
					/* shift the number before decimal left to after decimal at index 3*/
					amount[i]=amount[i+2];
					HLCD_gotoXY(1,i);
					HLCD_vidWriteChar(amount[i]);
					/* skip decimal iteration and move after it*/
					i=5;
				};
				/* shift the number left*/
				amount[i]=amount[i+1];
				HLCD_gotoXY(1,i);
				HLCD_vidWriteChar(amount[i]);
			}
			
			/* store Button in the array at least position */
			amount[6] = keys_arr[BTN-1];
			HLCD_gotoXY(1,6);
			HLCD_vidWriteChar(amount[6]);
			loc_counter++;
		}
		
		
	}
	
	while(myState != ENTER);
	
	myState = NOTHING;
}


/*
* AUTHOR			: Bassel Yasser Mahmoud
* FUNCTION			: EXTINT_FUNC
* DESCRIPTION		: check button press {Zero if less than 2 sec otherwise it will be Enter}
* RETURN			: void
*/
void EXTINT_FUNC(void)
{
	static Uchar8_t counter = 0;
	if (counter == 0)
	{
		(void)HTimer_vidDelayMs(100);
		// (void)HButton_ExtIntInit(DIO_PINB_2);
		(void)H_EXTINT_create(EXTINT2, FALLING_EDGE,EXTINT_FUNC);
		counter = 1;

	}
	else if(counter == 1)
	{
		(void)HTimer_enStop();
		if (global_u8OVFCounter < 20 && global_u8OVFCounter > 0)
		{
			myState = ZERO;
			
		}
		else if(global_u8OVFCounter >= 20)
		{
			myState = ENTER;
		}
		global_u8OVFCounter = 0;

		(void)H_EXTINT_create(EXTINT2, RISING_EDGE,EXTINT_FUNC);
		(void)HButton_ExtIntInit(DIO_PINB_2);

		counter = 0;
	}
}
