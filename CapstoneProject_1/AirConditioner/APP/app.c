/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include "../Common/STD_Types.h"
#include "../Common/BIT_Math.h"
#include "../Common/vect_table.h"

#include "../ECUAL/buzzer/buzzer.h"
#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/keypad/keypad.h"
#include "../ECUAL/lcd/lcd_interface.h"
#include "../ECUAL/temp_sensor/temp_sensor.h"

#include "app.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
extern st_Buzzer_t st_g_Buzzer;
extern st_TempSensor_t st_g_TempSensor;
extern Uchar8_t arr_g_bell[8];

Uchar8_t u8_g_tempValue = DEFAULT_TEMP;
Uchar8_t u8_g_SelectedValue = DEFAULT_TEMP;
Uchar8_t u8_g_setFlag = 0;
Uchar8_t u8_g_CursorPosition = 0;
Uchar8_t u8_g_SensorCounter = 50;

float32_t f32_l_CurrentTemp = 0;
/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/

/**
 * \brief Initialize all modules and execute welcome routine
 * 
 * \param 
 * 
 * \return void
 */
void APP_Init(void)
{
	/* Initialize used modules */
	HLCD_vidInit();
	HLCD_vidWritecmd(HLCD_DISPLAY_ON_CURSOR_OFF);
	KEYPAD_init();
	TSENSOR_Init(&st_g_TempSensor);
	BUZ_Init(&st_g_Buzzer);
	HLCD_vidCreatCustomChar(arr_g_bell, 1);
	sei();
	
	/* Display welcome message for one second */
	HLCD_gotoXY(0, 4);
	HLCD_WriteString("Welcome!");
	HTIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();
	
	/* Display Default Temperature */
	HLCD_WriteString(" Default temp:");
	HLCD_gotoXY(1, 7);
	HLCD_WriteInt(DEFAULT_TEMP);
	HTIM0_SyncDelay(1, Seconds);
	HLCD_ClrDisplay();

	APP_adjustInit();
}

/**
 * \brief Initialize temperature adjustment process
 * 
 * \param 
 * 
 * \return void
 */
static void APP_adjustInit(void)
{
	/* Ask user to enter temperature */
	HLCD_WriteString("Pick temperature");
	HTIM0_SyncDelay(500, mSeconds);
	HLCD_ClrDisplay();
	
	HLCD_WriteInt(MIN_TEMP);
	HLCD_gotoXY(0, 7);
	HLCD_WriteInt(u8_g_SelectedValue);
	HLCD_gotoXY(0, 14);
	HLCD_WriteInt(MAX_TEMP);

	u8_g_CursorPosition = 0;

	HLCD_gotoXY(1, 0);
	
	for(int i=0; i<(u8_g_SelectedValue-MIN_TEMP); i++)
	{
		HLCD_vidWriteChar('|');
		u8_g_CursorPosition ++;
	}

	HTIM0_AsyncDelay(TIME_OUT_SEC, Seconds, timeout);
}

/**
 * \brief Application main logic
 * 
 * \param 
 * 
 * \return void
 */
void APP_Start(void)
{
	Uchar8_t u8_l_PressedKey;

	u8_l_PressedKey = GetButton();

	switch(u8_l_PressedKey)
	{
		case KEY_INCREAMENT:
		{
			if(!u8_g_setFlag)
			{
				if(u8_g_tempValue == MAX_TEMP) break;
				
				if(u8_g_tempValue == MIN_TEMP)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("                ");
				}
				
				HLCD_gotoXY(0, 7);
				HLCD_WriteInt(++ u8_g_tempValue);
				if(u8_g_tempValue == MAX_TEMP)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("    Max Temp    ");
				}
				
				HLCD_gotoXY(1, u8_g_CursorPosition++);
				
				//u8_g_CursorPosition++;
				HLCD_vidWriteChar('|');
				HTIM0_AsyncEndDelay();
				HTIM0_AsyncDelay(TIME_OUT_SEC, Seconds, timeout);
			}
			else
			{
				HLCD_ClrDisplay();
				HLCD_WriteString("This Operation");
				HLCD_gotoXY(1, 0);
				HLCD_WriteString("is not allowed!");
				HTIM0_SyncDelay(500, mSeconds);

				HLCD_ClrDisplay();
			}
			break;
		}
		case KEY_DECREAMENT:
		{
			if(!u8_g_setFlag)
			{
				if(u8_g_tempValue == MIN_TEMP) break;
				
				if(u8_g_tempValue == MAX_TEMP)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("||||||||||||||||");
				}
				
				/* Display temperature */
				HLCD_gotoXY(0, 7);
				HLCD_WriteInt(-- u8_g_tempValue);
				
				/* Delete last bar */
				HLCD_gotoXY(1, --u8_g_CursorPosition);
				HLCD_vidWriteChar(' ');
				
				if(u8_g_CursorPosition == 0)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("     Min Temp    ");
				}
				
				/* Start new delay for timeout */
				HTIM0_AsyncEndDelay();
				HTIM0_AsyncDelay(TIME_OUT_SEC, Seconds, timeout);
			}
			else
			{
				HLCD_ClrDisplay();
				HLCD_WriteString("This Operation");
				HLCD_gotoXY(1, 0);
				HLCD_WriteString("is not allowed!");
				HTIM0_SyncDelay(500, mSeconds);

				HLCD_ClrDisplay();
			}
			break;
		}
		case KEY_SET:
		{
			if(!u8_g_setFlag)
			{
				u8_g_setFlag = 1;
				u8_g_SelectedValue = u8_g_tempValue;
				HLCD_ClrDisplay();
				HTIM0_AsyncEndDelay();
			}
			else
			{
				HLCD_ClrDisplay();
				HLCD_WriteString("This Operation");
				HLCD_gotoXY(1, 0);
				HLCD_WriteString("is not allowed!");
				HTIM0_SyncDelay(500, mSeconds);

				HLCD_ClrDisplay();
			}
			break;
		}
		case KEY_ADJUST:
		{
			/* Break if no temperature is set or no timeout */
			if(!u8_g_setFlag) break;
			
			u8_g_tempValue = u8_g_SelectedValue;
			u8_g_setFlag = 0;
			BUZ_SetState(&st_g_Buzzer, BUZ_OFF);

			APP_adjustInit();
			break;
		}
		case KEY_RESET:
		{
			/* Break if no temperature is set or no timeout */
			if(!u8_g_setFlag) break;
			
			u8_g_SelectedValue = DEFAULT_TEMP;
			break;
		}
	}
	
	if(u8_g_SensorCounter == 50)
	{
		u8_g_SensorCounter = 0;
		TSENSOR_ReadValue(&st_g_TempSensor, &f32_l_CurrentTemp);
		
		/* Approximate Reading to the closest integer */
		if(f32_l_CurrentTemp-(Uint32_t)f32_l_CurrentTemp >= 0.5)
		f32_l_CurrentTemp = (Uint32_t)f32_l_CurrentTemp+1;
		else
		f32_l_CurrentTemp = (Uint32_t)f32_l_CurrentTemp;
	}
	else
	{
		u8_g_SensorCounter++;
	}

	
	
	if(u8_g_setFlag)
	{
		HLCD_gotoXY(0,0);
		HLCD_WriteString("Current temp ");
		HLCD_WriteInt(f32_l_CurrentTemp);
		if(f32_l_CurrentTemp > u8_g_SelectedValue)
		{
			HLCD_vidWriteChar(1);
			BUZ_SetState(&st_g_Buzzer, BUZ_ON);
			return;
		}
		HLCD_gotoXY(0,15);
		HLCD_vidWriteChar(' ');
		BUZ_SetState(&st_g_Buzzer, BUZ_OFF);
	}
}

/**
 * \brief timeout callback function
 * 
 * \return void
 */
void timeout(void)
{
	u8_g_setFlag = 1;
	HLCD_ClrDisplay();
	HLCD_gotoXY(0, 4);
	HLCD_WriteString("Timeout!");
	HTIM0_SyncDelay(500, mSeconds);
	HLCD_vidWritecmd(HLCD_DISPLAY_ON_CURSOR_OFF);
}