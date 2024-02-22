const byte BTNPIN = 3;
const byte POTPIN = A1;

byte diceNum;

void setup() {
  Serial.begin(9600);
  pinMode(BTNPIN, INPUT);
  pinMode(POTPIN, INPUT);
  randomSeed(analogRead(0));
}

void loop() {
  // if the button has been pressed, read potentiometer to check what dice type
  // then call the rollDice method with that sort of dice
  if (digitalRead(BTNPIN) == HIGH) {
    Serial.println("Rolling dice...");
    // gives a value from 0 - 1023
    int diceType = analogRead(POTPIN);
    // use map(value, fromLow, fromHigh, toLow, toHigh)
    diceType = map(diceType, 0, 1023, 1, 6);

    rollDice(diceType);
  }
}

void rollDice(int diceType) {
  //
  diceNum = random(1, 6);
  Serial.print("Dice rolled: ");
  Serial.print(diceNum);

  switch (diceType) {
    case 1:
      diceNum = random(1, 4);
      Serial.print("4 sided dice rolling...");
      break;
    case 2:
      diceNum = random(1, 6);
      Serial.print("6 sided dice rolling...");
      break;
    case 3:
      diceNum = random(1, 8);
      Serial.print("8 sided dice rolling...");
      break;
    case 4:
      diceNum = random(1, 10);
      Serial.print("10 sided dice rolling...");
      break;
    case 5:
      diceNum = random(1, 12);
      Serial.print("12 sided dice rolling...");
      break;
    case 6:
      diceNum = random(1, 14);
      Serial.print("14 sided dice rolling...");
      break;

    default:
      Serial.print("map value is incorrect check pot val");
      break;
  }
  Serial.print(diceNum);
}