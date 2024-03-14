#include<Wire.h>
#include "SparkFun_Qwiic_OpenLog_Arduino_Library.h" // include library for openLog
#include "LibPrintf.h" // include printf()
OpenLog sdCard;
// LPS25HB address is 0x5C(92)
#define Adr 0x5C

const boolean CSVFILE = "data.csv";

void setup()
{
  // initialise I2C communication
  Wire.begin();
  sdCard.begin();

  // initialise serial communication, baud rate set = 9600
  Serial.begin(9600);

  sdCard.append("data.csv");  // checking if it is saving a file to the sdCard
  sdCard.println("working");
  sdCard.syncFile(); // save to sdCard

  // starting the I2C transmission
  Wire.beginTransmission(Adr);
  // select control register 1
  Wire.write(0x20);
  // set active mode, continuous update
  Wire.write(0x90);
  // stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop() // recieving/reading
{
  unsigned int data[3];
  // start I2C transmission 
  Wire.beginTransmission(Adr);
  // select pressure data register
  Wire.write(0x28 | 0x80);
// stop I2C transmission
Wire.endTransmission();

// request 3 bytes of data
Wire.requestFrom(Adr, 3);

//read the 3 bytes of data
// pressure lsb first
if(Wire.available() == 3)
{
  data[0] = Wire.read();
  data[1] = Wire.read();
  data[2] = Wire.read();
}
delay(300);

// convert pressure data
float pressure = ((data[2] * 65536) + (data[1] * 256) + data[0]) / 4096.0;

// output data to serial monitor 
printf("Pressure is:" pressure "hPa");
delay(1000);
}