#include <Servo.h>
static Servo receiverCH3switch;
static Servo receiverPowerSwitch;
const int receiverCH3switchPin = 6;
const int receiverPowerSwitchPin = 4;
bool pumpForcedOn = true;
bool powerLowWarningIssued = false;

void readCH3pwm() {
  const int CH3buttonPin = 5;

  int CH3button = pulseIn(CH3buttonPin, HIGH, 25000);
  //Serial.print(CH3button); Serial.println(" CH3 value");

  // no longer forced on
  if (CH3button > 1500 & pumpForcedOn) {
    pumpForcedOn = false;
  }

  // if signal is lost then force pump back on.
  if (CH3button <= 500 & !pumpForcedOn) {
    pumpForcedOn = true;
    receiverCH3switch.write(135);
    pumpOn = true;
  }
  //pump must be on before it can be turned off and button must be at high value
  //  below 500 indicates receiver lost connection, keep pump on. 
  if ((CH3button <= 1500 & CH3button > 500) & pumpOn & !pumpForcedOn) {
    receiverCH3switch.write(45);
    pumpOn = false;
  }

  //pump must be on before it can be turned off
  if (CH3button > 1500 & !pumpOn & !pumpForcedOn) {
    receiverCH3switch.write(135);
    pumpOn = true;
  }
}

void initPumpPower() {
  receiverCH3switch.attach(receiverCH3switchPin);
  receiverCH3switch.write(135);
}

void initReceiverPower() {
  receiverPowerSwitch.attach(receiverPowerSwitchPin);
  receiverPowerSwitch.write(135);  
}

void pulseReceiverPower() {
  if (!powerLowWarningIssued) {
    powerLowWarningIssued=true;
    Serial.println("Receiver off");
    receiverPowerSwitch.write(45);    //turn off receiver
    myDelay(3500);                    //takes three seconds for ESC to turn off.
    receiverPowerSwitch.write(135);   //turn on receiver
    Serial.println("Receiver on");
  }
}
