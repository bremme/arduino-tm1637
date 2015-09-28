#include "SevenSegmentTM1637.h"

// define clock and digital input pins (can be any digital pin)
#define PIN_CLK   4
#define PIN_DIO   5

// initialize global TM1637 Display object
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);


void setup() {
  Serial.begin(9600);
  display.begin();
  display.setBacklight(100);
  display.print("INIT");
  delay(1000);
};


void loop() {
  display.print("LOOP");
  delay(1000);
  display.print("COUNTING SOME DIGITS");
  display.clear();
  for (uint8_t i=0; i < 100; i++) {
    display.print(i);
    delay(100);
  };
  display.clear();
  display.print("SUCC");
  display.blink();
  delay(1000);

}
