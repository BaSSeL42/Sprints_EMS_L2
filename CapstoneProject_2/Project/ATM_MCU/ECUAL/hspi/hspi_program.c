/*
 * spi_program.c
 *
 * Created: 4/27/2023 3:54:39 AM
 *  Author: ME
 */ 
/*************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"

#include <util/delay.h>

#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/extint/extinterrupt.h"
#include "../../MCAL/spi/spi_interface.h"

#include "hspi_interface.h"

/*************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/
extern Uchar8_t *pu8_g_SlaveTxPtr;
extern Uchar8_t u8_g_SlaveTxIndex;
extern Uchar8_t u8_g_SlaveTxLen;

/*************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/
/**
 * \brief Initialize the MCU as the Master
 *		  in SPI communication
 *
 * \return void
 */
void HSPI_MasterInit(void)
{
	/* Set MOSI pin as Output */
	DIO_s8SETPinDir(HSPI_MOSI, OUTPUT);

	/* Set CLK pin as Output */
	DIO_s8SETPinDir(HSPI_CLK, OUTPUT);

	/* Set Slave Select pin(s) as Output */
	DIO_s8SETPinDir(HSPI_SS, OUTPUT);
	DIO_s8SETPinVal(HSPI_SS, HIGH);
			
	/* Set MISO pin as Input */
	DIO_s8SETPinDir(HSPI_MISO, INPUT);
	
	/* Initialize EXTI pin for slave requests */
	EXTINT_init(MASTER_SLAVE_REQUEST_PIN, RISING_EDGE);
	
	/* Initialize SPI Registers */
	SPI_MasterInit();
}

/**
 * \brief Initialize the MCU as a slave
 *		  in SPI communication				
 * 
 * \return void
 */
void HSPI_SlaveInit(void)
{
	/* Set MOSI pin as Input */
	DIO_s8SETPinDir(HSPI_MOSI, INPUT);

	/* Set CLK pin as Input */
	DIO_s8SETPinDir(HSPI_CLK, INPUT);

	/* Set Slave Select pin as Input (pulled up) */
	DIO_s8SETPinDir(HSPI_SS, INPUT);
	DIO_s8SETPinVal(HSPI_SS, HIGH);
	
	/* Set MISO pin as Output */
	DIO_s8SETPinDir(HSPI_MISO, OUTPUT);	
	
	/* Set pin for sending comm. requests to master as Output */
	DIO_s8SETPinDir(SLAVE_SEND_REQUEST_PIN, OUTPUT);	
	
	/* Initialize SPI Registers */
	SPI_SlaveInit();
	
	DIO_s8SETPinVal(HSPI_SS, HIGH);
}

/**
 * \brief Function to send a single character
 * 
 * \param u8_a_character character to send
 * 
 * \return void
 */
void HSPI_SendChar(Uchar8_t u8_a_character)
{
	Uchar8_t u8_l_dummyVar;
	
	DIO_s8SETPinVal(HSPI_SS, LOW);
	SPI_TranscieveChar(u8_a_character, &u8_l_dummyVar);
	DIO_s8SETPinVal(HSPI_SS, HIGH);
	
}

/**
 * \brief Send an entire string 
 * 
 * \param pchar_a_string String to send
 * 
 * \return void
 */
void HSPI_SendString(const char* pchar_a_string)
{
	Uchar8_t u8_l_StringIterator = 0;
	
	while(pchar_a_string[u8_l_StringIterator] != '\0')
	{
		HSPI_SendChar(pchar_a_string[u8_l_StringIterator]);
		u8_l_StringIterator++;
	}
}

/**
 * \brief Send an array of data
 * 
 * \param pu8_a_data: reference to array of data to send
 * \param u8_a_DataSize: Size of data to send
 * 
 * \return en_HSPI_ErrorState_t
 */
en_HSPI_ErrorState_t HSPI_SendData(Uchar8_t* pu8_a_data, Uchar8_t u8_a_DataSize)
{
	Uchar8_t u8_l_DataIterator = 0, u8_l_dummyVar;
	
	if(pu8_a_data != NULL)
	{
		/* Select Slave */
		DIO_s8SETPinVal(HSPI_SS, LOW);
		
		while(u8_l_DataIterator < u8_a_DataSize)
		{
			SPI_TranscieveChar(pu8_a_data[u8_l_DataIterator], &u8_l_dummyVar);
			u8_l_DataIterator ++;
		}
		
		/* Deselect Slave */
		DIO_s8SETPinVal(HSPI_SS, HIGH);
	}
	else
	{
		return HSPI_NOK;
	}
	
	return HSPI_OK;
}

/**
 * \brief Function to Receive a single character
 * 
 * \param pu8_a_character pointer to variable to store
 *						  received character
 * \return en_HSPI_ErrorState_t
 */
en_HSPI_ErrorState_t HSPI_ReceiveChar(Uchar8_t* pu8_a_character)
{
	Uchar8_t u8_l_dummyVar;
	
	if(pu8_a_character != NULL)
	{
		/* Select Slave */
		DIO_s8SETPinVal(HSPI_SS, LOW);
		
		/* Initiate communication with dummy bit for synchronization */
		SPI_TranscieveChar(DATA_END, &u8_l_dummyVar);
			
		/* Exchange char from slave with dummy char ('#') */
		SPI_TranscieveChar(DATA_END, pu8_a_character);
		
		/* Deselect Slave */
		DIO_s8SETPinVal(HSPI_SS, HIGH);
		
	}
	else
	{
		return HSPI_NOK;
	}
	
	return HSPI_OK;	
}

/**
 * \brief Receive an array of data
 * 
 * \param pu8_a_data: reference to buffer to store received data
 * \param u8_a_DataSize: size of storage buffer
 * 
 * \return en_HSPI_ErrorState_t
 */
void HSPI_ReceiveData(Uchar8_t *pu8_a_data, Uchar8_t u8_a_DataSize)
{
	Uchar8_t u8_l_DataIterator = 0, u8_l_dummyVar;

	/* Select Slave */
	DIO_s8SETPinVal(HSPI_SS, LOW);	

	/* Initiate communication with dummy bit for synchronization */
	SPI_TranscieveChar(DATA_END, &u8_l_dummyVar);
	
	do
	{
		SPI_TranscieveChar(DATA_END, &pu8_a_data[u8_l_DataIterator]);
						
	}while((pu8_a_data[u8_l_DataIterator++]!=DATA_END) && (u8_l_DataIterator < u8_a_DataSize));
	
	/* Deselect Slave */
	DIO_s8SETPinVal(HSPI_SS, HIGH);
}


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
en_HSPI_ErrorState_t HSPI_ExchangeData(Uchar8_t* pu8_a_TxDataArr, Uchar8_t* pu8_a_RxDataArr, Uchar8_t u8_a_DataLen)
{
	Uchar8_t u8_l_DataIterator = 0;
	
	if((pu8_a_TxDataArr != NULL) && (pu8_a_RxDataArr != NULL) && (u8_a_DataLen <= SPI_BUFFER_SIZE))
	{
		/* Select Slave */
		DIO_s8SETPinVal(HSPI_SS, LOW);
			
		while(u8_l_DataIterator < u8_a_DataLen)
		{
			SPI_TranscieveChar(pu8_a_TxDataArr[u8_l_DataIterator], &pu8_a_RxDataArr[u8_l_DataIterator]);
			u8_l_DataIterator ++;
		}
		
		/* Deselect Slave */
		DIO_s8SETPinVal(HSPI_SS, HIGH);
	}
	else
	{
		return HSPI_NOK;
	}
	
	return HSPI_OK;
}

/**
 * \brief Request to send data to the master
 * 
 * \param u8_a_data: data to send
 * 
 * \return void
 */
void HSPI_SlaveRequest(Uchar8_t* pu8_a_dataPtr, Uchar8_t u8_a_DataSize)
{
	/* Reset transmission data index */
	u8_g_SlaveTxIndex = 0;
	
	/* Set global transmission data ptr to point to given data */
	pu8_g_SlaveTxPtr = pu8_a_dataPtr;
	
	u8_g_SlaveTxLen = u8_a_DataSize;
	
	/* Set the Data register with value */
	//SPI_SetValue(pu8_g_SlaveTxPtr[u8_g_SlaveTxIndex++]);

	/* Send Request to Master */
	DIO_s8TOGPinVal(SLAVE_SEND_REQUEST_PIN);
}