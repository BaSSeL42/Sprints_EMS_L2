/*
 * ADC_interface.h
 *
 *  Created on: 17 Apr 2023
 *      Author: 20101
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

//#include "../../MCAL/MCU_CFG/MCU_Interface.h"
#include "../../Common/STD_Types.h"
#include "../../Common/BIT_Math.h"
#include "ADC_private.h"
#include "ADC_config.h"



Std_ReturnType ADC_Init(const ST_ADC_CFG_t *_adc);
Std_ReturnType ADC_Deinit(const ST_ADC_CFG_t *_adc);
Std_ReturnType ADC_SetChannel(const ST_ADC_CFG_t *_adc , EN_ADC_CHANNEL_SELECTION_t _channel);
Std_ReturnType ADC_StartConversion(const ST_ADC_CFG_t *_adc);
Std_ReturnType ADC_IsConversionDone(const ST_ADC_CFG_t *_adc);
Std_ReturnType ADC_GetConversionResult(const ST_ADC_CFG_t *_adc , Uint16_t *_ConversionResult);
Std_ReturnType ADC_Conversion(const ST_ADC_CFG_t *_adc , Uint16_t *_ConversionResult , EN_ADC_CHANNEL_SELECTION_t _channel);





#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
