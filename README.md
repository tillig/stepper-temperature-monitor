# Arduino Monitor for CNC/3D Printer Stepper Motor Temperature

I have a little CNC machine where I'm having some issues with the Z-axis motor (long story) so I thought I'd turn the voltage on it up just a touch. However, I don't want the motor running hot, either, so I thought, "Maybe I should create something to monitor the temperature of the stepper motors so I can just... see it."

This is that.

I'm measuring the temperature with three thermistors (one per motor, X/Y/Z) and the readout is on a simple 1602 display. It's not fancy but it works.

This [I2C 1602 tutorial](https://osoyoo.com/2017/07/09/arduino-lesson-i2c-lcd1602-display/) was helpful in figuring out how to make the 1602 work. I didn't have a ton of extra pins after adding the thermistors so the two-wire data connection was good.

The math for getting temperature from a thermistor is complex and [this tutorial](https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/) saved me. I won't lie, I didn't go re-solving all the equations myself. I got it working based on the formulae shown in the tutorial and called it a day.

I did notice that the thermistors I got seem to be reasonably accurate at room temperature but as they get warmer they become less precise. I didn't personally calculate the individual Steinhart-Hart constants for each thermistor, which is likely the problem; but I guess... just don't use these for, like, medical equipment or something. It's going to give you _an idea_ of the temperature, but it's not going to be spot-on.

## Parts

- [Arduino Uno](https://amzn.to/3r756LT)
- Three [100K ohm thermistors](https://amzn.to/3oDencJ)
- Three 100K ohm resistors
- [I2C 1602 display](https://amzn.to/36rvqbs)

## I2C Wiring

| I2C Pin | Arduino Pin |
| ------- | ----------- |
| GND     | GND         |
| VCC     | 5V          |
| SDA     | A4          |
| SCL     | A5          |

Note: I had to turn the backlight on the display _way down_ before I could see the text. As shipped from the factory, it was all the way up and drowning out the display.

## Thermistor Wiring

Again, be sure to check out [this tutorial](https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/) because it has a complete walkthrough of getting _one_ thermistor wired up.

Each thermistor goes:

```text
  Arduino 5V
      |
100K Thermistor +
      |
100K Thermistor -
      |
 100K Resistor + ---- 100K Resistor -
      |                     |
Arduino Analog Pin    Arduino Ground
```

Now, I know that thermistors / resistors don't have positive and negative sides, I just wanted to illustrate in crappy text form how the circuit worked. There's a picture on the tutorial I linked that I don't want to just straight lift.

To adapt that to three thermistors, it was basically a tiny custom circuitboard I soldered together such that the Arduino 5V went out to all three thermistors, each thermistor ran to its own resistor, and each thermistor ended up at its own analog in. That way I could read all three.

## Bringing the Pieces Together

Since both the I2C display and the circuitboard with the thermistors needs the Arduino 5V output, I integrated the display power/ground with the circuitboard power/ground. However, the I2C display connected entirely separately to its own analog pins, so I ran wires straight from the display to the Arduino.
