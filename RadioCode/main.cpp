/*
 * main.cpp
 *
 * Created: 7/9/2018 7:05:12 PM
 *  Author: Dominic
 */ 

#define F_CPU 8000000

//#include "CommEngine/CommEngine.h"
#include "DisplayDriver/DisplayDriver.h"
#include <util/delay.h>

int main(void)
{
	
	PinMap display_map = {PA5, PA2, PA1, &PORTA, &DDRA};
	PinMap radio_map = {PA4, PA2, PA0, &PORTA, &DDRA};
	CommEngine comm = CommEngine{display_map, radio_map};
	// This also configures the display
	DisplayDriver disp = DisplayDriver{&comm};
	
	// The traveling dash
	
	//Turn the display on
	disp.WriteCommand(disp.maxregs.SHUTDOWN, 0x01);
	
	disp.BlankDisplay();
	
	//Make a dash have a journey
	uint8_t space = 0;
	uint8_t prev = 0;
	for (;;) {
		disp.WriteCommand(prev+1, 0x8F);
		disp.WriteCommand(space+1, 0x00);
		prev = space;
		space = (space+1)%8;
		_delay_ms(100);
	}
	
	
}