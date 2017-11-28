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
  temp = 0; ph = 0; lat_f1 = 0; lat_f2 = 0; bite_f1 = 0; bite_f2 = 0; bite_f3 = 0; bite_f4 = 0;
  Serial.print("Setup done\n");
}

void loop() {
   // read sensors
   
   // store data
   if(true) { //Replace this with some timing check
      save_data(time, temp, ph, lat_f1, lat_f2, bite_f1, bite_f2, bite_f3, bite_f4);
   }
   
   // if bt connection
   if(Serial.available() > 0) {
      char command = Serial.read();
      // if get download command
      if(command == 'r') {
          //download
          send_data();
      // if get delete command
      } else if(command == 'd') {
          //delete
          delete_data();
      }
   }
}
