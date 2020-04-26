#include <Servo.h>
static Servo receiverPowerSwitch;
const int receiverPowerSwitchPin = 4;
bool powerLowWarningIssued = false;

void initReceiverPower() {
  receiverPowerSwitch.attach(receiverPowerSwitchPin);
  receiverPowerSwitch.write(135);  
}

void pulseReceiverPower() {
  if (!powerLowWarningIssued) {
    powerLowWarningIssued=true;
    Serial.println("Receiver off");
    receiverPowerSwitch.write(45);    //turn off receiver
    myDelay(1000);                    //takes three seconds for ESC to turn off.
    receiverPowerSwitch.write(135);   //turn on receiver
    Serial.println("Receiver on");
  }
}
