#include "UART.h"		//Includes delay.h, <MKL26Z4.h>, and <stdio.h>
//#include "FFT.h"		//includes ADC.h, kiss_fft.h, and <math.h>


char greetings[6] = "Hello";

	

unsigned int counter;

int main(void){
	
	//Initialize UART
	uart0_Init();
	
	//Initialize ADC
	//ADC_Init();
	
	//Set up FFT algorithm
	//FFT_Init();
	
	//Handshake
	//print_uart_settings();	
	
	while(1){
		while(!(UART0->S1 & UART_S1_RDRF_MASK));
		c = UART0->D;
		while(!(UART0->S1 & UART_S1_TDRE_MASK) && !(UART0->S1 & UART_S1_TC_MASK));
		UART0->D = c;
	}
}

