#include <Servo.h>
static Servo throttle;
bool disableESC = false;

void initReceiverPower() {
  const int ESCpin = 5;
  throttle.attach(ESCpin);
  throttle.writeMicroseconds(1450);
}

// this  is done as a low battery warning to the user
//   pulse power 3 times to get their attention
//   do it while foil operating
void pulseReceiverPower() {
  static int warningCount=0;
  
  if (current > 20 && warningCount < 2) {
    warningCount++;
    Serial.println("Receiver off");
    disableESC=true;
    myDelay(1000);                    //for a bit to get my attention.
    disableESC=false;
    Serial.println("Receiver on");
    myDelay(1000);                    //for a second at least.
  }
}

void relayCH2() {
  const int CH2inputPin = 2;  
  int CH2width = pulseIn(CH2inputPin, HIGH, 25000);
  //values range from about 1450 to 2000 from the receiver.
  if (disableESC) {
    throttle.writeMicroseconds(1450);
  } else {
    throttle.writeMicroseconds(CH2width);
  }
}
