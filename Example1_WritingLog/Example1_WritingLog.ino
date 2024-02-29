#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h> // include Qwicc library
#include <Wire.h> // include wire 

OpenLog sdCard; // create instance

const byte BTNPIN = 2; 
bool btnState = false;
bool lastBtnState = false;

void setup() {
  Wire.begin();
  sdCard.begin();
  Serial.begin(9600);

  if (sdCard.begin() == false) {
    Serial.println("Unable to communicate with Qwiic sdCard. Please check connections.");
    while (1);
  }

  pinMode(BTNPIN, INPUT);
}

void loop() {
  btnState = digitalRead(BTNPIN);

  if (btnState != lastBtnState) {
    if (btnState == HIGH) {
      saveJokeToFile();
    }
    delay(50); // debouncing delay
  }

  lastBtnState = btnState;
}

void saveJokeToFile() {
  // saying what the joke is
  String joke = "What does a pickle say when he wants to play cards? 'Dill me in!'";

  // sdCard commands to write to a file
  sdCard.print(joke);
  sdCard.println(); // add a newline to separate jokes
}