#include <Servo.h>

const byte MICPIN = 3;
const byte SERVOPIN = 6;

Servo servoLock;

void setup() {
  pinMode(MICPIN, INPUT);
  pinMode(SERVOPIN, OUTPUT);
  servoLock.attach(SERVOPIN);
}
void unlockLid() {
  servoLock.write(0);
  servoLock.write(90);
}
void loop() {
  if (analogRead(MICPIN) >= 162);
  unlockLid();
}
