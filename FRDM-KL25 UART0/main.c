/*
	Code created by Shannon Strutz
	Date : 5/7/2014
	Licensed under CC BY-NC-SA 3.0
	http://creativecommons.org/licenses/by-nc-sa/3.0/

	This was created for use with the FRDM-KL25Z
	Data is output through UART0 which should be connected to an FTDI UART to USB bridge, specifically this one: https://www.sparkfun.com/products/9873
	
	Connection diagram:
	
	FTDI Bridge | FRDM-KL25z
	   DTR      |    3V3
		 TXD      |    PTA1
	   RXD      |    PTA2
		 3V3      |    3V3
		 CTS      |    GND
		 GND      |    GND
		 
	The data is viewed through TeraTerm although you can use putty.  If you don't plan on making any critical changes to the UART0 function, then the
	setupd for those viewers is 115200 Baud, 1 stop bit, no parity.  The teraterm configuration file is included in this project
		 
*/


#include <MKL25Z4.h>
#include <stdio.h>
#include "UART.h"		//Includes delay.h, and <MKL26Z4.h>

int main(void){
	uart0_Init(); //Initialize UART
	print_uart_settings();
	while(1){		
		//printf("Hello world!");
	}
}


