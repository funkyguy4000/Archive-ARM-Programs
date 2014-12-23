/*
	Code created by Shannon Strutz
	Date : 5/7/2014
	Licensed under CC BY-NC-SA 3.0
	http://creativecommons.org/licenses/by-nc-sa/3.0/

*/

#include <MKL25Z4.h>	//Device definitions
#include <stdio.h>		//Standard IO library
#include "UART.h"			//UART0 device driver

int main(void){
	uart0_Init(); //Initialize UART
	print_uart_settings();
	while(1){		
		printf("\n Hello World ");
	}
}


