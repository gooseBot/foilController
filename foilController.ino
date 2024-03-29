/*
    Name:       foilController.ino
    Created:	5/22/2018 8:32:20 PM
    Author:     Eric
*/

/*
  Pins in use
  0,1 HC12 (serial1)
  2 CH2inputPin  
  3 batteryButtonPin
  4 temperaturePin
  5 ESCpin
  6 pumpPowerRelayPin
  7 rpmPulsePin
  9 BuzzerPin
  10 SD select
  14,15,16 SPI
  18 (A0) current
*/
 
// ino tabs are joing in alpha order before compiling
// variables must be declared before used.  So order of tabs is important
// writeLog is last as it uses variables defined earlier.

double ampSecondsConsumed = 0.0;
double ampSecondsWarning = 0.0;
double current = 0.0;
double maxCurrentThreshhold = 140.0;
double minCurrentThreshhold = 3.0;
double maxTempThreshhold = 50.0;
double temperatureC = 0.0;

void setup() {
   Serial.begin(9600);
   myDelay(3000);   //seems needed before serial output will work   
   initPumpPower();
   initReceiverPower();
   initSD();
   initBuzzer();
   initRPM();
   initBatterySize();
   initHC12();
}

void loop()
{
   int sensorReadInterval = 500;
  
   readCurrent();
   readTemperature();
   setPumpState();
   readBatteryButton();
   calcRPM();  
   // sound alarm when battery AmpHrs are nearly consumed.
   if (ampSecondsConsumed > ampSecondsWarning) {
      Serial.println("battery alarm");
      beep();
      pulseReceiverSignal(); 
   };
   // Kill throttle if over amp draw limit.
   if (current > maxCurrentThreshhold) {
      Serial.println("over current");
      beep();
      pulseReceiverSignalOverLimits(); 
   };
   // Kill throttle if over temp limit.
   if (temperatureC > maxTempThreshhold) {      
      Serial.println("over temperature");
      Serial.println(temperatureC);
      beep();      
      //pulseReceiverSignalOverLimits(); 
      writeDataToLog();
   };
   
   writeDataToLog();
   myDelay(sensorReadInterval);
}
