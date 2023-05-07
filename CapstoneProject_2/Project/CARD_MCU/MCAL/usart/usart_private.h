/*
 * usart_private.h
 *
 * Created: 4/23/2023 3:50:41 AM
 *  Author: sharpel
 */ 


#ifndef USART_PRIVATE_H_
#define USART_PRIVATE_H_


// registers

#define UDR     (*(VUchar8_t*)(0x2C))
#define UCSRA   (*(VUchar8_t*)(0x2B))
#define UCSRB   (*(VUchar8_t*)(0x2A))
#define UCSRC   (*(VUchar8_t*)(0x40))
#define UBRRH   (*(VUchar8_t*)(0x40))
#define UBRRL   (*(VUchar8_t*)(0x29))


#define USART_ASYNC_MODE     0
#define USART_SYNC_MODE      1
						    
#define USART_DIS_PARITY     0
#define USART_ODD_PARITY     1
#define USART_EVEN_PARITY    2
						    
						    
#define USART_DATA_SIZE_5    5
#define USART_DATA_SIZE_6    6
#define USART_DATA_SIZE_7    7
#define USART_DATA_SIZE_8    8
#define USART_DATA_SIZE_9    9
						    
						    
#define USART_ONE_STOP_BIT   1
#define USART_TWO_STOP_BITS  2

#define USART_NORMAL_SPEED   0
#define USART_DOUBLE_SPEED   1


#define ENTER_KEY            13


// UCSRA bitS nameS

#define MPCM     0
#define U2X      1
#define PE       2
#define DOR      3
#define FE       4
#define UDRE     5
#define TXC      6
#define RXC      7


// UCSRB bitS nameS

#define TXB8     0
#define RXB8     1
#define UCSZ2    2
#define TXEN     3
#define RXEN     4
#define UDRIE    5
#define TXCIE    6
#define RXCIE    7




// UCSRC bitS nameS

#define UCPOL    0
#define UCSZ0    1
#define UCSZ1    2
#define USBS     3
#define UPM0     4
#define UPM1     5
#define UMSEL    6
#define URSEL    7

#endif /* USART_PRIVATE_H_ */