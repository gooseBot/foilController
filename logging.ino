#include <SD.h>
File logFile;
char newfile[50];

void writeDataToLog() {
  if (pumpOn) {
    logFile = SD.open(newfile, FILE_WRITE);
    if (logFile) {
      logFile.print(millis());  logFile.print(",");
      logFile.print(current);  logFile.print(",");
      logFile.print(currentAnalog);  logFile.print(",");
      logFile.print(ampSecondsConsumed);  logFile.print(",");
      logFile.print(temperatureC); logFile.print(",");
      //logFile.println(temperatureC);
      logFile.print(lat,6); logFile.print(",");
      logFile.print(lng,6); logFile.print(",");
      logFile.println(speed); 
      logFile.close(); // close the file
    }
    //if the file didn't open, print an error:
    else {
      Serial.println("error opening output file");
      Serial.println(newfile);
    }
  }
}

void initSD() {
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  sprintf(newfile, "%u.csv", millis());
  Serial.println(newfile);
  logFile = SD.open(newfile, FILE_WRITE);
  if (logFile) {
    logFile.println("********* foilController Started **********");
    logFile.println("millis,current,currentAnalog,ampSecondsConsumed,temperatureC,lat,lng,speed"); 
    logFile.close(); // close the file
  } else {
    Serial.println("error opening output file");
  }
}
