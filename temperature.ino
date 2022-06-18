

void readTemperature() {
  const int temperaturePin = A2;
  int reading = analogRead(temperaturePin);
  // converting that reading to voltage
  temperatureC = reading * (500 / 1023.0);
}
