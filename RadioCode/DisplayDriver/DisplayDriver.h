/*
 * DisplayDriver.h
 *
 * Created: 7/14/2018 4:45:05 PM
 *  Author: Dominic
 */ 


#ifndef DISPLAYDRIVER_H_
#define DISPLAYDRIVER_H_

#include "../CommEngine/CommEngine.h"

struct MAX7221 {
	uint8_t NOOP = 0x00;
	uint8_t D0 = 0x01;
	uint8_t D1 = 0x02;
	uint8_t D2 = 0x03;
	uint8_t D3 = 0x04;
	uint8_t D4 = 0x05;
	uint8_t D5 = 0x06;
	uint8_t D6 = 0x07;
	uint8_t D7 = 0x08;
	uint8_t DECMODE = 0x09;
	uint8_t INTENSITY = 0x0A;
	uint8_t SCANLIM = 0x0B;
	uint8_t SHUTDOWN = 0x0C;
	uint8_t DISPTEST = 0x0F;
};

class DisplayDriver {
	
	// A communication engine instance
	CommEngine& comm_inst;
	
	public:
	const MAX7221 maxregs;
	
	const uint8_t font[16] = {
		0b01111110, // 0
		0b00110000, // 1
		0b01101101, // 2
		0b01111001, // 3
		0b00110011, // 4
		0b01011011, // 5
		0b01011111, // 6
		0b01110000, // 7
		0b01111111, // 8
		0b01111011, // 9
		0b01110111, // A
		0b00011111, // b
		0b01001110, // C
		0b00111101, // d
		0b01001111, // E
		0b01000111  // F
	};
	
	DisplayDriver(CommEngine* comm_inst);
	void WriteCommand(uint8_t reg, uint8_t data);
	void BlankDisplay();
	void DisplayHexWord(uint_fast16_t word);
};



#endif /* DISPLAYDRIVER_H_ */