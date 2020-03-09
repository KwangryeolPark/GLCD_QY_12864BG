/*
 * 작성자 박광렬
 * 날짜 : 2020.3.9
 * 
 * 128*64 GLCD
 * 핀 설정
 */

#include <basicGLCD.h>

basicGLCD GLCD;
const uint8_t DB[8] = {4, 5, 6, 7, 8, 9, 10, 11};
void setup() {
  Serial.begin(115200);
  
  GLCD.setDataPins(DB);
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
