#include "SevenSegmentTM1637.h"
#include "SevenSegmentFun.h"

// define clock and digital input pins
#define PIN_CLK   4
#define PIN_DIO   5

// initialize TM1637 Display objects
SevenSegmentTM1637 TM1637Display(PIN_CLK, PIN_DIO);
SevenSegmentFun    display(TM1637Display);


void setup() {
  // initialize the display
  TM1637Display.begin();
  Serial.begin(9600);
}


void loop() {
//  display.scrollingText("JULIA IS LIEF");
  display.snake(5);
//  display.nightrider();
  display.bombTimer(5,14,1000, "RUN!");
}
