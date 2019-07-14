#include "stm32f4xx.h"
#include "adc.h"
#include "usart.h"
#include "delay.h"
#include "senzor.h"	


int main(void)
{
	 	
	
	
	initSYSTIMER();
	
	initUSART2(USART2_BAUDRATE_115200);
	initADC1();
	uint32_t utmp32;
	while(1)
	{

		utmp32 = getSenzorADC();
		setSignalDistance(utmp32);
		printUSART2("-> ADC: %d[mm]\n",utmp32);
		
		delay_ms(100);
	
	}
}

