
// Build capacitor and resistor circut as in this link
// https://bestengineeringprojects.com/lm35-how-to-get-stable-temperature-reading/
// otherwise output is not stable and varies up to 6C!
// 1k ohm across output and ground to sensor
// 10 micro farad across vcc and ground to sensor
void readTemperature() {
  const int temperaturePin = A2;
  int reading = analogRead(temperaturePin);
  // converting that reading to voltage
  temperatureC = reading * (500 / 1023.0);
}
