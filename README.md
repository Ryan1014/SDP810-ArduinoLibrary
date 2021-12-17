# SDP810-ArduinoLibrary
This is an Arduino library for the Sensirion SDP810 pressure sensors.

I wrote this library for 2 reasons. First, to get some practice writing an Arduino library and second, I found the library provided by the manufactuerer to be a bit combersome.
I hope this library is as stright forward and simple for you as I had intended. Sugestions welcome. 

First some information about the Sensor.  
The SDP810-500pa and SDP810-125pa communicate through i2c. 
This library was writen to use the hardware i2c. 
On the arduino UNO those pins are pins A4 and A5.

```
Pinout of the sensor when looking at the back.
 ____________
| sensirion  |
 O   ....   O
|____________|
SDA GND VDD SCL
```


This sensor can read both temperature and pressure.  
The sensor can be set to read either differential pressure, or continuous flow, and it has 2 modes for reading data; a continous read mode(where you send a command to start the measurements, and it will continue taking samples that can be read out at any time),  
And a "triggered mode". In triggered mode you first have to send a command to tell the sensor to take a measument, wait atleast 45ms, 
and then read the data. 


Here is a list of basic commands for the library
- `start(measurement type)`	Used to start the sensor in countinous read mode	
- `stop()`	  Stop continous read mode
- `singleRead(measurment type)`	Used to start a triggered read sample
- `sleep()`  puts the sensor to sleep for low power consumption

These are the different "measurement types" that can be used with the `start()` or `singleRead()` commands  
- `massFlow`  	
- `differential`  
- `massFlowAverage`  
- `massFlowCS`	 
- `differentialAverage`  	
- `differentialCS`  

Once a start or single read command has been sent, you can use one of the commands below to get data from the sensor
- `getTempC()` 	Returns temperature in °Celsius as a floating point  
- `getTempF()`	Returns temperature in °Fahrenheit as a floating point  
- `getPressure()`	Returns pressure in pascals as a floating point  
- `getPressureInches()`	Returns pressure in inches water column as a floating point  
- `getScale()`	Returns sensor scaling factor  

---
To use this library, first include it in your arduino sketch  
`#include <SDP810.h>`

Then assign a name to your sensor  
`SDP810 mySensor;`

Next you will need to call the i2c Start function in your setup  
`i2cStart();`  

After that, you can use any of the commands with yoursensorname.command  
`mySensor.singleRead(massFlow);`

See the example sketch to get a better understanding.

