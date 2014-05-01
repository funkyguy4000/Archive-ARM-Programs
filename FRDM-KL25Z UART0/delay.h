#ifndef DELAY_H
#define DELAY_H


void Delay_ms(unsigned int time_del) {
	// delay is about 1 millisecond * time_del
	volatile int t;
	
	while (time_del--) {
		for (t=4800; t>0; t--)
			;
	}
}

#endif
// *******************************ARM University Program Copyright © ARM Ltd 2013*************************************   
