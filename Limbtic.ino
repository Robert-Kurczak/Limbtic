#include "SensorReader.h"

void setup(){
    Serial.begin(115200);
    
    //---SPI configuration---
    SPI.begin();
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
    //------

    sensorReader reader;
    reader.read();
}

void loop(){
    
}