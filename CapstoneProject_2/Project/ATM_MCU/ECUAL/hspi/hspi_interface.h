/*
 * spi_interface.h
 *
 * Created: 4/27/2023 3:53:49 AM
 *  Author: ME
 */ 


#ifndef HSPI_INTERFACE_H_
#define HSPI_INTERFACE_H_

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/

#define HSPI_MOSI					DIO_PINB_5
#define HSPI_MISO					DIO_PINB_6
#define HSPI_CLK					DIO_PINB_7
#define HSPI_SS						DIO_PINB_4

/* Used in master MCU for receiving slave requests */
#define MASTER_SLAVE_REQUEST_PIN	DIO_PINB_2		//EXTI2 Pin

/* Used in slave MCU for requesting communication from master */
#define SLAVE_SEND_REQUEST_PIN		DIO_PINB_0		

#define DATA_END					'#'
/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef enum
{
	HSPI_OK,
	HSPI_NOK
}en_HSPI_ErrorState_t;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * \brief Initialize the MCU as the Master
 *		  in SPI communication
 *
 * \return void
 */
void HSPI_MasterInit(void);

/**
 * \brief Initialize the MCU as a slave
 *		  in SPI communication				
 * 
 * \return void
 */
void HSPI_SlaveInit(void);

/**
 * \brief Function to send a single character
 * 
 * \param u8_a_character character to send
 * 
 * \return void
 */
void HSPI_SendChar(Uchar8_t u8_a_character);

/**
 * \brief Send an entire string 
 * 
 * \param pchar_a_string String to send
 * 
 * \return en_HSPI_ErrorState_t
 */
void HSPI_SendString(const char* pchar_a_string);

/**
 * \brief Send an array of data
 * 
 * \param pu8_a_data: reference to array of data to send
 * \param u8_a_DataSize: Size of data to send
 * 
 * \return en_HSPI_ErrorState_t
 */
en_HSPI_ErrorState_t HSPI_SendData(Uchar8_t* pu8_a_data, Uchar8_t u8_a_DataSize);

/**
 * \brief Function to Receive a single character
 * 
 * \param pu8_a_character pointer to variable to store
 *						  received character
 * \return en_HSPI_ErrorState_t
 */
en_HSPI_ErrorState_t HSPI_ReceiveChar(Uchar8_t* pu8_a_character);

/**
 * \brief Receive data in the reception buffer
 * 
 * \param 
 * 
 * \return en_HSPI_ErrorState_t
 */
void HSPI_ReceiveData(Uchar8_t *pu8_a_data, Uchar8_t u8_a_DataSize);


/**
 * \brief Send given data byte by byte to selected slave
 *		  and receive data in exchange into given array
 * \param pu8_a_TxDataArr: Reference to array of data to be transmitted
 * \param pu8_a_RxDataArr: Reference to array to store received data
 * \param u8_a_DataLen:	   Length of data to exchange (in bytes)
 *					       (Must be less than or equal SPI_BUFFER_SIZE)
 * 
 * \return en_HSPI_ErrorState_t
 */
en_HSPI_ErrorState_t HSPI_ExchangeData(Uchar8_t* pu8_a_TxDataArr, Uchar8_t* pu8_a_RxDataArr, Uchar8_t u8_a_DataLen);


/**
 * \brief Request to send data to the master
 * 
 * \param u8_a_data: data to send
 * 
 * \return void
 */
void HSPI_SlaveRequest(Uchar8_t* pu8_a_dataPtr, Uchar8_t u8_a_DataSize);



#endif /* SPI_INTERFACE_H_ */