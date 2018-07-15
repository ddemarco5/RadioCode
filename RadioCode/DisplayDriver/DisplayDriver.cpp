/*
 * DisplayDriver.cpp
 *
 * Created: 7/14/2018 4:45:57 PM
 *  Author: Dominic
 */ 
#include "DisplayDriver.h"

DisplayDriver::DisplayDriver(CommEngine* comm_inst):
	comm_inst(*comm_inst) {
		// Disable the display test register
		WriteCommand(maxregs.DISPTEST, 0x00);
		
		// Turn the display off
		WriteCommand(maxregs.SHUTDOWN, 0x00);
		
		// Bring display up in decode mode B for all digits
		//WriteCommand(maxregs.DECMODE, 0xFF);
		WriteCommand(maxregs.DECMODE, 0x00);
		
		// Set the scan limit to all 7 segments
		WriteCommand(maxregs.SCANLIM, 0x07);
		
		// Set intensity
		WriteCommand(maxregs.INTENSITY, 0x00);
	}

void DisplayDriver::WriteCommand(uint8_t reg, uint8_t data) {
	// Chip select low
	comm_inst.PinRegLow(comm_inst.display_map.pin_port_reg,comm_inst.display_map.select_pin);
	
	// Write the command register
	comm_inst.SendDisplayByte(reg);
	
	// Write the data
	comm_inst.SendDisplayByte(data);
	
	// Chip select high
	comm_inst.PinRegHigh(comm_inst.display_map.pin_port_reg,comm_inst.display_map.select_pin);
}

void DisplayDriver::BlankDisplay() {
	for (uint8_t i=0;i<8;i++) {
		WriteCommand(i+1,0x00);
	}
}

void DisplayDriver::DisplayHexWord(uint_fast16_t word) {
	for (uint8_t i=4; i>0; i--) {
		WriteCommand(i, font[word & 0x0F]);
		word = word >> 4;
	}
}
