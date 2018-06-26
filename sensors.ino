void readTemperature() {
  const int temperaturePin = 8;
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(temperaturePin);
  // converting that reading to voltage
  float voltage = reading * 5.0; voltage /= 1024.0;
  // now print out the temperature
  temperatureC = (voltage - 0.5) * 100;  //converting from 10 mv per degree wit 500 mV offset
                                         //to degrees ((voltage - 500mV) times 100)
}

void readCurrent() {
  // 5.0V to sensor
  // Output will be centered @ 2.5V
  // IMPORTANT: connect so current reduces voltage to analog in
  //(feed the wire from exposed ferrite side to enclosed side)
  // Analog reading @ 0A = 5.61/2 * 1024 / 5 = 574(actual reading 580)
  // A @ 0.0327 V / A => 2.5V - 2.35V = 0.15V => reading 154

  const byte a_pin = A0;
  const int zero_point = 586;
  const float amp_per_step = 0.366; // 2.2 / (586 - 580) Values to be adjusted/calibrated
  int steps;

  int currentSensorAnalog = analogRead(a_pin);
  //Serial.print(currentSensorAnalog); Serial.println(" reading");
  steps = zero_point - analogRead(a_pin);
  current = amp_per_step * steps;
  //Serial.print(current); Serial.println(" amps");
}
