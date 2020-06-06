/*
    Name:       foilController.ino
    Created:	5/22/2018 8:32:20 PM
    Author:     Eric
*/

/*
  Pins in use
  0,1 GPS (serial1)
  2 CH2inputPin
  3 CH3inputPin
  5 ESCpin
  6 pumpPowerRelayPin
  7 rpmPulsePin
  8 temperaturePin
  9 Buzzer
  10 SD select
  18 (A0) current
  14,15,16 SPI
*/
 
// ino tabs are joing in alpha order before compiling
// variables must be declared before used.  So order of tabs is important
// writeLog is last as it uses variables defined earlier.

double ampSecondsConsumed = 0;
int ampSecondsWarning = 0;

void setup() {
   Serial.begin(9600);
   myDelay(3000);   //seems needed before serial output will work
   initPumpPower();
   initReceiverPower();
   initSD();
   initGPS();
   initBuzzer();
   initRPM();
   initBatteryWarningLevel();
}

void loop()
{
   int sensorReadInterval = 500;
  
   readGPS();
   readCurrent();
   readTemperature();
   setPumpState();
   calcRPM();  
   // sound alarm when battery AmpHrs are consumed.
   if (ampSecondsConsumed > ampSecondsWarning) {
      beep();
      pulseReceiverPower(); 
   };  
   writeDataToLog();
   myDelay(sensorReadInterval);
}
