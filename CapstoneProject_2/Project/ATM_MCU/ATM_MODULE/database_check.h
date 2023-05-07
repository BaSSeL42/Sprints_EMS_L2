/*
 * database_check.h
 *
 * Created: 5/3/2023 5:02:41 PM
 *  Author: sharb
 */ 


#ifndef DATABASE_CHECK_H_
#define DATABASE_CHECK_H_

#define DB_SIZE                10
#define MAX_TRANS_AMOUNT      "5000.00"
/**************************************************************************************************************************
 *                                              User Defined Data Type
**************************************************************************************************************************/


typedef enum EN_dataError_t
{
	APPROVED = 0,
    FRAUD_CARD,
    CARD_STOLEN,
    EXCEED_MAX_DAILY_AMOUNT,
    INSUFFICIENT_FUND,
    DATA_ERROR
}EN_dataError_t;
typedef enum EN_accountState_t
{
	RUNNING=0,
	BLOCKED
	
}EN_accountState_t;
typedef struct ST_accountsDB_t
{
	float32_t balance;
	EN_accountState_t state;
	Uchar8_t primaryAccountNumber[20];
	
}ST_accountsDB_t;
EN_dataError_t isValidPanAccount(Uchar8_t * pan);
EN_dataError_t isRunningAccount(Uchar8_t * pan);
EN_dataError_t isValidAccountAmount(Uchar8_t * pan,Uchar8_t * amount,float32_t *newAmount);
EN_dataError_t isBelowMaxDailyAmount(Uchar8_t * amount);
EN_dataError_t DATABASE_checking (Uchar8_t * pan,Uchar8_t * amount,float32_t *newAmount);


#endif /* DATABASE_CHECK_H_ */