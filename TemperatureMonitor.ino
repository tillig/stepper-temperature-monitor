#include "Wire.h"
#include "LiquidCrystal_I2C.h"

// Thermistors are connected at A0, A1, A2
const int xThermistorPin = 0;
const int yThermistorPin = 1;
const int zThermistorPin = 2;

// Temp per axis (rounded to nearest degree)
int axisX, axisY, axisZ;

// Buffer for holding the formatted number to display in the 1602.
char formattedNumber[3];

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

// LCD address (for me) is 0x27, which is common.
// It's a 16 x 2 display.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  // Serial port baud rate needs to match here and in the VS Code extension or
  // you won't get any output. See settings.json.
  Serial.begin(115200);

  // Fixed display like:
  // X:___C    Y:___C
  // Z:___C
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X:");
  lcd.setCursor(5, 0);
  lcd.print("C    Y:");
  lcd.setCursor(15, 0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Z:");
  lcd.setCursor(5, 1);
  lcd.print("C");
}

void loop()
{
  // Write temps to their correct spots on the LCD.
  axisX = readTemperature(xThermistorPin);
  lcd.setCursor(2, 0);
  sprintf(formattedNumber, "%3d", axisX);
  lcd.print(formattedNumber);

  axisY = readTemperature(yThermistorPin);
  lcd.setCursor(12, 0);
  sprintf(formattedNumber, "%3d", axisY);
  lcd.print(formattedNumber);

  axisZ = readTemperature(zThermistorPin);
  lcd.setCursor(2, 1);
  sprintf(formattedNumber, "%3d", axisZ);
  lcd.print(formattedNumber);

  delay(1000);
}

int readTemperature(int pin)
{
  int Vo = analogRead(pin);
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

  // Kelvin to Celsius, rounded to nearest degree
  int rounded = round(T - 273.15);

  Serial.print("; ");
  Serial.print(rounded);
  Serial.println("C");

  return rounded;
}
