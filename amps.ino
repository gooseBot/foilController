int currentAnalog = 0;  //I logged this value when I calibrated the current sensor

unsigned long currentReadPeriod=0;

void readCurrent() {
  // 5.0V to sensor
  // Output will be centered @ 2.5V
  // IMPORTANT: connect so current reduces voltage to analog in
  //(feed the wire from exposed ferrite side to enclosed side)
  // Calculated analog reading @ 0A = 5.61/2 * 1024 / 5 = 574 (actual reading from sensor is: 580)
  // A @ 0.0327 V / A => 2.5V - 2.35V = 0.15V => reading 154

  const byte currentPin = A0;
  const int zeroPoint = 582;
  const double ampPerStep = 0.366; // 2.2amps / (586 - 580)  formula: [measured amps]/[analog reading with load - analog reading with 0 load]
  //const double ampPerStep = 0.383; // adjusted by amps consumed vs amps stored during charging on 7/2/18
  int currentAnalogSteps = 0;  
  static unsigned long lastCurrentReadingTime = 0;

  //first time through this needs to be set
  if (lastCurrentReadingTime==0) {lastCurrentReadingTime=millis();}
  
  currentAnalog = analogRead(currentPin);
  currentAnalogSteps = zeroPoint - analogRead(currentPin);
  current = ampPerStep * currentAnalogSteps;
  
  // accumlate drain on batteries if more than 3 amps are being drawn.  
  //     less than 3 is probably poor calibration and not actual draw.
  currentReadPeriod = millis() - lastCurrentReadingTime;
  if (current > minCurrentThreshhold) {
    ampSecondsConsumed += current * ((double)currentReadPeriod / 1000);
  }
  lastCurrentReadingTime = millis();
}
