#include <Wire.h>
#include "QGPMaker_MotorShield.h"
#include "QGPMaker_IICSensorbar.h"

SensorBar io;
QGPMaker_MotorShield AFMS = QGPMaker_MotorShield();

QGPMaker_DCMotor *M1 = AFMS.getMotor(1);
QGPMaker_DCMotor *M2 = AFMS.getMotor(2);
QGPMaker_DCMotor *M3 = AFMS.getMotor(3);
QGPMaker_DCMotor *M4 = AFMS.getMotor(4);

const byte IIC_ADDRESS = 0x3F;

const byte s0 = 0, s1 = 1, s2 = 2, s3 = 3, s4 = 4;

int last = 0;

void Go() {
  uint8_t i = 0;

  M1->run(BACKWARD);
  M2->run(FORWARD);
  M3->run(BACKWARD);
  M4->run(FORWARD);
  for (; i < 255; i++) {
    M1->setSpeed(i);
    M2->setSpeed(i);
    M3->setSpeed(i);
    M4->setSpeed(i);
  }
}

void Left() {   
  M4->run(FORWARD);
  M1->run(BACKWARD);
  M4->setSpeed(225);
  M1->setSpeed(225);   
  last = 1;
}

void Right() {
  M3->run(BACKWARD);
  M2->run(FORWARD);
  M3->setSpeed(225);
  M2->setSpeed(225);   
  last = 2;
}

void LLeft() {
  delay(80);
  M1->run(BRAKE);
  M4->run(BRAKE);
  last = 3;
}

void RRight() {
  delay(80);
  M2->run(BRAKE);
  M3->run(BRAKE);
  last = 4;
}

void Back() {
  M1->setSpeed(255);
  M2->setSpeed(255);
  M3->setSpeed(255);
  M4->setSpeed(255);
}

void Mid() {
  if (last == 1 || last == 2) {
    Back();
  } else if (last == 3) {
    M1->run(BACKWARD);
    M4->run(FORWARD);
    Back();
  } else if (last == 4) {
    M2->run(FORWARD);
    M3->run(BACKWARD);
    Back();
  }

  last = 0;
}

void Follow() {
  int st0 = io.digitalRead(s0);
  int st1 = io.digitalRead(s1);
  int st2 = io.digitalRead(s2);
  int st3 = io.digitalRead(s3);
  int st4 = io.digitalRead(s4);

  if (st0 || st1 || st2 || st3 || st4) {
    if (!st0) RRight();
    else if (!st4) LLeft();
    else if (!st1) Right();
    else if (!st3) Left();
    else if (!st2) Mid();
    else {
      if (last == 3) LLeft();
      else if (last == 4) RRight();
    }
  }

  delay(5);
}

void setup() {
  AFMS.begin();
  Go();
  io.begin(IIC_ADDRESS);
  io.pinMode(s0, INPUT);
  io.pinMode(s1, INPUT);
  io.pinMode(s2, INPUT);
  io.pinMode(s3, INPUT);
  io.pinMode(s4, INPUT);
}

void loop() {
  Follow();
}
