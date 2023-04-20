/*
 * ADC_config.h
 *
 *  Created on: 17 Apr 2023
 *      Author: 20101
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_


typedef enum
{
	AREF_INTERNAL = 0,
	AVCC_EXTERNAL_CAPACITOR,
	RESERVED,
	INTERNAL_VOLTAGE_EXTERNAL_CAPACITOR
}EN_ADC_REFERENCE_SELECTION_BITS_t;

typedef enum
{
	ADC_RIGHT_ADJUST_RESULT = 0,
	ADC_LEFT_ADJUST_RESULT
}EN_ADC_ADJUST_RESULT_t;


typedef enum
{
	ADC_CHANNEL_ZERO = 0,
	ADC_CHANNEL_ONE,
	ADC_CHANNEL_TWO,
	ADC_CHANNEL_THREE,
	ADC_CHANNEL_FOUR,
	ADC_CHANNEL_FIVE,
	ADC_CHANNEL_SIX,
	ADC_CHANNEL_SEVEN
}EN_ADC_CHANNEL_SELECTION_t;


typedef enum
{
	ADC_DIV2 = 0,
	ADC_DIV4,
	ADC_DIV8,
	ADC_DIV16,
	ADC_DIV32,
	ADC_DIV64,
	ADC_DIV128
}EN_ADC_PRESCALER_SELECTION_t;


typedef enum
{
	ADC_INTERRUPT = 0,
	ADC_FLAG_POLLING,
}EN_ADC_EVENT_TRIGGER_SOUREC_t;

typedef struct
{
	void(*interruptHandler)(void);
	EN_ADC_REFERENCE_SELECTION_BITS_t referenceSource;
	EN_ADC_ADJUST_RESULT_t resultAdjust;
	EN_ADC_PRESCALER_SELECTION_t prescalerDivision;
	EN_ADC_EVENT_TRIGGER_SOUREC_t triggerSource;
}ST_ADC_CFG_t;

/*====================================================*/

//#define EXT_INT0 __vector_1
//#define EXT_INT1 __vector_2
//#define EXT_INT2 __vector_3


#define ISR(INT_VECT)void INT_VECT(void) __attribute__ ((signal,used));\
void INT_VECT(void)

/*====================================================*/
#define AREF_INTERNAL()		CLEAR_BIT(ADMUX_REG,ADMUX_REG_REFS0_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_REFS1_BIT)


#define AVCC_EXTERNAL_CAPACITOR()		SET_BIT(ADMUX_REG,ADMUX_REG_REFS0_BIT);\
										CLEAR_BIT(ADMUX_REG,ADMUX_REG_REFS1_BIT)


#define INTERNAL_VOLTAGE_EXTERNAL_CAPACITOR()		SET_BIT(ADMUX_REG,ADMUX_REG_REFS0_BIT);\
													SET_BIT(ADMUX_REG,ADMUX_REG_REFS1_BIT)

#define LEFT_ADJUST_RESULT()		SET_BIT(ADMUX_REG,ADMUX_REG_ADLAR_BIT)

#define RIGHT_ADJUST_RESULT()		CLEAR_BIT(ADMUX_REG,ADMUX_REG_ADLAR_BIT)


#define ADC_CHANNEL_ZERO()  CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)

#define ADC_CHANNEL_ONE()   SET_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)

#define ADC_CHANNEL_TWO()  	CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
							SET_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)

#define ADC_CHANNEL_THREE()  	SET_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
								SET_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
								CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
								CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)


#define ADC_CHANNEL_FOUR()  CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
							SET_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)

#define ADC_CHANNEL_FIVE()  SET_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
							SET_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)

#define ADC_CHANNEL_SIX()  	CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
							SET_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
							SET_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)

#define ADC_CHANNEL_SEVEN() SET_BIT(ADMUX_REG,ADMUX_REG_MUX0_BIT);\
							SET_BIT(ADMUX_REG,ADMUX_REG_MUX1_BIT);\
							SET_BIT(ADMUX_REG,ADMUX_REG_MUX2_BIT);\
							CLEAR_BIT(ADMUX_REG,ADMUX_REG_MUX3_BIT)

#define ADC_ENABLE()	SET_BIT(ADCSRA_REG,ADCSRA_REG_ADEN_BIT)

#define ADC_DISABLE()	CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADEN_BIT)

#define ADC_START_CONVERSION() SET_BIT(ADCSRA_REG,ADCSRA_REG_ADSC_BIT)

#define ADC_INTERRUPT_ENABLE()	SET_BIT(ADCSRA_REG,ADCSRA_REG_ADIE_BIT)

#define ADC_INTERRUPT_DISABLE()	CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADIE_BIT)


#define ADC_PRESCALER_DIV2()	SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS0_BIT);\
								CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS1_BIT);\
								CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS2_BIT)

#define ADC_PRESCALER_DIV4()	CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS0_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS1_BIT);\
								CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS2_BIT)

#define ADC_PRESCALER_DIV8()	SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS0_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS1_BIT);\
								CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS2_BIT)


#define ADC_PRESCALER_DIV16()	CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS0_BIT);\
								CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS1_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS2_BIT)

#define ADC_PRESCALER_DIV32()	SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS0_BIT);\
								CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS1_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS2_BIT)

#define ADC_PRESCALER_DIV64()	CLEAR_BIT(ADCSRA_REG,ADCSRA_REG_ADPS0_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS1_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS2_BIT)

#define ADC_PRESCALER_DIV128()	SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS0_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS1_BIT);\
								SET_BIT(ADCSRA_REG,ADCSRA_REG_ADPS2_BIT)





#endif /* MCAL_ADC_ADC_CONFIG_H_ */