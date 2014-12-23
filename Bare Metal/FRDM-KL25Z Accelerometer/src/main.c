/*----------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
#include <MKL25Z4.H>
#include <stdio.h>
#include <math.h>
#include "gpio_defs.h"
#include "LEDs.h"
#include "i2c.h"
#include "mma8451.h"
#include "delay.h"

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
	//initiliaze RGB LED
	Init_RGB_LEDs();

if (init_mma() == 0)
{ 
  Control_RGB_LEDs(1,0,0);
  while (1); //stay in the infinite loop to indicate the error with the RED LED
}	
	
//Add Delay (1000); here	
	Delay(1000);
	
	while (1) {
		//Read the data on x, y, and z axis; // Use function call to read the axes data
		//Convert x, y, and z axis to roll and pitch as described in the class 
		// use function call to convert the data
		
		// Light green LED if pitch > 10 ; pick a pitch angle between 10 and 15 degrees
		// Light blue LED if roll > 10 ; pick a roll angle between 10 to 15 degrees
		
		// use LED function call "Control_RGB_LEDs" from previous labs and display  
		// roll and pitch angles using the tri-color LED; you may
		//ignore the yaw angle; for details, see lab manual for roll, pitch, and yaw
		//definitions
		
	}
}

