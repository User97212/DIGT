#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
OpenLog sdCard;

const String FILENAME = "joke.txt";  // does my code have the joke.txt file saved?

void setup() {

  Wire.begin();
  sdCard.begin();

  Serial.begin(9600);

  sdCard.append(FILENAME);
  sdCard.println("Knock knock joke");
  sdCard.syncFile();
  Serial.println("Knock knock joke");  // will my joke appear on the serial monitor?
}

void loop() {

  sdCard.println("Knock knock");
  Serial.println("Knock knock");  // is my joke being printed to the serial monitor?
  delay(1000);

  sdCard.println("who's there?");
  Serial.println("who's there?");
  delay(1000);

  sdCard.println("Justin's grade");
  Serial.println("Justin's grade");
  delay(1000);

  sdCard.println("South African wimpering");
  Serial.println("South African wimpering");
  delay(1000);

  sdCard.syncFile();  // is the joke also being printed on the sdCard file?
  delay(1000); // is it easy enough to read? not printing too fast?
}