/*
 * husart.c
 *
 * Created: 4/30/2023 5:45:18 PM
 *  Author: sharb
 */ 

#include "../../Common/STD_Types.h"

#include "husart.h"


EN_USART_ERROR HUSART_enInit(void)
{
	if(USART_init())return USART_NOT_OK;
	return USART_OK;
}
EN_USART_ERROR HUSART_enSendData(Uchar8_t Copy_u8DataH)
{
	if(USART_sendData(Copy_u8DataH))return USART_NOT_OK;
	return USART_OK;
}
EN_USART_ERROR HUSART_enRecieveData(Uchar8_t* Ref_u8DataH)
{
	*Ref_u8DataH = USART_receiveData();
	return USART_OK;
}

void HUSART_sendSTRING(Uchar8_t * Hstr)
{
	USART_sendSTRING(Hstr);
}
void HUSART_receiveSTRING(Uchar8_t * Hstr ,Uchar8_t Hsize )
{
	USART_receiveSTRING(Hstr,Hsize);
}