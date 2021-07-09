#include <SPI.h>

class hardware{
    public:
        //Reference to register, where PXpin lays
        volatile uint8_t& PORTreg;

        uint8_t PXpin;

        hardware(volatile uint8_t &PORTreg, uint8_t PXpin) : PORTreg(PORTreg), PXpin(PXpin){}

        //Functions for changing hardware controll pins state
        //Usually it's on/off functionality but sometimes used
        //for such function as SPI CS pin
        void on(){          
            PORTreg |= byte(1 << PXpin);
        }

        void off(){
            PORTreg &= ~byte(1 << PXpin);
        }
};

class LED : public hardware{
    public:
        LED(volatile uint8_t &PORTreg, uint8_t PXpin) : hardware(PORTreg, PXpin){}

        void blink(){
            //Takes signal struct
            //Blinks amount
        }
};


//Only one ADC in circuit, therefore it's static class. 
//CS pin configuration is hardcoded here. Yeah, I know.
class MCP3204 : public hardware{

};
