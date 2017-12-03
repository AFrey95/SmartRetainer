void save_data(time_t t, float temp, float ph, float lat_f1, 
               float lat_f2, float bite_f1, float bite_f2) {
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
               float lat_f2, float bite_f1, float bite_f2) {
  String dataString = String(t)
                    + ", " + String(temp) 
                    + ", " + String(ph)
                    + ", " + String(lat_f1)
                    + ", " + String(lat_f2)
                    + ", " + String(bite_f1)
                    + ", " + String(bite_f2);
  Serial.print(dataString);
}

void send_error() {
  Serial.write("Command character not recognized. Please send 'r', 'd', or 'o'.");
}

