#include "TinyGPS++.h"
TinyGPSPlus gps;

void readGPS() {
  while (Serial1.available() > 0) {
    byte gpsData = Serial1.read();
    //Serial.write(gpsData);

    gps.encode(gpsData);
    if (gps.location.isUpdated()) {
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);
      Serial.print(" gpsSpeed= ");
      Serial.println(gps.speed.mph(), 2);
      gpsSpeed = gps.speed.mph();
      gpsLat = gps.location.lat();
      gpsLng = gps.location.lng();
    }
  }
}

void initGPS() {
  Serial1.begin(9600);
}
