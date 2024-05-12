#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>  // includes library for sdCard
#include "LibPrintf.h"                               // includes library for CSV file
#include <SparkFun_LPS25HB_Arduino_Library.h>        // includes library for sensor
#include <Servo.h>                                   // include servo library

Servo parachuteServo;  // create an object that declares the servo that controls the parachute when the rocket is coming down
LPS25HB pSensor;       // create an object of the LPS25HB class, and enables the board to communicate with and retrieve data from the LPS25HB sensor
OpenLog sdCard;        // create an object of the OpenLog module object, which enables the board to communicate with the OpenLog module and log the data to an SD card

const String CSVFILE = "data.csv";
const byte SWTPIN = 2;
int swtState = 0;  // variable defining switche's state  (0 or 1/on or off)

void setup() {
  pinMode(SWTPIN, INPUT_PULLUP);
  // initialise I2C communication
  Wire.begin();
  pSensor.begin();
  sdCard.begin();  // open connection to the openLog
  sdCard.create(CSVFILE);
  sdCard.append(CSVFILE);
  Serial.begin(9600);  // initialise serial communication, baud rate set to 9600
  parachuteServo.attach(4);
  parachuteServo.write(0);  // default/initial position of the servo is 0 degrees

  // check to see if sdcard is connected
  sdCard.println("reading working: this is were you should see your pressure values");
  sdCard.syncFile();
  Serial.print("sdCard should have a file containing the text 'reading working: this is were you should see your pressure values' if this text is not in file, check connections on board");

  // if sensor isn't connected, display this on the serial monitor
  if (pSensor.isConnected() == false) {
    Serial.print("Error in sensor, check your connections");  // alerting the user that the sensor cannot be reached
  }

  // check to see if sdcard is connected
  byte status = sdCard.getStatus();  // retrieves and stores status of the sdcard

  Serial.print("Status byte: 0x");       // printing the status message in hex format to the serial monitor
  if (status < 0x10) Serial.print("0");  // add a leading zero if the status byte is less than 16 for consistent formatting
  Serial.println(status, HEX);           // print the status byte in hexadecimal format and move to a new line on the serial monitor
}
void parachuteDeploy() {
  float getPressure = pSensor.getPressure_hPa();  // get the current pressure reading from the sensor

  if (getPressure <= 250) {     // if that pressure reading is higher than or equal to 250hPa, go to next line
    parachuteServo.write(180);  // deploy parachute (assuming servo controls parachute deployment)
  } else {                      // if pressure reading is lower than 250hPa, go to next line
    parachuteServo.write(0);    // turn keep servo at 0 degrees (keep parachute closed)
  }
}
void loop() {
  swtState = digitalRead(SWTPIN);
  if (swtState == LOW) {
    Serial.print("Switch is OFF, turn on to work rocket");
  } else if (swtState == HIGH) {
    Serial.print("Switch is ON, rocket should work");
    // print the pressure reading in hPa
    sdCard.print("Pressure in hPa: ");
    sdCard.print(pSensor.getPressure_hPa());
    Serial.print("Pressure in hPa: ");
    Serial.println(pSensor.getPressure_hPa());
    delay(1000);  // wait a second so that the values on the sdcard are readable and not too fast

    // print the temperature in degrees C
    sdCard.print(", Temperature (degC): ");
    sdCard.print(pSensor.getTemperature_degC());
    Serial.print(", Temperature (degC): ");
    Serial.println(pSensor.getTemperature_degC());
    delay(1000);  // wait a second so that the values on the sdcard are readable and not too fast

    // print the amount of ms since the rocket took off
    sdCard.print(", Time: ");
    sdCard.print(millis());
    Serial.print(", Time: ");
    Serial.println(millis());
    delay(1000);  // wait a second so that the values on the sdcard are readable and not too fast
    parachuteDeploy();
  }
}