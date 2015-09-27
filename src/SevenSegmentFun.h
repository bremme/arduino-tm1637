#ifndef SevenSegmentFun_H
#define SevenSegmentFun_H

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include "SevenSegmentTM1637.h"


#define  TM1637_SNAKE_DEFAULT_DELAY         50
#define  TM1637_BOUNCH_BALL_DEFAULT_DELAY   100
#define  TM1637_NIGHTRIDER_DEFAULT_DELAY    200
//
//        A
//       ---
//  * F |   | B
// X     -G-
//  * E |   | C
//       ---
//        D
// X defines the colon (dots) and only applies to byte 1 (second from left)
//                BXGFEDCBA

#define TM1637_CHAR_VERT_LEVEL     B00110110  // | |

#define TM1637_CHAR_HOR_LEVEL_0    B00000000  //
#define TM1637_CHAR_HOR_LEVEL_1    B00001000  // _
#define TM1637_CHAR_HOR_LEVEL_2    B01001000  // _
#define TM1637_CHAR_HOR_LEVEL_3    B01001001

#define TM1637_CHAR_SNAKE_0        B00000001
#define TM1637_CHAR_SNAKE_1        B00000010
#define TM1637_CHAR_SNAKE_2        B00000100
#define TM1637_CHAR_SNAKE_3        B00001000
#define TM1637_CHAR_SNAKE_4        B00010000
#define TM1637_CHAR_SNAKE_5        B00100000

#define TM1637_CHAR_BALL_HIGH      B01100011
#define TM1637_CHAR_BALL_LOW       B01011100

class SevenSegmentFun : public SevenSegmentTM1637 {
  public:
    SevenSegmentFun(uint8_t pinClk, uint8_t pinDIO);
    void printLevelVertical(uint8_t level, bool leftToRight = true, uint8_t symbol = TM1637_CHAR_VERT_LEVEL);
    void printLevelHorizontal(uint8_t levels[4]);
    void scrollingText(const char* str, uint8_t repeats);
    void snake(uint8_t repeats = 1, uint16_t d = TM1637_SNAKE_DEFAULT_DELAY);
    void nightrider(uint8_t repeats = 10, uint16_t d = TM1637_NIGHTRIDER_DEFAULT_DELAY, uint8_t symbol = TM1637_CHAR_VERT_LEVEL);
    void bombTimer(uint8_t hours, uint8_t min, uint16_t speed = 60);
    void bombTimer(uint8_t hours, uint8_t min, uint16_t speed, char* str);
    void bouchingBall(uint16_t moves, uint16_t d, bool runForever = false);

    void printBall(const int8_t x, const int8_t y);
    void print4Bit( const uint8_t x, const uint8_t y, uint8_t symbol);

  private:
};

#endif
