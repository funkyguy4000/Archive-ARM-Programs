/* ###################################################################
**     Filename    : main.c
**     Project     : Luminosity Sensor TSL2561
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-12-22, 22:57, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "CI2C1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Luminosity.h"
#include <math.h>
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  uint8_t Data0High;
  uint8_t Data0Low;
  uint8_t Data1High;
  uint8_t Data1Low;
  uint16_t Channel0;
  uint16_t Channel1;
  uint16_t d0;
  uint16_t d1;
  float lux;
  double ratio;
	
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  
  GI2C1_Init();
  
  /* For example: for(;;) { } */
  for(;;){
	  GI2C1_SelectSlave(LumAdd);
	  GI2C1_ReadByteAddress8(LumAdd, (COMMAND | DATA0HIGH), &Data0High);
	  GI2C1_ReadByteAddress8(LumAdd, (COMMAND | DATA0LOW), &Data0Low);
	  GI2C1_ReadByteAddress8(LumAdd, (COMMAND | DATA1HIGH), &Data1High);
	  GI2C1_ReadByteAddress8(LumAdd, (COMMAND | DATA1LOW), &Data1Low);
	  
	  Channel0 = 256*Data0High + Data0Low;
	  Channel1 = 256*Data1High + Data1Low;
	  d0 = Channel0;
	  d1 = Channel1;
	  ratio = d1/d0;
	  
	  //Luminosity calculation
	  if (0 < ratio && ratio <= 0.5)
		  lux = ((0.0304 * d0) - (0.062 * d0 * pow(ratio,1.4)));
	  else if (0.5 < ratio && ratio <= 0.61)
		  lux = ((0.0224 * d0) - (0.031 * d1));
	  else if (0.61 < ratio && ratio <= 0.80)
		  lux = ((0.0128 * d0) - (0.0153 * d1));
	  else if (0.80 < ratio && ratio <= 1.30)
		  lux = ((0.0146 * d0) - (0.00112 * d1));
	  else
		  lux = 1;	//Device is saturated, readings no longer reliable

  }
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
