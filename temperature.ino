double temperatureC = 0;

void readTemperature() {
  //const int temperaturePin = 4;
  const int temperaturePin = A2;
  //getting the voltage reading from the temperature sensor
  int reading = analogRead(temperaturePin);
  // converting that reading to voltage
  double voltage = reading * 5.0; voltage /= 1024.0;
  // now print out the temperature
  temperatureC = (voltage - 0.5) * 100;  //converting from 10 mv per degree with 500 mV offset
                                         //to degrees ((voltage - 500mV) times 100)
}
