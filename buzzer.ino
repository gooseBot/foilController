
#include <TimerFreeTone.h>
const int buzzerPin = 9;

void initBuzzer() {
  pinMode(buzzerPin, OUTPUT); // Set buzzer - pin 9 as an output
}

void beep() {
  TimerFreeTone(buzzerPin, 2000, 250);
  myDelay(250);
  TimerFreeTone(buzzerPin, 3000, 150); 
}

void beepBatterySize(int batSize) {
  for (int i=0; i<batSize; i++){
    TimerFreeTone(buzzerPin, 2000, 100);  
    myDelay(350);
  }
}
