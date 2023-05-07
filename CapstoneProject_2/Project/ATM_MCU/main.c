/*
 * ATM_MCU.c
 *
 * Created: 4/29/2023 5:30:30 AM
 * Author : ME
 */ 
#define F_CPU 8000000UL
#include "APP/app.h"
void main(void)
{
	APP_Init();

    while (1) 
    {
		APP_Start();
    }
}

