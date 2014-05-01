#include <MKL25Z4.H>
#include "gpio_defs.h"

/* CEE-345 Microprocessor System Design
Demonstration of simple digital output
Use RGB LED on Freedom board*/

void Delay(unsigned int time_del) {
	// delay is about 1 millisecond * time_del
	volatile int t;
	
	while (time_del--) {
		for (t=4800; t>0; t--)
			;
	}
}


/*  Each LED corresponds to a bit on a port
    Red LED connected to Port B (PTB), bit 18 (RED_LED_POS)
    Green LED connected to Port B (PTB), bit 19 (GREEN_LED_POS)
    Blue LED connected to Port D (PTD), bit 1 (BLUE_LED_POS)
    Active-Low outputs: Write a 0 to turn on an LED

    Turning LEDs on and off
    Turn on one LED: PTx->PDOR = ~ MASK(yyy_LED_POS) ;
    Turn on two LEDs: PTx->PDOR = ~ ( MASK(yyy_LED_POS) | MASK(zzz_LED_POS) ) ;
    Turn all LEDs off: PTx->PDOR = 0xFFFFFFFF ;*/

void redGreenBlue(void)
{
		
		int del = 600;
	
	   // set just red led on
		 PTB->PDOR = ~ MASK(RED_LED_POS) ;
		 PTD->PDOR = 0xFFFFFFFF ;
		 
		 // wait for 500ms
		 Delay(del) ;
	
		 // set just green led on
		 PTB->PDOR = ~ MASK(GREEN_LED_POS) ;
		 PTD->PDOR = 0xFFFFFFFF ;
		 
		 // wait for 500ms
		 Delay(del) ;
		 
		 // set just blue led on
		 PTD->PDOR = ~ MASK(BLUE_LED_POS) ;
		 PTB->PDOR = 0xFFFFFFFF ;
		 
		 // wait for 500ms
		 Delay(del) ;
	
		 // set both red and green led on
		 PTB->PDOR = ~ (MASK(RED_LED_POS) | MASK(GREEN_LED_POS));
		 PTD->PDOR = 0xFFFFFFFF ;
		 
		 //wait for 500ms
		 Delay(del);
		 
		 // set both green a blue led on
		 PTB->PDOR = ~ (MASK(GREEN_LED_POS));
		 PTD->PDOR = ~ (MASK(BLUE_LED_POS));
		  
		 //wait for 500ms
		 Delay(del);
		 
		 // set both blue and red on
		 PTD->PDOR = ~ ( MASK(BLUE_LED_POS));
		 PTB->PDOR = ~  (MASK(RED_LED_POS)) ;
		 
		 //wait for 500ms
		 Delay(del);
		 
		 // set all of the leds on
		 PTD->PDOR = ~ (MASK(BLUE_LED_POS));
		 PTB->PDOR = ~ (MASK(GREEN_LED_POS) | MASK(RED_LED_POS));
		 
		 //wait for 500ms
		 Delay(del);
		 
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
unsigned int counter = 0;
int main (void) {
	
	//Delcare a global variable to be used in debug mode  	
	/*Configuration steps
	   1. Enable clock to GPIO ports
	   2. Enable GPIO ports
	   3. Set GPIO direction to output
	   4. Ensure LEDs are off */

	// Enable clock to ports B and D
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;
	
	// Make 3 pins GPIO
	//two steps process: configure pin multiplexer and select a GPIO pin 
	//first, set pin to GPIO by using MUX =1 in PCR register
	//second, select a GPIO pin
	//"&= ~PORT_PCR_MUX_MASK" below is used to make sure the MUX value 
	//never exceed 7 or 111 
	//use |= to leave other bits unchanged 
	PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1);          
	PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1);          
	PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;          
	PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1);          
	
	// Set ports to outputs: Port Data Direction Register (PDDR)
	PTB->PDDR |= MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PDDR |= MASK(BLUE_LED_POS);

	// Turn off LEDs: Port Set Output Register (PSOR) 
	PTB->PSOR = MASK(RED_LED_POS) | MASK(GREEN_LED_POS);
	PTD->PSOR = MASK(BLUE_LED_POS);
  // end of configuration code 
	
	// Code for flashing the LEDs	
	while (1) {		
   
		redGreenBlue();
	
		counter = counter + 1;   	
	}

}

