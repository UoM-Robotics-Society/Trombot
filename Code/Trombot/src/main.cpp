#include <Arduino.h>
#include "Sterpper.h"
//#include "lm/lm.h"

#define Controller_dir 12
#define Controller_pul 11
#define Controller_MS1 2
#define Controller_MS2 3

#define stepper_slowness_amount = 1000


Stepper Slide(Controller_pul, Controller_dir, Controller_MS1, Controller_MS2);

void setup() {

  Slide.setupstep(1, full);
  Serial.begin(9600);

}


// bool blow = false;
// unsigned long start = 0;
// long trombone_note = 0;
// int target = 0;

// void lm_do_note_up(uint32_t time, uint8_t channel, uint8_t note, uint8_t vel){
//   blow = false;
//   start = millis();
// };

// void lm_do_note_down(uint32_t time, uint8_t channel, uint8_t note, uint8_t vel) {
//     blow = true;
//     start = millis();
//     trombone_note = note;
// }; 

void loop(){
  Slide.step_once(1);
}

// void loop() {
//   // put your main code here, to run repeatedly:
//   //Get info, 
//   lm_tick();

//   // set goals for steps

//     //Cannot do until stepper is in my possession...
//     // just map midi to position
//     target = slide_conversion(trombone_note);

//   // step towards
//   Slide.steptowards(target);

//   // Tongue once instruction
//   if(millis() - start >= stepper_slowness_amount){
//     if(blow){
//       //tongue opens
//     }else{
//       //tongue closes
//     };
//   };
// };






// void lm_platform_features() {
//     lm_feature_note_channel(0, 64, 64);
//     lm_feature_offset(stepper_slowness_amount);
// }
// const char *lm_platform_name = "Trombot;Ver1.00;";
