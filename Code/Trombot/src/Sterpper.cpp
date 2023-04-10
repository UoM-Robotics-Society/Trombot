#include <Arduino.h>
#include "Sterpper.h"


    Stepper::Stepper(int pulse_pin, int direction_pin, int microstep1_pin, int microstep2_pin ): pul(pulse_pin), dir(direction_pin), ms1(microstep1_pin), ms2(microstep2_pin) { 
        pinMode(pul, OUTPUT);
        pinMode(dir, OUTPUT);
        pinMode(ms1, OUTPUT);
        pinMode(ms2, OUTPUT);
        digitalWrite(dir, LOW);
        digitalWrite(ms1, HIGH);
        digitalWrite(ms2, HIGH);
        fraction = 1;
        direction = 0;
        current_pos = 0;
    }

    void Stepper::setupstep(bool dir, resolution res){
        digitalWrite(pul, LOW);

        if(dir) digitalWrite(dir, HIGH);      // Set direction
        else digitalWrite(dir, LOW);

        switch(res){
            case full:
                digitalWrite(ms1, HIGH);             //Set to full steps
                digitalWrite(ms2, HIGH);
                fraction = 1;
                break;
            case half:
                digitalWrite(ms1, HIGH);
                digitalWrite(ms2, LOW);
                fraction = 0.5;
                break;
            case quarter:
                digitalWrite(ms1, LOW);
                digitalWrite(ms2, HIGH);
                fraction = 0.25;
                break;
            case eighth:
                digitalWrite(ms1, LOW);
                digitalWrite(ms2, LOW);
                fraction = 0.125;
                break;
            default:
                fraction = 0.125;
                digitalWrite(ms1, LOW);
                digitalWrite(ms2, LOW);
                break;
        }
        delayMicroseconds(10);
    }

    void Stepper::step_once(unsigned int period=350) {
        
        digitalWrite(pul, HIGH);              //pulse to trigger motion 
        delayMicroseconds(period);
        digitalWrite(pul, LOW);
        delayMicroseconds(period);

        if(dir) current_pos= current_pos + fraction;                      //update current position tracking
        else current_pos= current_pos - fraction;
    
    }

    void Stepper::move(double error, bool dir, resolution res, unsigned int timeperiod = 350){
        unsigned int fullsteps;
        double microsteps;
        fullsteps = (unsigned int) error;
        microsteps = error - fullsteps;
        period = (unsigned int) timeperiod;

        setupstep(dir, full);

        for(unsigned int i=0; i++; i<fullsteps){
            step_once(period);
        }

        setupstep(dir, res);
                
        for(int k=0; k++; k<(microsteps/fraction)){
            step_once(period);
        }
    }

    void Stepper::moveto(double pos, unsigned int period = 350){
        this->calc = pos - current_pos;                       //Determine steps and what direction
        if(calc<0) direction = 0;
        else direction = 1;
        move(abs(calc), direction, eighth, period);      // pulse in that direction
    };

    void Stepper::setpos(double pos){
        current_pos = pos;
    }

    // void Stepper::glide(unsigned int sub_steps, bool dir, resolution res, double speed){
    //     double timeperiod;
    //     timeperiod = 1000000/(res*speed);
    //     if(timeperiod>1) period = (unsigned int) timeperiod;
    //     else period = 1;

    //     setupstep(dir, res);

    //     for(int k=0; k++; k<sub_steps){
    //         this->step_once(period);
    //     }
    // }

    // void Stepper::glideto(double pos, resolution res, double speed){
    //     unsigned int glide_steps;
    //     calc = current_pos - pos;
    //     glide_steps = (unsigned int) calc*res;
    //     if(calc>0) direction =0;
    //     else direction = 1;
    //     glide(glide_steps, direction, res, speed);
    // }

    double Stepper::getpos(){
        return current_pos; 
    }

    void Stepper::newtarget(double pos){
        target = pos;
        targetchange = 1;
    }

    void Stepper::fullsteptowardstarget(unsigned int period = 350){
        calc = target - current_pos;
        Serial.println(calc);
        // Serial.println(current_pos);
        // Serial.println();
        if(calc<0) dir = 0;
        else dir = 1;
        
        if(targetchange){
            setupstep(direction, full);
            targetchange = 0;
        }

        if(abs(calc)>=1) step_once();                
        
        }