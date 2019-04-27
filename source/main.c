/***********************************************************************************
* @main.c
* @This code implements ADC and DMA interface.
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "core_cm0plus.h"
#include "uart.h"
#include "adc.h"
#include "dma.h"

void log_calc(uint16_t val);

uint32_t var, flag=0,led_flag=0, buff_add2=128;
uint16_t arr[256], dma_count=0, dma_flag, curr_val, max_val=0, max_flag=0, adc_max=0;

struct table value_table[] = {};

int main(void)
{
	uartinit();
	adc_init();
	dma_init();

	while(1)
	{

		if(dma_count<128 && dma_flag ==1 )
		{
			if(max_flag ==1)
			{
				max_flag = 0;

				if(adc_max >= max_val)
				{
					max_val = adc_max;
				}
				else
				{
					max_val = max_val*0.9;
				}
				myputstr("MAX VAL = ");
				myputint(max_val);
				myputstr("\n\r");
				//log_calc(max_val);
				adc_max = 0;
			}

			curr_val = (uint16_t)arr[buff_add2 + dma_count++];
			if(curr_val >= adc_max)
			{
				adc_max = curr_val;
			}
			myputstr("ADC VAL = ");
			myputint((uint16_t) curr_val);
			myputstr(" DMA VAL = ");
			myputint((uint16_t) dma_count);
			myputstr("\n\r");
		}

	}
}

void log_calc(uint16_t val)
{
	int i;
	float db_val;
	val = val / 3278;
	for(i=0; i<20; i++)
	{
		if(val == value_table[i].value)
		{
			db_val = value_table[i].db_value;
			myputfloat(db_val);
			myputstr("\n\r");
		}
	}
}


