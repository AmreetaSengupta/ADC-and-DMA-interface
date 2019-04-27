/***********************************************************************************
* @adc.h
* @This contains variable definition and function prototypes for adc.c
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "MKL25Z4.h"

void adc_init();
uint32_t adc_readvalue();
void led_toggle();

extern uint32_t var, flag, led_flag;
