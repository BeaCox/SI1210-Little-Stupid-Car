#include <Wire.h>
#include "QGPMaker_MotorShield.h"

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield(); 

QGPMaker_DCMotor *M1 = AFMS.getMotor(1);
QGPMaker_DCMotor *M2 = AFMS.getMotor(2);
QGPMaker_DCMotor *M3 = AFMS.getMotor(3);
QGPMaker_DCMotor *M4 = AFMS.getMotor(4);

void Go() {
  uint8_t i = 0;
  
  M1->run(BACKWARD);
  M2->run(FORWARD);
  M3->run(BACKWARD);
  M4->run(FORWARD);
  for (; i<113; i++) {
    M1->setSpeed(i);
    M2->setSpeed(i);
    M3->setSpeed(i);
    M4->setSpeed(i);
  }
  for (; i<128; i++) {
    M2->setSpeed(i);
    M3->setSpeed(i);
  }
}

void setup() {
  
  AFMS.begin();
  Go();
}

void loop() {
  
}
