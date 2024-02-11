#include <Servo.h>  // include servo library

const byte PAWPIN1 = 1;  // setting all the pins as constants
const byte PAWPIN2 = 2;
const byte PAWPIN3 = 3;
const byte PAWPIN4 = 4;
const byte LEFTEARPIN = 0;
const byte RIGHTEARPIN = 10;
const byte LEDPIN = 13;

Servo leftEar;  // declaring both servos
Servo rightEar;

void setup() {
  pinMode(PAWPIN1, INPUT);  // defining whether the components are output/input
  pinMode(PAWPIN2, INPUT);
  pinMode(PAWPIN3, INPUT);
  pinMode(PAWPIN4, INPUT);
  pinMode(LEDPIN, OUTPUT);
  pinMode(LEFTEARPIN, OUTPUT);
  pinMode(RIGHTEARPIN, OUTPUT);
  leftEar.attach(LEFTEARPIN);  // attach the servos to their pins
  rightEar.attach(RIGHTEARPIN);
}
void wagEars() {
  leftEar.write(0);  // wagEars method is for the ears to both move to 0, then 90, then to 0 again
  rightEar.write(0);
  leftEar.write(90);
  rightEar.write(90);
  leftEar.write(0);
  rightEar.write(0);
}

void blinkingLed() {
  byte randNumber = random(1, 3);  // choosing a random number between 1 and 3

  for (int i = 0; i < randNumber; i++) {  // the LED will then flash however many times the random number says to
    digitalWrite(LEDPIN, HIGH);
    delay(500);
    digitalWrite(LEDPIN, LOW);
    delay(500);
  }
}
void loop() {
  if (digitalRead(PAWPIN1) == HIGH) {
    digitalWrite(LEDPIN, HIGH);  // when paw 1 is pressed, LED is turned on
  }
  if (digitalRead(PAWPIN2) == HIGH) {
    digitalWrite(LEDPIN, LOW);  // when paw 2 is pressed, LED is turned off
  }
  if (digitalRead(PAWPIN3) == HIGH) {
    wagEars();  // when paw 3 is pressed, call the wagEars method
  }
  if (digitalRead(PAWPIN4) == HIGH) {
    blinkingLed();  // when paw 4 is pressed, call the blinkingLed method
  }
}