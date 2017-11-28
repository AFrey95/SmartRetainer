#include <SPI.h>
#include <SD.h>

const String DATA_FILE = "data.txt";
const int chipSelect = 4;
const int baud = 9600;
//bool serialConnected = false;
//String command = "";
long time;
float temp, ph, lat_f1, lat_f2, bite_f1, bite_f2;
//bite_f3, bite_f4;
int temp_pin = A0;
int ph_pin = A1;
int lat_pin1 = A2;
int lat_pin2 = A3;
int bite_pin1 = A4;
int bite_pin2 = A5;

void setup() {
  // put your setup code here, to run once:
  pinMode(temp_pin, INPUT);
  pinMode(ph_pin, INPUT);
  pinMode(lat_pin1, INPUT);
  pinMode(lat_pin2, INPUT);
  pinMode(bite_pin1, INPUT);
  pinMode(bite_pin2, INPUT);
  
  SD.begin(chipSelect);
  Serial.begin(baud);
}

void loop() {
   if(true) { //Replace this with some timing check
      // read sensors
     temp = temp_sensor(temp_pin);
     ph = PH_sensor(ph_pin);
     lat_f1 = pressure_sensor(lat_pin1);
     lat_f2 = pressure_sensor(lat_pin2);
     bite_f1 = pressure_sensor(bite_pin1);
     bite_f2 = pressure_sensor(bite_pin2);
     
     // store data
     save_data(time, temp, ph, lat_f1, lat_f2, bite_f1, bite_f2);
   }
   
   // if bt connection
   if(Serial.available() > 0) {
      char command = Serial.read();
      // if get download command
      if(command == 'r') {
          //download
          send_data();
      } else if(command == 'd') {
      // if get delete command
          //delete
          delete_data();
      }
      
   }
}
