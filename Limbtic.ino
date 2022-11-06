#include "SensorReader.h"

sensorReader reader;


void setup(){
    Serial.begin(115200);
    
    //---SPI configuration---
    SPI.begin();
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
    //------
}

void loop(){
    Serial.println(reader.getDataPackage());
}