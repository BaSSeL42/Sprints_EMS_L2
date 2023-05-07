/*
 * spi_private.h
 *
 * Created: 4/27/2023 3:54:14 AM
 *  Author: ME
 */ 


#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define SPI_CLK_MASK				0xfcfe

#define SPI_DIV_BY_2				0x0001
#define SPI_DIV_BY_4				0x0000
#define SPI_DIV_BY_8				0x0101
#define SPI_DIV_BY_16				0x0100
#define SPI_DIV_BY_32				0x0201
#define SPI_DIV_BY_64				0x0300
#define SPI_DIV_BY_128				0x0301

/* SPI Slave Functional States */
#define SPI_SLAVE_IDLE				0
#define SPI_SLAVE_SEND_BYTE			1
#define SPI_SLAVE_SEND_ARRAY		2
#define SPI_SLAVE_RECEIVE_BYTE		3
#define SPI_SLAVE_RECEIVE_ARRAY		4

#endif /* SPI_PRIVATE_H_ */