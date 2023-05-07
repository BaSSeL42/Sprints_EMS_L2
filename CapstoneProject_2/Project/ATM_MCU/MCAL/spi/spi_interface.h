/*
 * spi_interface.h
 *
 * Created: 4/27/2023 3:53:49 AM
 *  Author: ME
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
#define SPI_TIMEOUT			100000

#define SPI_BUFFER_SIZE		15

#define DATA_END			'#'
/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef enum
{
	SPI_OK,
	SPI_NOK
}en_SPI_ErrorState_t;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * \brief Initialize the MCU as the Master
 *		  in SPI communication
 *
 * \return void
 */
void SPI_MasterInit(void);

/**
 * \brief Initialize the MCU as a slave
 *		  in SPI communication				
 * 
 * \return void
 */
void SPI_SlaveInit(void);

/**
 * \brief Sets the value of the SPI data register
 * 
 * \param u8_a_data: Desired value
 * 
 * \return void
 */
void SPI_SetValue(Uchar8_t u8_a_data);

/**
 * \brief Exchange a letter with selected slave
 * 
 * \param u8_a_character Character to send
 * \param pu8_a_receivedChar Pointer to character to store received value
 * 
 * \return en_SPI_ErrorState_t
 */
en_SPI_ErrorState_t SPI_TranscieveChar(Uchar8_t u8_a_character, Uchar8_t* pu8_a_receivedChar);

/**
 * \brief Set a notification function for the SPI Interrupt 
 * 
 * \param pv_a_CallbackFn reference to the function to callback
 *						  when the SPI Interrupt is triggered
 * \return en_SPI_ErrorState_t
 */
en_SPI_ErrorState_t SPI_SetCallback(void (*pv_a_CallbackFn)(void));


#endif /* SPI_INTERFACE_H_ */