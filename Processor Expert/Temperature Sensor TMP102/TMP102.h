/*
 * TMP102.h
 *
 *  Created on: Dec 22, 2014
 *      Author: Student
 */

#ifndef TMP102_H_
#define TMP102_H_

//Device Address
//0x48 Addr -> GND
//0x49 Addr -> VCC
//0x50 Addr -> SDA
//0x51 Addr -> SCL
#define TempAdd			0x48


//Register Definitions
//Note that only the pointer register is direclty accessed
#define POINTER			0x00
#define TEMPERATURE		0x00
#define CONFIGURATION	0x01
#define THIGHLIMIT		0x02
#define TLOWLIMIT		0x03


#endif /* TMP102_H_ */
