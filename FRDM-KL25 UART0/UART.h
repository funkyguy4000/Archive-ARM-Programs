/* UART0 Device Driver

	Code created by Shannon Strutz
	Date : 5/7/2014
	Licensed under CC BY-NC-SA 3.0
	http://creativecommons.org/licenses/by-nc-sa/3.0/

*/

int sysclk = 48000000;
int baud = 115200;
uint32_t osr = 15;
uint16_t sbr;
uint8_t temp;

struct __FILE
{
  int handle;
};

FILE __stdout;  //Use with printf
FILE __stdin;		//use with fget/sscanf, or scanf


//Retarget the fputc method to use the UART0
int fputc(int ch, FILE *f){
	while(!(UART0->S1 & UART_S1_TDRE_MASK) && !(UART0->S1 & UART_S1_TC_MASK));
	UART0->D = ch;
	return ch;
}

//Retarget the fgetc method to use the UART0
int fgetc(FILE *f){
	while(!(UART0->S1 & UART_S1_RDRF_MASK));
	return UART0->D;
}

//Generic UART0 getchar method
char uart0_getchar(void){
  while(!(UART0->S1 & UART_S1_RDRF_MASK));
	return UART0->D;	
}

//Generic UART0 putchar method
void uart0_putchar(char ch){
  while(!(UART0->S1 & UART_S1_TDRE_MASK) && !(UART0->S1 & UART_S1_TC_MASK));
	UART0->D = ch;
}

void uart0_Init(void){	
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK; 										// enable clock gating to uart0 module 
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;											// enable clock gating to port A 	
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK; 		// disable rx and tx for register programming 
	// set uart clock to oscillator clock 
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(01);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
	// set pins to uart0 rx/tx 
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
	
	sbr = (uint16_t)((sysclk)/(baud * osr+1));
	temp = UART0->BDH & ~(UART0_BDH_SBR(0x1F));
	UART0->BDH = temp | UART_BDH_SBR(((sbr & 0x1F00) >> 8));
	UART0->BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK);
	UART0->C4 |= UART0_C4_OSR(osr);													// set oversampling ratio 
	
	// keep default settings for parity and loopback
	UART0->C1 = 0;
	UART0->C3 |= 0;
	UART0->MA1 = 0;
	UART0->MA2 = 0;
	UART0->S1 |= 0x00;
	UART0->S2 = 0x00;
	UART0->C2 |= UART0_C2_TE_MASK | UART0_C2_RE_MASK;				//enable UART
}

void print_uart_settings(){
	printf("\n ========== UART0 Settings =========  \n");
	printf("\n Baud Rate: 0x%X                      \n", baud);
	printf("\n Over-sampling Ratio: 0x%X            \n", osr);
	
	
	//Data size
	if(UART0_C1_M_MASK == 0){
		printf("\n Data size: 8-bit                   \n");
	}
	else{
		printf("\n Data size: 9-bit										\n");
	}
	
	//Everything Parity
	if(UART0_C1_PE_MASK == 0){
			printf("\n Parity: None                     \n");
	}
	else{
		printf("\n Parity: Enabled                    \n");
		if(UART0_C1_PT_MASK == 0){
			printf("\n Parity Type: Even parity 				\n");
		}
		else{
			printf("\n Parity Type: Odd parity 					\n");
		}
	}
	
	//Stop bits
	if (UART0_BDH_SBNS_MASK == 0){
		printf("\n Stop Bits: 1 bit 									\n");
	}
	else{
		printf("\n Stop Bits: 2 bit 									\n");
	}
	
	printf("\n \n");	
	printf("\n === Raw Register Settings ===        \n");
	printf("\n UART0_BDH_Register: 0x%X             \n",UART0->BDL);
	printf("\n UART0_BDL_Register: 0x%X             \n",UART0->BDH);
	printf("\n UART0_C1_Register:  0x%X             \n",UART0->C1);
	printf("\n UART0_C2_Register:  0x%X             \n",UART0->C2);
	printf("\n UART0_C3_Register:  0x%X             \n",UART0->C3);
	printf("\n UART0_C4_Register:  0x%X             \n",UART0->C4);
	printf("\n UART0_C5_Register:  0x%X             \n",UART0->C5);
	printf("\n UART0_MA1_Register: 0x%X             \n",UART0->MA1);
	printf("\n UART0_MA2_Register: 0x%X             \n",UART0->MA2);
}
