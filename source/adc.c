/***********************************************************************************
* @main.c
* @This code implements ADC APIs.
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "adc.h"

void adc_init()
{

/******************************4.3915 ms*****************************/

	SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV4(2); //Bus clock divide by 3
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; //Enable the ADC Clock

	ADC0->CFG1 |= ADC_CFG1_ADIV(3); //Selects the divide ratio
	ADC0->CFG1 |= ADC_CFG1_ADLSMP(1); //Long sample time selected
	ADC0->CFG1 |= ADC_CFG1_MODE(3); //single ended 16-bit conversion
	ADC0->CFG1 |= ADC_CFG1_ADICLK(1); //Bus clock

	ADC0->SC3 |= ADC_SC3_ADCO_MASK; //Enable continuous conversion
	ADC0->SC3 |= ADC_SC3_AVGE_MASK; //Hardware average function enabled
	//ADC0->SC3 |= ADC_SC3_AVGS(3) ;
	ADC0->SC3 |= ADC_SC3_AVGS_MASK; //32 samples averaged

	ADC0->SC1[0] &= ~ADC_SC1_ADCH_MASK;

	ADC0->SC2 |= ADC_SC2_DMAEN_MASK; //Enable DMA

	ADC0->SC1[0] |=  ADC_SC1_AIEN_MASK;
	NVIC_EnableIRQ(ADC0_IRQn);
	__enable_irq();


	SIM->SCGC5 |= 0x400;
	PORTB->PCR[11] = 0x100;
	GPIOB->PDDR |=0x800;
}

uint32_t adc_readvalue()
{
	while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	return ADC0->R[0];
}

void led_toggle()
{
	if(led_flag == 0)
	GPIOB->PSOR |= 0x800;
	else
	GPIOB->PCOR |= 0x800;
}


void ADC0_IRQHandler(void)
{
	__disable_irq();
	var = ADC0->R[0];
	led_toggle();
	led_flag = ~led_flag;
	flag = 1;
	__enable_irq();
}
