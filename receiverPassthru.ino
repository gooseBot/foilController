#include <Servo.h>
#include "CRC8.h"

CRC8 crc;

static Servo throttle;
int throttleNeutral = 1450;
int HC12pwm = 0;

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

void pulseReceiverSignalOverAmp() {
  static int warningCount=0;  
  Serial.println(F("Excessive amp draw ramp down throttle"));
  rampDownThrottle();
}

void relayHC12() {
  throttle.writeMicroseconds(readHC12());
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
    //don't use myDelay as that will call relayHC12() 
    //  and defeat purpose of rampDown low battery warning.
    delay(100);  
  } while (tCurrent < rampPeriod);
}

int readHC12() {
  static unsigned long lastPWMreadingTime = 0;  
  //first time through this needs to be set
  if (lastPWMreadingTime==0) {lastPWMreadingTime=millis();}
  static int returnValue;
    
  if (Serial1.available()>0) {                 // If HC-12 has data
    String s = Serial1.readStringUntil('\n');  //look into timeout on readStringUntil
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
  // if its been more than .5 seconds then shut down motor.
  if (PWMreadPeriod > 500){
    return 0;
  } else {
    return returnValue;
  }
}
