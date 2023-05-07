/*
 * CARD_MCU.c
 *
 * Created: 4/29/2023 6:11:52 AM
 * Author : ME
 */ 
#define F_CPU 8000000UL
#include "APP/app.h"
int main(void)
{
	APP_Init();
    while (1) 
    {
      APP_Start();
    }
}



