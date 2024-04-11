#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
#include "LibPrintf.h"
#include <SparkFun_LPS25HB_Arduino_Library.h>  // include library for sensor

LPS25HB pSensor; // create an object of the LPS25HB class, and enables the board to communicate with and retrieve data from the LPS25HB sensor
OpenLog sdCard; // create an object of the OpenLog module object, which enables the board to communicate with the OpenLog module and log the data to an SD card

const String CSVFILE = "data.csv";
const byte SWTPIN = 2;
int swtState = 0; // variable defining switche's state  (0 or 1/on or off)

void setup() {
  pinMode(SWTPIN, INPUT_PULLUP);
  // initialise I2C communication
  Wire.begin();
  pSensor.begin();
  sdCard.begin();  // open connection to the openLog
  sdCard.create(CSVFILE);
  sdCard.append(CSVFILE);
  Serial.begin(9600); // initialise serial communication, baud rate set to 9600
  
  // check to see if sdcard is connected
  sdCard.println("reading working: this is were you should see your pressure values");
  sdCard.syncFile();
  Serial.print("sdCard should have a file containing the text 'reading working: this is were you should see your pressure values'");
 
  // if sensor isn't connected, display this on the serial monitor
  if (pSensor.isConnected() == false) {
    Serial.print("Error in sensor, check your connections"); // alerting the user that the sensor cannot be reached
  }

  //TEACHER COMMENT any check for the sdcard?

}

void loop() {
  swtState = digitalRead(SWTPIN);
   if (swtState == LOW) {
    Serial.print("Switch is OFF, turn on to work rocket");
   }
    else if (swtState == HIGH) { 
    Serial.print("Switch is ON, rocket should work");
  // print the pressure reading in hPa
  sdCard.print("Pressure in hPa: ");
  sdCard.print(pSensor.getPressure_hPa());
  Serial.print("Pressure in hPa: ");
  Serial.println(pSensor.getPressure_hPa());
  delay(1000); // wait a second so that the values on the sdcard are readable and not too fast

  // print the temperature in degrees C
  sdCard.print(", Temperature (degC): ");
  sdCard.print(pSensor.getTemperature_degC());
  Serial.print(", Temperature (degC): ");
  Serial.println(pSensor.getTemperature_degC());
  delay(1000); // wait a second so that the values on the sdcard are readable and not too fast

  // print the amount of ms since the rocket took off
  sdCard.print(", Time: ");
  sdCard.print(millis());
  Serial.print(", Time: ");
  Serial.println(millis());
  delay(1000);  // wait a second so that the values on the sdcard are readable and not too fast
}
  }
