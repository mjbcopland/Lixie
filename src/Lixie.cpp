/*
  Lixie.cpp - Library for driving Lixie displays!
  Created by Connor Nishijima, October 26th 2016.
  Released under the GPLv3 license.
*/

#include "Lixie.h" 

Lixie::Lixie(uint8_t numDigits, uint8_t dataPin) : NUM_DIGITS(numDigits), DATA_PIN(dataPin) {}

void Lixie::begin() {
  FastLED.addLeds<WS2812B, dataPin, GRB>(leds, leds.size());
  foreground = CRGB::White;
  background = CRGB::Black;
  clear();
}

void Lixie::clear() {
  // compiler will optimise this?
  // memset(buffer, -1, sizeof(buffer));
  for (auto &i : buffer) i = -1;
}

void Lixie::show() {
  leds = background;

  for (uint8_t i = 0; i < NUM_DIGITS; i++) {
    if (buffer[i] != -1) {
      uint16_t L1 = (i * LEDS_PER_DIGIT) + addresses[buffer[i]];
      uint16_t L2 = L1 + (LEDS_PER_DIGIT / 2);

      leds[L1] = leds[L2] = foreground;
    }
  }

  FastLED.show();
}

byte get_size(uint16_t input){
  byte places = 0;
  uint16_t multiply = 10;
  bool done = false;

  if(input >= 0){
    places++;
  }

  while(done == false){
    if(input >= multiply){
      places++;
      multiply *= 10;
    }
    else{
      done = true;
    }
  }
 
  return places;
}

void Lixie::write_int(float input){
  clear();

  byte places = get_size(input);
  
  for(byte i = 0; i < places; i++){
    while (input >= 10) {
      input = input / 10.0;
    }
	
    uint16_t input_ones = uint16_t(input);
    push_digit(input_ones);
    float input_next = float(input) - input_ones;
    input = (input_next*10.0)+0.0005;
  }

  show();
}

void Lixie::write_digit(byte input, byte index){
  uint16_t start = (index*20);

  for(uint16_t i = start; i < start+20; i++){
	setBit(i,0);
  }
  
  uint16_t L1 = start+addresses[input];
  uint16_t L2 = start+addresses[input] + 10;

  setBit(L1,1);
  setBit(L2,1);
  
  show();
}

// void Lixie::push_digit(byte number) {
size_t Lixie::write(uint8_t c) {
  
  if (NUM_DIGITS > 1) {
    for (uint16_t i = NUM_LEDS - 1; i >= 20; i--) {
      setBit(i,getBit(i - 20));
    }
    for (uint16_t i = 0; i < 20; i++) {
      setBit(i,0);
    }
  }
  else {
    clear();
  }

  uint16_t L1 = addresses[number];
  uint16_t L2 = addresses[number] + 10;

  setBit(L1,1);
  setBit(L2,1);
}

void Lixie::write_string_f(char* input, byte len){
  for(byte i = 0; i < len; i++){
	if(char_is_number(input[i]) == true){
	  push_digit(input[i]-'0');
	}
  }
  show();
}

void Lixie::write_char(char c, size_t index) {
  if (isDigit(c)) write_digit(c-'0', index);
}

void Lixie::print_binary() {
  for (size_t i = 0; i < numLeds; i++) {
    if (i % 20 == 0 && i != 0) Serial.print('\t');
    Serial.print(getBit(i));
  }
  Serial.println();
}