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
// https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation I didn't
// calculate these, and I found my thermistors aren't super accurate, so maybe
// if I did calculate them I'd get more precise results.
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
  axisY = readTemperature(yThermistorPin);
  axisZ = readTemperature(zThermistorPin);

  Serial.print("X: ");
  Serial.print(axisX);
  Serial.println(" C");

  Serial.print("Y: ");
  Serial.print(axisY);
  Serial.println(" C");

  Serial.print("Z: ");
  Serial.print(axisZ);
  Serial.println(" C");

  Serial.println();
  delay(1000);
}

float readTemperature(int pin)
{
  // I think I must have wired things up wrong/backwards from the tutorial
  // because just analogRead(pin) did show that the resistance went up as
  // temperature went up (correct) but the calculated temperature reading went
  // _down_ (incorrect).
  int Vo = 1023 - analogRead(pin);
  Serial.print("pin ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.print(Vo);
  Serial.print(" Vo; R2: ");
  float R2 = R1 * (1023.0 / (float)Vo - 1.0);
  Serial.print(R2);
  Serial.print("; logR2: ");
  float logR2 = log(R2);
  Serial.print(logR2);

  // Steinhart-Hart equation for converting resistance to temperature Kelvin.
  float T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));

  // Kelvin to Celsius
  T = T - 273.15;

  Serial.print("; ");
  Serial.print(T);
  Serial.println("C");

  return T;
}
