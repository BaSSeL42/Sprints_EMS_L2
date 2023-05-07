/*
 * h_ext_int.h
 *
 * Created: 4/13/2023 3:17:27 PM
 *  Author: sharb
 */ 


#ifndef H_EXT_INT_H_
#define H_EXT_INT_H_

#include "../../MCAL/extint/extinterrupt.h"

/*
Description : This function initializes the external interrupt number and it's detecting type and initialize call back function.
ARGS        : takes the EXINT_NUMBER( INT0,INT1 OR INT2) and sense control and and pointer to the function we want to execute when interrupt occurs.
return      : return EXTINT_OK if the EXINT_NUMBER initializes correctly, EXTINT_NOT_OK otherwise
*/
EN_EXTINT_ERROR H_EXTINT_create(EN_EXINT_NUMBER INTx ,EN_Sence_Control INTxSense,void(*ptrfunc)(void));



#endif /* H_EXT_INT_H_ */