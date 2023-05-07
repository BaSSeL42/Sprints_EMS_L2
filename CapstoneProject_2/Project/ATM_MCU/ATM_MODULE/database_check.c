/*
 * database_check.c
 *
 * Created: 5/3/2023 5:02:24 PM
 *  Author: sharb
 */ 


#include "../Common/STD_Types.h"
#include "database_check.h"
#include <string.h>
#include <stdlib.h>

ST_accountsDB_t accountsDB[DB_SIZE] = 
{
   
   
   {15000.00,1,"2224122412241224"},
   {55550.00,1,"43144314431443144"},
   {2000.00,0,"1234567891234567894"},
   {45000.00,0,"4417123456789113"},
	{5000.00,1,"1111111111111111111"},	   

};

EN_dataError_t isBelowMaxDailyAmount(Uchar8_t * amount)
{
    EN_dataError_t LOCAL_returnValue = APPROVED;
    Schar8_t state = strcmp(amount,MAX_TRANS_AMOUNT);
    if( state>0) LOCAL_returnValue = EXCEED_MAX_DAILY_AMOUNT;
    return LOCAL_returnValue;
}


EN_dataError_t isValidPanAccount(Uchar8_t * pan)
{
	EN_dataError_t LOCAL_returnValue = FRAUD_CARD;
    Uchar8_t loc_Counter;
    Schar8_t state;
    for(loc_Counter = 0 ; loc_Counter<DB_SIZE;loc_Counter++)
    {
     state = strcmp(pan,accountsDB[loc_Counter].primaryAccountNumber);
     if(state == 0 )
      {
         LOCAL_returnValue = APPROVED;
         break;
      }
    }
	return LOCAL_returnValue;
}


EN_dataError_t isRunningAccount(Uchar8_t * pan)
{
	EN_dataError_t LOCAL_returnValue = CARD_STOLEN;
	Uchar8_t loc_Counter;
	Schar8_t state;
	for(loc_Counter = 0 ; loc_Counter<DB_SIZE;loc_Counter++)
	{
		state = strcmp(pan,accountsDB[loc_Counter].primaryAccountNumber);
		if(state == 0 )
		{
            if(accountsDB[loc_Counter].state == RUNNING)
			LOCAL_returnValue = APPROVED;
			break;
		}
	}
	return LOCAL_returnValue;
}

EN_dataError_t isValidAccountAmount(Uchar8_t * pan,Uchar8_t * amount,float32_t *newAmount)
{
    float32_t Conv_amount = atof(amount);
	EN_dataError_t LOCAL_returnValue = INSUFFICIENT_FUND;
	Uchar8_t loc_Counter;
	Schar8_t state;
	for(loc_Counter = 0 ; loc_Counter<DB_SIZE;loc_Counter++)
	{
		state = strcmp(pan,accountsDB[loc_Counter].primaryAccountNumber);
		if(state == 0 )
		{
			if(accountsDB[loc_Counter].balance >= Conv_amount)
            {
              accountsDB[loc_Counter].balance-=Conv_amount;
              *newAmount = accountsDB[loc_Counter].balance;
              LOCAL_returnValue = APPROVED;
              break;
            }
			
		}
	}
	return LOCAL_returnValue;
}


EN_dataError_t DATABASE_checking (Uchar8_t * pan,Uchar8_t * amount,float32_t *newAmount)
{
    
    EN_dataError_t Returend_Val;
    Returend_Val = isValidPanAccount(pan);
    if(Returend_Val == FRAUD_CARD) return Returend_Val;
    Returend_Val = isRunningAccount(pan);
    if(Returend_Val == CARD_STOLEN) return Returend_Val;
    Returend_Val = isBelowMaxDailyAmount(amount);
    if(Returend_Val == EXCEED_MAX_DAILY_AMOUNT) return Returend_Val;
    Returend_Val = isValidAccountAmount(pan , amount,newAmount);
    if(Returend_Val == INSUFFICIENT_FUND) return Returend_Val;
    
    
    Returend_Val = APPROVED;
    
    
}