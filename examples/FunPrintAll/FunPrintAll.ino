#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
#include "SevenSegmentFun.h"

#define SERIAL_BAUD 9600
// define clock and digital input pins (can be any digital pin)
#define PIN_CLK   4
#define PIN_DIO   5

// initialize TM1637 Display object
SevenSegmentFun    display(PIN_CLK, PIN_DIO);


void setup() {
  Serial.begin(SERIAL_BAUD);
};


void loop() {

  // print show vertical level variations
  introDuceNextDemo("AUDIO VOLUME DEMO");
  audioVolume();

  introDuceNextDemo("BOUNCHING BALL DEMO");
  uint16_t numMoves = 100; uint16_t timeDelay = 100;
  display.bouchingBall(numMoves, timeDelay);

  introDuceNextDemo("SCROLLING TEXT DEMO");
  repeats = 2;
  display.scrollingText("ARDUINO TM1637 FUN", repeats);

  introDuceNextDemo("REMEMBER KIT? NIGHTRIDER DEMO");
  uint8_t repeats = 4;
  display.nightrider(repeats);

  introDuceNextDemo("SNAKE DEMO");
  display.snake(repeats);

  introDuceNextDemo("EQUALIZER DEMO");
  equalizer();

  introDuceNextDemo("GET READY FOR THE BOMB");
  uint8_t hours = 5; uint8_t min = 16; uint16_t speed = 10000;
  display.bombTimer(hours, min, speed, " RUN ");
  delay(1000);;
};

// Demo for displaying a vertical level, for example audio volume, battery charge etc.
void audioVolume() {


  for (uint8_t repeats=0; repeats < 2; repeats++) {
    for (uint8_t level=0; level < 125; level+=25) {
      display.printLevelVertical(level);
      delay(200);
    };
    for (uint8_t level=100; level != 0; level-=25) {
      display.printLevelVertical(level);
      delay(200);
    };
  }

    // maybe try another symbol instead of default | |
    uint8_t symbol = display.encode((uint8_t)0);
    bool leftToRight = false;   // print the other direction


    for (uint8_t repeats=0; repeats < 2; repeats++) {
      for (uint8_t level=0; level < 125; level+=25) {
        display.printLevelVertical(level, leftToRight, symbol);
        delay(200);
        if ( level == 100 ) {
          display.blink();
        }
      };
      for (uint8_t level=100; level != 0; level-=25) {
        display.printLevelVertical(level, leftToRight, symbol);
        delay(200);
      };
    }
  // 0, 25, 50, 75, 100

}

void equalizer() {
  // initialize horizontal level counters
    int8_t i,j,k,l;
    uint8_t levels[4];

    // repeat 5 times
    for ( uint8_t r=0; r < 4; r++) {
      // increae i and k, decrease j and l
      for (i=0,j=100,k=0,l=100; i <= 100; i+=33, j-=33, k+=33, l-=33) {
          levels[0] = i; levels[1] = j; levels[2] = k; levels[3] = l;
          display.printLevelHorizontal(levels);
          delay(100);
      }
      // increae j and l, decrease i and k
      for (i=100,j=0,k=100,l=0; i >= 0; i-=33, j+=33, k-=33, l+=33) {
          levels[0] = i; levels[1] = j; levels[2] = k; levels[3] = l;
          display.printLevelHorizontal(levels);
          delay(100);
      }
    }
}

void introDuceNextDemo(char* str) {
  display.print(str);
  delay(500);
}
