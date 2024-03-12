#include <Servo.h>

const byte MICPIN = 3;
const byte SERVOPIN = 6;
const byte LEDPIN = 8;
const byte BTNPIN = 12;

Servo servoLock;

void setup() {
  Serial.begin(9600);
  pinMode(MICPIN, INPUT);
  pinMode(BTNPIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(SERVOPIN, OUTPUT);
  servoLock.attach(SERVOPIN);
  servoLock.write(0);  //locked
}
void moveLid(boolean lockMe) {
  if (lockMe) {
    Serial.print("Not valid");
    servoLock.write(0);  //locked
  } else {
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    servoLock.write(90);  //unlocked
  }
}
void loop() {
  if (analogRead(MICPIN) >= 162) {
    moveLid(false);
    delay(5000);
    Serial.print("Accepted, unlocked");
    digitalWrite(LEDPIN, HIGH);
    delay(100);
    moveLid(true);
  } // when button pressed, the box is locked
  if (digitalRead(BTNPIN) == HIGH) {
    moveLid(false);
    Serial.print("Button pressed, box locked");
  }
}
