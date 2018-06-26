/*
    Name:       foilController.ino
    Created:	5/22/2018 8:32:20 PM
    Author:     Eric
*/

float current;
double speed = 0;
float temperatureC;
bool pumpOn = true;

void setup() {
  Serial.begin(9600);
  initCH3();
  initSD();
  initGPS();
  delay(1000);
}

void loop()
{
  readGPS();
  readCurrent();
  readTemperature();
  readCH3pwm();
  writeDataToLog();
  myDelay(500);
}



