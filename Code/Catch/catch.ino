#include <Wire.h>
#include "QGPMaker_MotorShield.h"

QGPMaker_MotorShield AFMS = QGPMaker_MotorShield();
QGPMaker_Servo *s0 = AFMS.getServo(0);
QGPMaker_Servo *s1 = AFMS.getServo(1);
QGPMaker_Servo *s2 = AFMS.getServo(2);
QGPMaker_Servo *s3 = AFMS.getServo(3);

void down() {
  s0->writeServo(0);
  s3->writeServo(135);
  delay(200);
  s1->writeServo(100);
  delay(200);
  s2->writeServo(55);
  delay(200);
}

void up() {
  s3->writeServo(80);
  s2->writeServo(100);
  s1->writeServo(5   );
}

void Catch() {
  down();
  s0->writeServo(110);
  delay(500);
  up();
}

void setup() {
  AFMS.begin(50);
  Serial.begin(9600);
}

void loop() {
  s3->writeServo(80);
  s1->writeServo(130);
  s2->writeServo(40);
  delay(500);
  Catch();
  delay(10000);
}
