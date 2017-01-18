#include <Lixie.h>

Lixie lix(1, 13); // 1 digit on pin 13

int counter = 0;

CHSV color = {HUE_RED, 255, 255};

void setup() {
  lix.begin();

  // set foreground color
  lix.foreground = color;
}

void loop() {
  lix.print(counter);
  lix.show();

  if (++counter == 10) {
    // move 1/8th along the color wheel 
    color.hue += 256/8;

    // update foreground color
    lix.foreground = color;

    // reset counter
    counter = 0;
  }
  
  delay(300);
}
