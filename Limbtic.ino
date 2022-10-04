#include "SensorReader.h"

sensorReader reader;


void setup(){
    Serial.begin(115200);
    
    //---SPI configuration---
    SPI.begin();
    SPI.beginTransaction(SPISettings(16000000, MSBFIRST, SPI_MODE0));
    //------

    
    // reader.getDataPackage();
    // reader.read();
    // Serial.println(reader.getDataPackage());
}

void loop(){
    Serial.println(reader.getDataPackage());
    Serial.println("\n");
    delay(200);
}