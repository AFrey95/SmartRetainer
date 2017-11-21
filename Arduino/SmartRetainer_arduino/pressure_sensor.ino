//pin declaration
int ain= A1;
float value;

float Pressure_sensor_test(int ain) {
  float fsrForce;
  float fsrConductance;
  float fsrResistance;
  float fsrVoltage;
  float fsrReading;
  
  fsrReading = analogRead(A1);  
 
 
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
   
 
  if (fsrVoltage == 0) {
    
  } else {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;
   
 
    fsrConductance = 1000000;           // we measure in micromhos so 
    fsrConductance /= fsrResistance;
    
    
 
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
           
    } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
                 
    }
  
 }
 return(fsrForce);
}
