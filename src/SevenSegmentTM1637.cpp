
#include "SevenSegmentTM1637.h"

const PROGMEM uint8_t asciiMap[96] = {
  TM1637_CHAR_SPACE,
  TM1637_CHAR_EXC,
  TM1637_CHAR_D_QUOTE,
  TM1637_CHAR_POUND,
  TM1637_CHAR_DOLLAR,
  TM1637_CHAR_PERC,
  TM1637_CHAR_AMP,
  TM1637_CHAR_S_QUOTE,
  TM1637_CHAR_L_BRACKET,
  TM1637_CHAR_R_BRACKET,
  TM1637_CHAR_STAR,
  TM1637_CHAR_PLUS,
  TM1637_CHAR_COMMA,
  TM1637_CHAR_MIN,
  TM1637_CHAR_DOT,
  TM1637_CHAR_F_SLASH,
  TM1637_CHAR_0,          // 48 (ASCII)
  TM1637_CHAR_1,
  TM1637_CHAR_2,
  TM1637_CHAR_3,
  TM1637_CHAR_4,
  TM1637_CHAR_5,
  TM1637_CHAR_6,
  TM1637_CHAR_7,
  TM1637_CHAR_8,
  TM1637_CHAR_9,
  TM1637_CHAR_COLON,
  TM1637_CHAR_S_COLON,
  TM1637_CHAR_LESS,
  TM1637_CHAR_EQUAL,
  TM1637_CHAR_GREAT,
  TM1637_CHAR_QUEST,
  TM1637_CHAR_AT,
  TM1637_CHAR_A,          // 65 (ASCII)
  TM1637_CHAR_B,
  TM1637_CHAR_C,
  TM1637_CHAR_D,
  TM1637_CHAR_E,
  TM1637_CHAR_F,
  TM1637_CHAR_G,
  TM1637_CHAR_H,
  TM1637_CHAR_I,
  TM1637_CHAR_J,
  TM1637_CHAR_K,
  TM1637_CHAR_L,
  TM1637_CHAR_M,
  TM1637_CHAR_N,
  TM1637_CHAR_O,
  TM1637_CHAR_P,
  TM1637_CHAR_Q,
  TM1637_CHAR_R,
  TM1637_CHAR_S,
  TM1637_CHAR_T,
  TM1637_CHAR_U,
  TM1637_CHAR_V,
  TM1637_CHAR_W,
  TM1637_CHAR_X,
  TM1637_CHAR_Y,
  TM1637_CHAR_Z,
  TM1637_CHAR_L_S_BRACKET,  // 91 (ASCII)
  TM1637_CHAR_B_SLASH,
  TM1637_CHAR_R_S_BRACKET,
  TM1637_CHAR_A_CIRCUM,
  TM1637_CHAR_UNDERSCORE,
  TM1637_CHAR_A_GRAVE,       // 96 (ASCII)
  TM1637_CHAR_a,
  TM1637_CHAR_b,
  TM1637_CHAR_c,
  TM1637_CHAR_d,
  TM1637_CHAR_e,
  TM1637_CHAR_f,
  TM1637_CHAR_g,
  TM1637_CHAR_h,
  TM1637_CHAR_i,
  TM1637_CHAR_j,
  TM1637_CHAR_k,
  TM1637_CHAR_l,
  TM1637_CHAR_m,
  TM1637_CHAR_n,
  TM1637_CHAR_o,
  TM1637_CHAR_p,
  TM1637_CHAR_q,
  TM1637_CHAR_r,
  TM1637_CHAR_s,
  TM1637_CHAR_t,
  TM1637_CHAR_u,
  TM1637_CHAR_v,
  TM1637_CHAR_w,
  TM1637_CHAR_x,
  TM1637_CHAR_y,
  TM1637_CHAR_z,
  TM1637_CHAR_L_ACCON,  // 123 (ASCII)
  TM1637_CHAR_BAR,
  TM1637_CHAR_R_ACCON,
  TM1637_CHAR_TILDE     // 126 (ASCII)
};


SevenSegmentTM1637::SevenSegmentTM1637(uint8_t pinClk, uint8_t pinDIO) :
  _pinClk(pinClk),
  _pinDIO(pinDIO)
{
  // setup pins
  pinAsOutput(_pinClk);
  pinAsOutput(_pinDIO);
  digitalHigh(_pinClk);
  digitalHigh(_pinDIO);
  // setup defaults
  setCursor(0, TM1637_DEFAULT_CURSOR_POS);
  setPrintDelay(TM1637_DEFAULT_PRINT_DELAY);
  setColonOn(TM1637_DEFAULT_COLON_ON);
  setBacklight(TM1637_DEFAULT_BACKLIGHT);

  // write command SET_DATA   (Command1)
  command(
    TM1637_COM_SET_DATA |
    TM1637_SET_DATA_WRITE |
    TM1637_SET_DATA_A_ADDR |
    TM1537_SET_DATA_M_NORM
  );

  // fill bufer with all On
  // uint8_t allSegmentsOn[4] = {255, 255, 255, 255};
  // memcpy(_printBuffer, allSegmentsOn, 4);

};

// Print API
size_t  SevenSegmentTM1637::write(uint8_t byte) {
  Serial.println("w uint8_t byte");
  Serial.print("cursor:\t"); Serial.println(_cursorPos);
  // if ( _cursorPos < TM1637_MAX_COLOM ) {
  //   _printBuffer[_cursorPos] = encode( (char)byte );
  //   writeRawBytes(&_printBuffer[_cursorPos], 1, _cursorPos);
  // } else {
  //   // set position to max -> stay in else state if more bytes are comming
  //   _cursorPos = TM1637_MAX_COLOM - 1;
  //   shiftLeft(_printBuffer,TM1637_MAX_COLOM);
  //   _printBuffer[_cursorPos] = encode( (char)byte );
  //   writeRawBytes(_printBuffer, TM1637_MAX_COLOM, 0);
  // }
  // _cursorPos++;   // incrase counter

  static uint8_t printBuffer[4] = {0, };

  if ( _cursorPos == _numCols ) {
    shiftLeft(printBuffer, _numCols);
    printBuffer[_cursorPos] = encode( (char)byte );
    printRaw( printBuffer, _numCols, 0);
  };

  if (_cursorPos < _numCols) {
    printBuffer[_cursorPos] = encode( (char)byte );
    printRaw( printBuffer, _cursorPos+1, 0);
    setCursor(1, _cursorPos + 1);
  };

}

// null terminated char array
size_t  SevenSegmentTM1637::write(const char* str) {
  Serial.println("w const char*");
  // size_t l = encode(_printBuffer, str, TM1637_PRINT_BUFFER_SIZE);
  // writeRawBytes(_printBuffer, l, _cursorPos);
  uint8_t encodedBytes[4];

  encode(encodedBytes, str, 4);
  uint8_t i =4;
  while( str[i] != '\0' ) {
    printRaw(encodedBytes);
    shiftLeft(encodedBytes, 4);
    encodedBytes[3] = encode( str[i] );
    i++;
    if ( i == TM1637_MAX_CHARS) {
      break;
    }
  }



};

// byte array with length
size_t  SevenSegmentTM1637::write(const uint8_t* buffer, size_t size) {
  Serial.println("w const uint8_t* buffer, size_t size");
  // if ( size > TM1637_PRINT_BUFFER_SIZE ) {
  //   size = TM1637_PRINT_BUFFER_SIZE;
  // }
  // for (uint8_t i=0; i < size; i++) {
  //   _printBuffer[i] = encode( (char)buffer[i] );
  // };
  //
  // writeRawBytes(_printBuffer, (uint8_t)size, _cursorPos);


  // uint8_t encodedBytes[4];
  // encode(encodedBytes, buffer, 4);
  //
  // for (uint8_t i=4; i < size; i++) {
  //   printRaw(encodedBytes);
  //   shiftLeft(encodedBytes, 4);
  //   encodedBytes[3] = encode(buffer[i]);
  //   delay(_printDelay);
  // };

  uint8_t encodedBytes[TM1637_MAX_CHARS];
  if ( size > TM1637_MAX_CHARS) {
    size = TM1637_MAX_CHARS;
  }
  size_t length = encode(encodedBytes, buffer, size);
  printRaw(encodedBytes,length);

  // for (uint8_t i=4; i < size; i++) {
  //   printRaw(encodedBytes);
  //   shiftLeft(encodedBytes, 4);
  //   encodedBytes[3] = encode(buffer[i]);
  //   delay(_printDelay);
  // };
  //
  // TM1637_MAX_CHARS

};

void  SevenSegmentTM1637::printRaw(uint8_t rawByte, uint8_t position) {
  uint8_t cmd[2];
  cmd[0] = TM1637_COM_SET_ADR | position;
  cmd[1] = rawByte;
  command(cmd, 2);
};

void  SevenSegmentTM1637::printRaw(const uint8_t* rawBytes, size_t length, uint8_t position) {

  // if fits on display
  if ( (length + position) <= _numCols) {
    uint8_t cmd[5] = {0, };
    cmd[0] = TM1637_COM_SET_ADR | (position & B111);  // sets address
    memcpy(&cmd[position+1], rawBytes, length);       // copy bytes
    cmd[2] |= (_colonBit)?TM1637_COLON_BIT:0;         // set colon bit
    command(cmd, length+1);                           // send to display
  }
  // does not fit on display, need to print with delay
  else {
    // First print 1-4 characters
    uint8_t numtoPrint = _numCols - position;
    printRaw(rawBytes, numtoPrint, position);
    delay(_printDelay);

    uint8_t remaining = length - numtoPrint + 3;
    uint8_t i         = 1;
    while( remaining >= _numCols) {
      printRaw(&rawBytes[i], _numCols, 0);
      delay(_printDelay);
      remaining--;
      i++;
    };
  }

};

void  SevenSegmentTM1637::writeRawBytes(const uint8_t* rawBytes, uint8_t length, uint8_t position) {

  static bool longFlag = false;

  // if writing more than 4 bytes
  if ( length > 4 ) {
    uint8_t remaining = length;
    uint8_t i=0;
    longFlag = true;
    while ( remaining > 4) {
      writeRawBytes( &rawBytes[i], 4, 0);
      delay(_printDelay);
      remaining -= 1;
      i++;
    };
    // renter this function with only 4 bytes
    writeRawBytes( &rawBytes[i], 4, 0);

    longFlag = false;
    return;   // where done return
  };

  uint8_t addr =     TM1637_COM_SET_ADR; //| (position & B111);

  uint8_t buffer[length+1];
  buffer[0] = addr;
  for (uint8_t i=0; i < length; i++) {
    buffer[i+1] = rawBytes[i];
  }
  command(buffer, length+1);

  // // Write command SET_ADDR       (Command2)
  // i2cStart();
  // i2cWriteByte(
  //   TM1637_COM_SET_ADR |
  //   (position & B111)
  // );
  // i2cAck();
  // TM1637_DEBUG_PRINT(F("Write SET_ADDR:\t")); TM1637_DEBUG_PRINTLN((
  //   TM1637_COM_SET_ADR |
  //   (position & B111)
  // ), BIN);

  // Write DATA                   (DATA1..DATAN)
  // for( uint8_t i=0; i < length; i++ ) {
  //   i2cWriteByte( rawBytes[i] | _colonBit );
  //   i2cAck();
  //   TM1637_DEBUG_PRINT(F("Write DATA:\t")); TM1637_DEBUG_PRINTLN( rawBytes[i], BIN);
  // };
  // i2cStop();

  // Write command SET_DISPLAY    (Command3)
  // i2cStart();
  // i2cWriteByte(
  //   TM1637_COM_SET_DISPLAY |
  //   ( _displayCmd & B00001111)
  // );
  // i2cAck();
  // i2cStop();

}

// Liquid cristal API
void SevenSegmentTM1637::begin(uint8_t cols, uint8_t rows) {
  _numCols = cols;
  _numRows = rows;
  clear();
  print(F(" ON "));
  delay(TM1637_BEGIN_DELAY);
  blink();
  clear();
};

void SevenSegmentTM1637::init(uint8_t cols, uint8_t rows) {
  begin(cols, rows);
}

void SevenSegmentTM1637::clear(void) {
  uint8_t rawBytes[4] = {0,0,0,0};
  printRaw(rawBytes);
  home();
};

void SevenSegmentTM1637::home(void) {
  setCursor(0, 0);
};

void SevenSegmentTM1637::setCursor(uint8_t row, uint8_t col) {
  col = (col > TM1637_MAX_COLOM -1)?TM1637_MAX_COLOM-1:col;
  _cursorPos = col;

};

void SevenSegmentTM1637::setBacklight(uint8_t value) {
  value = (value    > 100 )?100:value;  // 0..100 brightness
  value /= 10;                          // 0..10
  value = (value > 8   )?  8:value;     // only 8 levels and off
  uint8_t cmd = TM1637_COM_SET_DISPLAY;;
  switch ( value ) {
    case 0:
      cmd |= TM1637_SET_DISPLAY_OFF;
      break;
    case 1:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_1;
      break;
    case 2:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_2;
      break;
    case 3:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_4;
      break;
    case 4:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_10;
      break;
    case 5:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_11;
      break;
    case 6:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_12;
      break;
    case 7:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_13;
      break;
    case 8:
      cmd |= TM1637_SET_DISPLAY_ON | TM1637_SET_DISPLAY_14;
      break;
    };
    bool ack = command(cmd);
    TM1637_DEBUG_PRINT(F("SET_DISPLAY:\t")); TM1637_DEBUG_PRINTLN((
      cmd
    ), BIN);
    TM1637_DEBUG_PRINT(F("Acknowledged:\t")); TM1637_DEBUG_PRINTLN(ack);
};

void SevenSegmentTM1637::setContrast(uint8_t value) {
  setBacklight(value);
}

void SevenSegmentTM1637::on(void) {
  setBacklight(TM1637_DEFAULT_BACKLIGHT);
};

void SevenSegmentTM1637::off(void) {
  setBacklight(0);
  clear();
};

// SevenSegmentTM1637 public methods
void SevenSegmentTM1637::printTime(uint8_t hour, uint8_t min, bool blink) {

  static bool displayDots = true;

  if ( blink ) {
    displayDots = true;
  } else {
    displayDots = !displayDots;
  }

  _printBuffer[0] = encode(uint8_t(hour / 10));
  _printBuffer[1] = (displayDots)?(encode( uint8_t(hour % 10)) | TM1637_COLON_BIT):encode(uint8_t(hour % 10));
  _printBuffer[2] = encode(uint8_t(min / 10));
  _printBuffer[3] = encode(uint8_t(min % 10));
  writeRawBytes(_printBuffer, 4, 0);

  if ( blink ) {
    _printBuffer[1] &= ( _printBuffer[1] & B01111111 );
    delay(TM1637_DEFAULT_BLINK_DELAY);
    writeRawBytes( &_printBuffer[1], 1, 1);
  };

};

void SevenSegmentTM1637::printTime(uint16_t t, bool blink) {
  uint8_t hour = t / 100;
  t -= (hour * 100);
  uint8_t min  = t;
  printTime(hour, min);
};

// positive counter 0..99, negative counter 0..-9
void SevenSegmentTM1637::printDualCounter(int8_t leftCounter, int8_t rightCounter) {

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
    writeRawBytes(zeroByte,1,1);
  };

  // clear most left byte if only single digit
  if ( rightCounter < 10 && rightCounter > 0) {
    writeRawBytes(zeroByte,1,2);
    setCursor(0,3);
  } else {
    setCursor(0,2);
  }
  print(rightCounter);

  // set to previous state
  setColonOn(colonOn);
}

void  SevenSegmentTM1637::blink(uint8_t blinkDelay, uint8_t repeats) {
  for (uint8_t i=0; i < repeats; i++) {
    setBacklight(0);                    // turn backlight off
    delay(blinkDelay);
    setBacklight(100);
    delay(blinkDelay);
  }
}

void  SevenSegmentTM1637::setPrintDelay(uint16_t printDelay) {
  _printDelay = printDelay;
};

bool  SevenSegmentTM1637::getColonOn(void) {
  return ( _colonBit > 0 );
};

void  SevenSegmentTM1637::setColonOn(bool setToOn) {
  if (setToOn) {
    _colonBit = TM1637_COLON_BIT;
  } else {
    _colonBit = 0;
  }
}

// Helpers
uint8_t SevenSegmentTM1637::encode(char c) {
  if ( c < ' ') { // 32 (ASCII)
    return 0;
  }
  return pgm_read_byte_near(asciiMap + c - ' ');
};

uint8_t SevenSegmentTM1637::encode(int16_t d) {
  // can only encode single digit
  if ( d > 9 || d < 0) {
    return 0;
  };
  return pgm_read_byte_near(asciiMap + d + '0' - ' ');
};

size_t  SevenSegmentTM1637::encode(uint8_t* buffer, const char* str, size_t bufferSize) {
  size_t i;

  for (i=0; i < bufferSize; i++) {
    if (str[i] == '\0' ) {
      return i;
    }
    buffer[i] = encode( str[i] );
  };
  return i;
}

size_t  SevenSegmentTM1637::encode(uint8_t* buffer, const uint8_t* byteArr, size_t arrSize) {
  size_t i;

  for (i=0; i < arrSize; i++) {
    buffer[i] = encode( (char)byteArr[i] );
  };
  return i;
}

void    SevenSegmentTM1637::shiftLeft(uint8_t* buffer, size_t length) {
  for (uint8_t i=0; i < length ; i++) {
    buffer[i] = buffer[i+1];
  }
}

// SevenSegmentTM1637 LOW LEVEL
bool    SevenSegmentTM1637::command(uint8_t cmd) const{
  i2cStart();
  i2cWriteByte(cmd);
  bool acknowledged = i2cAck();
  i2cStop();
  return acknowledged;
};

bool    SevenSegmentTM1637::command(const uint8_t* command, uint8_t length) const {
  bool acknowledged = true;
  i2cStart();
  for (uint8_t i=0; i < length;i++) {
    i2cWriteByte(command[i]);
    acknowledged &= i2cAck();
  };
  i2cStop();
  return acknowledged;
};

uint8_t SevenSegmentTM1637::i2cReadByte(void) const {
  uint8_t readKey = 0;

  i2cStart();
  i2cWriteByte(TM1637_COM_SET_DATA | TM1637_SET_DATA_READ);
  i2cAck();

  pinAsInput(_pinDIO);
  digitalHigh(_pinDIO);
  delayMicroseconds(5);

  for ( uint8_t i=0; i < 8; i++) {

    readKey >>= 1;
    digitalLow(_pinClk);
    delayMicroseconds(30);

    digitalHigh(_pinClk);

    if ( isHigh(_pinDIO) ) {
      readKey = readKey | B1000000;
    };

    delayMicroseconds(30);


  };
  pinAsOutput(_pinDIO);
  i2cAck();
  i2cStop();
  return readKey;
};

void    SevenSegmentTM1637::i2cWriteByte(uint8_t command) const{
  i2cWriteByte(_pinClk, _pinDIO, command);
};

void    SevenSegmentTM1637::i2cWriteByte(uint8_t pinClk, uint8_t pinDIO, uint8_t command) {
  // CLK in bits
  for ( uint8_t i=0; i < 8; i++) {
    digitalLow(pinClk);   // CLK LOW

    if ( command & B1) {
      digitalHigh(pinDIO);// DIO HIGH
    } else {
      digitalLow(pinDIO); // DIO LOW
    }
    delayMicroseconds(TM1637_CLK_DELAY_US);

    command >>= 1;

    digitalHigh(pinClk);   // CLK HIGH
    delayMicroseconds(TM1637_CLK_DELAY_US);
  };
}

void    SevenSegmentTM1637::i2cStart(void) const {
  i2cStart(_pinClk, _pinDIO);
};

void    SevenSegmentTM1637::i2cStart(uint8_t pinClk, uint8_t pinDIO) {
  digitalHigh(pinDIO);   // DIO HIGH
  digitalHigh(pinClk);   // CLK HIGH
  delayMicroseconds(TM1637_CLK_DELAY_US);

  digitalLow(pinDIO);    // DIO  LOW
}


void    SevenSegmentTM1637::i2cStop(void) const {
  i2cStop(_pinClk, _pinDIO);
};

void    SevenSegmentTM1637::i2cStop(uint8_t pinClk, uint8_t pinDIO) {
  digitalLow(pinClk);   // CLK LOW
  delayMicroseconds(TM1637_CLK_DELAY_US);

  digitalLow(pinDIO);    // DIO LOW
  delayMicroseconds(TM1637_CLK_DELAY_US);

  digitalHigh(pinClk);   // CLK HIGH
  delayMicroseconds(TM1637_CLK_DELAY_US);

  digitalHigh(pinDIO);   // DIO HIGH
}

bool    SevenSegmentTM1637::i2cAck(void) const {
  i2cAck(_pinClk, _pinDIO);
};

bool  SevenSegmentTM1637::i2cAck(uint8_t pinClk, uint8_t pinDIO) {
  bool acknowledged = false;

  digitalLow(pinClk);          // CLK  LOW
  pinAsInputPullUp(pinDIO);    // DIO INPUT PULLUP (state==HIGH)
  delayMicroseconds(TM1637_CLK_DELAY_US);

  acknowledged = isLow(pinDIO);// Ack should pull the pin low again

  digitalHigh(pinClk);         // CLK HIGH
  delayMicroseconds(TM1637_CLK_DELAY_US);

  digitalLow(pinClk);          // CLK  LOW
  pinAsOutput(pinDIO);

  return acknowledged;
}
