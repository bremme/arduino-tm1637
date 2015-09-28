/* Serial Print example
* Print what ever you type to the serial monitor to the display. Make sure to set your serial monitor to line end: NEW LINE!
*/

#include "SevenSegmentTM1637.h"

// define clock and digital input pins (can be any digital pin)
#define PIN_CLK     4
#define PIN_DIO     5
#define BUFFER_SIZE 128

// initialize global TM1637 Display object
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);
// initialize serial buffer
char str[BUFFER_SIZE];

// setup loop
void setup() {
  Serial.begin(9600);
  display.begin();
};

// main loop
void loop() {
  // if received new serial data, print to display
  if ( serialEvent() ) {
    display.print(str);
  };
};

// serial event function
bool serialEvent() {
  static uint8_t i=0; // make static counter to keep track of count

  // check if new data arrived
  while( Serial.available() ) {

    // if buffer is full return
    if ( i == BUFFER_SIZE-1) {
      str[i] = '\0';
      i = 0;
      Serial.println(F("BUFFER FULL"));
      Serial.print(F("ECHO:\t"));
      Serial.println(str);
      return true;
    }
    // read new char from serial port
    char c = Serial.read();

    // if new line return
    if ( c == '\n') {
      str[i] = '\0';
      i = 0;
      Serial.print(F("ECHO:\t"));
      Serial.println(str);
      return true;
    } else {
      str[i] = c;
    }
    i++;  // increase counter
  };
};
