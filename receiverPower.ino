#include <Servo.h>
static Servo throttle;
int throttleNeutral = 1450;

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
    Serial.println("Power warning ramp down throttle");
    rampDownThrottle();
  }
}

void relayCH2() {
  throttle.writeMicroseconds(readCH2());
}

void rampDownThrottle() {
  int rampRate = 100;  //microseconds per second
  int CH2width = readCH2();
  int rampHeight = CH2width - throttleNeutral;
  unsigned long rampPeriod = ((double)rampHeight/rampRate)*1000L;        
  unsigned long tStart = millis();
  unsigned long tCurrent = 0;
  do {
    tCurrent = millis()-tStart;
    int rampValue = ((double)rampHeight/rampPeriod)*tCurrent;    
    throttle.writeMicroseconds(CH2width-rampValue);
    //Serial.println(CH2width-rampValue);
  } while (tCurrent < rampPeriod);
}

int readCH2() {
  const int CH2inputPin = 2;  
  return pulseIn(CH2inputPin, HIGH, 25000); 
}
