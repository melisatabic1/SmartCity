#ifndef __ADC1_H
#define __ADC1_H

#include "stm32f4xx.h"
#include "delay.h"

void 		initADC1(void);	  //definisemo varijablu ADC1  i varijablu koja ce uzimati vrijednosti sa ADC1
uint16_t 	getADC1(void);    //void koristimo da izbjegnemo upozorenje kompajlera

#endif 
