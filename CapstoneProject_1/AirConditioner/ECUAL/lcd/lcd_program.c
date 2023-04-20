/*
 * AUTHOR		: Bassel Yasser
 * FILE			: HLCD_Source.c
 * DATE			: Apr 16, 2023
 * DESCRIPTION	: Function Implementation
 * 					- void HLCD_vidInit(void)
 * 					- void HLCD_vidWritecmd(Uchar8_t u8commandCopy)
 * 					- void HLCD_vidWriteChar(Uchar8_t u8CharCopy)
 * 					- void HLCD_ClrDisplay(void)
 * 					- void HLCD_ShiftLeft(void)
 * 					- void HLCD_gotoXY(Uchar8_t row, Uchar8_t pos)
 * 					- void HLCD_WriteString(Uchar8_t* str)
 * 					- void HLCD_WriteInt(Uint32_t number)
 * 					- void HLCD_WriteArabic(Uchar8_t u8ArCharCopy)
 * 					- void HLCD_vidCreatCustomChar(Uchar8_t* pu8custom, Uchar8_t u8Location)
 */

/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include <util/delay.h>
#include <stdlib.h>
#include "../../Common/STD_Types.h"
#include "../../Common/Bit_Math.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "lcd_interface.h"
#include "lcd_config.h"

/**************************************************************************************************
 * 										Macros
 *************************************************************************************************/



#define INDEX		10
/**************************************************************************************************
 * 										Global Variables
 *************************************************************************************************/
#if HLCD_MODE == HLCD_4_BIT_MODE

extern st_lcdDataPin_t dataPin[4];

#elif HLCD_MODE == HLCD_8_BIT_MODE

extern st_lcdDataPin_t dataPin[8];


#endif


/**************************************************************************************************
 * 						functions implementation
 *************************************************************************************************/
/*
 * function		: HLCD_vidInit
 * description 	: func to set LCD initialization
 * input param 	: void
 * return		: void
 * */
void HLCD_vidInit(void)
{
	for (Uchar8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_s8SETPinDir(dataPin[i].en_dataPin,OUTPUT);
	}

	DIO_s8SETPinDir(LCD_RS_PORT_PIN,OUTPUT);
	DIO_s8SETPinDir(LCD_RW_PORT_PIN,OUTPUT);
	DIO_s8SETPinDir(LCD_EN_PORT_PIN,OUTPUT);

	_delay_ms(40);

	HLCD_vidWritecmd(HLCD_CURSOR_HOME);
	_delay_ms(1);
#if HLCD_MODE == HLCD_4_BIT_MODE

	HLCD_vidWritecmd(HLCD_4_BIT_MODE_SELECTION);
	_delay_ms(1);

#elif HLCD_MODE == HLCD_8_BIT_MODE
	HLCD_vidWritecmd(HLCD_8_BIT_MODE_SELECTION);
	_delay_ms(1);
#endif
	HLCD_vidWritecmd(HLCD_CLEAR_DISPLAY);
	_delay_ms(4);

	HLCD_vidWritecmd(HLCD_ENTRY_MODE_CURSOR_INCREMENT);
	_delay_ms(1);

	HLCD_vidWritecmd(HLCD_DISPLAY_ON_CURSOR_ON_NO_BLINK);
	_delay_ms(1);
}



/*
 * function		: HLCD_vidWritecmd
 * description 	: func to configure some commands on lcd
 * input param 	:
 * 					u8commandCopy --> take lcd cmd instructions from instruction table <https://components101.com/sites/default/files/component_datasheet/16x2%20LCD%20Datasheet.pdf>
 * return		: void
 * */
void HLCD_vidWritecmd(Uchar8_t u8commandCopy)
{
	DIO_s8SETPinVal(LCD_RW_PORT_PIN, LOW); // WRITE
	DIO_s8SETPinVal(LCD_RS_PORT_PIN, LOW); // CMD

#if HLCD_MODE == HLCD_4_BIT_MODE

	Uchar8_t loc_u8DataReg = 0;
	loc_u8DataReg = (u8commandCopy & 0xF0);
	loc_u8DataReg >>= 4;

	for (Uchar8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_s8SETPinVal(dataPin[i].en_dataPin, ((loc_u8DataReg >> i)&1) );
	}

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(1);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low

	_delay_us(200);

	loc_u8DataReg = (u8commandCopy & 0x0F);

	for (Uchar8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_s8SETPinVal(dataPin[i].en_dataPin, ((loc_u8DataReg >> i)&1) );
	}

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(1);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low
	_delay_ms(2);


#elif HLCD_MODE == HLCD_8_BIT_MODE
	for (Uchar8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_s8SETPinVal(dataPin[i].en_dataPin, ((u8commandCopy >> i)&1) );
	}

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(2);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low
	_delay_ms(2);
#endif


}



/*
 * function		: HLCD_vidWriteChar
 * description 	: func to write char on lcd
 * input param 	: u8CharCopy -> take ascii code of char   or   char address on CGROM
 * return		: void
 * */
void HLCD_vidWriteChar(Uchar8_t u8CharCopy)
{
	DIO_s8SETPinVal(LCD_RW_PORT_PIN, LOW); // WRITE
	DIO_s8SETPinVal(LCD_RS_PORT_PIN, HIGH); // DATA

#if HLCD_MODE == HLCD_4_BIT_MODE

	Uchar8_t loc_u8DataReg = 0;
	loc_u8DataReg = (u8CharCopy & 0xF0);
	loc_u8DataReg >>= 4;

	for (Uchar8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_s8SETPinVal(dataPin[i].en_dataPin, ((loc_u8DataReg >> i)&1) );
	}

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(1);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low

	_delay_us(200);

	loc_u8DataReg = (u8CharCopy & 0x0F);

	for (Uchar8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_s8SETPinVal(dataPin[i].en_dataPin, ((loc_u8DataReg >> i)&1) );
	}

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(1);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low
	_delay_ms(2);


#elif HLCD_MODE == HLCD_8_BIT_MODE
	for (Uchar8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		DIO_s8SETPinVal(dataPin[i].en_dataPin, ((u8CharCopy >> i)&1) );
	}

	DIO_s8SETPinVal(LCD_EN_PORT_PIN, HIGH); //ENABLE high
	_delay_ms(2);
	DIO_s8SETPinVal(LCD_EN_PORT_PIN, LOW); //ENABLE low
#endif

}


/*
 * function		: HLCD_ClrDisplay
 * description 	: func to clear anything on lcd
 * input param 	: void
 * return		: void
 * */
void HLCD_ClrDisplay(void)
{
	HLCD_vidWritecmd(HLCD_CLEAR_DISPLAY);
	_delay_ms(4);
	HLCD_vidWritecmd(HLCD_CURSOR_HOME);
	_delay_ms(4);

}



/*
 * function		: HLCD_ShiftLeft
 * description 	: func to shift the lcd display from right to left
 * input param 	: void
 * return		: void
 * */
void HLCD_ShiftLeft(void)
{
	HLCD_vidWritecmd(HLCD_DISPLAY_SHIFT_LEFT);
	_delay_ms(1);

}




/*
 * function		: HLCD_gotoXY
 * description 	: func to determine position which char print at this position on lcd  ### NOTE : (2rows x 16coloms)
 * input param 	:
 * 				  row -> take row number 0 or 1
 * 				  pos -> take colom number from 0 ~ 16
 * return		: void
 * */
void HLCD_gotoXY(Uchar8_t row, Uchar8_t pos)
{
	if (row==0 && pos < 16)
	{
		HLCD_vidWritecmd((pos & 0x0F)| 0x80);
	}
	else if (row==1 && pos < 16)
	{
		HLCD_vidWritecmd((pos & 0x0F)| 0xC0);
	}
}




/*
 * function		: HLCD_WriteString
 * description 	: func to write string on lcd
 * input param 	: str --> which take string as argument
 * return		: void
 * */
void HLCD_WriteString(Uchar8_t* str)
{
	Uint16_t count = 0;
	Uchar8_t string = str[count];
	while(string)
	{
		HLCD_vidWriteChar(string);
		string = str[++count];
	}
}



/*
 * function		: HLCD_WriteInt
 * description 	: func to write integer number on lcd
 * input param 	: number --> which take number as argument
 * return		: void
 * */
void HLCD_WriteInt(Uint32_t number)
{
	Uchar8_t STR[INDEX];
	itoa(number, STR, 10);
	HLCD_WriteString(STR);
}


/*
 * function		: HLCD_WriteArabic
 * description 	: func to write Arabic string on lcd
 * input param 	: u8ArCharCopy --> which take string as argument
 * return		: void
 * */
void HLCD_WriteArabic(Uchar8_t u8ArCharCopy)
{
	HLCD_vidWritecmd(0x04);
	HLCD_vidWriteChar(u8ArCharCopy);
}



/*
 * function		: HLCD_vidCreatCustomChar
 * description 	: func to store new patterm on CGRAM
 * input param 	:
 * 				  pu8custom  -> take pointer to array which having LCD Custom Character Generated data ### take only 8 characters
 * 				  u8Location -> determine location on CGRAM [0 ~ 8]
 * return		: void
 * */
void HLCD_vidCreatCustomChar(Uchar8_t* pu8custom, Uchar8_t u8Location)
{
	if (u8Location < 8)  // CGRAM only store 8 characters
	{
		HLCD_vidWritecmd(LCD_SET_CGRAM_ADDR_CMD + (u8Location*8));
		_delay_ms(1);
		for (Uchar8_t i = 0; i < 8 ; i++)
		{
			HLCD_vidWriteChar(pu8custom[i]);
		}
	}
}

/**************************************************************************************************
 * 											END
 *************************************************************************************************/



