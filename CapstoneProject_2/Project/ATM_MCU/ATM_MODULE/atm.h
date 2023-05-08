/*
 * atm.h
 *
 * Created: 02/05/2023 19:03:44
 *  Author: 20101
 */ 


#ifndef ATM_H_
#define ATM_H_

/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include <string.h>
#include "../Common/STD_Types.h"
#include "../ECUAL/buzzer/buzzer.h"
#include "../ECUAL/keypad/keypad.h"
#include "../ECUAL/lcd/lcd_interface.h"
#include "../ECUAL/hspi/hspi_interface.h"
#include "../ECUAL/h_ext_int/h_ext_int.h"
#include "../ECUAL/htimer0/htimer0.h"
#include "../ECUAL/Button/button.h"
#include "../ECUAL/icu/sw_icu.h"

/*************************************************************************************************************
* 													Macros
************************************************************************************************************/
#define		ATM_REQUEST_PIN			'P'
#define		ATM_REQUEST_PAN			'G'
#define		ATM_REQUEST_EJECTED		'E'
#define     LCD_LINE_ZERO            0
#define     LCD_LINE_ONE             1
#define     LCD_COL_ZERO             0
#define     PIN_LENGTH               5
#define		MAX_PAN_LENGTH			 20
#define     AMOUNT_LENGTH            6
#define     ZERO_CHAR               '0'

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef enum
{
	PIN_MATCHED,
	PIN_NOT_MATCHED,
	NULL_POINTER,
	PIN_OK,
	PIN_NOT_OK
}EN_PinState;

typedef enum
{
	ZERO = 0,
	ENTER,
	NOTHING

}en_buttonStatus;

typedef enum
{
	DATA_OK,
	NULL_DATA_PTR,
	DATA_NOT_RECEIVED
}en_CardDataErrorState_t;

/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/

/**
 * \brief Displays welcome routine
 * 
 * \return void
 */
void Welcome(void);

/**
 * (Author: Sherif Ashraf)
 * \brief Check if the pin user enters is the same as the cardholder's pin
 * \param pinFromAtm   : reference to pin entered by user
 * \param pinFromServer: reference to pin received from card
 * \return EN_PinState
 */
EN_PinState PIN_checkPinMatching(Uchar8_t *pinFromAtm,Uchar8_t *pinFromServer);

/*
* AUTHOR			: Sharpel
* FUNCTION			: Get_pin
* DESCRIPTION		: get pin from user (on the atm )
* ARGS		        : pointer to array (the size of array must be 5 or more) to store entered pin by user
* RETURN			: PIN_OK if user enters 4 numbers , PIN_NOT_OK otherwise
*/
EN_PinState Get_pin(Uchar8_t *enteredpin);

/**
 * (Author: Sherif Ashraf)
 * \brief Locks the system and sound the buzzer
 * \param pst_a_buzzer: reference to the buzzer
 * \return en_BuzzerErrorState_t
 */
en_BuzzerErrorState_t deinitAtm(st_Buzzer_t* pst_a_buzzer);

/**
 * (Author: Alaa Hisham)
 * \brief Get the card pan and pin
 * \param pu8_a_pan: reference to buffer to receive pan from card
 * \param pu8_a_pin: reference to buffer to receive pin from card
 * \return en_CardDataErrorState_t
 */
en_CardDataErrorState_t ATM_GetCardData(Uchar8_t *pu8_a_pan, Uchar8_t *pu8_a_pin);

/*
* AUTHOR			: Sharpel
* FUNCTION			: get_amount_left
* DESCRIPTION		: get amount from user ( on the atm )
* ARGS		        : pointer to array (the size of array must be 8 or more and equal "0000.00" initial value) to store entered pin by user
* RETURN			: void
*/
void get_amount_left (Uchar8_t * amount);



/*
* AUTHOR			: Bassel Yasser
* FUNCTION			: EXTINT_FUNC
* DESCRIPTION		: when timer 2 ISR is fire it changes the state of (Enter or Zero)
* ARGS		        : void
* RETURN			: void
*/
void EXTINT_FUNC(void);


/**
 * (Author: Alaa Hisham)
 * \brief Carries out the routine for approved card
 * \param f32_a_NewBalance: the balance to display after transaction 
 * \return void
 */
void ATM_ApprovedCard(float32_t f32_a_NewBalance);



#endif /* ATM_H_ */