#include <SD.h>
File logFile;
char newfile[13];

void writeDataToLog() {
  if (current > currentThreshhold) {
    logFile = SD.open(newfile, FILE_WRITE);
    if (logFile) {
      logFile.print(millis()/1000/60.0);  logFile.print(",");
      logFile.print(rpm);  logFile.print(",");
      logFile.print(current);  logFile.print(",");
      logFile.print(currentAnalog);  logFile.print(",");
      logFile.print(currentReadPeriod);  logFile.print(",");
      logFile.print(ampSecondsConsumed/3600.0);  logFile.print(",");
      logFile.print(temperatureC); logFile.print(",");
      logFile.print(ampSecondsWarning); logFile.print(",");
      //logFile.print(CH2pwm); logFile.print(",");      
      logFile.println(readHC12()); 
      logFile.close();
    } else {
      Serial.println(F("error opening output file"));
      Serial.println(newfile);
    }
  }
}

void initSD() {
  Serial.println(F("init SD"));
  
  if (!SD.begin(10)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  
  for (int i = 0; i <= 255; i++) {
     sprintf(newfile, "data%03d.csv", i);
     Serial.print(newfile);
     if (SD.exists(newfile)) {
        Serial.println(F(" exists"));
     } else {
        Serial.println(F(" to be created"));
        break;
     }
  }
  
  logFile = SD.open(newfile, FILE_WRITE);
  
  if (logFile) {
    logFile.println(F("********* foilController Started **********"));
    //logFile.println(F("time,rpm,current,currentAnalog,currentReadPeriod,ampHoursConsumed,temperatureC,ampSecondsWarning,CH2,HC12")); 
    logFile.println(F("time,rpm,current,currentAnalog,currentReadPeriod,ampHoursConsumed,temperatureC,ampSecondsWarning,HC12")); 
    logFile.close(); 
    Serial.println(F("created log file"));
  } else {
    Serial.println(F("error opening output file"));
  }
  
}
