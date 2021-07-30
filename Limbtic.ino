#include "hardware.h"

LED readerLED('L', 0);
MCP3204 A2D('B', 0);
MuxArr Mux('L', 1, 2, 3);

void setup(){
  //---Hardware initalization---
  //------

  //---SPI configuration---
  SPI.begin();

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  //------

  Serial.begin(115200);

  // double startTime = micros();

  // for(uint8_t i = 0; i < 8; i++){
  //   Mux.setChannel(i);

  //   for(uint8_t j = 0; j < 4; j++){
  //     Serial.print(i * 4 + j);
  //     Serial.print(": ");
  //     Serial.println(A2D.read(j));
  //     // A2D.read(j);
  //   }
    
  // }

  // double endTime = micros();

  // Serial.println("--------------------");
  // Serial.print("Czas wykonania: ");
  // Serial.println(endTime - startTime);
  // Serial.println();

  Mux.setChannel(0);

  readerLED.High();
  delay(250);
  readerLED.Low();
}

double sample2Resistance(unsigned sample){
  return 51200.0 * sample / (6301.54 - sample) - 81.38; //Offest due to breadboard wires resistance
}

void loop(){
  //Serial.println(sample2Resistance(A2D.read(0)));
}
