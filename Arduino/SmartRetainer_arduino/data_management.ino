/*
  Austin Bergman
  Andrew Frey
  Kieran Holland
  Brenden Krevis
  12/15/2017
  Kulkarni Orthodontics Retainer Sensor Project
  Fall 2017

  void save_data(time_t t, float temp, float ph, float lat_f1, float lat_f2, long bite_f1, long bite_f2)
    This function takes in the current Epoch time and 6 data points. The data is then concatenated
    into a string, separating each value with a comma-space. The string of data is then appended
    with a newline to the file on the SD card, specified by the global variable DATA_FILE.

  bool delete_data()
    Deletes the file spceified by the global variable DATA_FILE. Returns true if the data was
    sucessfully deleted. Returns false otherwise.

  voic send_all_data()
    Uses the serial port to send all the data in the file specified by the global varialbe
    DATA_FILE. If data was successfully send, the data is then deleted from the SD card by
    calling delete_data().

  void send_one(time_t t, float temp, float ph, float lat_f1, float lat_f2, long bite_f1, long bite_f2)
    Recives and concatenates data identically to save_data(...), then immediately sends the data via
    serial and does not save the data.

  void send_id()
    Used to send ID information. Sends all the data in the file specified by the global variable ID_FILE.

  void send_error()
    Sends an error message via serial.

*/

void save_data(time_t t, float temp, float ph, float lat_f1, 
               float lat_f2, long bite_f1, long bite_f2) {
  String dataString = String(t)
                    + ", " + String(temp) 
                    + ", " + String(ph)
                    + ", " + String(lat_f1)
                    + ", " + String(lat_f2)
                    + ", " + String(bite_f1)
                    + ", " + String(bite_f2);

//  Serial.println("Trying to write to " + DATA_FILE);
  File data = SD.open(DATA_FILE, FILE_WRITE);
  if(data) {
    data.println(dataString);
    data.close();
  }
}

bool delete_data() {
  return SD.remove(DATA_FILE);
}

void send_all_data() {
  bool sent = false;
  File data = SD.open(DATA_FILE);
  while(data.available()) {
    Serial.write(data.read());
    sent = true;
  }
  data.close();
  if(sent) {
    delete_data();
  }
}

void send_one(time_t t, float temp, float ph, float lat_f1, 
               float lat_f2, long bite_f1, long bite_f2) {
  String dataString = String(t)
                    + ", " + String(temp) 
                    + ", " + String(ph)
                    + ", " + String(lat_f1)
                    + ", " + String(lat_f2)
                    + ", " + String(bite_f1)
                    + ", " + String(bite_f2);
  Serial.println(dataString);
}

void send_id() {
  File data = SD.open(ID_FILE);
  while(data.available()) {
    Serial.write(data.read());
  }
}

void send_error() {
  Serial.println("Command character not recognized. Please send 'r', 'd', or 'o'.");
}

