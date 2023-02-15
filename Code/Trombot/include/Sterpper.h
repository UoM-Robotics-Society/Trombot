//This class is written to control an easydriver, the code keeps track of position, however this code is written with belt transmission in mind as such tracking is ot cyclical, so it will take the long way around if you only care about angle 

#include <Arduino.h>
// #define CaVaN false  // the sad remains of my beautiful logic system where CaVaN = false and ~CaVaN = true  


class Stepper{
    public:
        Stepper(int pulse_pin, int direction_pin );
        //Intialiser of the Stepper object, automatically sets the objects internal tracking of position to 0.
        //@param pulse_pin     : arduino pin connected of step/pulse/pul of the driver
        //@param direction_pin : arduino pin connected of direction/dir of the driver

        void pulse(unsigned int num, bool dir);
        //Basic input to driver the stepper. moves a number of steps at max speed
        //@param num : number of steps you want to move as an UNSIGNED INTEGER, use a normal int variable at your own peril
        //@param dir : Diretion of steps as a bool value 0 or 1 the direction orientation depends on the motors wiring so be careful


        void moveto(int pos);
        // Moves the stepper motor to the input position.
        //@param pos : Position you want the stepper to move to.

        int setpos(int pos);
        // assigns current position as input number, useful if your start up position is not where you want 0 to be or to keep position from scaling up and up and up
        //@param pos : input pos
        //not written yet :)

        //Speed control movement to come also :) 

        int getpos();
        // returns the current position of the stepper as an int value

    private:
        int newnum, current_pos, pulse_pin, direction_pin, calc;
        bool direction;

};