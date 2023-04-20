
#include "APP/app.h"

#define F_CPU 8000000UL

void main(void)
{

	APP_Init();
	
	while(1)
	{
		
		APP_Start();

	}
}