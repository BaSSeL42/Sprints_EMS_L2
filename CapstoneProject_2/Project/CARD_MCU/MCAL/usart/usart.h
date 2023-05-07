/*
 * usart.h
 *
 * Created: 4/23/2023 3:49:27 AM
 *  Author: sharpel
 */ 


#ifndef USART_H_
#define USART_H_

typedef enum EN_USART_ERROR{
	USART_OK=0,
	USART_NOT_OK
	}EN_USART_ERROR;


/*
Name   : USART_init
Description : This function initializes USART Module with selected options in USART.cfg file.
Args   : Void (all options defined as macros).
return : Std_ReturnType (E_OK) if Module initializes Correctly, (E_NOT_OK) otherwise.
*/
EN_USART_ERROR USART_init(void);

/*
Name   : USART_sendData
Description : This function Send Data To Receiver (we can change size of data from USART.cfg file) we select 8 bits data size.
Args   : take one argument (data to be sent) must be same size as the size we select in Initialization function.
return : Std_ReturnType (E_OK) if module sent data Correctly, (E_NOT_OK) otherwise.
*/
EN_USART_ERROR USART_sendData(Uchar8_t data);


/*
Name   : USART_receiveData
Description : This function Receive Data from sender (we can change size of data from USART.cfg file) we select 8 bits data size.
Args   : void
return : data received. must be same size as the size we select in Initialization function.
*/
Uchar8_t USART_receiveData(void);


/*
Name   : USART_sendSTRING
Description : This function send array of data To Receiver. (we can change size of data from USART.cfg file) we select 8 bits data size.
Args   : pointer to the array of data to be sent
return : void
*/
void USART_sendSTRING(Uchar8_t * str);


/*
Name   : USART_receiveSTRING
Description : This function receive data from sender and store it in array.
Args   : pointer to the array to store data received in it and size of data.
return : void
*/
void USART_receiveSTRING(Uchar8_t * str,Uchar8_t size);




#endif /* USART_H_ */