
#ifndef LUMINOSITY_H_
#define LUMINOSITY_H_

//Device Address
// Addr -> GND 		= 0x29;
// Addr -> Float 	= 0x39;
// Addr -> VCC		= 0x49;
#define LumAdd			0x39

#define COMMAND			0x80
#define CONTROL			0x00
#define TIMING			0x01
#define THRESHLOWLOW	0x02
#define THRESHLOWHIGH	0x03
#define THRESHHIGHLOW	0x04
#define THRESHHIGHHIGH	0x05
#define INTERRUPT		0x06
#define	CRC				0x08
#define ID				0x0A
#define DATA0LOW		0x0C
#define DATA0HIGH		0x0D
#define DATA1LOW		0x0E
#define DATA1HIGH		0x0F

#endif /* LUMIONSITY_H_ */
