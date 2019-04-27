/***********************************************************************************
* @uart.h
* @This contains variable definition and function prototypes for uart.c
* @authors Amreeta Sengupta & Ridhi Shah
************************************************************************************/
#include "board.h"
#include "pin_mux.h"
#include "MKL25Z4.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#define UART0_CLOCK_GATING 0X00000400
#define PORTA_CLOCK_GATING 0X00000200
#define UART0_CLOCK_FREQUENCY 0X04000000
#define UART0_C1_CONFIG 0X00
#define UART0_C2_CONFIG 0X00
#define UART0_PIN_MODE 	0X00000200
#define UART0_BDH_VALUE 0X00
#define UART0_BDL_VALUE 0X0C

//#define nonblocking

void uartinit();
void tx_wait();
void rx_wait();
void myputchar(char ch);
void myputint(uint16_t num);
void myputstr(char *s);
void myputfloat(float a);
char mygetchar();
int get_num();
