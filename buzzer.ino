const int buzzerPin = 9;

void initBuzzer() {
  pinMode(buzzerPin, OUTPUT); // Set buzzer - pin 9 as an output
}

void beep() {
  tone(buzzerPin, 2000, 250);
  myDelay(250);
  tone(buzzerPin, 3000, 150); 
}

void beepBatterySize(int batSize) {
  for (int i=0; i<batSize; i++){
    tone(buzzerPin, 2000, 100);  
    myDelay(150);
  }
}
