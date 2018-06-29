void readTemperature() {
  const int temperaturePin = 8;
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(temperaturePin);
  // converting that reading to voltage
  double voltage = reading * 5.0; voltage /= 1024.0;
  // now print out the temperature
  temperatureC = (voltage - 0.5) * 100;  //converting from 10 mv per degree wit 500 mV offset
                                         //to degrees ((voltage - 500mV) times 100)
}

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
  int currentAnalogSteps = 0;

  currentAnalog = analogRead(currentPin);
  //Serial.print(currentAnalog); Serial.println(" amps analog");
  currentAnalogSteps = zeroPoint - analogRead(currentPin);
  current = ampPerStep * currentAnalogSteps;
  // accumlate drain on batteries if more than 2 amps are being drawn.  
  //     less than 2 is probably poor calibration and not actual draw.
  if (current > 2) {
    ampSecondsConsumed += current * ((double)sensorReadInterval / 1000);
  }  
  //Serial.print(current); Serial.println(" amps");
  //Serial.print(ampSecondsConsumed); Serial.println(" consumed");
}
