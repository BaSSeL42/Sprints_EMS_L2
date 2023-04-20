/*
 * AUTHOR		: Bassel Yasser
 * FILE			: HLCD_Configure.c
 * DATE			: Apr 16, 2023
 * DESCRIPTION	: Pin Configuration For LCD
 */


/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include "../../MCAL/DIO/DIO_Interface.h"
#include "HLCD_Interface.h"
#include "HLCD_Configure.h"



/**************************************************************************************************
 * 											User Defined Pins
 *************************************************************************************************/
#if HLCD_MODE == HLCD_4_BIT_MODE


st_lcdDataPin_t dataPin[4] = {
		{DIO_PIND_4},
		{DIO_PIND_5},
		{DIO_PIND_6},
		{DIO_PIND_7}
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

/**************************************************************************************************
 * 											END
 *************************************************************************************************/
