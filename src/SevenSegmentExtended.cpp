#include "SevenSegmentExtended.h"


SevenSegmentExtended::SevenSegmentExtended(uint8_t pinClk, uint8_t pinDIO) :
  SevenSegmentExtended(pinClk, pinDIO)
{ };

void SevenSegmentExtended::printTime(uint16_t t, bool blink) {
  uint8_t hour = t / 100;
  t -= (hour * 100);
  uint8_t min  = t;
  printTime(hour, min, blink);
};

void SevenSegmentExtended::printTime(uint8_t hour, uint8_t min, bool blink) {

  // static bool displayColon = true;
  //
  // if ( blink ) {
  //   displayDots = true;
  // } else {
  //   displayDots = !displayDots;
  // }

  uint8_t buffer[4];

  buffer[0] = encode((hour / 10));
  buffer[1] = encode((hour % 10));
  buffer[2] = encode((min / 10));
  buffer[3] = encode((min % 10));

  printRaw(buffer, 4, 0);

  // if ( blink ) {
  //   buffer[1] &= ( buffer[1] & B01111111 );
  //   delay(TM1637_DEFAULT_BLINK_DELAY);
  //   printRaw( &buffer[1], 1, 1);
  // };

};

// positive counter 0..99, negative counter 0..-9
void SevenSegmentExtended::printDualCounter(int8_t leftCounter, int8_t rightCounter) {

  leftCounter = (leftCounter > 99)?99:leftCounter;
  rightCounter = (rightCounter > 99)?99:rightCounter;

  // get current state
  bool colonOn = getColonOn();
  uint8_t zeroByte[1] = {0};

  setColonOn(true);

  setCursor(0,0);
  print(leftCounter);

  if ( leftCounter < 10 && leftCounter > 0) {
    // to display colon
    printRaw(zeroByte,1,1);
  };

  // clear most left byte if only single digit
  if ( rightCounter < 10 && rightCounter > 0) {
    printRaw(zeroByte,1,2);
    setCursor(0,3);
  } else {
    setCursor(0,2);
  }
  print(rightCounter);

  // set to previous state
  setColonOn(colonOn);
}
