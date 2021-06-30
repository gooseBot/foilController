#include "CRC8.h"

int potPin = 18;  
int buzzerPin = 19;

CRC8 crc;

void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  //delay(4000);
  //https://bgsu.instructure.com/courses/1157282/pages/tutorial-active-buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  delay(500);    
  digitalWrite(buzzerPin, LOW);
  delay(500);      
}

void loop()
{
  int val = analogRead(potPin);
  Serial.print(val);
  val = map(val,735,880,2000,1500);
  String sVal = String(val);
  Serial.println(","+sVal);

  byte lByte= lowByte(val);
  byte hByte= highByte(val);
  crc.add(lByte);
  crc.add(hByte);
  String sCRC = String(crc.getCRC());
  Serial1.println(sVal + "," + sCRC);
  crc.restart();
  delay(100);
}
