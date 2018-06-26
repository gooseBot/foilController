
#include <Servo.h>
static Servo myservo;
const int reciverCH3switchPin = 6;
bool forcedOn = true;

void readCH3pwm() {
  const int CH3buttonPin = 5;

  int CH3button = pulseIn(CH3buttonPin, HIGH, 25000);
  Serial.print(CH3button); Serial.println(" CH3 value");

  // no longer forced on
  if (CH3button > 1500 & forcedOn) {
    forcedOn = false;
  }

  // if signal is lost then force pump back on.
  if (CH3button <= 500 & !forcedOn) {
    forcedOn = true;
    myservo.write(135);
    pumpOn = true;
  }
  //pump must be on before it can be turned off and button must be at high value
  //  below 500 indicates receiver lost connection, keep pump on. 
  if ((CH3button <= 1500 & CH3button > 500) & pumpOn & !forcedOn) {
    myservo.write(45);
    pumpOn = false;
  }

  //pump must be on before it can be turned off
  if (CH3button > 1500 & !pumpOn & !forcedOn) {
    myservo.write(135);
    pumpOn = true;
  }
}
void initCH3() {
  myservo.attach(reciverCH3switchPin);
  myservo.write(135);
}
