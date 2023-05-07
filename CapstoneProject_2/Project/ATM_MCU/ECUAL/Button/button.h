/*
 * button.h
 *
 *  Created on: Apr 4, 2023
 *      Author: hp
 */

#ifndef HAL_BUTTON_BUTTON_H_
#define HAL_BUTTON_BUTTON_H_

#include "../../MCAL/DIO/DIO_Interface.h"

typedef enum
{
	BUTTON_NOK = 0,
	BUTTON_OK

}enu_buttonError_t;



enu_buttonError_t HButton_Init(enu_pin en_pinx);
enu_buttonError_t HButton_getPinVal(enu_pin en_pinx,  Uchar8_t* pu8_refVal );
enu_buttonError_t HButton_ExtIntInit(enu_pin en_pinx);


#endif /* HAL_BUTTON_BUTTON_H_ */
