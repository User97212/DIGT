#include <Wire.h> // wires that allow us to send signals through wire from arduino to components, hides all of the complexity of sending 0 and 1
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h" // include library for openLog
OpenLog sdCard; // openLog stores or logs the serial data - creates instance

const String FILENAME = "joke.txt";  // string stores letters, in this case it is storing my file that contains the joke

void setup() {
  //
  Wire.begin();
  sdCard.begin();

  Serial.begin(9600);  // 9600bps is used for debug statements

  sdCard.append(FILENAME);  // checking if it is saving a file to the sdCard
  sdCard.println("Knock knock joke");
  sdCard.syncFile();  // save to the sdCard
}

void loop() {
  // print "whatever the joke is" to the sdCard, check that this has worked by also printing it to the serial monitor
  sdCard.println("Knock knock");
  Serial.println("Knock knock ");
  delay(1000);  // delay 1000ms (1s) so it isn't printed too fast on the serial monitor

  sdCard.println("who's there?");
  Serial.println(" who's there? ");
  delay(1000);

  sdCard.println("Justin's grade");
  Serial.println(" Justin's grade ");
  delay(1000);

  sdCard.println("South African wimpering");
  Serial.println(" South African wimpering ");
  delay(1000);

  sdCard.syncFile();  // save to the sdCard
  delay(1000);
}