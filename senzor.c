#include "senzor.h"	 

uint32_t getSenzorADC(){
	
		volatile uint32_t utmp32, i;    //izvrsava ono sto mu se kaze
		float s = 0;                    //setujemo na nula
		uint32_t Vcc = 5;               //napon, senzor radi od 3,5 do 5 volti
		uint32_t resolution = (2^12)-1; //rezolucija 4095
		
		for(i=0;i<(SAMPLES);i++)        //samples=500, ako je broja manji od 500 vrijedi for petlja,
		{
			utmp32 = getADC1();
			s += (float)(utmp32*utmp32);  //suma svih clanova s+, kvadriramo zato sto moze poprimiti neg.vr.
			delay_us(500);
		}
		
        utmp32 = (uint32_t)sqrtf((s)/(SAMPLES)); //vadimo korijen i opet dobivamo poz.vr. (uzorkovanje)
		utmp32 = ((Vcc*utmp32)/resolution);

		return utmp32;	//vraca vrijednost
}

void setSignalDistance(uint32_t utmp32){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 
	GPIOA->MODER |= 0x00040000;             							
    GPIOA->OTYPER = 0x00000000;											 
    GPIOA->OSPEEDR |= 0x00040000; 	
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  								
    GPIOD->MODER |= 0x55000000;             							
    GPIOD->OTYPER = 0x00000000;											 
    GPIOD->OSPEEDR |= 0xFF000000;
    

	if(utmp32 >=300 & utmp32 <= 1200){
		GPIOD->ODR |= 0xF000;
		GPIOA->ODR &= ~0x0200;
	} 
	
	 
	else {
		GPIOD->ODR &= ~0xF000;
		GPIOA->ODR |= 0x0200;
		}
	   
} 

	

   
    
		
