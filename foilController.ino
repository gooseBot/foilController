/*
    Name:       foilController.ino
    Created:	5/22/2018 8:32:20 PM
    Author:     Eric
*/

double current = 0;
double speed = 0;
double lat = 0;
double lng = 0;
double temperatureC = 0;
double ampSecondsConsumed = 0;
int sensorReadInterval = 500;
int currentAnalog = 0;  //I logged this value when I calibrated the current sensor
bool pumpOn = true;

void setup() {
  Serial.begin(9600);
  initCH3();
  initSD();
  initGPS();
  initBuzzer();
  delay(1000);
}

void loop()
{
  readGPS();
  readCurrent();
  readTemperature();
  readCH3pwm();
  writeDataToLog();
  // sound alarm when 2.5AmpHrs are consumed.
  if (ampSecondsConsumed > 9000) { beep(); };
  myDelay(sensorReadInterval);
}



