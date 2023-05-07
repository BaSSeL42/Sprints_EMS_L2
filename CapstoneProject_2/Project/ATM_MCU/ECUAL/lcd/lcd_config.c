/*
 * AUTHOR		: Bassel Yasser
 * FILE			: HLCD_Configure.c
 * DATE			: Apr 16, 2023
 * DESCRIPTION	: Pin Configuration For LCD
 */


/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include "../../Common/STD_Types.h"
#include "../../MCAL/dio/dio_interface.h"
#include "lcd_interface.h"
#include "lcd_config.h"



/**************************************************************************************************
 * 											User Defined Pins
 *************************************************************************************************/
#if HLCD_MODE == HLCD_4_BIT_MODE


st_lcdDataPin_t dataPin[4] = {
		{DIO_PINA_4},
		{DIO_PINA_5},
		{DIO_PINA_6},
		{DIO_PINA_7}
};

#elif HLCD_MODE == HLCD_8_BIT_MODE

st_lcdDataPin_t dataPin[8] = {
		{DIO_PINA_0},
		{DIO_PINA_1},
		{DIO_PINA_2},
		{DIO_PINA_3},
		{DIO_PINA_4},
		{DIO_PINA_5},
		{DIO_PINA_6},
		{DIO_PINA_7}
};


#endif

Uchar8_t arr_g_bell[8] =
{
	0b00000000,
	0b00000100,
	0b00001110,
	0b00001110,
	0b00011111,
	0b00000000,
	0b00000100,
	0b00000000
};

/**************************************************************************************************
 * 											END
 *************************************************************************************************/
