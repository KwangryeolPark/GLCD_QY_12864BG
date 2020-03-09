#include "basicGLCD.h"
#include "charList.h"
extern char charList[][6];

basicGLCD::basicGLCD(void) {

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void basicGLCD::setDataPins(const uint8_t DB0, const uint8_t DB1, const uint8_t DB2, const uint8_t DB3, const uint8_t DB4, const uint8_t DB5, const uint8_t DB6, const uint8_t DB7) {
  _DB[0] = DB0;
  _DB[1] = DB1;
  _DB[2] = DB2;
  _DB[3] = DB3;
  _DB[4] = DB4;
  _DB[5] = DB5;
  _DB[6] = DB6;
  _DB[7] = DB7;
};

void basicGLCD::setDataPins(const uint8_t DB[8]) {
  for(int i = 0; i < 8; i++)
    _DB[i] = DB[i];
};

void basicGLCD::setRSPin(const uint8_t RS) {
  _RS = RS;
};

void basicGLCD::setCSPins(const uint8_t CS1, const uint8_t CS2) {
  _CS1 = CS1;
  _CS2 = CS2;
};

void basicGLCD::setRSTPin(const uint8_t RST) {
  _RST = RST;
};
void basicGLCD::setENPin(const uint8_t EN) {
  _EN = EN;
};
void basicGLCD::setRWPin(const uint8_t RW) {
  _RW = RW;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void basicGLCD::sendCommand(const char command) {
  makeAllOutput();
  for(int i = 0; i < 8; i++) digitalWrite(_DB[i], command & (1 << i));
  digitalWrite(_RS, LOW);
  digitalWrite(_RW, LOW);
  digitalWrite(_EN, HIGH);
  delayMicroseconds(commandDelay);
  digitalWrite(_EN, LOW);
  delayMicroseconds(commandDelay);
};

void basicGLCD::sendData(const char data) {
  makeAllOutput();
  for(int i = 0; i < 8; i++) digitalWrite(_DB[i], data & (1 << i));
  digitalWrite(_RS, HIGH);
  digitalWrite(_RW, LOW);
  digitalWrite(_EN, HIGH);
  delayMicroseconds(commandDelay);
  digitalWrite(_EN, LOW);
  delayMicroseconds(commandDelay);
};

void basicGLCD::setPage(const uint8_t page) {
  switch(page) {
    case LEFT:
      digitalWrite(_CS1, HIGH);
      digitalWrite(_CS2, LOW);
      break;

    case RIGHT:
      digitalWrite(_CS1, LOW);
      digitalWrite(_CS2, HIGH);
      break;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void basicGLCD::setScroll(uint16_t scroll) {
  sendCommand(CMD_SET_SCROLL | (_scroll = scroll));
}
uint16_t basicGLCD::scrollPosition(void) {
  return _scroll;
}
void basicGLCD::setCursor(int x, int y) {
  sendCommand(CMD_SET_HEIGHT | (y)); //x 세로
  sendCommand(CMD_SET_WIDTH | (x * 6)); //y 가로
  sendCommand(CMD_SET_SCROLL | (_scroll)); //z 스크롤 (아래 -> 위로)
};
void basicGLCD::sendChar(const char data[6]) {
  for(int i = 0; i < 6; i++) sendData(data[i]);
};

void basicGLCD::sendString(const String str) {
  char c[str.length() + 1] = {0};
  str.toCharArray(c, sizeof(c) / sizeof(char));
  for(int i = 0; c[i] != 0; i++) sendChar(charList[c[i] - ' ']);
};

void basicGLCD::clear(void) {
  switch(_clearDirection) {
    case LeftToRight:
      setPage(LEFT);
      for(int ii = 0; ii < 8; ii++) {
        for(int i = 0; i < 64; i++) {
          sendCommand(CMD_SET_HEIGHT | (ii));
          sendCommand(CMD_SET_WIDTH | (i));
          sendData(0x00);
        }
      }
      setCursor(0, 0);

      setPage(RIGHT);
      for(int ii = 0; ii < 8; ii++) {
        for(int i = 0; i < 64; i++) {
          sendCommand(CMD_SET_HEIGHT | (ii));
          sendCommand(CMD_SET_WIDTH | (i));
          sendData(0x00);
        }
      }
      setCursor(0, 0);
      break;

    case RightToLeft:
      setPage(RIGHT);
      for(int ii = 0; ii < 8; ii++) {
        for(int i = 63; i >= 0; i--) {
          sendCommand(CMD_SET_HEIGHT | (ii));
          sendCommand(CMD_SET_WIDTH | (i));
          sendData(0x00);
        }
      }
      setCursor(0, 0);

      setPage(LEFT);
      for(int ii = 0; ii < 8; ii++) {
        for(int i = 63; i >= 0; i--) {
          sendCommand(CMD_SET_HEIGHT | (ii));
          sendCommand(CMD_SET_WIDTH | (i));
          sendData(0x00);
        }
      }
      setCursor(0, 0);
      break;
  }
  setPage(LEFT);
};

void basicGLCD::setClearDirection(uint8_t dir) {
  _clearDirection = dir;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t basicGLCD::init(void) {
  uint16_t pinTest = _RS * _CS1 * _CS2 * _EN * _RW;
  for(int i = 0; i < 8; i++) pinTest *= _DB[i];

  if(pinTest == 0) return -1;

  pinMode(_RS, OUTPUT);
  pinMode(_RW, OUTPUT);
  pinMode(_EN, OUTPUT);
  makeAllOutput();
  pinMode(_CS1, OUTPUT);
  pinMode(_CS2, OUTPUT);
  if(_RST != 0) pinMode(_RST, OUTPUT);

  digitalWrite(_CS1, HIGH);
  digitalWrite(_CS2, HIGH);
  if(_RST != 0) digitalWrite(_RST, HIGH);

  setPage(LEFT);
  sendCommand(0x3F);
  setPage(RIGHT);
  sendCommand(0x3F);
  delay(100);
  clear();

  setCursor(0, 0);
  return 1;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void basicGLCD::makeAllOutput(void) {
  for(int i = 0; i < 8; i++) {
    pinMode(_DB[i], OUTPUT);
    digitalWrite(_DB[i], LOW);
  }
};
