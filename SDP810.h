/*
 Arduino Library for SDP810-500pa and 125pa
 functions:
 getPress()
 startRead()
 stopRead()
softReset()
sleep()
awake()
readSN()
*/


#ifndef SDP810_h
#define SDP810_h

//read modes
#define massFlow 1
#define massFlowAverage 2
#define massFlowCS 2
#define differential 3
#define differentialAverage 4
#define differentialCS 4

#include "Arduino.h"

void i2cStart();

//byte getCRC(uint8_t,size_t);

class SDP810{
    public:
    SDP810();
    /* start continuous read
   continous read has 4 modes:
    Mass flow  
    Mass flow with Averaging
    Differential Pressure
    Differential Pressure with Averaging*/
    void start(byte);

    //Stop continuous read
    void stop();

    /*Send request for single read(triggered mode)
    Single read has 4 modes:
        Mass flow  
        Mass flow with clock strectching
        Differential Pressure
        Differential Pressure with clock stretching*/
    void singleRead(byte);  

    // Enter sleep mode(will automatically exit when sent either a singleRead or start command)     
    void sleep();

/*
 below are the commands to get data from the sensor.
 these can be called anytime after the sensor has been placed
 in continuous mode, or 45ms after a call to singleRead
*/
    // this will return the temperature in celsius
    float getTempC();

    // this will return the temperature in fahrenheit
    float getTempF();

    // this will return the pressure in pascals
    float getPressure();

    // this will return the pressure in inches water column
    float getPressureInches();

    // this will return the scaling factor for the sensor
    int getScale();

    private: 
    // this function will return the CRC 
    byte getCRC(uint8_t*,size_t);  
    
};

#endif


/*softSerial mySerial();

mySerial.print(sdp.read().toString());

SensorData sd = sdp.read();
int temp = sd.temp;

SDP810 spd;
SensorData spd.triggeredRead(..)


struct SensorData {
    int press;
    int temp;
    int scale;
    float getTempF();
} SensorData;

startContinuous(bool mode, bool averaging) { //Mode 1 is Mass flow 0 is Differential; averaging 0 is off 1 is on


}
// this funtion will get all info form the sensorand you can then call getTemp, getPress or getScale.
SensorData triggeredRead(bool mode, bool clockStretch){ //Mode 1 is Mass flow 0 is Differential; clockStretch 0 is off 1 is on
    SensorData ret;
    start...;
    ret.press = i2creadddd() << 8 | i2creadddd();
    i2creadddd();
    ret.press = i2creadddd() << 8 | i2creadddd();
    i2creadddd();
    ret.press = i2creadddd() << 8 | i2creadddd();
    i2creadddd();

    return ret;
}

read(){

}





class
    void i2cStart();

    float GetTempF();
    float GetTempC();
    float GetHumid();

    byte GetTempHighByte();
    byte GetTempLowByte();
    byte GetHumidHighByte();
    byte GetHumidLowByte();

#endif

190239
crc calculator

http://www.sunshine2k.de/coding/javascript/crc/crc_js.html*/