/*
 * spi_register.h
 *
 * Created: 4/27/2023 5:00:22 AM
 *  Author: ME
 */ 


#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

#define  SPDR                     *((volatile Uchar8_t*)0x2f)		/* SPI Data Register */

#define  SPSR                     *((volatile Uchar8_t*)0x2e) 		/* SPI Status Register		*/
#define  SPSR_SPIF                7									/* SPI Interrupt Flag		*/
#define  SPSR_WCOL                6									/* SPI Write Collision Flag */
#define  SPSR_SPI2X               0									/* Double SPI Speed Bit		*/


#define  SPCR                     *((volatile Uchar8_t*)0x2d)		/* SPI Control Register */
#define  SPCR_SPIE                7									/* SPI Interrupt Enable */
#define  SPCR_SPE                 6									/* SPI Enable			*/
#define  SPCR_DORD                5									/* Data Order			*/
#define  SPCR_MSTR                4									/* Master/Slave Select  */
#define  SPCR_CPOL                3									/* Clock Polarity		*/
#define  SPCR_CPHA                2									/* Clock Phase			*/
#define  SPCR_SPR1                1									/* SPI Prescaler bit 1  */
#define  SPCR_SPR0                0									/* SPI Prescaler bit 0  */

#define  SPCSR                    *((volatile Uint16_t*)0x2d)		/* SPI Control and Status Registers */

#endif /* SPI_REGISTER_H_ */