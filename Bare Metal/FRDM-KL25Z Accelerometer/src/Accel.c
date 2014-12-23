#include <MKL25Z4.H>
#include "leds.h"
#include "i2c.h"
#include "mma8451.h"

//global tick count
volatile uint32_t TICK;
//mma data ready
uint32_t DATA_READY;
//pwm values
int16_t RED_INT;
int16_t BLUE_INT;
int16_t GREEN_INT;

void SysTick_Handler()
{
	TICK++;
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks 
 *------------------------------------------------------------------------------*/
void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = TICK;
  while ((TICK - curTicks) < dlyTicks);
}

void Accel_Demo(void)
{

	DATA_READY =0;
	
	SysTick_Config(SystemCoreClock/1000);     /* Generate interrupt each 1 ms */
	init_leds_pwm();													/* inits leds for pwm	*/
	i2c_init();																/* init i2c	*/
	init_mma();																/* init mma peripheral */
	
	Delay(5);
	
	while(1)	{
		
		__WFI();		
		read_full_xyz();
		
		change_red(RED_INT);
		change_green(GREEN_INT);
		change_blue(BLUE_INT);

			
	}
	
}	

