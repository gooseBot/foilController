#include <Servo.h>
static Servo pumpPowerRelay;
bool pumpOn = true;
int batteryId = 0;
const int pumpPowerRelayPin = 6;

void setPumpState() {
  const int CH3buttonPin = 5; 
  static bool CH3stateChanged=false; 
  int CH3button = pulseIn(CH3buttonPin, HIGH, 25000);  
    
  // if signal is lost then force pump on.
  //  below 500 indicates receiver lost connection, keep pump on.
  //  this is a failsafe and allows flushing pump by simply
  //  turning off the transmitter (power off ESC first via breaker). 

  if (CH3button > 1500 & !CH3stateChanged) {
    CH3stateChanged=true;
    if (batteryId < 1) {
      batteryId++;
    }else{
      batteryId=0;
    }
    initBatteryWarningLevel();
  }

  if (CH3button <= 1500 & CH3button > 500 & CH3stateChanged) {
    CH3stateChanged=false;
  }
  
  if (CH3button <= 500) {
    //if no remote turn on pump (this is for flushing)
    pumpPowerRelay.write(135);
    pumpOn = true;
  } else {
    // turn off pump if foil is not operating 
    Serial.println(current);
    if (current < 3.0 ) {
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

void initBatteryWarningLevel() {
    int batteryOptions[] = {5, 8};            
    ampSecondsWarning = batteryOptions[batteryId]*0.67*3600;  // select battery warning capacity
    beepBatterySize(batteryOptions[batteryId]);
}
