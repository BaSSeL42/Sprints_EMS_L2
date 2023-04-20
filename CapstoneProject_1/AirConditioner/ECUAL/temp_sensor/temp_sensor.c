/*
* temp_sensor.c
*
* Created: 4/17/2023 5:50:07 AM
*  Author: ME
*/
/*************************************************************************************************************
* 													Includes
************************************************************************************************************/
#include "../../Common/STD_Types.h"

#include "../../MCAL/dio/dio_interface.h"
#include "../../MCAL/adc/adc_interface.h"

#include "temp_sensor.h"
/*************************************************************************************************************
* 												Global Variables
************************************************************************************************************/
st_TempSensor_t st_g_TempSensor = {TEMP_SENSOR_PIN};
float32_t f32_g_StepSize;
	
extern ST_ADC_CFG_t st_g_ADC_Config;

/*************************************************************************************************************
* 											Function Implementation
************************************************************************************************************/
/**
* \brief Function to initialize the sensor port/pin
*
* \param pst_a_sensor reference to sensor info
*
* \return void
*/
void TSENSOR_Init(st_TempSensor_t* pst_a_sensor)
{
	DIO_s8SETPinDir(pst_a_sensor->Pin, INPUT);
}


en_SensorError_t TSENSOR_ReadValue(st_TempSensor_t *pst_a_Sensor, float32_t *f32_a_Value)
{
	Uint16_t u16_l_digialValue;
	
	if(pst_a_Sensor != NULL && f32_a_Value != NULL)
	{
		ADC_Conversion(&st_g_ADC_Config, &u16_l_digialValue, TEMP_SENSOR_CHANNEL);
		
		if(st_g_ADC_Config.referenceSource == AVCC_EXTERNAL_CAPACITOR)
		{
			f32_g_StepSize = 5.0/1024;
		}
		else if(st_g_ADC_Config.referenceSource == INTERNAL_VOLTAGE_EXTERNAL_CAPACITOR)
		{
			f32_g_StepSize = 2.56/1024;
		}
		
		/* get value in degrees (V_Sensor = 10 mv/°C × T)*/
		*f32_a_Value = u16_l_digialValue *100 * f32_g_StepSize;
	}
	else
	{
		return SENSOR_NOK;
	}
	
	return SENSOR_OK;
}
