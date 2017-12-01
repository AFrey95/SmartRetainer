#include <math.h>

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
    //vdig = analogRead(apin);
    
    // calculate average of last number of samples
    int numsamples = 10;
    int buf[numsamples];
    for(int i = 1; i<= numsamples; i++)
    {
       buf[i] = analogRead(apin); // reads in value between 0 and 1024 for input voltage
    }
    
    for(int j = 1; j<=numsamples; j++) // add up all the samples
    {
       sumvdig = sumvdig + buf[j]; 
    }
    vdig = sumvdig/numsamples; //divide by number of samples to get average
    
    
    // convert reference voltage value to actual sensed voltage
    float v_sense;
    v_sense = (vdig * v_source) / 1024; 
   

    
    
    // calculate R
    R = v_sense/(v_source-v_sense)*Ra;
    
    // calculate temperature in Kelvin
    tempK = 1/((1/temp0K)+(1/B*log(R/R0)));
    
    // convert Kelvin to Celcius
    tempC = tempK - 273.15;
    
    // convert Celcius to Farenheit
    tempF = tempC*1.8 + 32;
    
    // scale tempF for output ONLY TEMP F WILL BE CALIBRATED
    tempF = 1.05 * tempF + 6;
    
    return tempF;
} 
