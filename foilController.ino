
/*
    Name:       foilController.ino
    Created:	5/22/2018 8:32:20 PM
    Author:     Eric
*/

double current = 0;
double gpsSpeed = 0;
double gpsLat = 0;
double gpsLng = 0;
double temperatureC = 0;
double ampSecondsConsumed = 0;
int sensorReadInterval = 500;
int currentAnalog = 0;  //I logged this value when I calibrated the current sensor
bool pumpOn = true;
unsigned long currentReadPeriod=0;

void setup() {
  Serial.begin(9600);
  myDelay(5000);   //seems needed before serial output will work
  initPumpPower();
  initReceiverPower();
  initSD();
  initGPS();
  initBuzzer();
  initRPM();
}

void loop()
{
  readGPS();
  readCurrent();
  readTemperature();
  readCH3pwm();
  calcRPM();  
  // sound alarm when 2.5AmpHrs are consumed.
  if (ampSecondsConsumed > 9000) { 
    Serial.println("power warning");
    beep();
    pulseReceiverPower(); 
  };
  writeDataToLog();
  myDelay(sensorReadInterval);
}
