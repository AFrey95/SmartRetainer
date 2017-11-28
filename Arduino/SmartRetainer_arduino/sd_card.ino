void save_data(long time, float temp, float ph, float lat_f1, 
               float lat_f2, float bite_f1, float bite_f2) {
  String dataString = String(time)
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

void send_data() {
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

