/***********************************************************************************
* @main.c
* @This code implements UART drivers in blocking and rx non-blocking way.
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "core_cm0plus.h"
#include "ring.h"
#include "uart.h"
#include "adc.h"
#include "dma.h"

uint32_t var, flag=0,led_flag=0, buff_add2=128;
uint16_t arr[256], dma_count=0, dma_flag, curr_val, max_val;

int main(void)
{
	uartinit();
	adc_init();
	dma_init();

	while(1)
	{
		if(dma_count<128 && dma_flag ==1)
		{
			myputint((uint16_t)arr[buff_add2 + dma_count++]);
			myputstr("\n\r");
		}


		/*
		//var=adc_readvalue();
		//myputint(var);
		if(flag == 1)
		{
			flag = 0;
			//led_toggle();
			//myputstr("ADC VALUE:");
			//myputint(var);
			//led_flag = ~led_flag;
		}*/
	}
}




