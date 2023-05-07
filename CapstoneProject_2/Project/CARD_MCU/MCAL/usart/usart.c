/*
 * usart.c
 *
 * Created: 4/23/2023 3:49:14 AM
 *  Author: sharpel
 */ 

#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"
#include "usart_private.h"
#include "usart_config.h"
#include "usart.h"


EN_USART_ERROR USART_init(void)
{
	
	/* select UCSRC Register*/
	SET_BIT(UCSRC,URSEL);
	
	/* select USART mode (ASYNC,SYNC) */
	#if USART_SET_MODE == USART_ASYNC_MODE
	CLEAR_BIT(UCSRC,UMSEL);
	
	#elif USART_SET_MODE == USART_SYNC_MODE
	SET_BIT(UCSRC,UMSEL);
	
	#else 
	return USART_NOT_OK;
	
	#endif
	
	/* select USART Parity mode (DIS,ODD,EVEN) */
	#if USART_SET_PARITY_MODE == USART_DIS_PARITY
	CLEAR_BIT(UCSRC,UPM0);
	CLEAR_BIT(UCSRC,UPM1);
	
	#elif USART_SET_PARITY_MODE == USART_ODD_PARITY
	SET_BIT(UCSRC,UPM0);
	SET_BIT(UCSRC,UPM1);
	
	#elif USART_SET_PARITY_MODE == USART_EVEN_PARITY
	CLEAR_BIT(UCSRC,UPM0);
	SET_BIT(UCSRC,UPM1);
	
	#else 
	return USART_NOT_OK;
	
	#endif
	
	/* select USART Stop Bit (One,Two) */
	#if USART_SET_STOP_BIT == USART_ONE_STOP_BIT
	CLEAR_BIT(UCSRC,USBS);
	
	#elif USART_SET_STOP_BIT == USART_TWO_STOP_BITS
	SET_BIT(UCSRC,USBS);
	
	#else 
	return USART_NOT_OK;
	
	#endif
	
	/* select USART Data size (5,6,7,8,9) */
	#if USART_SET_DATA_SIZE == USART_DATA_SIZE_5
	CLEAR_BIT(UCSRC,UCSZ0);
	CLEAR_BIT(UCSRC,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);
	
	#elif USART_SET_DATA_SIZE == USART_DATA_SIZE_6
	SET_BIT(UCSRC,UCSZ0);
	CLEAR_BIT(UCSRC,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);
	
	#elif USART_SET_DATA_SIZE == USART_DATA_SIZE_7
	CLEAR_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);
	
	#elif USART_SET_DATA_SIZE == USART_DATA_SIZE_8
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	CLEAR_BIT(UCSRB,UCSZ2);
	
	#elif USART_SET_DATA_SIZE == USART_DATA_SIZE_9
	SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);
	
	#else 
	return USART_NOT_OK;
	
	#endif
	
	/* select USART Speed (Normal,Double) */
	#if USART_SET_SPEED == USART_NORMAL_SPEED
	CLEAR_BIT(UCSRA,U2X);
	
	#elif USART_SET_MODE == USART_SYNC_MODE
	SET_BIT(UCSRA,U2X);
	
	#else
	return USART_NOT_OK;
	
	#endif
	/* Enable Transmit and receive bits in UCSRB*/
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	
	/* assign UBRRL and UBRRH with calculated BAUD_PRESCALLER */
	UBRRL = BAUD_PRESCALLER;
	UBRRH = (BAUD_PRESCALLER>>8);
	
   return USART_OK;
}
EN_USART_ERROR USART_sendData(Uchar8_t data)
{
	// WAIT UNTIL ISEMPTY FLAG IS SET
	while(!GET_BIT(UCSRA,UDRE));
	
	// assign data to UDR register to be sent
	UDR = data;
	
	return USART_OK;
}
Uchar8_t USART_receiveData(void)
{
	// WAIT UNTIL Recieve FLAG IS SET
	while(!GET_BIT(UCSRA,RXC));
	return UDR;
}
void USART_sendSTRING(Uchar8_t * str)
{
	Uchar8_t COUNTER = 0;
	while(str[COUNTER] != null)
	{
		USART_sendData(str[COUNTER]);
		COUNTER++;
	}
}
void USART_receiveSTRING(Uchar8_t * str ,Uchar8_t size )
{
	Uchar8_t COUNTER = 0;
	while(COUNTER < size-1)
	{
		
		str[COUNTER]= USART_receiveData();
		if(str[COUNTER] == ENTER_KEY)break;
		USART_sendData(str[COUNTER]);
		COUNTER++;
	}
	str[COUNTER] = null;
}


