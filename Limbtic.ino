#include "hardware.h"

void setup(){
  //---Hardware initalization---
  LED readerLED('L', 0);
  MCP3204 A2D('B', 0);
  MuxArr Mux('L', 1, 2, 3);
  //------

  //---SPI configuration---
  SPI.begin();

  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  //------

  Serial.begin(115200);

  double startTime = micros();

  // for(uint8_t i = 0; i < 4; i++){
  //   for(uint8_t j = 0; j < 8; j++){
  //     Mux.setChannel(j);
  //     Serial.println(A2D.read(i));
  //   }

  //   Serial.println("---");
  // }

  int printedValues = 0;
  for(uint8_t i = 0; i < 8; i++){
    Mux.setChannel(i);

    for(uint8_t j = 0; j < 4; j++){
      Serial.println(A2D.read(j));
      printedValues++;
    }

    if(printedValues == 8){
      Serial.println("---");
      printedValues = 0;
    }
    
  }

  Serial.println(micros() - startTime);

  readerLED.High();
  delay(250);
  readerLED.Low();
}

void loop(){}
