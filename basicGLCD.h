#ifndef _BASIC_GLCD_H
#define _BASIC_GLCD_H

#ifdef ARDUINO
  #if (ARDUINO >= 100)
  #include <Arduino.h>
  #else
  #include <WProgram.h>
  #include <pins_arduino.h>
  #endif
#endif

#ifdef TARGET_LPC1768
  #include <Arduino.h>
#endif



#define commandDelay  5

#define CMD_SET_HEIGHT 0xB8
#define CMD_SET_WIDTH  0x40
#define CMD_SET_SCROLL  0xC0

#define LEFT  0
#define RIGHT  1

#define LeftToRight 0
#define RightToLeft 1

class basicGLCD {
public:
  basicGLCD(void);

  uint8_t init(void);
  void clear(void);
  void sendString(const String str);
  void sendChar(const char data[6]);
  void setCursor(int x, int y);
  void setPage(const uint8_t page);
  void sendData(const char data);
  void sendCommand(const char command);
  void setRWPin(const uint8_t RW);
  void setENPin(const uint8_t EN);
  void setRSTPin(const uint8_t RST);
  void setCSPins(const uint8_t CS1, const uint8_t CS2);
  void setRSPin(const uint8_t RS);
  void setDataPins(const uint8_t DB[8]);
  void setDataPins(const uint8_t DB0, const uint8_t DB1, const uint8_t DB2, const uint8_t DB3, const uint8_t DB4, const uint8_t DB5, const uint8_t DB6, const uint8_t DB7);
  void setScroll(uint16_t scroll);
  uint16_t scrollPosition(void);
  void setClearDirection(uint8_t);
private:
  uint8_t _DB[8] = {0};
  uint8_t _RS = 0;
  uint8_t _CS1 = 0;
  uint8_t _CS2 = 0;
  uint8_t _RST = 0;
  uint8_t _EN = 0;
  uint8_t _RW = 0;
  uint16_t _scroll = 0;
  uint8_t _clearDirection = LeftToRight;
  void makeAllOutput(void);
};


#endif
