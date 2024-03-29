#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
#include "LibPrintf.h"
#include <SparkFun_LPS25HB_Arduino_Library.h>  // include library for sensor
LPS25HB pSensor;                               // create an object of the LPS25HB class

const String CSVFILE = "data.csv";
OpenLog sdCard;

const byte OpenLogAddress = 42;  // default Qwiic OpenLog I2C address

void setup() {
  // initialise I2C communication
  Wire.begin();
  pSensor.begin();
  sdCard.begin();  // open connection to the openLog
  sdCard.create(CSVFILE);
  sdCard.append(CSVFILE);
  // test to see if it is connected
  sdCard.println("reading working: this is were you should see your pressure values");
  sdCard.syncFile();
  // initialise serial communication, baud rate set = 9600
  Serial.begin(9600);
  Serial.print("sdCard should have a file containing the text 'reading working: this is were you should see your pressure values'");

  // if it isn't connected, display this on the serial monitor
  if (pSensor.isConnected() == false) {
    Serial.print("Sensor Error, check your connections");                      // alerting the user that the sensor cannot be reached
    Serial.println("See Example2_I2C_Configuration for how to change these");  // giving a suggestion for a solution
  }
}


void loop() {
  // print the pressure reading in hPa
  sdCard.print("Pressure in hPa: ");
  sdCard.print(pSensor.getPressure_hPa());
  Serial.print("Pressure in hPa: ");
  Serial.println(pSensor.getPressure_hPa());
  delay(1000);

  // print the temperature in degrees C
  sdCard.print(", Temperature (degC): ");
  sdCard.print(pSensor.getTemperature_degC());
  Serial.print(", Temperature (degC): ");
  Serial.println(pSensor.getTemperature_degC());
  delay(1000);


  // print the amount of ms since the rocket took off
  sdCard.print(", Time: ");
  sdCard.print(millis());
  Serial.print(", Time: ");
  Serial.println(millis());

  delay(1000);  // wait - 40 ms is the maximum update rate of the sensor (25 Hz)
}