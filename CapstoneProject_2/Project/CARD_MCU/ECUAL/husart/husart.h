/*
 * husart.h
 *
 * Created: 4/30/2023 5:45:32 PM
 *  Author: sharb
 */ 


#ifndef HUSART_H_
#define HUSART_H_

#include "../../MCAL/usart/usart.h"

EN_USART_ERROR HUSART_enInit(void);
EN_USART_ERROR HUSART_enSendData(Uchar8_t Copy_u8DataH);
EN_USART_ERROR HUSART_enRecieveData(Uchar8_t* Ref_u8DataH);

void HUSART_sendSTRING(Uchar8_t * Hstr);
void HUSART_receiveSTRING(Uchar8_t * Hstr ,Uchar8_t Hsize );


#endif /* HUSART_H_ */