#include <SPI.h>

//SPI comunication should be manualy initialized in main cpp file.

class hardware{
    private:
        struct pinRegs{
            volatile uint8_t& stateReg;
            volatile uint8_t& dirReg;

            pinRegs(volatile uint8_t& stateReg, volatile uint8_t& dirReg) : stateReg(stateReg), dirReg(dirReg){};
        };

        //Function returns struct with PORT and DDR registers based on given port ID letter
        //Returned registers are used for changing pin state (Low/High) and pin direction (In/Out)
        pinRegs getRegisters(char port){
            switch(port){
                case 'A':
                    return pinRegs(PORTA, DDRA);

                case 'B':
                    return pinRegs(PORTB, DDRB);
                
                case 'C':
                    return pinRegs(PORTC, DDRC);

                case 'D':
                    return pinRegs(PORTD, DDRD);
                
                case 'G':
                    return pinRegs(PORTG, DDRG);

                case 'L':
                    return pinRegs(PORTL, DDRL);
            }
        }

    public:
        pinRegs pinRegisters;
        const uint8_t pin = -1;

        hardware(char port) : pinRegisters(getRegisters(port)){};
        hardware(char port, uint8_t pin) : pinRegisters(getRegisters(port)), pin(pin){};

        //---DDR---
        void setToOut(){
            pinRegisters.dirReg |= byte(1 << pin);
        }
        
        void setToOut(uint8_t pin){
            pinRegisters.dirReg |= byte(1 << pin);
        }

        void setToIn(){
            pinRegisters.dirReg &= ~byte(1 << pin);
        }

        void setToIn(uint8_t pin){
            pinRegisters.dirReg |= byte(1 << pin);
        }
        //------

        //Functions for changing hardware controll pins state
        //Usually it's on/off functionality but sometimes used
        //for such function as SPI CS pin

        //---PORT---
        void High(){          
            pinRegisters.stateReg |= byte(1 << pin);
        }

        void High(uint8_t pin){          
            pinRegisters.stateReg |= byte(1 << pin);
        }

        void Low(){
            pinRegisters.stateReg &= ~byte(1 << pin);
        }

        void Low(uint8_t pin){
            pinRegisters.stateReg &= ~byte(1 << pin);
        }
        //------
};

class LED : public hardware{
    public:
        LED(char port, uint8_t pin) : hardware(port, pin){
            this->setToOut();
        }

        void blink(){
            //Takes signal struct
            //Blinks amount
        }
};

class MCP3204 : public hardware{
    public:
        MCP3204(char port, uint8_t pin) : hardware(port, pin){
            //Out direction of CS pin
            this->setToOut();

            //Inactive CS pin
            this->High();
        }

    int read(char channel){
        //Active low CS pin
        this->Low();

        //---Transfer---
        //Start byte
        SPI.transfer(0b00000110);
        
        //Channel selector byte
        byte dataP1 = SPI.transfer(channel << 6);
        
        //Don't care byte for retriving rest of data
        byte dataP2 = SPI.transfer(0b00000000);
        //------

        //Inactive CS pin
        this->High();

        //---Data proccesing---
        dataP1 &= 0b00001111;

        return (dataP1 << 8) | dataP2;
    //------
    }
};

class MuxArr : public hardware{
    public:
        uint8_t CH0pin;
        uint8_t CH1pin;
        uint8_t CH2pin;

        MuxArr(char port, uint8_t CH0pin, uint8_t CH1pin, uint8_t CH2pin) : hardware(port){
            this->CH0pin = CH0pin;
            this->CH1pin = CH1pin;
            this->CH2pin = CH2pin;

            this->setToOut(CH0pin);
            this->setToOut(CH1pin);
            this->setToOut(CH2pin);
        }

        //Shhhh, don't tell anyone about this.
        void setChannel(uint8_t channel){
            switch(channel){
                case 0:
                    this->Low(CH0pin);
                    this->Low(CH1pin);
                    this->Low(CH2pin);
                    break;
                
                case 1:
                    this->High(CH0pin);
                    this->Low(CH1pin);
                    this->Low(CH2pin);
                    break;

                case 2:
                    this->Low(CH0pin);
                    this->High(CH1pin);
                    this->Low(CH2pin);
                    break;

                case 3:
                    this->High(CH0pin);
                    this->High(CH1pin);
                    this->Low(CH2pin);
                    break;

                case 4:
                    this->Low(CH0pin);
                    this->Low(CH1pin);
                    this->High(CH2pin);
                    break;

                case 5:
                    this->High(CH0pin);
                    this->Low(CH1pin);
                    this->High(CH2pin);
                    break;

                case 6:
                    this->Low(CH0pin);
                    this->High(CH1pin);
                    this->High(CH2pin);
                    break;

                case 7:
                    this->High(CH0pin);
                    this->High(CH1pin);
                    this->High(CH2pin);
                    break;
            }

            //delay(100);
        }
};