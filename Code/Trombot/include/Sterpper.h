#include <Arduino.h>
// #define CaVaN false  // the sad remains of my beautiful logic system where CaVaN = false and ~CaVaN = true  

class Stepper{
    public:
        Stepper(int pulse_pin, int direction_pin );

        void pulse(unsigned int num, bool dir);

        void moveto(int pos);

        int getpos();

    private:
        int newnum, current_pos, pulse_pin, direction_pin, calc;
        bool direction;

};