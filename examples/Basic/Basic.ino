#include "SevenSegmentTM1637.h"

// define clock and digital input pins (can be any digital pin)
#define PIN_CLK   4
#define PIN_DIO   5

// initialize global TM1637 Display object
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);


void setup() {
  Serial.begin(9600);
  // display.begin();
  display.setBacklight(100);
  display.command(B01000000);
  uint8_t buffer[3] = {B11000000, 255, 128};
  display.command(buffer,3);
  // display.writeRawBytes(buffer,2,0);

  // uint8_t cmd = B10001111;
  // display.command(cmd);
  // cmd = B01000100;
  // display.command(cmd);
  // cmd = B11000000;
  // uint8_t data= 255;
  // uint8_t b[2] = {cmd, data};
  // display.command(b,2);


  // display.print(F("INIT"));
  delay(1000);
};


void loop() {

  // display.print(F("LOOP"));
  delay(1000);

  // print

}
