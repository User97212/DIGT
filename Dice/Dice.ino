// add a LCD library of functions
#include <Adafruit_LiquidCrystal.h>

// set up all pins as constants
const byte BTNPIN = 3;
const byte NOISEPIN = A0;
const byte POTPIN = A1;

byte diceNum;

// connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal screen(0);

// setip which pins are input/output
// and randomise where we start the numbers from
void setup() {
  Serial.begin(9600);
  pinMode(BTNPIN, INPUT);
  pinMode(POTPIN, INPUT);

  randomSeed(analogRead(NOISEPIN));

// checking if it is being printed to the LCD screen properly
  if(!screen.begin(16, 2)){ // merit/excellence check
  Serial.println("couldn't start the screen? check wiring");
  while(1);
  }
}

void loop() {
  // if the button has been pressed, and the LCD screen is working, read potentiometer to check what dice type
  // then call the rollDice method with the dice relating to the pot val
  if (digitalRead(BTNPIN) == HIGH) {
    screen.println("Rolling dice..."); // screen print will print everything on the LCD screen
    // gives a value from 0 - 1023
    int diceType = analogRead(POTPIN);
    // use map(value, fromLow, fromHigh, toLow, toHigh)
    diceType = map(diceType, 0, 1023, 1, 6);
    // calling the diceType method
    rollDice(diceType);
  }
}

void rollDice(int diceType) {
  // rolling dice to pick a diceType
  diceNum = random(1, 6);
  screen.print("Dice rolled: ");
  screen.print(diceNum);

  switch (diceType) {
    // if diceType val = 1, roll a 4 sided dice
    case 1:
      diceNum = random(1, 4);
      screen.print("4 sided roll:");
      break;
      // if diceType val = 2, roll a 6 sided dice
    case 2:
      diceNum = random(1, 6);
      screen.print("6 sided roll:");
      break;
      // if diceType val = 3, roll a 8 sided dice
    case 3:
      diceNum = random(1, 8);
      screen.print("8 sided roll:");
      break;
      // if diceType val = 4, roll a 10 sided dice
    case 4:
      diceNum = random(1, 10);
      screen.print("10 sided roll:");
      break;
      // if diceType val = 5, roll a 12 sided dice
    case 5:
      diceNum = random(1, 12);
      screen.print("12 sided roll:");
      break;
      // if diceType val = 6, roll a 14 sided dice
    case 6:
      diceNum = random(1, 14);
      screen.print("14 sided roll:");
      break;
      // if diceType val doesn't = 1 - 6, show in serial monitor so I can see my mistake
    default:
      Serial.print("map value is incorrect check pot val"); // using serial monitor so that it shows the error, if the LCD screen isn't working
      break;
  }
  screen.print(diceNum);
}