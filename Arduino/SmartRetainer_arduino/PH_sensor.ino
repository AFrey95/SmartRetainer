/*
  Austin Bergman
  11/12/2017
  Kulkarni Orthodontics Retainer Sensor Project
  Fall 2017

  PH_sensor(apin)
  This function takes the input of the integer representing the analog pin
  This function also takes in an integer specifying the mode of operation
  which the measurement point of the PH meter is introduced into the system.

  This function returns a PH value ranging from 0.0 to 14.0.

*/
# include <math.h>

float PH_sensor(int apin)
{
  // define variables
  unsigned long int avgValue;  //Store the average value of the sensor feedback
  float phValue; // measured PH value
  int buf[10], temp;

  for (int i = 0; i < 10; i++) //Get 10 sample value from the sensor for smooth the value
  {
    buf[i] = analogRead(apin);
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
  phValue = 3.5 * phValue;

  return phValue;
}
