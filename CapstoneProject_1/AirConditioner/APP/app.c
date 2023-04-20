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

Uchar8_t u8_gs_PressedKey;
Uchar8_t u8_gs_tempValue = DEFAULT_TEMP;
Uchar8_t u8_gs_SelectedValue = DEFAULT_TEMP;
Uchar8_t u8_gs_CursorPosition = 0;
Uchar8_t u8_gs_SensorCounter = 50;

Uchar8_t u8_g_setFlag = 0;
float32_t f32_l_CurrentTemp = 0;
/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/
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

/**
 * \brief Initialize all modules and execute welcome routine
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
	
	/* Create custom characters */
	HLCD_vidCreatCustomChar(arr_g_bell, 1);
	
	/* Enable Global Interrupt */
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

	APP_AdjustInit();
}

/**
 * \brief Initialize temperature adjustment process
 * 
 * \return void
 */
void APP_AdjustInit(void)
{
	/* Ask user to enter temperature */
	HLCD_WriteString("Pick temperature");
	HTIM0_SyncDelay(500, mSeconds);
	HLCD_ClrDisplay();
	
	/* Display temperature selection screen */
	HLCD_WriteInt(MIN_TEMP);
	HLCD_gotoXY(0, 7);
	HLCD_WriteInt(u8_gs_SelectedValue);
	HLCD_gotoXY(0, 14);
	HLCD_WriteInt(MAX_TEMP);

	u8_gs_CursorPosition = 0;

	HLCD_gotoXY(1, 0);
	
	if(u8_gs_SelectedValue == MAX_TEMP)
	{
		HLCD_WriteString("    Max Temp    ");
		u8_gs_CursorPosition = 16;
	}
	else if (u8_gs_SelectedValue == MIN_TEMP)
	{
		HLCD_WriteString("    Min Temp    ");
	}
	else
	{
		for(int i=0; i<(u8_gs_SelectedValue-MIN_TEMP); i++)
		{
			HLCD_vidWriteChar('|');
			u8_gs_CursorPosition ++;
		}
	}
	
	/* Set Timeout */
	HTIM0_AsyncDelay(TIME_OUT_SEC, Seconds, timeout);
}

/**
 * \brief Application main logic
 * 
 * \return void
 */
void APP_Start(void)
{
	u8_gs_PressedKey = KEYPAD_GetButton();

	switch(u8_gs_PressedKey)
	{
		case KEY_INCREAMENT:
		{
			if(!u8_g_setFlag)
			{	/* Do nothing if max temp is selected */
				if(u8_gs_tempValue == MAX_TEMP) break;
				
				/* Increment temp value */
				HLCD_gotoXY(0, 7);
				HLCD_WriteInt(++ u8_gs_tempValue);
				
				if(u8_gs_tempValue == MAX_TEMP)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("    Max Temp    ");
				}
				else if(u8_gs_tempValue == MIN_TEMP+1)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("|               ");
					u8_gs_CursorPosition = 1;
				}
				else
				{
					/* Increment bars */
					HLCD_gotoXY(1, u8_gs_CursorPosition++);
					HLCD_vidWriteChar('|');
				}
				
				/* Reset Timeout */
				HTIM0_AsyncEndDelay();
				HTIM0_AsyncDelay(TIME_OUT_SEC, Seconds, timeout);
			}
			else /* Wrong Operation */
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
			{	/* Do nothing if min temp is selected */
				if(u8_gs_tempValue == MIN_TEMP) break;
				
				/* Display temperature */
				HLCD_gotoXY(0, 7);
				HLCD_WriteInt(-- u8_gs_tempValue);
				
				if(u8_gs_tempValue == MAX_TEMP-1)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("||||||||||||||||");
				}
				else if(u8_gs_tempValue == MIN_TEMP)
				{
					HLCD_gotoXY(1, 0);
					HLCD_WriteString("     Min Temp    ");
				}
				else
				{
					/* Delete last bar */
					HLCD_gotoXY(1, --u8_gs_CursorPosition);
					HLCD_vidWriteChar(' ');
				}
				
				/* Reset timeout */
				HTIM0_AsyncEndDelay();
				HTIM0_AsyncDelay(TIME_OUT_SEC, Seconds, timeout);
			}
			else
			{/* Wrong Operation */
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
				/* Store selected temperature value */
				u8_gs_SelectedValue = u8_gs_tempValue;
				
				HLCD_ClrDisplay();
				/* Disable timeout */
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
			if(!u8_g_setFlag) break;
			u8_gs_tempValue = u8_gs_SelectedValue;
			u8_g_setFlag = 0;
			BUZ_SetState(&st_g_Buzzer, BUZ_OFF);

			APP_AdjustInit();
			break;
		}
		case KEY_RESET:
		{
			if(!u8_g_setFlag) break;
			u8_gs_SelectedValue = DEFAULT_TEMP;
			HLCD_ClrDisplay();
			HLCD_WriteString("Temp set to 20");
			HLCD_gotoXY(1, 0);
			HLCD_WriteString("degrees!");
			HTIM0_SyncDelay(500, mSeconds);

			HLCD_ClrDisplay();
			break;
		}
		default:
		{
			if(u8_gs_SensorCounter == 50)
			{
				u8_gs_SensorCounter = 0;
				TSENSOR_ReadValue(&st_g_TempSensor, &f32_l_CurrentTemp);
				
				/* Approximate Reading to the closest integer */
				if(f32_l_CurrentTemp-(Uint32_t)f32_l_CurrentTemp >= 0.5)
				{f32_l_CurrentTemp = (Uint32_t)f32_l_CurrentTemp+1;}
				else
				{f32_l_CurrentTemp = (Uint32_t)f32_l_CurrentTemp;}
			}
			else
			{
				u8_gs_SensorCounter++;
				return;
			}
			
			if(u8_g_setFlag)
			{
				/* Display Current temperature */
				HLCD_gotoXY(0,0);
				HLCD_WriteString("Current temp ");
				HLCD_WriteInt(f32_l_CurrentTemp);
				
				if(f32_l_CurrentTemp > u8_gs_SelectedValue)
				{	/* Turn buzzer on and display icon */
					HLCD_vidWriteChar(1);
					BUZ_SetState(&st_g_Buzzer, BUZ_ON);
					return;
				}
				
				HLCD_gotoXY(0,15);
				HLCD_vidWriteChar(' ');
				BUZ_SetState(&st_g_Buzzer, BUZ_OFF);
			}
		}
	}
	
}