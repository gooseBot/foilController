#include <Servo.h>
static Servo receiverPowerSwitch;
const int receiverPowerSwitchPin = 4;

void initReceiverPower() {
  receiverPowerSwitch.attach(receiverPowerSwitchPin);
  receiverPowerSwitch.write(135);  
}

// this  is done as a low battery warning to the user
//   pulse power 3 times to get their attention
//   do it while foil operating
void pulseReceiverPower() {
  static int warningCount=0;
  
  if (current > 20 && warningCount < 2) {
    warningCount++;
    Serial.println("Receiver off");
    receiverPowerSwitch.write(45);    //turn off receiver
    myDelay(1000);                    //for a bit to get my attention.
    receiverPowerSwitch.write(135);   //turn on receiver
    Serial.println("Receiver on");
    myDelay(1000);                    //for a second at least.
  }
}
