#include <SD.h>
File myFile;

void writeDataToLog() {
  if (pumpOn) {
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.print(current);  myFile.print(",");
      myFile.print(temperatureC); myFile.print(",");
      myFile.println(speed);
      myFile.close(); // close the file
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
}
