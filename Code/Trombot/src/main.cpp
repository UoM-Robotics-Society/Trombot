#include <Arduino.h>
#include "Sterpper.h"

#define Controller_dir 12
#define Controller_pul 11
#define Controller_MS1 2
#define Controller_MS2 3

//Stepper Slide(Controller_pul, Controller_dir);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);

  pinMode(Controller_pul, OUTPUT);
  pinMode(Controller_dir, OUTPUT);
  pinMode(Controller_MS1, OUTPUT);
  pinMode(Controller_MS2, OUTPUT);

  digitalWrite(Controller_dir, HIGH);
  digitalWrite(Controller_MS2, LOW); //Change this for microstepping https://www.schmalzhaus.com/EasyDriver/
  digitalWrite(Controller_MS1, LOW); //see above


  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("pulsing");
  digitalWrite(Controller_pul, HIGH);
  delayMicroseconds(100);
  digitalWrite(Controller_pul, LOW);
  delayMicroseconds(100);
  delay(5);
}