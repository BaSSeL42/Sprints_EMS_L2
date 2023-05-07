/*
 * Ext_Interrupt.h
 *
 * Created: 4/7/2023 11:19:13 PM
 *  Author: sharpel
 */ 


#ifndef EXT_INTERRUPT_H_
#define EXT_INTERRUPT_H_

#include "../../Common/vect_table.h"
#include "../../Common/BIT_Math.h"
#include "../../Common/STD_Types.h"
#include "ext_config.h"


// EXT_INT TYPEDEFS
typedef enum EN_EXTINT_ERROR {
	EXTINT_OK=0,
	EXTINT_NOT_OK
}EN_EXTINT_ERROR;

typedef enum EN_Sence_Control {
	LOW_LEVEL=0,
	FALLING_EDGE,
	RISING_EDGE,
	ANY_LOGICAL_CHANGE
}EN_Sence_Control;

typedef enum EN_EXINT_NUMBER{
	EXTINT0=0,
	EXTINT1,
	EXTINT2,
}EN_EXINT_NUMBER;

typedef enum EN_GLOBAL_INT{
	DISABLE=0,
	ENABLE
}EN_GLOBAL_INT;

// EXT_INT prototypes

/*
Description : This function initializes the GLOBAL_INTERRUPT
ARGS        : takes the state ( ENABLE OR DISABLE )
return      : return EXTINT_OK if the PIN initializes correctly, EXTINT_NOT_OK otherwise
*/
EN_EXTINT_ERROR SET_GLOBAL_INTERRUPT(EN_GLOBAL_INT state);


/*
Description : This function initializes the external interrupt number and it's detecting type
ARGS        : takes the EXINT_NUMBER( INT0,INT1 OR INT2) and sense control.
return      : return EXTINT_OK if the EXINT_NUMBER initializes correctly, EXTINT_NOT_OK otherwise
*/
EN_EXTINT_ERROR EXTINT_init(EN_EXINT_NUMBER INTx ,EN_Sence_Control INTxSense);

/*
Description : This function takes the external interrupt number and initialize call back function.
ARGS        : takes the EXINT_NUMBER( INT0,INT1 OR INT2) and pointer to the function we want to execute.
return      : return EXTINT_OK if the EXINT_NUMBER initializes correctly, EXTINT_NOT_OK otherwise
*/
EN_EXTINT_ERROR EXTINT_CallBack(EN_EXINT_NUMBER INTx,void(*ptrfunc)(void));

#endif /* EXT_INTERRUPT_H_ */