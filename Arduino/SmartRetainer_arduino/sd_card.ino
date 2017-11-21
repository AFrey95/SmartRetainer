void save_data(long time, int temp, int ph, int lat_f1, int lat_f2, int bite_f1, int bite_f2, int bite_f3, int bite_f4) {
  String dataString = String(time)
                    + ", " + String(temp) 
                    + ", " + String(ph)
                    + ", " + String(lat_f1)
                    + ", " + String(lat_f2)
                    + ", " + String(bite_f1)
                    + ", " + String(bite_f2)
                    + ", " + String(bite_f3)
                    + ", " + String(bite_f4);

//  Serial.println("Trying to write to " + DATA_FILE);
  File data = SD.open(DATA_FILE, FILE_WRITE);
  if(data) {
    data.println(dataString);
    data.close();
  }
//    Serial.println("Write successful.");
//  } else {
//    Serial.println("Could not write");
//  }
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
