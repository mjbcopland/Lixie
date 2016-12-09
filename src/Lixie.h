/*
  Lixie.h - Library for driving Lixie displays!
  Created by Connor Nishijima, October 26th 2016.
  Released under the GPLv3 license.
*/

#ifndef lixie_h
#define lixie_h

#include "Arduino.h"
#include "FastLED.h"

#define write_string(input) write_string_f(input, sizeof(input)-1);

class Lixie
{
public:
	void begin();
	void clear();

	void write_int(float input);
	void push_digit(byte number);
	void write_digit(byte input, byte index);

	void write_string_f(char* input, byte len);
	void write_char(char input, byte index);

	void show();
	void print_binary();
	
	void color_on(const CRGB &color);
	void color_on(const CRGB &color, size_t index);

	void color_off(const CRGB &color);
	void color_off(const CRGB &color, size_t index);
};

#endif
