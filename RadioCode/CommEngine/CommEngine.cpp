/*
 * CommEngine.cpp
 *
 * Created: 7/9/2018 6:51:12 PM
 * Author : Dominic
 *
 * The purpose of this class is to provide a facility to communicate with the MAX7221 display driver AND
 * the SI4734-D60 chips. Due to the platform I'm using for this project (attiny861), program memory will be limited,
 * and this library will be very purpose-built. Though it is only meant to be code to bit-bang 3 wire communication
 * on ports that can be specified. The actual communication logic will be put in different libraries.
 */ 

#define F_CPU 8000000UL  // 8 MHz (we've disabled the clock division fuse)

#include "CommEngine.h"
#include <util/delay.h>



// Constructor
CommEngine::CommEngine(PinMap display_map, PinMap radio_map) {
	this->display_map = display_map;
	this->radio_map = radio_map;
	
	// Clock and select pins will ALWAYS be outputs, so set that here in the constructor
	PinRegHigh(display_map.data_direction_reg, display_map.select_pin);
	PinRegHigh(display_map.data_direction_reg, display_map.clock_pin);
	
	// We also want to make sure that chip select starts high (its default state)
	PinRegHigh(display_map.pin_port_reg,display_map.select_pin);
	
	// Make sure data and clock are low to start
	PinRegLow(display_map.pin_port_reg,display_map.data_pin);
	PinRegLow(display_map.pin_port_reg,display_map.clock_pin);
	
	// Wait a bit just to make sure all the pins are in the correct state
	_delay_us(50);
	
}

void CommEngine::SendByte(uint8_t data_byte, PinMap &device) {
	
	// We're writing data, so set data pin direction to output
	PinRegHigh(device.data_direction_reg,device.data_pin);
	
	
	// Drop chip select to let our chip know we want to talk to it.
	//PinRegLow(device.pin_port_reg,device.select_pin);

	// Delay 5 mics after we drop chip select
	//_delay_us(5);
	
	for (uint8_t i = 0; i < 8; ++i, data_byte <<= 1) {
		
		// Clock low
		PinRegLow(device.pin_port_reg,device.clock_pin);
		
		// Check our shifted bit
		if (data_byte & 0x80) {
			// Write data line high
			PinRegHigh(device.pin_port_reg,device.data_pin);
		}
		else {
			// Write data line low
			PinRegLow(device.pin_port_reg,device.data_pin);
		}
		
		// Clock high
		PinRegHigh(device.pin_port_reg,device.clock_pin);

	}
	
	// Make data and clock lines low again
	PinRegLow(device.pin_port_reg,device.clock_pin);
	PinRegLow(device.pin_port_reg,device.data_pin);
	
	// Wait a bit to ensure clock has gone back down before we set chip select high again
	//_delay_us(5);
	
	// Make chip select high again
	//PinRegHigh(device.pin_port_reg,device.select_pin);
	
	// Set data line back to input
	PinRegLow(device.data_direction_reg,device.data_pin);
}


// These would better be suited to a macro for speed, but we're saving a little bit of size in the compiled
// program this way, and we're not dying for speed in this application. It might get optimized out anyway, and it increases read/understandability
void CommEngine::PinRegHigh(volatile uint8_t *reg, uint8_t pin) {
	*reg |= _BV(pin);
}

void CommEngine::PinRegLow(volatile uint8_t *reg, uint8_t pin) {
	*reg &= ~_BV(pin);
}