#include <MKL25Z4.h>
#include <stdio.h>
#include "delay.h"

#define _SBR 				0x68
#define _BAUD				115200
#define _OSR					16

#define _BDH				0x00
#define _BDL				0x1A
#define _C1  				0x00
#define _C2  				//UART0_C2_RIE_MASK
#define _C3  				0x00
#define _C4					0x0F
#define _C5					0x00
#define _MA1  			0x00
#define _MA2  			0x00
#define _S1  				0x1F
#define _S2 				0xC0

#define calc_baud			src_clk/(sbr*(UART0_C4_OSR_MASK + 1))
#define calc_sbr			src_clk/(calc_baud*(UART0_C4_OSR_MASK + 1))

int c;

/*

uart0clk = 2000 * 1000
i=4;
sbr_val = (uint32)(uart0clk/(baud_rate * i)) = 4.3402777
calculated_baud = (uart0clk/ (i*sbr_val));


*/




void uart0_Init(void){	
	
	//SIM module configurations
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;  //If enabled, MCGPLLCLK clock with fixed divide by two, else MCGFLLCLK
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	//Still need to do pin alternative function initilization
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x2);
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x2);
	
	//Turn off the transmitter and reciever so they can be programmed
	UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);
	
	//Set interrupt parameters
	//NVIC_EnableIRQ(UART0_IRQn);
	//NVIC_SetPriority(UART0_IRQn, 3);
	
	
	
	UART0->BDH = _BDH;
	UART0->BDL = _BDL;
	
	UART0->C1 = _C1;
	UART0->C3 = _C3;	
	UART0->C4 = _C4;
	UART0->MA1 |= _MA1;
	UART0->MA2 |= _MA2;
	
	UART0->S1 |= _S1;
	UART0->S2 |= _S2;
	
	UART0->C2 |= UART_C2_TE_MASK | UART0_C2_RE_MASK;
	asm("CPSIE i");

}

/*
void uart0_isr(void){
	if (UART0->S1 & UART_S1_RDRF_MASK)
	{
		c = UART0->D;
		if (!(UART0->S1&UART_S1_TDRE_MASK) && !(UART0->S1&UART_S1_TC_MASK))
		{
			UART0->D |= c;
		}
	}
}
*/


void print_uart_settings(void){
	printf("\n ========== UART0 Settings ========= ");
	printf("\n Baud Rate: 0x%X \n", _BAUD);
	printf("\n Over-sampling Ratio: 0x%X \n", _OSR);
	printf("\n Data size: 8-bit");
	printf("\n Parity: None");
	printf("\n Stop Bit: 1 bit");
	printf("\n");	
	printf("\n === Raw Register Settings === ");
	printf("\n UART0_BDH_Register: 0x%X \n", _BDH);
	printf("\n UART0_BDL_Register: 0x%X \n", _BDH);
	printf("\n UART0_C1_Register: 0x%X \n", 	_C1);
	//printf("\n UART0_C2_Register: 0x%X \n", 	_C2);
	printf("\n UART0_C3_Register: 0x%X \n", 	_C3);
	printf("\n UART0_C4_Register: 0x%X \n", 	_C4);
	printf("\n UART0_C5_Register: 0x%X \n", 	_C5);
	//printf("\n UART0_S1_Register:	0x%X \n", 	_S1);
	//printf("\n UART0_S2_Register: 0x%X \n", 	_S2);
	printf("\n UART0_MA1_Register: 0x%X \n", _MA1);
	printf("\n UART0_MA2_Register: 0x%X \n", _MA2);
	printf("\n");
	printf("\n");
	printf("\n	8 8888         8 8888888888 8888888 8888888888 d888888o.            8 888888888o.          ,o888888o.              8888888 8888888888 8 8888        8 8 8888    d888888o.                                                              ");
	printf("\n	8 8888         8 8888             8 8888     .`8888:' `88.          8 8888    `^888.    . 8888     `88.                  8 8888       8 8888        8 8 8888  .`8888:' `88.                                                            ");
	printf("\n	8 8888         8 8888             8 8888     8.`8888.   Y8          8 8888        `88. ,8 8888       `8b                 8 8888       8 8888        8 8 8888  8.`8888.   Y8                                                            ");
	printf("\n	8 8888         8 8888             8 8888     `8.`8888.              8 8888         `88 88 8888        `8b                8 8888       8 8888        8 8 8888  `8.`8888.                                                                ");
	printf("\n	8 8888         8 888888888888     8 8888      `8.`8888.             8 8888          88 88 8888         88                8 8888       8 8888        8 8 8888   `8.`8888.                                                               ");
	printf("\n	8 8888         8 8888             8 8888       `8.`8888.            8 8888          88 88 8888         88                8 8888       8 8888        8 8 8888    `8.`8888.                                                              ");
	printf("\n	8 8888         8 8888             8 8888        `8.`8888.           8 8888         ,88 88 8888        ,8P                8 8888       8 8888888888888 8 8888     `8.`8888.                                                             ");
	printf("\n	8 8888         8 8888             8 8888    8b   `8.`8888.          8 8888        ,88' `8 8888       ,8P                 8 8888       8 8888        8 8 8888 8b   `8.`8888.                                                            ");
	printf("\n	8 8888         8 8888             8 8888    `8b.  ;8.`8888          8 8888    ,o88P'    ` 8888     ,88'                  8 8888       8 8888        8 8 8888 `8b.  ;8.`8888                                                            ");
	printf("\n	8 888888888888 8 888888888888     8 8888     `Y8888P ,88P'          8 888888888P'          `8888888P'                    8 8888       8 8888        8 8 8888  `Y8888P ,88P'                                                            ");
	printf("\n																																																																																																																				 ");
	printf("\n      #######      /                                                     		       ");
	printf("\n    /       ###  #/                                                                ");
	printf("\n   /         ##  ##                                                                ");
	printf("\n   ##        #   ##                                                                ");
	printf("\n    ###          ##                                                                ");
	printf("\n   ## ###        ##  /##      /###   ###  /###   ###  /###     /###   ###  /###    ");
	printf("\n    ### ###      ## / ###    / ###  / ###/ #### / ###/ #### / / ###  / ###/ #### / ");
	printf("\n      ### ###    ##/   ###  /   ###/   ##   ###/   ##   ###/ /   ###/   ##   ###/  ");
	printf("\n        ### /##  ##     ## ##    ##    ##    ##    ##    ## ##    ##    ##    ##   ");
	printf("\n          #/ /## ##     ## ##    ##    ##    ##    ##    ## ##    ##    ##    ##   ");
	printf("\n           #/ ## ##     ## ##    ##    ##    ##    ##    ## ##    ##    ##    ##   ");
	printf("\n            # /  ##     ## ##    ##    ##    ##    ##    ## ##    ##    ##    ##   ");
	printf("\n  /##        /   ##     ## ##    /#    ##    ##    ##    ## ##    ##    ##    ##   ");
	printf("\n /  ########/    ##     ##  ####/ ##   ###   ###   ###   ### ######     ###   ###  ");
	printf("\n/     #####       ##    ##   ###   ##   ###   ###   ###   ### ####       ###   ### ");
	printf("\n|                       /                                                          ");
	printf("\n                       /                                                           ");
	printf("\n                      /                                                            ");
	printf("\n                     /                                                             ");
	printf("\n                                                                                   ");
	printf("\n      #######                                                                      ");
	printf("\n    /       ###                                                                    ");
	printf("\n   /         ##   #                                   #                            ");
	printf("\n   ##        #   ##                                  ##                            ");
	printf("\n    ###          ##                                  ##                            ");
	printf("\n   ## ###      ######## ###  /###   ##   ####      ######## ######                 ");
	printf("\n    ### ###   ########   ###/ #### / ##    ###  / ######## /#######                ");
	printf("\n      ### ###    ##       ##   ###/  ##     ###/     ##   /      ##                ");
	printf("\n        ### /##  ##       ##         ##      ##      ##          /                 ");
	printf("\n          #/ /## ##       ##         ##      ##      ##         /                  ");
	printf("\n           #/ ## ##       ##         ##      ##      ##        ###                 ");
	printf("\n            # /  ##       ##         ##      ##      ##         ###                ");
	printf("\n  /##        /   ##       ##         ##      /#      ##          ###               ");
	printf("\n /  ########/    ##       ###         ######/ ##     ##           ##               ");
	printf("\n/     #####       ##       ###         #####   ##     ##          ##               ");
	printf("\n|                                                                 /                ");
	printf("\n                                                                 /                 ");
	printf("\n                                                                /                  ");
	printf("\n                                                               /   								 ");
	
	Delay_ms(1000);
	printf("\n Analysis starting in 5 seconds");
	Delay_ms(1000);
	printf("\n.");
	Delay_ms(1000);
	printf("\n.");
	Delay_ms(1000);
	printf("\n.");
	Delay_ms(1000);
	printf("\n.");
	Delay_ms(1000);
	printf("\n.");
	
}


char uart0_getchar(void){
      /* Wait until character has been received */
      while ((UART0->S1 == 0x00) & UART0_S1_RDRF_MASK);
    
      /* Return the 8-bit data from the receiver */
      return UART0->D;
}

void uart0_putchar(char ch){
      /* Wait until space is available in the FIFO */
      while((UART0->S1 == 0x00)  & UART0_S1_TDRE_MASK);
    
      /* Send the character */
      UART0->D = ch;
    
 }

void tell_a_story(void){
	putchar('?');
}


                                                                                   
