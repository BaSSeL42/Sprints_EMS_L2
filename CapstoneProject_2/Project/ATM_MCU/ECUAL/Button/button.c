/*
 * button.c
 *
 *  Created on: Apr 4, 2023
 *      Author: hp
 */


#include "../../Common/std_types.h"
#include "../../Common/Bit_Math.h"
//#include "../../MCAL/DIO/DIO_Interface.h"

#include "button.h"



enu_buttonError_t HButton_Init(enu_pin en_pinx)
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < PIN_INVALID )
	{
		DIO_s8SETPinDir(en_pinx, INPUT);
	}
	else
	{
		errorStatus = BUTTON_OK;
	}

	return errorStatus;
}


enu_buttonError_t HButton_getPinVal(enu_pin en_pinx,  Uchar8_t* pu8_refVal )
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < PIN_INVALID && pu8_refVal != NULL )
	{
		(void)DIO_s8GETPinVal(en_pinx, pu8_refVal);
	}
	else
	{
		errorStatus = BUTTON_OK;
	}

	return errorStatus;

}


enu_buttonError_t HButton_ExtIntInit(enu_pin en_pinx)
{
	enu_buttonError_t errorStatus = BUTTON_OK;

	if ( en_pinx < PIN_INVALID )
	{
		DIO_s8SETPinVal(en_pinx, HIGH);
	}
	else
	{
		errorStatus = BUTTON_OK;
	}

	return errorStatus;
}


