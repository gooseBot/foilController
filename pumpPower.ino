#include <Servo.h>
static Servo pumpPowerRelay;
bool pumpOn = true;
int batteryId = 0;
int CH3button=0;

void setPumpState() {
  const int CH3inputPin = 3; 
  static bool CH3stateChanged=false; 
  CH3button = pulseIn(CH3inputPin, HIGH, 25000);  
    
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
    if (current < currentThreshhold ) {
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

void initBatteryWarningLevel() {
    int batteryOptions[] = {5, 8};            
    ampSecondsWarning = batteryOptions[batteryId]*0.67*3600;  // select battery warning capacity
    beepBatterySize(batteryOptions[batteryId]);
}
