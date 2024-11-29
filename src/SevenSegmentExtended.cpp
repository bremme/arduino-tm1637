#include "SevenSegmentExtended.h"


SevenSegmentExtended::SevenSegmentExtended(uint8_t pinClk, uint8_t pinDIO) :
  SevenSegmentTM1637(pinClk, pinDIO)
{ };

void SevenSegmentExtended::printTime(uint16_t t, bool blink, uint16_t blinkDelay) {
  uint8_t hour = min(t / 100, 23);
  uint8_t min  = min(t % 100, 59);
  printTime(hour, min, blink);
};

void SevenSegmentExtended::printTime(uint8_t hour, uint8_t min, bool blink, uint16_t blinkDelay) {

  bool colonWasOn = getColonOn();
  setColonOn(true);

  uint8_t buffer[4];

  buffer[0] = encode(int16_t(hour / 10));
  buffer[1] = encode(int16_t(hour % 10));
  buffer[2] = encode(int16_t(min / 10));
  buffer[3] = encode(int16_t(min % 10));

  printRaw(buffer, 4, 0);

  // turn colon off and on again
  if (blink) {
    delay(blinkDelay);
    setColonOn(false);
    printRaw(buffer[1],1);
    delay(blinkDelay);
    setColonOn(true);
    printRaw(buffer[1],1);
  }

  setColonOn(colonWasOn);

};

void SevenSegmentExtended::printNumber(int16_t number, bool zeroPadding, bool rollOver, bool alignRight) {
  const int16_t maxNumber = 9999;
  const int16_t minNumber = -999;
  int16_t sign = number / abs(number);

  // roll over if rollOver is set to true
  if (rollOver) {
    number = sign * (abs(number) % 10000);
  // limit number by default
  } else {
    number = number > maxNumber?maxNumber:number;
    number = number < minNumber?minNumber:number;
  }

  // clear the display first
  clear();

  // align left is the default behavior, just forward to print
  if (alignRight == false) {
    print(number);
    return;
  }

  if (sign == -1) {
    number *= -1;
    print("-");
  }

  char toPrint[5];
  if (zeroPadding)
    sprintf(toPrint, "%04d", number);
  else
    sprintf(toPrint, "%4d", number);
  print(toPrint);
};

// positive counter 0..99, negative counter 0..-9
void SevenSegmentExtended::printDualCounter(int8_t leftCounter, int8_t rightCounter, bool zeroPadding) {

  int8_t max = 99;
  int8_t min = -9;
  uint8_t zeroByte = encode('0');

  leftCounter = (leftCounter > max)?max:leftCounter;
  leftCounter = (leftCounter < min)?min:leftCounter;
  rightCounter = (rightCounter > max)?max:rightCounter;
  rightCounter = (rightCounter < min)?min:rightCounter;

  bool colonWasOn = getColonOn();     // get current state
  setColonOn(true);                   // turn on the colon
  home();                             // set cursor to zero

  char toPrint[5];
  if (zeroPadding)
    sprintf(toPrint, "%02d%02d", leftCounter, rightCounter);
  else
    sprintf(toPrint, "%-2d%2d", leftCounter, rightCounter);
  print(toPrint);

  // set to previous state
  setColonOn(colonWasOn);
};
