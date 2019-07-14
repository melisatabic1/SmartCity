#include "adc.h"

void initADC1(void)
{/// i
	//wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww
	// ADC PA1 -> ADC123_IN1 konfigurisati ADC1  na kanalu 15
	//------------------------------------------------------------------ 
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 								
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; 									
	GPIOC->MODER |= GPIO_MODER_MODER5; //ovdje mijenjamo pin npr za pin a1 pisemo moder1								
	GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR5; 		//ne mijenjamo						
	
	ADC1->CR1 = 0x00000200;												// 12-bit resolution (15 ADCCLK cycles), 1 channel
																		// discontinious mode on regular channels
																		// single conversion mode
	ADC1->SMPR1 = 0x00000000;											// conversion time 3 cycles of ADCCLK clock!
	ADC1->SQR1 = 0x000000000;											// select one channel in regular sequence
	ADC1->SQR2 = 0x000000000;
	ADC1->SQR3 = 0x00000000F;											// select channel 1 npr za kanal 14 na zadnjem mjestu stavim E
	ADC1->CR2 =  0x000000400;  //kontrolni registar
	ADC->CCR = 0x00010000;												// ADC clock 84/4 = 21MHz!
	
	ADC1->CR2 |= ADC_CR2_ADON;											// turn on the ADC
}

uint16_t getADC1(void)   //uzima varijablu def.u adc.h
{
	uint16_t adc_data;  //vrijednost adc
	uint32_t time;
	
	adc_data = ADC1->DR;		//uzima vr. iz data registra										// clear the EOC flag
		
	time = TIM2->CNT;    //uzima vrijeme od TIM2 kojeg smo def u delay.c- tajmer izvrsava funkciju brojaca
	ADC1->CR2 |= ADC_CR2_SWSTART;										// start conversion of regular channels
	while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC); //ceka da kanal zavrsi regularnu konverziju i vraca vr.adc
	time = TIM2->CNT - time;
	adc_data = ADC1->DR;												// get the data
	
			
	//printUSART2("-> ADC: conversion time: [%d] 1/84MHz\n",time);
	return adc_data; 
}
