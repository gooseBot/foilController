#include <SD.h>
File logFile;

void writeDataToLog() {
  if (pumpOn) {
    logFile = SD.open("test.txt", FILE_WRITE);
    if (logFile) {
      logFile.print(current);  logFile.print(",");
      logFile.print(ampSecondsConsumed);  logFile.print(",");
      logFile.print(temperatureC); logFile.print(",");
      logFile.println(speed);
      logFile.close(); // close the file
    }
    //if the file didn't open, print an error:
    else {
      Serial.println("error opening test.txt");
    }
  }
}

void initSD() {
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  logFile = SD.open("test.txt", FILE_WRITE);
  if (logFile) {
    logFile.println("********* foilController Started **********"); 
    logFile.close(); // close the file
  } else {
    Serial.println("error opening test.txt");
  }
}
