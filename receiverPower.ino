#include <Servo.h>
#include "CRC8.h"

CRC8 crc;

static Servo throttle;
//int throttleNeutral = 1450;
int throttleNeutral = 1400;
int HC12pwm = 0;
//int CH2pwm = 0;

void initHC12() {
  Serial1.begin(9600);
  Serial1.setTimeout(100);
}

void initReceiverPower() {
  const int ESCpin = 5;
  throttle.attach(ESCpin);
  throttle.writeMicroseconds(throttleNeutral);  
}

// this  is done as a low battery warning to the user
//   pulse power 2 times to get their attention
//   do it while foil operating
void pulseReceiverSignal() {
  static int warningCount=0;  
  if (current > 20 && warningCount < 2) {
    warningCount++;
    Serial.println(F("Power warning ramp down throttle"));
    rampDownThrottle();
  }
}

//void relayCH2() {
//  throttle.writeMicroseconds(readCH2());
//  //Serial.println(CH2pwm);
//}

void relayHC12() {
  throttle.writeMicroseconds(readHC12());
  //Serial.println(readHC12());
}

void rampDownThrottle() {
  int rampRate = 50;  //microseconds per second
  int PWMwidth = readHC12();
  int rampHeight = PWMwidth - throttleNeutral;
  unsigned long rampPeriod = ((double)rampHeight/rampRate)*1000L;        
  unsigned long tStart = millis();
  unsigned long tCurrent = 0;
  do {
    tCurrent = millis()-tStart;
    int rampValue = ((double)rampHeight/rampPeriod)*tCurrent;    
    throttle.writeMicroseconds(PWMwidth-rampValue);
    myDelay(100);
    //Serial.println(CH2width-rampValue);
  } while (tCurrent < rampPeriod);
}

//int readCH2() {
//  const int CH2inputPin = 2;  
//  CH2pwm = pulseIn(CH2inputPin, HIGH, 25000); 
//  return CH2pwm;
//}

int readHC12() {
  static unsigned long lastPWMreadingTime = 0;  
  //first time through this needs to be set
  if (lastPWMreadingTime==0) {lastPWMreadingTime=millis();}
  static int returnValue;
    
  if (Serial1.available()>0) {        // If HC-12 has data
    String s = Serial1.readStringUntil('\n');  //look into timeout
    //Serial.println(s);
    int commaIndex = s.indexOf(',');
    String sPWM = s.substring(0, commaIndex);
    String sCRC = s.substring(commaIndex + 1);    
    int PWM = sPWM.toInt();    
    int CRC = sCRC.toInt();    
        
    byte lByte= lowByte(PWM);
    byte hByte= highByte(PWM);
    crc.add(lByte);
    crc.add(hByte);
    int xmitCRC = crc.getCRC();        
    crc.restart();
    
    if (xmitCRC==CRC && commaIndex>0 && PWM>1400 && PWM <2100) {   
      returnValue = PWM;   
      lastPWMreadingTime = millis();      
    } 
  }
  unsigned long PWMreadPeriod = millis() - lastPWMreadingTime;
  if (PWMreadPeriod > 500){
    return 0;
  } else {
    return returnValue;
  }
}
