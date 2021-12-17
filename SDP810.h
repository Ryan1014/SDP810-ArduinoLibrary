/*
 Arduino Library for SDP810-500pa and 125pa
 Writen by Ryan Peters 12/16/21
*/


#ifndef SDP810_h
#define SDP810_h

//Measurment types
#define massFlow 1
#define massFlowAverage 2 // averages since last read
#define massFlowCS 2  //use i2C clock Strecting (useful for triggered read mode)
#define differential 3
#define differentialAverage 4
#define differentialCS 4

#include "Arduino.h"

//softSerial mySerial();
void i2cStart();

//byte getCRC(uint8_t,size_t);

class SDP810{
    public:
    SDP810();
 /*start continuous read
   continuous read has 4 modes:
        -Mass flow  
        -Mass flow with Averaging
        -Differential Pressure
        -Differential Pressure with Averaging*/
    void start(byte);

    //Stop continuous read
    void stop();

  /*Send request for single read(triggered mode)
    Single read has 4 modes:
        -Mass flow  
        -Mass flow with clock strectching
        -Differential Pressure
        -Differential Pressure with clock stretching*/
    void singleRead(byte);  

    // Enter sleep mode(will automatically exit when sent either a singleRead or start command)     
    void sleep();

    // soft reset the sensor
    void reset();

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
