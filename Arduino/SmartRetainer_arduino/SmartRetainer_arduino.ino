/*
  SmartRetainer_arduino.ino

  Austin Bergman
  Andrew Frey
  Kieran Holland
  Brenden Krevis
  12/15/2017
  Kulkarni Orthodontics Retainer Sensor Project
  Fall 2017

  Arduino code for controlling the SmartRetainer retainer device.

*/

/* LIBRARIES */
#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <SD.h>
#include <math.h>


/* CONSTANTS */
const String DATA_FILE = "data.txt";
const String ID_FILE = "id.txt";
const int chipSelect = 3;
const int baud = 9600;
const time_t startTime = 1512249503; // Epoch Time for Saturday, December 2, 2017 4:18:23 PM GMT-05:00.
                                     // Chosen as a date close to the project demo so the time keeping 
                                     // code does not display dates from 1970.
const int sampling_period = 100;

/* VARIABLES */
time_t cur_time, last_time = 0;
unsigned long last_millis = 0;
float temp, ph, lat_f1, lat_f2;
long bite_f1, bite_f2;
int temp_pin = A0;
int ph_pin = A1;
int lat_pin1 = A2;
int lat_pin2 = A3;
int bite_pin1 = A4;
int bite_pin2 = A5;

/* SETUP */
void setup() {
  //Begin serial communication. Enables Bluetooth capabilities.
  Serial.begin(baud);
  
  //Pin assignments
  pinMode(temp_pin, INPUT);
  pinMode(ph_pin, INPUT);
  pinMode(lat_pin1, INPUT);
  pinMode(lat_pin2, INPUT);
  pinMode(bite_pin1, INPUT);
  pinMode(bite_pin2, INPUT);
  
  //SD setup
  boolean sd_ready = false;
  for(int i = 1; i <= 5 && !sd_ready; i++) {
    sd_ready = SD.begin(chipSelect);
  }
  
  //Set the current time
  setTime(startTime);
}

/* MAIN LOOP */
void loop() {
   cur_time = now(); //get current time
   
   // Read the sensors (at most) every #{sampling_period} milliseconds
   // and save the data.
   if(abs(millis() - last_millis) >= sampling_period) {
     // read sensors
     temp = temp_sensor(temp_pin);
     ph = pH_sensor(ph_pin);
     lat_f1 = pressure_sensor(lat_pin1);
//     lat_f2 = pressure_sensor(lat_pin2);
     lat_f2 = 1;
     bite_f1 = bite_sensor(bite_pin1);
     bite_f2 = bite_sensor(bite_pin2);
     save_data(cur_time, temp, ph, lat_f1, lat_f2, bite_f1, bite_f2);
     last_millis = millis();
   }
   
   // If data as been received at the serial port. Occurs, when
   // a command is sent from the mobile app.
   if(Serial.available() > 0) {
      char command = Serial.read();
      switch(command) {
        //send all data on SD card, then wipe the card
        case 'r': send_all_data(); break;
        //delete data on the card
        case 'd': delete_data(); break;
        //send the most recent data collected
        case 'o': send_one(cur_time, temp, ph, lat_f1, lat_f2, bite_f1, bite_f2); break;
        //send the ID number
        case 'i': send_id(); break;
        //send an error message
        default: send_error(); break;
      }
   }
}
