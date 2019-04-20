#include "dma.h"

extern uint16_t arr[256], dma_count, dma_flag;
extern uint32_t buff_add2;
uint32_t buff_add1 = 0,buff_temp;

void dma_init()
{

	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;     //DMA MUX clock gate enable
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;        //DMA clock gate control enable

	DMAMUX0->CHCFG[0] = 0x00;       //DMA Channel Disable
	DMA0->DMA[0].SAR = (uint32_t)&ADC0->R[0];
	DMA0->DMA[0].DAR= (uint32_t) &arr[buff_add1];
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(128*2);
	DMA0->DMA[0].DCR |= DMA_DCR_EINT_MASK;
	DMA0->DMA[0].DCR |= DMA_DCR_ERQ_MASK;
	DMA0->DMA[0].DCR |= DMA_DCR_CS_MASK;
	DMA0->DMA[0].DCR |= DMA_DCR_SSIZE(2);
	DMA0->DMA[0].DCR |= DMA_DCR_DINC_MASK;
	DMA0->DMA[0].DCR |= DMA_DCR_DSIZE(2);

	DMAMUX0->CHCFG[0] |= DMAMUX_CHCFG_ENBL(1) | DMAMUX_CHCFG_SOURCE(40);
	__enable_irq();
	NVIC_EnableIRQ(DMA0_IRQn);
}


void DMA0_IRQHandler(void)
{
	dma_flag = 1;
	__disable_irq();
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;	// Clear Done Flag
	DMA0->DMA[0].DSR_BCR |= DMA_DSR_BCR_DONE_MASK;	// Clear Done Flag

	buff_temp = buff_add1;
	buff_add1 = buff_add2;
	buff_add2 = buff_temp;

	DMA0->DMA[0].DAR = (uint32_t)&arr[buff_add1];
	DMA0->DMA[0].DSR_BCR = DMA_DSR_BCR_BCR(128*2);

	dma_count = 0;

	__enable_irq();
}
