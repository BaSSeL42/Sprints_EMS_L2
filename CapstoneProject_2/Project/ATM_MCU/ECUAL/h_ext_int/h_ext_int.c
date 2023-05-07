/*
 * h_ext_int.c
 *
 * Created: 4/13/2023 3:17:38 PM
 *  Author: sharpel
 */ 
#include "h_ext_int.h"


/*
Description : This function initializes the external interrupt number and it's detecting type and initialize call back function.
ARGS        : takes the EXINT_NUMBER( INT0,INT1 OR INT2) and sense control and and pointer to the function we want to execute when interrupt occurs.
return      : return EXTINT_OK if the EXINT_NUMBER initializes correctly, EXTINT_NOT_OK otherwise
*/

EN_EXTINT_ERROR H_EXTINT_create(EN_EXINT_NUMBER INTx ,EN_Sence_Control INTxSense,void(*ptrfunc)(void))
{
	if(!EXTINT_init(INTx,INTxSense) && !EXTINT_CallBack(INTx,ptrfunc)) return EXTINT_OK;
	return EXTINT_NOT_OK;
	
}