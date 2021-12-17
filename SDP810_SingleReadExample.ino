/*
 * This is an example  sketch showing how to use the SDP810-ArduinoLibrary
 * This Sketch starts the sensor in continuous measurement mode and prints out the current measurment every second
 */

#include <SDP810.h> //include library

SDP810 mySensor;    //give your sensor a name

float temp;         //declare your variables to store your information
float pressure;
float scale;

void setup() {
  Serial.begin(115200); // Start Serial port to dispaly output
  i2cStart();           // Start the i2C communication to the sensor
}

void loop() {

  mySensor.singleRead(massFlowCS);// tell the sensor to take a measurement (measurement type: Mass Flow with i2c Clock Streching)
  Serial.println("Starting Single Measurement");

  delay(45);  // wait 45ms for sensor to finish reading

  temp = mySensor.getTempF(); //request the temperature from your sensor and store in the variable temp
  Serial.print("Temperature F is: ");//print the temperature to the serial port
  Serial.println(temp);
  Serial.println("");
  

  mySensor.singleRead(massFlowCS);// Tell the sensor to take a measurement (measurement type: Mass Flow with i2c Clock Streching)
  Serial.println("Starting Single Measurement");
  
  delay(45);  // wait 45ms for sensor to finish reading
  
  pressure = mySensor.getPressure();//request the pressure from your sensor and store it in the variable pressure
  Serial.print("Pressure is: ");//print the pressure to the serial port
  Serial.println(pressure);
  Serial.println("\n");
  
  delay(1000);// wait one second before taking the second measurement
  
}
