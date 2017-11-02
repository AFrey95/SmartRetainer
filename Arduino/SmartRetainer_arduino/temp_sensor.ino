#include <math.h>

double temp_sensor(int apin){
    float tempF; // output temperature in degrees Farenheit
    float tempC; // output temperature in degrees Celcius
    float temp0 = 25; // 25 degrees C
    int R0 = 10000; // Thermistor resistance at 25 degrees C
    float R; // Measured Thermistor Resistance
    int Ra = 10000; // fixed resistor used in voltage divider circuit
    float B = 3428; // B constant for 25 to 80 degrees C for NXFT15H103FA
    int vdig = analogRead(apin); // reads in value between 0 and 1024 for input voltage
    float v_source = 5.00; // source voltage used for circuit
    
    // convert reference voltage value to actual sensed voltage
    float v_sense;
   
    v_sense = (vdig * v_source) / 1024; 
   
    
    // calculate R
    R = v_sense/(v_source-v_sense)*Ra;
    
    // calculate temperature in Celcius
    tempC = 1/((1/temp0)+(1/B*log(R/R0)));
    
    // convert Celcius to Farenheit
    tempF = tempC*1.8 + 32;
    
    return tempF;
} 


