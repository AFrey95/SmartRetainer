/*
  temp_sensor.ino
  
  Austin Bergman
  Andrew Frey
  Kieran Holland
  Brenden Krevis
  12/13/2017
  Kulkarni Orthodontics Retainer Sensor Project
  Fall 2017
  
  temp_sensor(apin)
  
  This module takes an interger input which indicates which pin the 
  temperature sensor is connected to on the Arduino and it provides a
  temperature output in degrees Farenheit.
  
  Inputs:
  int apin: Analog input pin to which the temperature sensor is connected
  
  Output:
  float tempF:  Measured Temperature of thermistor in degrees Farenheit
*/

float temp_sensor(int apin){
    float tempF; // output temperature in degrees Farenheit
    float tempC; // output temperature in degrees Celcius
    float tempK; // output temperature in Kelvin
    float temp0 = 25; // 25 degrees C
    float temp0K = 273.15 + temp0; // 25 deg C converted to Kelvin
    int R0 = 10000; // Thermistor resistance at 25 degrees C
    float R; // Measured Thermistor Resistance
    int Ra = 10000; // fixed resistor used in voltage divider circuit
    float B = 3428; // B constant for 25 to 80 degrees C for NXFT15H103FA
    float v_source = 5.00; // source voltage used for circuit
    int vdig; // stores value between 0 and 1024 for input voltage
    int sumvdig = 0; 
   
    
    // calculate average of last number of samples
    int numsamples = 10;
    int buf[numsamples];
    // first use loop to store the last numsamples values in an array
    for(int i = 1; i<= numsamples; i++)
    {
       buf[i] = analogRead(apin); // reads in value between 0 and 1024 for input voltage
    }
    
    // used another for loop to sum all of the values in the storage array
    for(int j = 1; j<=numsamples; j++) // add up all the samples
    {
       sumvdig = sumvdig + buf[j]; 
    }
    vdig = sumvdig/numsamples; //divide by number of samples to get average
    
    // convert digital voltage which ranges from 0 to 1024 to the actual
    //   analog voltage which ranges from 0 to v_source
    float v_sense;
    v_sense = (vdig * v_source) / 1024; 
   
    // calculate R of the thermistor using the voltage divider equation
    R = v_sense/(v_source-v_sense)*Ra;
    
    // calculate temperature in Kelvin using the thermistor B equation
    tempK = 1/((1/temp0K)+(1/B*log(R/R0)));
    
    // convert Kelvin to Celcius
    tempC = tempK - 273.15;
    
    // convert Celcius to Farenheit
    tempF = tempC*1.8 + 32;
    
    // scale tempF for output ONLY TEMP F WILL BE CALIBRATED
    tempF = 1.05 * tempF - 6;
    
    return tempF;
} 
