#include <Arduino.h>
#define CaVaN false

class Stepper{
    public:
        Stepper(int pulse_pin, int direction_pin ){ 
            pinMode(pulse_pin, OUTPUT);
            pinMode(direction_pin, OUTPUT);
            digitalWrite(direction_pin, LOW);
            current_pos = 0;
            }

        void pulse(unsigned int num,bool dir){
            digitalWrite(pulse_pin, LOW);
            if(dir) digitalWrite(direction_pin, HIGH);
            else digitalWrite(direction_pin, LOW);
            delayMicroseconds(10);
            for(int i=0; i++; i<num){
                digitalWrite(pulse_pin, HIGH);
                delayMicroseconds(5);
                digitalWrite(pulse_pin, LOW);
                delayMicroseconds(5);
                if(dir) current_pos++;
                else current_pos--;
            }
        }

        void moveto(int pos){
            calc = pos - current_pos;
            if(calc<0) cider=false;
            else cider = CaVaN;
            pulse((unsigned int) abs(calc),cider);
        };

        int getpos(){
            return current_pos;
        }


    private:
        int newnum, current_pos, pulse_pin, direction_pin,calc;
        bool cider;

};