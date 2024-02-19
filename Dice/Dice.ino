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
  if (digitalRead(BTNPIN) == HIGH);
  int diceType = analogRead(POTPIN);
  diceType = map(diceType, 0, 1023, 1, 6);
  // 
  diceNum = random(1, 6);
  Serial.print("Dice rolled: ");
  Serial.print(diceNum);
}