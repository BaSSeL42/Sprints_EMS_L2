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
#include "../../Common/vect_table.h"

#include <util/delay.h>

#include "spi_register.h"
#include "spi_private.h"
#include "spi_config.h"
#include "spi_interface.h"

/*************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/
Uchar8_t u8_g_SlaveReceive;
Uchar8_t u8_g_SlaveTxIndex=0, u8_g_SlaveRxIndex=0;
/* Variables to store number of bytes received & to send */
Uchar8_t u8_g_SlaveRxLen, u8_g_SlaveTxLen;

Uchar8_t *pu8_g_SlaveTxPtr = NULL;
Uchar8_t arr_g_SlaveRxBuffer[SPI_BUFFER_SIZE] = {NULL};

void (*SPI_CallbackFn)(void) = NULL;

/*************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/
/**
 * \brief Initialize the MCU as the Master
 *		  in SPI communication
 *
 * \return void
 */
void SPI_MasterInit(void)
{
	/* Set MCU as Master */
	SET_BIT(SPCR, SPCR_MSTR);
		
	/* Configure Prescaler bits in SPCR and SPI2X bit in SPSR */
	SPCSR &= SPI_CLK_MASK;
	SPCSR |= SPI_CLK_SELECT;
	
	SPCR &= ~(1 << SPCR_CPOL);
	SPCR &= ~(1 << SPCR_CPHA);
			
	/* Enable SPI */
	SET_BIT(SPCR, SPCR_SPE);
}


/**
 * \brief Initialize the MCU as a slave
 *		  in SPI communication				
 * 
 * \return void
 */
void SPI_SlaveInit(void)
{
	/* Set MCU as Slave */
	CLEAR_BIT(SPCR, SPCR_MSTR);
	
    // Set SPI mode to mode 0 (phase 0, polarity 0)
    SPCR &= ~(1 << SPCR_CPOL);
    SPCR &= ~(1 << SPCR_CPHA);
	
	/* Enable SPI Interrupt */
	SET_BIT(SPCR, SPCR_SPIE);
	
	/* Enable SPI */
	SET_BIT(SPCR, SPCR_SPE);
}

/**
 * \brief Sets the value of the SPI data register
 * 
 * \param u8_a_data: Desired value
 * 
 * \return void
 */
void SPI_SetValue(Uchar8_t u8_a_data)
{
	SPDR = u8_a_data;
	//_delay_ms(1);
}

/**
 * \brief Exchange a letter with selected slave
 * 
 * \param u8_a_character Character to send
 * \param pu8_a_receivedChar Pointer to character to store received value
 * 
 * \return en_SPI_ErrorState_t
 */
en_SPI_ErrorState_t SPI_TranscieveChar(Uchar8_t u8_a_character, Uchar8_t* pu8_a_receivedChar)
{
	Uint32_t u32_l_timeCount = 0;
	
	if(pu8_a_receivedChar != NULL)
	{		
		SPDR = u8_a_character;

		/* Wait until Interrupt flag is raised */
		while((GET_BIT(SPSR, SPSR_SPIF) == 0) && (u32_l_timeCount < SPI_TIMEOUT))
		{
			u32_l_timeCount ++;
		}
		
		if(SPI_TIMEOUT == u32_l_timeCount) {return SPI_NOK;}
		
		/* Store the received value */
		*pu8_a_receivedChar = SPDR;
		
		/* Todo: Optimize Slave ISR to remove delay */
		/* Delay for slave to finish processing data */
		_delay_us(100);
	}
	else
	{
		return SPI_NOK;
	}
	
	return SPI_OK;
}

/**
 * \brief Set a notification function for the SPI Interrupt 
 * 
 * \param pv_a_CallbackFn reference to the function to callback
 *						  when the SPI Interrupt is triggered
 * \return en_SPI_ErrorState_t
 */
en_SPI_ErrorState_t SPI_SetCallback(void (*pv_a_CallbackFn)(void))
{
	if(pv_a_CallbackFn != NULL)
	{
		SPI_CallbackFn = pv_a_CallbackFn;
	}
	else
	{
		return SPI_NOK;
	}
	
	return SPI_OK;
}

/*************************************************************************************************************
 * 													  ISRs
 ************************************************************************************************************/
ISR(SPI_STC_INT)
{
	/*------------------------ Reception ------------------------*/
	u8_g_SlaveReceive = SPDR;
	//DIO_s8SETPortVal(DIO_PORTA, u8_g_SlaveReceive);
	
	/* If Max size is exceeded, start overriding data */
	if(u8_g_SlaveRxIndex == SPI_BUFFER_SIZE) u8_g_SlaveRxIndex = 0;
	if(u8_g_SlaveReceive != DATA_END)
	{
		/* Store received byte in buffer */
		arr_g_SlaveRxBuffer[u8_g_SlaveRxIndex] = u8_g_SlaveReceive;
		u8_g_SlaveRxIndex++;
	}
	else
	{	// Get the number of received bytes
		u8_g_SlaveRxLen = u8_g_SlaveRxIndex;
	}
	
	/*------------------------- Sending -------------------------*/
	//u8_g_SlaveTxIndex++;
	if((u8_g_SlaveTxIndex < u8_g_SlaveTxLen) && (pu8_g_SlaveTxPtr != NULL))
	{
		SPDR = pu8_g_SlaveTxPtr[u8_g_SlaveTxIndex++];
	}
	else if(u8_g_SlaveTxIndex >= u8_g_SlaveTxLen)
	{
		SPDR = DATA_END;
	}
}