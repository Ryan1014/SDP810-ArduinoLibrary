#include "Arduino.h"
#include "SDP810.h"
#include <Wire.h>

//definitions
#define address 0x25



void i2cStart(){
    Wire.begin();
    //SWire.begin(); //use for software I2C
}




//constructor for the class
SDP810::SDP810(){

}

/* start continuous read
   continous read has 4 modes:
    Mass flow  
    Mass flow with Averaging
    Differential Pressure
    Differential Pressure with Averaging*/

void SDP810::start(byte mode){     
byte highByte = 0x36;             
byte lowByte;

switch(mode){

  case 1:
    lowByte = 0x08;
  break;

  case 2:
    lowByte = 0x03;
  break;

  case 3:
    lowByte = 0x1E;
  break;

  case 4:
    lowByte = 0x15;
  break;

  default:// default differential average
    lowByte = 0x15;
  break;
}

  Wire.beginTransmission(address);
  Wire.write(highByte); 
  Wire.write(lowByte);
  Wire.endTransmission();
}


//Stop continuous read
void SDP810::stop(){
  Wire.beginTransmission(address);
  Wire.write(0x3F); 
  Wire.write(0xF9);
  Wire.endTransmission();
}


/* send request for single read(triggered mode)
   Single read has 4 modes:
    Mass flow  
    Mass flow with clock strectching
    Differential Pressure
    Differential Pressure with clock stretching*/

void SDP810::singleRead(byte mode){
byte highByte;
byte lowByte;

switch(mode){
  case 1:
    highByte = 0x36;
    lowByte = 0x24;
  break;

  case 2:
    highByte = 0x37;
    lowByte = 0x26;
  break;

    case 3:
    highByte = 0x36;
    lowByte = 0x2F;
  break;

    case 4:
    highByte = 0x37;
    lowByte = 0x2D;
  break;

  default: //default to differential
    highByte = 0x36;
    lowByte = 0x2F;
  break;
}

  Wire.beginTransmission(address);
  Wire.write(highByte); 
  Wire.write(lowByte);
  Wire.endTransmission();

}       

// Enter sleep mode(will automatically exit when sent either a singleRead or start command)
void SDP810::sleep(){
  Wire.beginTransmission(address);
  Wire.write(0x36); 
  Wire.write(0x77);
  Wire.endTransmission();
}

// soft reset the sensor
void SDP810::reset(){
  Wire.beginTransmission(address);
  Wire.write(0x00); 
  Wire.write(0x06);
  Wire.endTransmission();
}

/*
 below are the commands to get data from the sensor.
 these can be called anytime after the sensor has been placed
 in continuous mode, or 45ms after a call to singleRead
*/


// this will return the temperature in celsius
float SDP810::getTempC(){
float temperature;
byte crc;
bool crcFlag = 0;
byte timeout = 2;
byte message[9];
int i = 0;
  Wire.requestFrom(address,9);

    while(!crcFlag && timeout>0){
      while(Wire.available()){  
        message[i] = Wire.read();
        i++;
      }
      crc = getCRC(&message[3],2);
      if(crc == message[5]){crcFlag = 1;}
      timeout--;
    }
  if(timeout == 0){return NULL;}
  temperature = ((message[3] << 8) | (message[4]));
  temperature /= 200.0;
  return temperature;
}

// this will return the temperature in fahrenheit
float SDP810::getTempF(){
  return ((getTempC()*9)/5)+32;
}

// this will return the pressure in pascals
float SDP810::getPressure(){
int16_t pressure;
float scale = 60.0;
byte crc;
bool crcFlag = 0;
byte timeout = 2;
byte message[9];
int i = 0;
  Wire.requestFrom(address,9);

    while(!crcFlag && timeout>0){
      while(Wire.available()){  
        message[i] = Wire.read();
        i++;
      }
      crc = getCRC(&message[0],2);
      if(crc == message[2]){crcFlag = 1;}
      timeout--;
    }
  if(timeout == 0){return NULL;}
  pressure = ((message[0] << 8) | (message[1]));
  scale = ((message[6] << 8) | (message[7]));
  float pressurePa = pressure/scale;
  return pressurePa;
}

//this will return the pressure in inches water column
float SDP810::getPressureInches(){
  return getPressure()/248.84;
}

// this will return the scaling factor for the sensor
int SDP810::getScale(){
int scale;
byte crc;
bool crcFlag = 0;
byte timeout = 2;
byte message[9];
int i = 0;
  Wire.requestFrom(address,9);

    while(!crcFlag && timeout>0){
      while(Wire.available()){  
        message[i] = Wire.read();
        i++;
      }
      crc = getCRC(&message[6],2);
      if(crc == message[8]){crcFlag = 1;}
      timeout--;
    }
  if(timeout == 0){return NULL;}
  scale = ((message[6] << 8) | (message[7]));
  return scale;
}

// this function will return the CRC 
byte SDP810::getCRC(uint8_t* data, size_t count){
      uint8_t crc = 0xFF;

    /* calculates 8-Bit checksum with given polynomial */
    for (size_t current_byte = 0; current_byte < count; ++current_byte) {
        crc ^= (data[current_byte]);
        for (uint8_t crc_bit = 8; crc_bit > 0; --crc_bit) {
            if (crc & 0x80)
                crc = (crc << 1) ^ 0x31;
            else
                crc = (crc << 1);
        }
    }
    return crc;

}
