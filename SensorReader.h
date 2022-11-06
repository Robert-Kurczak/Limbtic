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
        
        struct sensor{
            char mux;
            char channel;

            sensor(char mux, char channel) : mux(mux), channel(channel){}
        };

        sensor sensorsArray[10] = {
            sensor(1, 1),
            sensor(0, 1),
            sensor(3, 4),
            sensor(2, 4),
            sensor(1, 4),
            sensor(0, 4),
            sensor(3, 0),
            sensor(2, 0),
            sensor(1, 0),
            sensor(0, 0)
        };

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

        void setMuxChannel(int channel){
                MUX_CH_PORTS_STATE &= 0b00000000;
                MUX_CH_PORTS_STATE |= channel;

                delay(5); //propagation time
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

        String getDataPackage(){
            String package = "";

            for(int i = 0; i < 10; i++){
                setMuxChannel(sensorsArray[i].channel);

                char data[64];
                sprintf(data, "%04d", readADC(sensorsArray[i].mux));

                package += data;
                package += ";";
            }

            package += "\n";
            return package;
        }

        // String getReading(int sensorIndex){
        //     setMuxChannel(sensorsArray[sensorIndex].channel);

        //     char data[64];
        //     sprintf(data, "%04d| M%d C%d", readADC(sensorsArray[sensorIndex].mux), sensorsArray[sensorIndex].mux, MUX_CH_PORTS_STATE);

        //     return data;
        // }
};