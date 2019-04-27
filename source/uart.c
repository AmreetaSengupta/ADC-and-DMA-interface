/***********************************************************************************
* @uart.c
* @This code implements UART APIs for printing and scanning.
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "uart.h"

extern int tx_flag;
//ring_t *tx_ptr, *rx_ptr;
extern char ele, read;

void uartinit()
{
	SIM->SCGC4 |= UART0_CLOCK_GATING; //Enable clock to UART0
	SIM->SCGC5 |= PORTA_CLOCK_GATING; //Enable clock to PORTA
	SIM->SOPT2 |= UART0_CLOCK_FREQUENCY; //Enable the UART0 clock frequency to 48MHz
	UART0->C1 |= UART0_C1_CONFIG; //Setting UART optional features to default
	UART0->C2 |= UART0_C2_CONFIG; //Setting UART features to default

	PORTA->PCR[1] |= UART0_PIN_MODE; //Setting alternate mode 2 for PORTA
	PORTA->PCR[2] |= UART0_PIN_MODE; //Setting alternate mode 2 for PORTA

	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK ); //Disable Transmitter and Receiver Enable

	UART0->BDH |= UART0_BDH_VALUE;
	UART0->BDL |= UART0_BDL_VALUE;

	UART0->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK ); //Enable Transmitter and Receiver Enable

	#ifdef nonblocking
		UART0->C2 |= UART0_C2_RIE_MASK;
		__enable_irq();
		NVIC_EnableIRQ(UART0_IRQn);
	#endif
}

void tx_wait()
{
	while(!(UART0->S1 & UART_S1_TDRE_MASK));
}

void rx_wait()
{
	while(!(UART0->S1 & UART_S1_RDRF_MASK));
}

void myputchar(char ch)
{
	tx_wait();
	UART0->D = ch;

}

void myputstr(char *s)
{
	while(*s)
	{
		myputchar(*s++);
	}
}

char mygetchar()
{
	char r;
	rx_wait();
	r = UART0->D;
	return r;
}

void myputint(uint16_t num)
{
	char str[10];
	sprintf(str,"%d",num);
	myputstr(str);
}

void myputfloat(float a)
{
 uint8_t i=2;
 myputint((uint16_t)a);
 myputstr(".");
 while(i!=0)
 {
	a = a - (uint16_t)a;
	a *= 10;
	myputchar(0x30 + (uint16_t)a);
	i-=1;
 }
}

int get_num()
{
	char str[10];
	unsigned int i=0;
	while(1)
	{
		str[i]= mygetchar();
		if(str[i]=='\r')
		{
			str[i]='\0';
			myputchar('\n');
			myputchar('\r');
			break;
		}
		else if(str[i]==0x7f)
		{
			myputchar(str[i]);
			i--;
		}
		else if(str[i]>='0' && str[i]<='9')
		{
			myputchar(str[i]);
			i+=1;
		}
		else
		{
			myputchar(str[i]);
			myputstr("\n\r Not valid! Enter again!\n\r");
			i=0;
		}
	}
	return atoi(str);
}

#ifdef nonblocking
void UART0_IRQHandler(void)
{
	int err;
	__disable_irq();

	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{

		err = insert( rx_ptr,UART0->D);
		if(err == 1)
		{
			err = 5;
		}

	}
	__enable_irq();
}
#endif
