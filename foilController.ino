/*
    Name:       PWMmeasure.ino
    Created:	5/22/2018 8:32:20 PM
    Author:     LIDDY-PC\Eric
*/

#include <TinyGPS++.h>
#include <SD.h>
#include <Servo.h>

Servo myservo;
File myFile;
TinyGPSPlus gps;

// 5.0V to sensor
// Output will be centered @ 2.5V
// IMPORTANT: connect so current reduces voltage to analog in
//(feed the wire from exposed ferrite side to enclosed side)
// Analog reading @ 0A = 5.61/2 * 1024 / 5 = 574(actual reading 580)
// A @ 0.0327 V / A => 2.5V - 2.35V = 0.15V => reading 154
const byte a_pin = A0;
const int zero_point = 586;
const float amp_per_step = 0.366; // 2.2 / (586 - 580) Values to be adjusted/calibrated
int steps;
float current;
double speed = 0;

const int CH3buttonPin = 5;
const int reciverCH3switchPin = 6;
const int temperaturePin = 8;
bool pumpOn = true;
bool forcedOn = true;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  myservo.attach(reciverCH3switchPin);
  myservo.write(135);

  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  delay(1000);
}

void loop()
{

  while (Serial1.available() > 0) {
    byte gpsData = Serial1.read();
    //Serial.write(gpsData);

    gps.encode(gpsData);
    if (gps.location.isUpdated()) {
      //Serial.print("Latitude= ");
      //Serial.print(gps.location.lat(), 6);
      //Serial.print(" Longitude= ");
      //Serial.println(gps.location.lng(), 6);
      //Serial.print(" Speed= ");
      //Serial.println(gps.speed.mph(), 2);
      speed = gps.speed.mph();
    }
  }

  int currentSensorAnalog = analogRead(a_pin);
  //Serial.print(currentSensorAnalog); Serial.println(" reading");
  steps = zero_point - analogRead(a_pin);
  current = amp_per_step * steps;
  //Serial.print(current); Serial.println(" amps");

  //getting the voltage reading from the temperature sensor
  int reading = analogRead(temperaturePin);
  // converting that reading to voltage
  float voltage = reading * 5.0; voltage /= 1024.0;
  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)

  int CH3button = pulseIn(CH3buttonPin, HIGH, 25000);
  Serial.print(CH3button); Serial.println(" CH3 value");

  // no longer forced on
  if (CH3button > 1500 & forcedOn) {
    forcedOn = false;     
  }

  // if signal is lost then force pump back on.
  if (CH3button<=500 & !forcedOn) {
    forcedOn = true;
    myservo.write(135);
    pumpOn = true;
  }
  //pump must be on before it can be turned off and button must be at high value
  //  below 500 indicates receiver lost connection, keep pump on. 
  if ((CH3button <= 1500 & CH3button > 500) & pumpOn & !forcedOn) {
    myservo.write(45);
    pumpOn = false;
  } 

  //pump must be on before it can be turned off
  if (CH3button > 1500 & !pumpOn & !forcedOn) {
    myservo.write(135);
    pumpOn = true;
  }

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

  myDelay(500);

}

void myDelay(int mseconds) {
  // this delay keeps the arduino working, built in delay stops most activity
  //   this type of delay seems to be needed to make the servo libarary work
  //   not sure why.
  unsigned long starttime = millis();   //going to count for a fixed time
  unsigned long endtime = starttime;
  while ((endtime - starttime) <= (unsigned long)mseconds) // do the loop
  {
    endtime = millis();                  //keep the arduino awake.
  }
}
