#include <Arduino.h>
#include "Sterpper.h"


    Stepper::Stepper(int pulse_pin, int direction_pin, int microstep1_pin, int microstep2_pin ){ 
        pinMode(pulse_pin, OUTPUT);
        pinMode(direction_pin, OUTPUT);
        pinMode(microstep1_pin, OUTPUT);
        pinMode(microstep2_pin, OUTPUT);
        digitalWrite(direction_pin, LOW);
        digitalWrite(microstep1_pin, HIGH);
        digitalWrite(microstep2_pin, HIGH);
        current_pos = 0;
    }

    void Stepper::setupstep(bool dir,resolution resolution){
        digitalWrite(pulse_pin, LOW);

        if(dir) digitalWrite(direction_pin, HIGH);      // Set direction
        else digitalWrite(direction_pin, LOW);

        switch(resolution){
            case full:
                digitalWrite(microstep1_pin, HIGH);             //Set to full steps
                digitalWrite(microstep2_pin, HIGH);
                fraction = 1;
                break;
            case half:
                digitalWrite(microstep1_pin, HIGH);
                digitalWrite(microstep2_pin, LOW);
                fraction = 0.5;
                break;
            case quarter:
                digitalWrite(microstep1_pin, LOW);
                digitalWrite(microstep2_pin, HIGH);
                fraction = 0.25;
                break;
            case eighth:
                digitalWrite(microstep1_pin, LOW);
                digitalWrite(microstep2_pin, LOW);
                fraction = 0.125;
                break;
            default:
                fraction = 0.125;
                digitalWrite(microstep1_pin, LOW);
                digitalWrite(microstep2_pin, LOW);
                break;
        }
        delayMicroseconds(10);
    }

    void Stepper::step_once(unsigned int period=1) {
        
        digitalWrite(pulse_pin, HIGH);              //pulse to trigger motion 
        delayMicroseconds(period);
        digitalWrite(pulse_pin, LOW);
        delayMicroseconds(period);
        if(direction) current_pos= current_pos + fraction;                      //update current position tracking
        else current_pos= current_pos - fraction;
    
    }

    void Stepper::move(double error, bool dir, resolution resolution, unsigned int timeperiod = 5){
        unsigned int fullsteps;
        double microsteps;
        fullsteps = (unsigned int) error;
        microsteps = error - fullsteps;
        period = (unsigned int) timeperiod;

        setupstep(dir, full);

        for(unsigned int i=0; i++; i<fullsteps){
            step_once(period);
        }

        setupstep(dir, resolution);
                
        for(int k=0; k++; k<(microsteps/fraction)){
            step_once(period);
        }
    }

    void Stepper::moveto(double pos, unsigned int period = 5){
        this->calc = pos - current_pos;                       //Determine steps and what direction
        if(calc<0) direction = 0;
        else direction = 1;
        move(abs(calc), direction, eighth, period);      // pulse in that direction
    };

    void Stepper::setpos(double pos){
        current_pos = pos;
    }

    void Stepper::glide(unsigned int sub_steps, bool dir, resolution resolution, double speed){
        double timeperiod;
        timeperiod = 1000000/(resolution*speed);
        if(timeperiod>1) period = (unsigned int) timeperiod;
        else period = 1;

        setupstep(dir, resolution);

        for(int k=0; k++; k<sub_steps){
            this->step_once(period);
        }
    }

    void Stepper::glideto(double pos, resolution resolution, double speed){
        unsigned int glide_steps;
        calc = current_pos - pos;
        glide_steps = (unsigned int) calc*resolution;
        if(calc>0) direction =0;
        else direction = 1;
        glide(glide_steps, direction, resolution, speed);
    }

    double Stepper::getpos(){
        return current_pos; 
    }

    void Stepper::newtarget(double pos){
        target = pos;
        targetchange = 1;
    }

    void Stepper::fullsteptowardstarget(double pos, unsigned int period = 1){
        calc = target - current_pos;
        if(calc<0) direction = 0;
        else direction = 1;
        
        if(targetchange){
            setupstep(direction, full);
            targetchange = 0;
        }

        if(abs(calc)>=1) step_once();                
        
        }