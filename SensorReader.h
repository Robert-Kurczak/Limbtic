#include <SPI.h>

#define CS 35
#define CS_port PORTB
#define CS_pin 0
#define LED 46
//CH_A = L0
//CH_B = L1
//CH_C = L2

class sensorReader{
    private:
        int readADC(char channel){
            //CS low
            CS_port &= ~byte(1 << CS_pin);

            byte channelBytes[4] = {0b10010100, 0b11010100, 0b10100100, 0b11100100};

            //---Transfer---
            //Start byte
            SPI.transfer(channelBytes[channel]);

            //Don't care bytes for retriving data
            byte dataP1 = SPI.transfer(0b00000000);
            byte dataP2 = SPI.transfer(0b00000000);

            //CS high
            CS_port |= byte(1 << CS_pin);
            //------

            //---Data processing---
            int resultInt = dataP1;
            resultInt = resultInt << 8;
            resultInt = resultInt | dataP2;
            resultInt = resultInt >> 3;
            //------

            return resultInt;
        }

        void setMuxChannel(char channel){
                PORTL &= 0b11111000;
                PORTL |= channel;
        }


    public:
        sensorReader(){
            pinMode(49, OUTPUT);
            pinMode(48, OUTPUT);
            pinMode(47, OUTPUT);

            pinMode(CS, OUTPUT);
            digitalWrite(CS, HIGH);
        }

        void read(){
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 8; j++){
                    setMuxChannel(j);
                    
                    Serial.print("Mux: ");
                    Serial.print(i);
                    Serial.print(" | Channel: ");
                    Serial.print(j);
                    Serial.print(" | Value: ");
                    Serial.println(readADC(i));
                }
            }
        }
};