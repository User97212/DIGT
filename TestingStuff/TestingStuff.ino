
const byte PAWPIN1 = 1;
const byte PAWPIN2 = 2;
const byte PAWPIN3 = 3;
const byte PAWPIN4 = 4;

const byte LEDPIN = 13;  //

void setup() {
  pinMode(PAWPIN1, INPUT);
  pinMode(PAWPIN2, INPUT);
  pinMode(PAWPIN3, INPUT);
  pinMode(PAWPIN4, INPUT);
  pinMode(LEDPIN, OUTPUT);  // tools --> auto format
}

void loop() {
  if (digitalRead(PAWPIN1) == HIGH) {
    digitalWrite(LEDPIN, HIGH); // when paw 1 is pressed, turn LED is turned on
  }
  if (digitalRead(PAWPIN2) == HIGH) {
    digitalWrite(LEDPIN, LOW);
  }
  if (digitalRead(PAWPIN3) == HIGH) {
    playMusic();
  }
  if (digitalRead(PAWPIN4) == HIGH) {
    int score = playGame();
  }
}

void playMusic(){
  // play an MP3 file here
}

int playGame(){
  byte score = 99;
  // play simon says game
  return score
}