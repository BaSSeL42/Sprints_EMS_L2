/*
 * DIO_prog.c
 *
 *  Created on: 5 Apr 2023
 *      Author: 20101
 */

#include "../../Common/STD_Types.h"
#include "../../Common/Bit_Math.h"

#include "dio_private.h"
#include "dio_interface.h"



volatile Uchar8_t* portReg[4] = { PORTA_REG, PORTB_REG, PORTC_REG, PORTD_REG };
volatile Uchar8_t* ddrReg[4] = { DDRA_REG, DDRB_REG, DDRC_REG, DDRD_REG };
volatile Uchar8_t* pinReg[4] = { PINA_REG, PINB_REG, PINC_REG, PIND_REG };


Uchar8_t DIO_s8SETPortDir(enu_port enPortCopy,  enu_dir enPortDir)
{
	Uchar8_t errStatus = DIO_E_OK;

	if (enPortCopy < PORT_INVALID && enPortDir < DIR_INVALID)
	{
		if (enPortDir == INPUT)
		{
			*ddrReg[enPortCopy] = 0x00;
		}
		else if(enPortDir == OUTPUT)
		{
			*ddrReg[enPortCopy] = 0xff;
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errStatus = DIO_E_NOK;
	}
	return errStatus;
}


Uchar8_t DIO_s8SETPortVal(enu_port enPortCopy,  Uchar8_t u8PortVal)
{
	Uchar8_t errStatus = DIO_E_OK;
	if (enPortCopy < PORT_INVALID)
	{
		*portReg[enPortCopy] = u8PortVal;
	}
	else
	{
		errStatus = DIO_E_NOK;
	}


	return errStatus;
}



Uchar8_t DIO_s8GETPortVal(enu_port enPortCopy,  Uchar8_t* pu8Val)
{
	Uchar8_t errStatus = DIO_E_OK;
	if (enPortCopy < PORT_INVALID )
	{
		*pu8Val = *pinReg[enPortCopy];
	}
	else
	{
		errStatus = DIO_E_NOK;
	}
	return errStatus;
}




Uchar8_t DIO_s8SETPinDir (enu_pin enPinCopy, enu_dir enPortDir)
{
	Uchar8_t errStatus = DIO_E_OK;
	Uchar8_t portID;
	Uchar8_t pinID;

	if (enPinCopy < PIN_INVALID && enPortDir< DIR_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		if (enPortDir == INPUT)
		{
			CLEAR_BIT(*ddrReg[portID],pinID);
		}
		else if(enPortDir == OUTPUT)
		{
			SET_BIT(*ddrReg[portID],pinID);
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errStatus = DIO_E_NOK;
	}
	return errStatus;
}


Uchar8_t DIO_s8SETPinVal (enu_pin enPinCopy, enu_val enPortVal)
{
	Uchar8_t errStatus = DIO_E_OK;
	Uchar8_t portID;
	Uchar8_t pinID;

	if (enPinCopy < PIN_INVALID && enPortVal< VAL_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		if (enPortVal == LOW)
		{
			CLEAR_BIT(*portReg[portID],pinID);
		}
		else if(enPortVal == HIGH)
		{
			SET_BIT(*portReg[portID],pinID);
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errStatus = DIO_E_NOK;
	}
	return errStatus;
}


Uchar8_t DIO_s8TOGPinVal (enu_pin enPinCopy)
{
	Uchar8_t errStatus = DIO_E_OK;
	Uchar8_t portID;
	Uchar8_t pinID;

	if (enPinCopy < PIN_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		TOGGLE_BIT(*portReg[portID],pinID);
	}
	else
	{
		errStatus = DIO_E_NOK;
	}
	return errStatus;

}

Uchar8_t DIO_s8GETPinVal (enu_pin enPinCopy, Uchar8_t* pu8Val)
{
	Uchar8_t errStatus = DIO_E_OK;
	Uchar8_t portID;
	Uchar8_t pinID;
	if (enPinCopy < PIN_INVALID)
	{
		portID = enPinCopy/8;
		pinID  = enPinCopy%8;

		*pu8Val = GET_BIT(*pinReg[portID], pinID);

	}
	else
	{
		errStatus = DIO_E_NOK;
	}
	return errStatus;
}