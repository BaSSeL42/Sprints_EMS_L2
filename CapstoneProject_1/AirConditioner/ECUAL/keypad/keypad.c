/*
 * keypad.c
 *
 * Created: 4/17/2023 4:07:05 AM
 *  Author: ME
 */ 
/*************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"

#include "../../MCAL/dio/dio_interface.h"

#include "keypad.h"
/*************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/

/*************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/
void KEYPAD_init()
{
	// INITIALIZE ROWS AS OUTPUTS
	DIO_s8SETPinDir(R1,OUTPUT);
	DIO_s8SETPinDir(R2,OUTPUT);
	DIO_s8SETPinDir(R3,OUTPUT);
	// INITIALIZE COLUMNS AS INPUTS
	DIO_s8SETPinDir(C1,INPUT);
	DIO_s8SETPinDir(C2,INPUT);
	DIO_s8SETPinDir(C3,INPUT);
	
}
EN_KEYPAD_BTNS checkR1()
{
	DIO_s8SETPinVal(C1,HIGH);
	DIO_s8SETPinVal(C2,HIGH);
	DIO_s8SETPinVal(C3,HIGH);
	DIO_s8SETPinVal(R2,HIGH);
	DIO_s8SETPinVal(R3,HIGH);
	DIO_s8SETPinVal(R1,LOW);
	
	Uchar8_t val = HIGH;
	DIO_s8GETPinVal(C1,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C1,&val);
		}
		return KEY_INCREAMENT;
	}
	
	DIO_s8GETPinVal(C2,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C2,&val);
		}
		return KEY_DECREAMENT;
	}
	
	DIO_s8GETPinVal(C3,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C3,&val);
		}
		return KEY_SET;
	}
	return KEY_NOTHING;
	
}
EN_KEYPAD_BTNS checkR2()
{
	
	DIO_s8SETPinVal(C1,HIGH);
	DIO_s8SETPinVal(C2,HIGH);
	DIO_s8SETPinVal(C3,HIGH);
	DIO_s8SETPinVal(R1,HIGH);
	DIO_s8SETPinVal(R3,HIGH);
	DIO_s8SETPinVal(R2,LOW);
	
	Uchar8_t val = HIGH;
	DIO_s8GETPinVal(C1,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C1,&val);
		}
		return KEY_ADJUST;
	}
	
	DIO_s8GETPinVal(C2,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C2,&val);
		}
		return KEY_RESET;
	}
	
	DIO_s8GETPinVal(C3,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C3,&val);
		}
		return KEY_6;
	}
	return KEY_NOTHING;
	
}
EN_KEYPAD_BTNS checkR3()
{
	
	DIO_s8SETPinVal(C1,HIGH);
	DIO_s8SETPinVal(C2,HIGH);
	DIO_s8SETPinVal(C3,HIGH);
	DIO_s8SETPinVal(R1,HIGH);
	DIO_s8SETPinVal(R2,HIGH);
	DIO_s8SETPinVal(R3,LOW);
	
	Uchar8_t val = HIGH;
	DIO_s8GETPinVal(C1,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C1,&val);
		}
		return KEY_7;
	}
	
	DIO_s8GETPinVal(C2,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C2,&val);
		}
		return KEY_8;
	}
	
	DIO_s8GETPinVal(C3,&val);
	if(val == LOW)
	{
		while (val == LOW)
		{
			DIO_s8GETPinVal(C3,&val);
		}
		return KEY_9;
	}
	return KEY_NOTHING;
}

EN_KEYPAD_BTNS KEYPAD_GetButton()
{
	EN_KEYPAD_BTNS PRESSED = KEY_NOTHING;
	PRESSED = checkR1();
	if(PRESSED != KEY_NOTHING) return PRESSED;
	PRESSED = checkR2();
	if(PRESSED != KEY_NOTHING) return PRESSED;
	PRESSED = checkR3();
	if(PRESSED != KEY_NOTHING) return PRESSED;
	return PRESSED;
	
}
