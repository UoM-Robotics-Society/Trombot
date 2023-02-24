//This class is written to control an easydriver, the code keeps track of position, however this code is written with belt transmission in mind as such tracking is ot cyclical, so it will take the long way around if you only care about angle 

#include <Arduino.h>
// #define CaVaN false  // the sad remains of my beautiful logic system where CaVaN = false and ~CaVaN = true  

enum resolution {full = 1, half= 2, quarter = 4, eighth = 8};


class Stepper{
    public:
        Stepper(int pulse_pin, int direction_pin, int microstep1_pin, int microstep2_pin);
        //Intialiser of the Stepper object, automatically sets the objects internal tracking of position to 0.
        //@param pulse_pin     : arduino pin connected of step/pulse/pul of the driver
        //@param direction_pin : arduino pin connected of direction/dir of the driver

        void move(double error, bool dir, resolution resolution, unsigned int period);
        //Basic input to drive the stepper. moves a number of steps then microsteps. if not within resolution it will move the closest amount of steps that is capable below the inputted number  
        //@param num : number of steps you want to move as a double where 1.0 is a full step
        //@param dir : Diretion of steps as a bool value 0 (forward) or 1 (backward) the physical direction orientation depends on the motors wiring so be careful
        //@param resolution : enum input of the available resolutions of microstepping ("full", "half", "quarter" and "eigth")
        //@param period: time between steps in microseconds, if no value is input this value defaults to 5 microseconds. This has a software lower limit of 1 microsecond

        void moveto(double pos, unsigned int period);
        // Moves the stepper motor to the input position, moving using the move function (fullsteps then micro steps).
        //@param pos : Position you want the stepper to move to.
        //@param period: time between steps in microseconds, if no value is input this value defaults to 5 microseconds. This has a software lower limit of 1 microsecond

        void setpos(double pos);
        //assigns current position as input number, useful if your start up position is not where you want 0 to be or to keep position from scaling up and up and up
        //@param pos : input position
        

        void glide(unsigned int sub_steps, bool dir, resolution resolution, double speed);
        //"Glides" the stepper from one point to another at a constant speed and step size
        //@param sub_steps : number of (micro)steps to move 
        //@param dir : direction as 0 forward and 1 backward
        

        void glideto(double pos, resolution resolution, double speed);
        // moves the stepper at a constant speed at a set resolution to a target position
        //@param pos : input position
        //@param resolution : step size to glide through
        //@param speed : Speed the motor should glide at in full steps per second. 

        double getpos();
        // returns the current position of the stepper as double

    private:
        double current_pos, calc, microsteps, fraction, timeperiod;
        int newnum, pulse_pin, direction_pin, microstep1_pin, microstep2_pin;
        unsigned int sub_steps, fullsteps, period, glide_steps;
        bool direction;

};