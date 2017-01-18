/*
  Lixie.h - Library for driving Lixie displays!
  Created by Connor Nishijima, October 26th 2016.
  Released under the GPLv3 license.
*/

#pragma once

#include <Print.h>
#include <FastLED.h>

class Lixie : public Print {
private:
	constexpr size_t  NUM_DIGITS;
	constexpr uint8_t DATA_PIN;

	int8_t buffer[NUM_DIGITS];

	CRGBArray<NUM_DIGITS*LEDS_PER_DIGIT> leds;

	static constexpr uint8_t LEDS_PER_DIGIT = 20;
	static constexpr uint8_t addresses[10] = {3, 4, 2, 0, 8, 6, 5, 7, 9, 1};

public:
	Lixie(uint8_t, uint8_t);

	void begin();
	void clear();

	void write_int(float input);
	void push_digit(byte number);
	void write_digit(byte input, byte index);

	void write_string_f(char* input, byte len);
	void write_char(char input, byte index);

	void show();
	void print_binary();
	
	CRGBArray<numDigits> foreground;
	CRGBArray<numDigits> background;
};
