/*
 * temp_sensor.h
 *
 * Created: 4/17/2023 5:49:43 AM
 *  Author: ME
 */ 


#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_


/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/
//#define TEMP_SENSOR_PORT			GPIO_PORTA_INDEX
#define TEMP_SENSOR_PIN				DIO_PINA_0
#define TEMP_SENSOR_CHANNEL			ADC_CHANNEL_ZERO

/*************************************************************************************************************
 * 											User-defined data types
 ************************************************************************************************************/
typedef struct  
{
	Uchar8_t Pin;
}st_TempSensor_t;

typedef enum
{
	SENSOR_OK,
	SENSOR_NOK
}en_SensorError_t;
/*************************************************************************************************************
 * 											  Function Prototypes
 ************************************************************************************************************/
/**
 * \brief Function to initialize the sensor port/pin
 * 
 * \param pst_a_sensor reference to sensor info
 * 
 * \return void
 */
void TSENSOR_Init(st_TempSensor_t* pst_a_sensor);

en_SensorError_t TSENSOR_ReadValue(st_TempSensor_t *pst_a_Sensor, float32_t *f32_a_Value);


#endif /* TEMP_SENSOR_H_ */