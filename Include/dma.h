/***********************************************************************************
* @dma.h
* @This contains variable definition and function prototypes for dma.c
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "MKL25Z4.h"
#include "adc.h"
#include "uart.h"

void dma_init();

struct table
{
	uint8_t value;
	float db_value;
};
