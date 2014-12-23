/* ###################################################################
**     Filename    : main.c
**     Project     : TMP102
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-12-22, 22:13, # CodeGen: 0
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
#include "TMP102.h"
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  
  uint8_t MSB;		//Store the first byte of temperature data
  uint8_t LSB;		//Store the second byte of tempeature data
  uint16_t temp;	//temperature variable
  float tempC;		//Celsius temperature
  float tempF;		//Fahrenheit temperature
  
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  GI2C1_Init();
  
  for(;;){
	  GI2C1_SelectSlave(TempAdd);
	  
	  
	  GI2C1_ReadByteAddress8(TempAdd, 0x00, &MSB);
	  GI2C1_ReadByteAddress8((byte)TempAdd, (POINTER | TEMPERATURE), &MSB);
	  GI2C1_ReadByteAddress8((byte)TempAdd, (POINTER | TEMPERATURE), &LSB);
	  GI2C1_UnselectSlave();
	  
	  temp = ((MSB<<8) | LSB) >> 4;
	  tempC = temp * 0.0625;
	  tempF = (tempC * 1.8) + 32;		
	  
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
