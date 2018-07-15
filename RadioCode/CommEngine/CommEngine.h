/*
 * CommEngine.h
 *
 * Created: 7/9/2018 7:00:54 PM
 *  Author: Dominic
 */ 


#ifndef COMMENGINE_H_
#define COMMENGINE_H_

#include <avr/io.h>

struct PinMap {
	// The pins we're using
	uint8_t select_pin, clock_pin, data_pin;
	// We're assuming all the pins share these ports (not universal, but works with my application)
	volatile uint8_t *pin_port_reg, *data_direction_reg;
	};

class CommEngine {
	
	public:
		PinMap display_map, radio_map;
		// Make sure to pass the display map, THEN the radio map
		CommEngine(PinMap display_map, PinMap radio_map);
		void SendByte(uint8_t data_byte, PinMap &device);
		void PinRegHigh(volatile uint8_t *reg, uint8_t pin);
		void PinRegLow(volatile uint8_t *reg, uint8_t pin);
		void SendDisplayByte(uint8_t data_byte) { SendByte(data_byte, display_map); }
};


#endif /* COMMENGINE_H_ */