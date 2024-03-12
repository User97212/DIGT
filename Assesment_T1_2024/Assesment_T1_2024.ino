#include<Wire.h>
// LPS25HB address is 0x5C(92)
#define Adr 0x5C

void setup()
{
  // initialise I2C communication
  Wire.begin();
  // initialise serial communication, baud rate set = 9600
  Serial.begin(9600);

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

void loop()
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
Serial.print("Pressure is: ");
Serial.print(pressure);
Serial.println(" hPa");
delay(1000);
}