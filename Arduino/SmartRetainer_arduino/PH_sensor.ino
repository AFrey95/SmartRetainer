/*
  Austin Bergman
  11/12/2017
  Kulkarni Orthodontics Retainer Sensor Project
  Fall 2017

  PH_sensor(apin)
  
  Input:
  int apin: analog input pin to which the pH sensor is connected
  
  Output:
  float phValue: measured pH value ranging from 0.0 to 14.0

*/

float PH_sensor(int apin)
{
  // define variables
  unsigned long int avgValue;  //Store the average value of the sensor feedback
  float phValue; // measured PH value
  int buf[10], temp;

  //Get 10 sample values from the sensor in order to smooth the output
  for (int i = 0; i < 10; i++) 
  {
    buf[i] = analogRead(apin); // store the readings in an array
    delay(10);
  }
  for (int i = 0; i < 9; i++) //sort the analog from small to large
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)               //take the average value of 6 center sample
    avgValue += buf[i];
  phValue = (float)avgValue * 5.0 / 1024 / 6; //convert the analog into millivolt
  phValue = 3.5 * phValue - 0.70; // PH value calibrated by shifting down by 0.70 12/1/17

  return phValue; // pH value between 0.0 and 14.0 returned
}
