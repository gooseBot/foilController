#include <Servo.h>
static Servo pumpPowerRelay;
bool pumpOn = true;

void setPumpState() {
  // if signal is lost then force pump on.
  //  below 500 indicates receiver lost connection, keep pump on.
  //  this is a failsafe and allows flushing pump by simply
  //  turning off the transmitter (power off ESC first via breaker). 
  if (readHC12() <= 500) {
    //if no remote turn on pump (this is for flushing)
    pumpPowerRelay.write(135);
    pumpOn = true;
  } else {
    // turn off pump if foil is not operating 
    if (current < minCurrentThreshhold ) {
      pumpPowerRelay.write(45);
      pumpOn = false;
    } else {
      pumpPowerRelay.write(135);
      pumpOn = true;    
    }
  }
}

void initPumpPower() {
  const int pumpPowerRelayPin = 6;
  pumpPowerRelay.attach(pumpPowerRelayPin);
  pumpPowerRelay.write(135);
  pumpOn = true;  
}
