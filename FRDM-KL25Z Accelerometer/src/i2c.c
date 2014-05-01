#include <MKL25Z4.H>
#include "i2c.h"

//init i2c0
void i2c_init(void){
	//clock i2c peripheral and port E
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= (SIM_SCGC5_PORTE_MASK);
	
	//set pins to I2C function
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	PORTE->PCR[25] |= PORT_PCR_MUX(5);
		
	//set to 100k baud
	//baud = bus freq/(scl_div+mul)
 	//~400k = 24M/(64); icr=0x12 sets scl_div to 64
 	I2C0->F = (I2C_F_ICR(0x12) | I2C_F_MULT(0));
	
	//enable i2c and set to master mode
	I2C0->C1 |= (I2C_C1_IICEN_MASK );
}


//send start sequence
void i2c_start(){
	I2C_TRAN;							/*set to transmit mode */
	I2C_M_START;					/*send start	*/
}

//send device and register addresses
void i2c_read_setup(uint8_t device, uint8_t address){
	i2c_start();
	I2C0->D = device;
	I2C_WAIT;
	I2C0->D = address;
	I2C_WAIT;
	I2C_M_RSTART;
	I2C0->D =(device|0x1);
	I2C_WAIT;
	I2C_REC;
}


//read a byte and ack/nack as appropriate
uint8_t i2c_repeated_read(uint8_t isLastRead){
	uint8_t data;

	
	if(isLastRead){       /*If this is the last READ (isLastRead); if no, send NACK; if yes, send ACK*/
			NACK; 				    /*set NACK after read	*/
	}
	else{
			ACK;					    /*ACK after read	*/
	}
	data = I2C0->D;				/*Add a dummy read*/	
	I2C_WAIT;							/*wait for completion*/
	             			    
	 							        
	
	if(isLastRead)	{     //if this is the last READ (isLastRead), if yes, send STOP
			I2C_M_STOP;       /*send stop	*/
	}
	data = I2C0->D; 			/*read data	*/

	return data;					/*return data*/				
}



//////////funcs for reading and writing a single byte
//using 7bit addressing reads a byte from dev:address
uint8_t i2c_read_byte(uint8_t dev, uint8_t address){
	uint8_t data;
	i2c_start();					/*set to transmit mode */
												/*send start	*/
	I2C0->D = dev; 				/*1. send dev address	*/
	I2C_WAIT;							/*wait for completion */
	I2C0->D = address;		/*2. send read address	*/
	I2C_WAIT;							/*wait for completion */
		
	I2C_M_RSTART;					/*repeated start */
	I2C0->D = (dev|0x1);	/*3. send dev address (read)	*/
	I2C_WAIT;							/*wait for completion */
	I2C_REC;							/*set to receive mode */
	NACK;									/*set NACK after read	*/
	
	data=I2C0->D;			  	/*dummy read	*/
	I2C_WAIT;							/*wait for completion */
	
	I2C_M_STOP;						/*send stop	*/
	data |= I2C0->D;			/*read data	*/

	return data;       /*return data*/
}



//using 7bit addressing writes a byte data to dev:address
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data){
	
		i2c_start();									/*set to transmit mode & send start*/
		I2C0->D = dev;								/*send dev address	*/

		I2C_WAIT;											/*wait for ack */	
		I2C0->D = address;						/*send write address	*/

		I2C_WAIT;											/*wait for ack */		
		I2C0->D = data;								/*send data	*/
		
		I2C_WAIT;											/*wait for ack*/
		I2C_M_STOP;										/*send Stop*/
	
}

