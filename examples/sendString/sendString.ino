/*
 * 작성자 박광렬
 * 날짜 : 2020.3.9
 * 
 * 128*64 GLCD
 * 핀 설정, 문자 보내기, 커서 설정
 */

#include <basicGLCD.h>

basicGLCD GLCD;

void setup() {
  Serial.begin(115200);
  
  GLCD.setDataPins(4,5,6,7,8,9,10,11);
  GLCD.setRSPin(A3);
  GLCD.setCSPins(A0, A1);
  GLCD.setENPin(3);
  GLCD.setRWPin(2);
  GLCD.setRSTPin(A2);
  while(GLCD.init() != 1) {
    Serial.println("You have to set all pins");
    return 0;
  }

  GLCD.setPage(LEFT);

  GLCD.setCursor(0, 0);
  GLCD.sendString("A");
  GLCD.setCursor(1, 1);
  GLCD.sendString("B");
  GLCD.setCursor(0, 2);
  GLCD.sendString("C");
  GLCD.setCursor(7, 2);
  GLCD.sendString("D");

  
}

void loop() {
}
