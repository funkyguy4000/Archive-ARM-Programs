//configure I2C control register 1; I2C0->C1 to select master mode  
//(for details, see I2C register mask in mkl25z4.h file)
#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK                     // Select Mater Mode (Start) logic '1' indicates START otherwise STOP
#define I2C_M_STOP 		I2C0->C1 &= ~I2C_C1_MST_MASK  	                                          // Select Master Mode (Stop) 
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK                    // Select Repeat Start

//configure I2C register "I2C_C1_TX_MASK" to allow I2C bus to transmit sensor data; logic '1' to transmit mode, otherwise receiving mode 
#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK                      // I2C bus to Transmit
#define I2C_REC 			I2C0->C1 &= ~I2C_C1_TX_MASK		                                          //I2C bus to receive

#define BUSY_ACK 	    while(I2C0->S & 0x01)                            //I2C Bus Busy
#define TRANS_COMP		while(!(I2C0->S & 0x80))                         //I2C Bus data transafer Complete
																																			 //Enable Interrupt waiting flag
#define I2C_WAIT			while((I2C0->S & I2C_S_IICIF_MASK)==0) {} \
                                 I2C0->S |= I2C_S_IICIF_MASK;
	
#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK                      //Acknolegement of data NOT received
#define ACK           I2C0->C1 &= ~I2C_C1_TXAK_MASK                     //Acknolegement of data received

void i2c_init(void);                                                    //function definition for i2c_init

void i2c_start(void);                                                   //function definition for i2c_start 
	
void i2c_read_setup(uint8_t dev, uint8_t address);                      //function definition for i2c_read_setup
	
uint8_t i2c_repeated_read(uint8_t isLastRead);                                     //function definition for i2c_repeated_read
	
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);                    //function definition for i2c_read_byte

void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);        //function definition for i2c_write_byte
