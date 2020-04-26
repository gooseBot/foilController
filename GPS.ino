#include "TinyGPS++.h"
TinyGPSPlus gps;

double gpsSpeed = 0;
double gpsLat = 0;
double gpsLng = 0;

void readGPS() {
  while (Serial1.available() > 0) {
    byte gpsData = Serial1.read();
    //Serial.write(gpsData);

    gps.encode(gpsData);
    if (gps.location.isUpdated()) {
      gpsSpeed = gps.speed.mph();
      gpsLat = gps.location.lat();
      gpsLng = gps.location.lng();
    }
  }
}

void initGPS() {
  Serial1.begin(9600);
}
