#include <SPI.h>
#include <SD.h>

const String DATA_FILE = "data.txt";
const int chipSelect = 4;
const int baud = 9600;
//bool serialConnected = false;
//String command = "";
long time;
int temp, ph, lat_f1, lat_f2, bite_f1, bite_f2, bite_f3, bite_f4;

void setup() {
  // put your setup code here, to run once:
  SD.begin(chipSelect);
  Serial.begin(baud);
  
}

void loop() {
   // read sensors
   
   // store data
   if(true) { //Replace this with some timing check
      save_data(time, temp, ph, lat_f1, lat_f2, bite_f1, bite_f2, bite_f3, bite_f4);
   }
   
   // if bt connection
   if(Serial.available() > 0) {
      String command = Serial.read();
      // if get download command
      if(command == "download") {
          //download
          send_data();
      } else if(command == "delete") {
      // if get delete command
          //delete
          delete_data();
      }
   }   
}
