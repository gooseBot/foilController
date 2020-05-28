#include <SD.h>
File logFile;
char newfile[13];

void writeDataToLog() {
  if (pumpOn) {
    logFile = SD.open(newfile, FILE_WRITE);
    if (logFile) {
      logFile.print(millis());  logFile.print(",");
      logFile.print(rpm);  logFile.print(",");
      logFile.print(current);  logFile.print(",");
      logFile.print(currentAnalog);  logFile.print(",");
      logFile.print(currentReadPeriod);  logFile.print(",");
      logFile.print(ampSecondsConsumed);  logFile.print(",");
      logFile.print(temperatureC); logFile.print(",");
      //logFile.println(temperatureC);
      logFile.print(gpsLat,6); logFile.print(",");
      logFile.print(gpsLng,6); logFile.print(",");
      logFile.print(gpsSpeed); logFile.print(",");
      logFile.println(ampSecondsWarning);
      logFile.close(); // close the file
    } else {
      Serial.println("error opening output file");
      Serial.println(newfile);
    }
  }
}

void initSD() {
  Serial.println("init SD");
  
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  
  for (int i = 0; i <= 255; i++) {
     sprintf(newfile, "data%03d.csv", i);
     Serial.print(newfile);
     if (SD.exists(newfile)) {
        Serial.println(" exists");
     } else {
        Serial.println(" to be created");
        break;
     }
  }
  
  logFile = SD.open(newfile, FILE_WRITE);
  
  if (logFile) {
    logFile.println("********* foilController Started **********");
    logFile.println("millis,rpm,current,currentAnalog,currentReadPeriod,ampSecondsConsumed,temperatureC,lat,lng,gpsSpeed,ampSecondsWarning"); 
    logFile.close(); // close the file
    Serial.println("created log file");
  } else {
    Serial.println("error opening output file");
  }
  
}
