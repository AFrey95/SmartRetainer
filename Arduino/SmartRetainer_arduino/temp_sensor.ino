#include <math.h>

double temp_sensor(int apin){
    double tempF; // output temperature in degrees Farenheit
    double tempC; // output temperature in degrees Celcius
    double temp0 = 25; // 25 degrees C
    int R0 = 10000; // Thermistor resistance at 25 degrees C
    double R; // Measured Thermistor Resistance
    int Ra = 10000; // fixed resistor used in voltage divider circuit
    double B = 3428; // B constant for 25 to 80 degrees C for NXFT15H103FA
    int apin; // analog input pin
    int vdig = analogRead(apin); // reads in value between 0 and 1024 for input voltage
    int v_source = 5; // source voltage used for circuit
    
    // convert reference voltage value to actual sensed voltage
    double v_sense = vdig/1024*v_source; 
    
    // calculate R
    R = v_sense/(v_souce-v_sense)*Ra;
    
    // calculate temperature in Celcius
    tempC = 1/((1/temp0)+(1/B*log(R/R0)));
    
    // convert Celcius to Farenheit
    tempF = tempC*1.8 + 32;
    
    return tempF;
} 

