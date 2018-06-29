#include <TinyGPS++.h>
TinyGPSPlus gps;

void readGPS() {
  while (Serial1.available() > 0) {
    byte gpsData = Serial1.read();
    //Serial.write(gpsData);

    gps.encode(gpsData);
    if (gps.location.isUpdated()) {
      //Serial.print("Latitude= ");
      //Serial.print(gps.location.lat(), 6);
      //Serial.print(" Longitude= ");
      //Serial.println(gps.location.lng(), 6);
      //Serial.print(" Speed= ");
      //Serial.println(gps.speed.mph(), 2);
      speed = gps.speed.mph();
      lat = gps.location.lat();
      lng = gps.location.lng();
    }
  }
}

void initGPS() {
  Serial1.begin(9600);
}
