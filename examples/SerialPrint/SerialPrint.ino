/* Serial Print example
*
*/

#include "SevenSegmentTM1637.h"

// define clock and digital input pins (can be any digital pin)
#define PIN_CLK     4
#define PIN_DIO     5
#define BUFFER_SIZE 128

// initialize global TM1637 Display object
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);

char str[BUFFER_SIZE];

void setup() {
  Serial.begin(9600);
  display.begin();
};

void loop() {

  if ( serialEvent() ) {
    display.print(str);
  }
}


bool serialEvent() {
  static uint8_t i=0;

  while( Serial.available() ) {

    if ( i == BUFFER_SIZE-1) {
      str[i] = '\0';
      i = 0;
      Serial.println(F("BUFFER FULL"));
      Serial.print(F("ECHO:\t"));
      Serial.println(str);
      return true;
    }

    char c = Serial.read();

    if ( c == '\n') {
      str[i] = '\0';
      i = 0;
      Serial.print(F("ECHO:\t"));
      Serial.println(str);
      return true;
    } else {
      str[i] = c;
    }
    i++;
  };
};
