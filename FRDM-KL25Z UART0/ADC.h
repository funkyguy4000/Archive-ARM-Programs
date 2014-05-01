#include <MKL25Z4.h>

#define ADC_CHANNEL (8)
#define VREF 				(3.3)
#define ADCRANGE 		(0xffff)

void ADC_Init(void){
	
	SIM->SCGC6 |= (1UL << SIM_SCGC6_ADC0_SHIFT);
	
	ADC0->CFG1 = 0x00;
	ADC0->SC2 = 0;
}

unsigned Measure(void) {
	unsigned res = 0;
	 
	 // Write to ADC0_SC1A 
	 //   0 --> AIEN Conversion interrupt diabled
	 //   0 --> DIFF single end conversion 
	 //   01000 --> ADCH, selecting AD8 
   ADC0->SC1[0] = ADC_CHANNEL ; // writing to this clears the COCO flag 
	 
	 // test the conversion complete flag, which is 1 when completed
   while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)); // empty loop
	
   // Read results from ADC0_RA as an unsigned integer	
   res = ADC0->R[0] ; // reading this clears the COCO flag  
	 
   return res ; 
}
	
