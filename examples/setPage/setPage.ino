/*
 * 작성자 박광렬
 * 날짜 : 2020.3.9
 * 
 * 128*64 GLCD
 * 핀 설정, 페이지 설정, 글자 지우기
 * 
 * 커서는 페이지마다 따로 설정해야한다.
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
  GLCD.setCursor(2, 0);


  GLCD.setPage(RIGHT);
  GLCD.setCursor(0, 0);
  GLCD.sendString("B");


  GLCD.setPage(LEFT);
  GLCD.sendString("C");
  
}

void loop() {
}
