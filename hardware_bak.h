#include <SPI.h>

class hardware{
    public:

        void highState(){

        }

        //Returns struct with 2 bytes,
        //DDR byte, for setting pins Mode
        //PORT byte, for setting pins state
        static registers pinRegs(char port){
            switch(port){
                case 'A':
                    return registers(DDRA, PORTA);
                    break;

                case 'B':
                    return registers(DDRB, PORTB);
                    break;
                
                case 'C':
                    return registers(DDRC, PORTC);
                    break;

                case 'D':
                    return registers(DDRD, PORTD);
                    break;
                
                case 'G':
                    return registers(DDRG, PORTG);
                    break;
                
                case 'L':
                    return registers(DDRL, PORTL);
                    break;
            }
        }
};

//Static MCP3204 with CS pin at PB0
class MCP3204 : public hardware{
    private:
        static const byte Regs[2];
        static const uint8_t CSpin;

    public:

        static void initialize(char port, uint8_t pin){
            Regs.DDR
        }

        static int read(uint8_t channel){
            //digitalWrite(CSpin, LOW);
            PORTB &= ~byte(1 << CSpin);

            //---Transfer---
            //Start byte
            SPI.transfer(0b0000001);
            
            //Channel selector byte
            byte dataP1 = SPI.transfer(byte((1 << 7) | (channel << 4)));
            
            //Don't care byte for retriving rest of data
            byte dataP2 = SPI.transfer(0b00000000);
            //------

            //digitalWrite(CSpin, HIGH);
            PORTB |= byte(1 << CSpin);

            //---Data proccesing---
            dataP1 &= 0b00000011;

            return (dataP1 << 8) | dataP2;
            //------
        }
};

class LED : hardware{
    private:
        const byte reg;
        const uint8_t pin;

    public:
        LED(char port, uint8_t pin) : reg(portRegister(port)), pin(pin){}
};