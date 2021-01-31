// Thermistors are connected at A0, A1, A2
const int xThermistorPin = 0;
const int yThermistorPin = 1;
const int zThermistorPin = 2;

// Temp per axis
float axisX, axisY, axisZ;

// Resistor value - I'm using 100K ohm NTC 3950 thermistors and 100K ohm
// resistors, but R1 = 10000 was in the tutorial, which also used 100K ohm
// resistors and changing it to 100000 made the return values really wrong,
// so... 10K it is. It's a little cargo cult and I'm going to just go with it.
const float R1 = 10000;

// Steinhart-Hart coefficients for NTC thermistors (most common)
// https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
const float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup()
{
  // Serial port baud rate needs to match here and in the VS Code extension or
  // you won't get any output. See settings.json.
  Serial.begin(115200);
}

void loop()
{
  axisX = readTemperature(xThermistorPin);

  Serial.print("X Temperature: ");
  Serial.print(axisX);
  Serial.println(" F");

  delay(1000);
}

float readTemperature(int pin)
{
  int Vo = analogRead(pin);
  float R2 = R1 * (1023.0 / (float)Vo - 1.0);
  float logR2 = log(R2);

  // Steinhart-Hart equation for converting resistance to temperature Kelvin.
  float T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));

  // Kelvin to Celsius
  T = T - 273.15;

  // Celsius to Fahrenheit
  T = (T * 9.0) / 5.0 + 32.0;

  return T;
}
