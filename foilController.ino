
/*
    Name:       foilController.ino
    Created:	5/22/2018 8:32:20 PM
    Author:     Eric
*/

// ino tabs are joing in alpha order before compiling
// variables must be declared before used.  So order of tabs is important
// writeLog is last as it uses variables defined earlier.

double ampSecondsConsumed = 0;

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
   int sensorReadInterval = 500;
  
   readGPS();
   readCurrent();
   readTemperature();
   readCH3pwm();
   calcRPM();  
   // sound alarm when 2.5 AmpHrs are consumed.
   if (ampSecondsConsumed > 9000) {  
      Serial.println("power warning");
      beep();
      pulseReceiverPower(); 
   };  
   writeDataToLog();
   myDelay(sensorReadInterval);
}
