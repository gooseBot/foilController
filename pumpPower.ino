#include <Servo.h>
static Servo receiverCH3switch;
const int receiverCH3switchPin = 6;
bool pumpForcedOn = true;
bool pumpOn = true;

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
