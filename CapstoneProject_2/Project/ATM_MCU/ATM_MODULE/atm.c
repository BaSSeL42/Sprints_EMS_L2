/*
* atm.c
*
* Created: 02/05/2023 19:03:32
*  Author: 20101
*/

#include "atm.h"
#include <util/delay.h>
#include "../ECUAL/Button/button.h"
#include "../ECUAL/HTimer/HTimer.h"

Uchar8_t buttonPressed;
en_buttonStatus myState;

Uchar8_t  ATMpin[5] = "";
Uchar8_t  CARDpin[5], CARDpan[20];
extern Uchar8_t keys_arr [10];
extern Uchar8_t global_u8OVFCounter;
Uchar8_t Entered_amount [8] = "0000.00";
extern Uchar8_t EnterCheck;
extern Uchar8_t ZeroCheck;
en_buttonStatus myState = NOTHING;

void Welcome(void)
{
	HLCD_ClrDisplay();
	HLCD_gotoXY(0,0);
	HLCD_WriteString((Uchar8_t *)"Welcome To Atm");
	HTIM0_SyncDelay(1,Seconds);
	HLCD_ClrDisplay();
	HLCD_gotoXY(0,0);
	HLCD_WriteString((Uchar8_t *)"Insert Your Card");
}

void ATM_ApprovedCard(float32_t f32_a_NewBalance)
{
	HLCD_gotoXY(0, 4);
	HLCD_WriteString("Approved");
	HLCD_gotoXY(1, 2);
	HLCD_WriteString("Transaction");
	
	HTIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
	
	/* Todo: remaining balance */
	HLCD_gotoXY(0, 4);
	HLCD_WriteString("Remaining");
	HLCD_gotoXY(1, 0);
	HLCD_WriteString("Balance  ");
	HLCD_DisplayFloat(f32_a_NewBalance);
	
	HTIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
	
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
	while (loc_counter < PIN_LENGTH && myState != ENTER)
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
			
			/* Update cursor position and increament counter*/
			HLCD_gotoXY(LCD_LINE_ONE,loc_counter++);
			HLCD_vidWriteChar('*');
			
		}
		

	}
	
	
	/* check if user types less than pin length and press enter*/
	if(loc_counter<PIN_LENGTH)
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
		if(!strcmp(pinFromAtm,pinFromServer)) // Compare This Two Array Equal Or Not
		{
			ret = PIN_MATCHED;//Return PIN_MATCHED From PinState Enum
			HLCD_ClrDisplay();// Clear Screen
			HLCD_WriteString("PIN_MATCHED");//Print PIN_MATCHED On Lcd
			_delay_ms(5000);
		}
		else
		{
			ret = PIN_NOT_MATCHED;//Return PIN_NOT_MATCHED From PinState Enum
			HLCD_ClrDisplay();// Clear Screen
			HLCD_WriteString("PIN_NOT_MATCHED");//Print PIN_NOT_MATCHED On Lcd
			_delay_ms(5000);
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
		HLCD_WriteString(amount);
        
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
	


	Uchar8_t u8_g_ReceivePIN = 0;
	//EN_PinState u8_g_MatchPIN;
	//Uchar8_t arr_g_CardPIN[5];
	//Uchar8_t arr_g_CardPAN[20];

	void Card_Trigger(void)
	{
		u8_g_ReceivePIN = 1;
	}

	EN_PinState ATM_ValidatePIN(void)
	{
		EN_PinState u8_l_MatchPIN;
		
		/* Request PIN From Card */
		HSPI_SendChar(ATM_REQUEST_PIN);
		_delay_ms(5);
		HSPI_ReceiveData(CARDpin, 5);
		_delay_ms(3000);
		
		/* Request PIN From Card */
		HSPI_SendChar(ATM_REQUEST_PAN);
		_delay_ms(5);
		HSPI_ReceiveData(CARDpan, 20);
		
		u8_l_MatchPIN = PIN_checkPinMatching(CARDpin, ATMpin);
		
		return u8_l_MatchPIN;
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
