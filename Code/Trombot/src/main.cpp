#include <Arduino.h>
#include "Sterpper.h"

#define Controller_dir 7
#define Controller_pul 6

Stepper Slide(Controller_pul, Controller_dir);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  pinMode(Controller_pul, OUTPUT);
  pinMode(Controller_dir, OUTPUT);
  digitalWrite(Controller_dir, HIGH);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("pulsing!");
  digitalWrite(Controller_pul, HIGH);
  delayMicroseconds(5);
  digitalWrite(Controller_pul, LOW);
  delayMicroseconds(5);
  delay(200);
}