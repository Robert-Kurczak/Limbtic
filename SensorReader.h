#include <SPI.h>

//D53
#define CS_PORT_DIR DDRB
#define CS_PORT_STATE PORTB
#define CS_PIN 0

//D46
#define LED_PORT_DIR DDRL
#define LED_PORT_STATE PORTL
#define LED_PIN 3

//CH_A = L0
//CH_B = L1
//CH_C = L2
#define MUX_CH_PORTS_DIR DDRL
#define MUX_CH_PORTS_STATE PORTL

class sensorReader{
    private:
        //Channel from 0 to 3
        int readADC(char channel){
            //CS low
            CS_PORT_STATE &= ~byte(1 << CS_PIN);

            byte channelBytes[4] = {0b10010100, 0b11010100, 0b10100100, 0b11100100};

            //---Transfer---
            //Start byte
            SPI.transfer(channelBytes[channel]);

            //Don't care bytes for retriving data
            byte dataP1 = SPI.transfer(0b00000000);
            byte dataP2 = SPI.transfer(0b00000000);

            //CS high
            CS_PORT_STATE |= byte(1 << CS_PIN);
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
                MUX_CH_PORTS_STATE &= 0b11111000;
                MUX_CH_PORTS_STATE |= channel;
        }


    public:
        sensorReader(){
            //Setting mux channel selectors as output
            MUX_CH_PORTS_DIR |= 0b00000111;

            //Setting ADC CS pin as output
            CS_PORT_DIR |= byte(1 << CS_PIN);

            //Setting ADC CS pin high be default (not listening)
            CS_PORT_STATE |= byte(1 << CS_PIN);
        }

        void read(){
            for(int i = 0; i < 8; i++){
                setMuxChannel(i);

                for(int j = 0; j < 4; j++){
                    Serial.print("Mux: ");
                    Serial.print(j);
                    Serial.print(" | Channel: ");
                    Serial.print(i);
                    Serial.print(" | Value: ");
                    Serial.println(readADC(j));
                }
            }
        }

        String getDataPackage(){
            String package = "";

            for(int i = 0; i < 3; i++){
                setMuxChannel(i);

                for(int j = 0; j < 4; j++){
                    char data[64];

                    sprintf(data, "%04d", readADC(j));

                    // Serial.println(readADC(j));
                    
                    package += data;
                    package += ";";
                }
            }

            return package;
        }
};