#include "SevenSegmentTM1637.h"

// define clock and digital input pins (can be any digital pin)
#define PIN_CLK     4
#define PIN_DIO     5

SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

void setup() {
  Serial.begin(9600);
  display.begin();
  display.setPrintDelay(200);
}

void loop() {
  // display.clear();
  // display.print(F(" ON "));
  // delay(2000);
  display.clear();
  char str[] ="HALLO TEST THIS LALA";
  uint8_t buffer[20];
  display.encode(buffer,str,20);
  display.printRaw(buffer, 20);
  delay(2000);
  display.clear();
  display.print(str);Serial.println(str);
  delay(2000);
  display.clear();
  display.print(134, HEX);Serial.println(134, HEX);
  delay(2000);

}
