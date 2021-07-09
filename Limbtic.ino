#include "hardware.h"

void setup(){
  Serial.begin(115200);

  LED testLED(PORTH, 5);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
