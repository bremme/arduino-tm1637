/*
	Serial Print example

	Prints what you type to the serial monitor to the display. Make sure to set your serial monitor to line end: NEW LINE!

	The circuit:
  * connect TM1637 pin CLK to Arduino pin D4
  * connect TM1637 pin DIO to Arduino pin D5
  * connect TM1637 pin Vcc to Arduino pin 5V
  * connect TM1637 pin GND to Arduino pin GND

	Created 25 September 2015
	By Bram Harmsen

	http://url/of/online/tutorial.cc

*/


#include "SevenSegmentTM1637.h"

// define clock and digital input pins (can be any digital pin)
const byte PIN_CLK = 4;
const byte PIN_DIO = 5;
const byte BUFFER_SIZE = 128;

// initialize global TM1637 Display object
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);
// initialize global serial buffer
char serialBuffer[BUFFER_SIZE];

// setup loop
void setup() {
  display.begin();
  Serial.begin(9600);
  Serial.println(F("Enter some text followed by ENTER"));
  Serial.println(F("also make sure to set the line ending to newline (\\n)"));
};

// main loop
void loop() {
  // if received new serial data, print to display
  if ( receivedSerialString() ) {
    display.print(serialBuffer);
    Serial.print(F("Echo:\t"));
    Serial.println(serialBuffer);
  };
};

// serial event function
bool receivedSerialString() {
  static unsigned int i=0; // make static counter to keep track of count

  // check if new data arrived
  while( Serial.available() ) {

    // if buffer is full return
    if ( i == BUFFER_SIZE-1) {
      serialBuffer[i] = '\0'; // add termination char
      i = 0;
      Serial.println(F("Buffer full!"));
      return true;
    }
    // read new char from serial port
    char c = Serial.read();

    // if new line return
    if ( c == '\n') {
      serialBuffer[i] = '\0'; // add termination char
      i = 0;
      return true;
    } else {
      serialBuffer[i] = c;
    }
    i++;  // increase counter
  };
};
