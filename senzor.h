#ifndef __SENZOR_H__
#define __SENZOR_H__

#define SAMPLES 500  //definiseo broj uzoraka
#include "stm32f4xx.h"

uint32_t getSenzorADC();    //definisemo varjablu koja ce uzimati vrijednost sa senzora prikljucenog na pin PC5 za kojeg smo def.ADC
void     setSignalDistance(uint32_t utmp32); //varijabla koja ce uzimati vrijednosti udaljenosti

#endif
