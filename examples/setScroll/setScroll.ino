/*
   작성자 박광렬
   날짜 : 2020.3.9

   128*64 GLCD
   setScroll
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
  while (GLCD.init() != 1) {
    Serial.println("You have to set all pins");
    return 0;
  }

  for (uint16_t i = 0; i < 64; i++) {
    GLCD.setPage(LEFT);
    GLCD.setScroll(i);
    GLCD.setCursor(0, 0);
    GLCD.sendString("A");

    Serial.print("LEFT : ");
    Serial.print(GLCD.scrollPosition());

    GLCD.setPage(RIGHT);
    GLCD.setScroll(i / 2);
    GLCD.setCursor(0, 0);
    GLCD.sendString("B");
    
    Serial.print("\t\tRight : ");
    Serial.println(GLCD.scrollPosition());
    delay(1000);
  }
}

void loop() {
}
