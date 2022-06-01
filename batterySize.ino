int batteryId = 0;
const int batteryButtonPin = 3;

void initBatterySize() {  
  pinMode(batteryButtonPin, INPUT_PULLUP);
  initBatteryWarningLevel();
}

void readBatteryButton() {
  int buttonValue = digitalRead(batteryButtonPin);
  if (buttonValue == LOW){
    if (batteryId < 3) {
      batteryId++;
    }else{
      batteryId=0;
    }
    initBatteryWarningLevel();
  }
}
   
void initBatteryWarningLevel() {
    int batteryOptions[] = {5, 8, 13, 28};    
    int batteryOptionsAlias[] = {1, 2, 3, 4};            
    ampSecondsWarning = batteryOptions[batteryId]*0.67*3600;  // select battery warning capacity
    beepBatterySize(batteryOptionsAlias[batteryId]);    
}
