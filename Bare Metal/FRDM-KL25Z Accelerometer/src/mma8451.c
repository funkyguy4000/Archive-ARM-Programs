#include <MKL25Z4.H>
#include "mma8451.h"
#include "i2c.h"
#include "delay.h"
#include <math.h>

int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

//mma data ready
extern uint32_t DATA_READY;



//initializes mma8451 sensor
//i2c has to already be enabled
int init_mma()
{
	  //check for device if it is present
		if(i2c_read_byte(MMA_ADDR, REG_WHOAMI) == WHOAMI)	{
  		Delay(10);
			//set active mode, 14 bit samples and 100 Hz ODR (0x19)
			i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
			return 1;
		}
		//else error
		return 0;
}

void read_full_xyz()
{
	int i;
	uint8_t data[6];
	int16_t temp[3];
	
	i2c_start();
//Add function call for i2C read setup        //	i2c_read_setup(MMA_ADDR , REG_XHI);
	i2c_read_setup(MMA_ADDR, REG_XHI);
	
// Read five bytes in repeated read mode to data array "data[6]"
	for(i = 0; i<3; i++){
		data[i] = i2c_repeated_read(0);
	}
// Read last byte ending repeated read_mode
	data[i] = i2c_repeated_read(1);
	
// save acceleration data into temp variables for all 3-axis into temp[i] array
//data type for temp[i] should be int16_t;
//index number for the data array is multiplied by 2 due to a 14-bit accel. data
	
	for(i=0; i<3; i++){
		temp[i] = (int16_t)((data[2*i]<<8) | data[2*i+1]);
	}
	// Add the following code to align accel. data in the data array for 14 bits
	acc_X = temp[0]/4;
	acc_Y = temp[1]/4;
	acc_Z = temp[2]/4;
}


void read_xyz(void)
{
	// sign extend byte to 16 bits - need to cast to signed since function
	// returns uint8_t which is unsigned
	int8_t XH = (int8_t) i2c_read_byte(MMA_ADDR, REG_XHI);
	int8_t XL = (int8_t) i2c_read_byte(MMA_ADDR, REG_XLO);
	acc_X = (int16_t)((XH<<8) | XL);
	Delay(100);
	
	// Add two other 2-axis here
	int8_t YH = (int8_t) i2c_read_byte(MMA_ADDR, REG_YHI);
	int8_t YL = (int8_t) i2c_read_byte(MMA_ADDR, REG_YLO);
	acc_Y = (int16_t)((YH<<8) | YL);
	Delay(100);
	
	int8_t ZH = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZHI);
	int8_t ZL = (int8_t) i2c_read_byte(MMA_ADDR, REG_ZLO);
	acc_Z = (int16_t)((ZH<<8) | ZL);
	Delay(100);
	
}

void convert_xyz_to_roll_pitch(void) {
	
	//When the full-scale is set to 2g, the measurement range is -2g to +1.99975g, 
	//and each count corresponds to 1g/4096
  //(0.25 mg) at 14-bits resolution
	//where the COUNTS_PER_G is a constant 4096
	//compute ax, ay, ax from acc_X, acc_Y, and acc_Z. acc_X, acc_Y, and acc.Z are data	
	//output from the accelerometer on the Freedom board
	
	read_xyz();
	//ax, ay, and az all have an unit of 'g' and are float data type 
	float ax = acc_X / COUNTS_PER_G;
	float ay = acc_Y / COUNTS_PER_G;
	float az = acc_Z / COUNTS_PER_G;
	
	float tanphi = ay/az;
	float phi = atan(tanphi);
	
	float tantheta = -ax / sqrt(pow(ay, 2) + pow(az, 2));
	float theta = atan(tantheta);
	
	
	//The last step is to go from accelerations (gs) to angles. The conversion
	//is to use trigonometry as show below. For the details on how this is
	//derived, you can visit the link: 
	//http://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf
	
	
	
	//roll = 
	//pitch =
	
}


