/*
 * adc_program.c
 *
 * Created: 4/17/2023 6:33:08 AM
 *  Author: ME
 */ 
/*************************************************************************************************************
 * 													Includes
 ************************************************************************************************************/

#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"
#include "../../Common/vect_table.h"

#include "adc_private.h"
#include "adc_interface.h"

/*************************************************************************************************************
 * 												Global Variables
 ************************************************************************************************************/
ST_ADC_CFG_t st_g_ADC_Config = {NULL, AVCC_EXTERNAL_CAPACITOR, ADC_RIGHT_ADJUST_RESULT, ADC_DIV64, ADC_FLAG_POLLING};
	

//void (*ADC_CallbakcFn)(void) = NULL;
/*************************************************************************************************************
 * 											Function Implementation
 ************************************************************************************************************/
Std_ReturnType ADC_Init(const ST_ADC_CFG_t *_adc)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL == _adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ADC_DISABLE();

		switch(_adc->referenceSource)
		{
			case AREF_INTERNAL : AREF_INTERNAL(); break;
			case AVCC_EXTERNAL_CAPACITOR : AVCC_EXTERNAL_CAPACITOR(); break;
			case INTERNAL_VOLTAGE_EXTERNAL_CAPACITOR : INTERNAL_VOLTAGE_EXTERNAL_CAPACITOR(); break;
			case RESERVED:/*nothing*/break;
		}

		switch(_adc->prescalerDivision)
		{
			case ADC_DIV2 : ADC_PRESCALER_DIV2(); break;
			case ADC_DIV4 : ADC_PRESCALER_DIV4(); break;
			case ADC_DIV8 : ADC_PRESCALER_DIV8(); break;
			case ADC_DIV16 : ADC_PRESCALER_DIV16(); break;
			case ADC_DIV32 : ADC_PRESCALER_DIV32(); break;
			case ADC_DIV64 : ADC_PRESCALER_DIV64(); break;
			case ADC_DIV128 : ADC_PRESCALER_DIV128(); break;
		}

		switch(_adc->resultAdjust)
		{
			case ADC_RIGHT_ADJUST_RESULT : RIGHT_ADJUST_RESULT(); break;
			case ADC_LEFT_ADJUST_RESULT : LEFT_ADJUST_RESULT(); break;
		}

		switch(_adc->triggerSource)
		{
			case ADC_INTERRUPT: ADC_INTERRUPT_ENABLE();// MCU_vEnableInterrupt(); 
			break;
			case ADC_FLAG_POLLING: ADC_INTERRUPT_DISABLE();break;
		}
		ADC_ENABLE();

		ret = E_OK;
	}

	return ret;
}
Std_ReturnType ADC_Deinit(const ST_ADC_CFG_t *_adc)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL == _adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		ADC_DISABLE();
		ADC_INTERRUPT_DISABLE();
		ret = E_OK;
	}

	return ret;
}
Std_ReturnType ADC_SetChannel(const ST_ADC_CFG_t *_adc , EN_ADC_CHANNEL_SELECTION_t _channel)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL == _adc)
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(_channel)
		{
			case ADC_CHANNEL_ZERO: ADC_CHANNEL_ZERO(); break;
			case ADC_CHANNEL_ONE: ADC_CHANNEL_ONE(); break;
			case ADC_CHANNEL_TWO: ADC_CHANNEL_TWO(); break;
			case ADC_CHANNEL_THREE: ADC_CHANNEL_THREE(); break;
			case ADC_CHANNEL_FOUR: ADC_CHANNEL_FOUR(); break;
			case ADC_CHANNEL_FIVE: ADC_CHANNEL_FIVE(); break;
			case ADC_CHANNEL_SIX: ADC_CHANNEL_SIX(); break;
			case ADC_CHANNEL_SEVEN: ADC_CHANNEL_SEVEN(); break;
		}
		ret = E_OK;
	}

	return ret;
}
Std_ReturnType ADC_StartConversion(const ST_ADC_CFG_t *_adc)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL == _adc)
	{
		ret = E_NOT_OK;
	}
	else
	{

		ADC_START_CONVERSION();
		ret = E_OK;
	}

	return ret;
}
Std_ReturnType ADC_GetConversionResult(const ST_ADC_CFG_t *_adc , Uint16_t *_ConversionResult)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL == _adc || NULL == _ConversionResult)
	{
		ret = E_NOT_OK;
	}
	else
	{
		
		while(GET_BIT(ADCSRA_REG,ADCSRA_REG_ADIF_BIT) == 0);

		CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADIF_BIT);

		switch(_adc->resultAdjust)
		{
			case ADC_RIGHT_ADJUST_RESULT : *_ConversionResult = ADCL_REG + (ADCH_REG << 8); break;
			case ADC_LEFT_ADJUST_RESULT :  *_ConversionResult = (Uint16_t)((ADCL_REG + (ADCH_REG << 8))>>6); break;
		}


		ret = E_OK;
	}

	return ret;
}
Std_ReturnType ADC_Conversion(const ST_ADC_CFG_t *_adc , Uint16_t *_ConversionResult , EN_ADC_CHANNEL_SELECTION_t _channel)
{
	Std_ReturnType ret = E_NOT_OK;

	if(NULL == _adc || NULL == _ConversionResult)
	{
		ret = E_NOT_OK;
	}
	else
	{

		ADC_Init(_adc);
		ADC_SetChannel(_adc,_channel);
		ADC_StartConversion(_adc);
		ADC_GetConversionResult(_adc,_ConversionResult);

		ret = E_OK;
	}

	return ret;
}

//Std_ReturnType ADC_AsyncConversion(const ST_ADC_CFG_t *_adc , Uint16_t *_ConversionResult , EN_ADC_CHANNEL_SELECTION_t _channel, void (*Callback)(void))
//{
	//Std_ReturnType ret = E_NOT_OK;
//
	//if(NULL == _adc || NULL == _ConversionResult)
	//{
		//ret = E_NOT_OK;
	//}
	//else
	//{
		////ADC_CallbakcFn = Callback; 
		//ADC_Init(_adc);
		//ADC_SetChannel(_adc,_channel);
		//ADC_StartConversion(_adc);
//
		//ret = E_OK;
	//}
//
	//return ret;
//}
//
//ISR(ADC_INT)
//{
	//ADC_GetConversionResult(_adc,_ConversionResult);
	//ADC_CallbakcFn();
//}