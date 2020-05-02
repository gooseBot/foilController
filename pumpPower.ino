#include <Servo.h>
static Servo pumpPowerRelay;
bool pumpOn = true;
const int pumpPowerRelayPin = 6;

void setPumpState() {
  const int CH3buttonPin = 5;  
  int CH3button = pulseIn(CH3buttonPin, HIGH, 25000);  
    
  // if signal is lost then force pump on.
  //  below 500 indicates receiver lost connection, keep pump on.
  //  this is a failsafe and allows flushing pump by simply
  //  turning off the transmitter (power off ESC first via breaker). 
  if (CH3button <= 500) {
    pumpPowerRelay.write(135);
    pumpOn = true;
  } else {    
    // if have signal then turn off pump if foil is not operating 
    Serial.println(current);
    if (current < 2.0 ) {
      pumpPowerRelay.write(45);
      pumpOn = false;
    } else {
      pumpPowerRelay.write(135);
      pumpOn = true;    
    }
  }
}

void initPumpPower() {
  pumpPowerRelay.attach(pumpPowerRelayPin);
  pumpPowerRelay.write(135);
  pumpOn = true;
}
