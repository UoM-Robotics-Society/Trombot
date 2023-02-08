#include <Arduino.h>
#include "Sterpper.h"


    Stepper::Stepper(int pulse_pin, int direction_pin ){ 
        pinMode(pulse_pin, OUTPUT);
        pinMode(direction_pin, OUTPUT);
        digitalWrite(direction_pin, LOW);
        current_pos = 0;
    }

    void Stepper::pulse(unsigned int num, bool dir){
        digitalWrite(pulse_pin, LOW);
        if(dir) digitalWrite(direction_pin, HIGH); // Set direction
        else digitalWrite(direction_pin, LOW);
        delayMicroseconds(10); 
        for(int i=0; i++; i<num){
            digitalWrite(pulse_pin, HIGH);      //pulse to trigger motion 
            delayMicroseconds(5);
            digitalWrite(pulse_pin, LOW);
            delayMicroseconds(5);
            if(dir) current_pos++;  //update current position tracking
            else current_pos--;
        }
    }

    void Stepper::moveto(int pos){
        calc = pos - current_pos;           //Determine steps and what direction
        if(calc<0) direction =false;
        else direction = true;
        pulse((unsigned int) abs(calc),direction); // pulse in that direction
    };

    int Stepper::getpos(){
        return current_pos; 
    }