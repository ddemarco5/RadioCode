/*
 * main.cpp
 *
 * Created: 7/9/2018 7:05:12 PM
 *  Author: Dominic
 */ 

#define F_CPU 8000000

#include "CommEngine.h"
#include <util/delay.h>

int main(void)
{
	
	PinMap display_map = {PA5, PA2, PA1, &PORTA, &DDRA};
	PinMap radio_map = {PA4, PA2, PA0, &PORTA, &DDRA};
	CommEngine comm = CommEngine{display_map, radio_map};
	
		
	for(uint8_t i = 0; i < 10; i++) {
		_delay_ms(1000);
		//display test mode
		comm.SendByte(0x0F,comm.display_map);
		comm.SendByte(0x0F,comm.display_map);
		
		_delay_ms(1000);
		//shutdown mode
		comm.SendByte(0x0C,comm.display_map);
		comm.SendByte(0x0C,comm.display_map);
		
	}
	
}