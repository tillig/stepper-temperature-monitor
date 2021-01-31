# Arduino Monitor for CNC/3D Printer Stepper Motor Temperature

I have a little CNC machine where I'm having some issues with the Z-axis motor (long story) so I thought I'd turn the voltage on it up just a touch. However, I don't want the motor running hot, either, so I thought, "Maybe I should create something to monitor the temperature of the stepper motors so I can just... see it."

This is that.

I'm measuring the temperature with three thermistors (one per motor, X/Y/Z) and the readout is on a simple 1602 display. It's not fancy but it works.

The math for getting temperature from a thermistor is complex and [this tutorial](https://www.circuitbasics.com/arduino-thermistor-temperature-sensor-tutorial/) saved me. I won't lie, I didn't go re-solving all the equations myself. I got it working based on the formulae shown in the tutorial and called it a day.

This [I2C 1602 tutorial](https://osoyoo.com/2017/07/09/arduino-lesson-i2c-lcd1602-display/) was helpful in figuring out how to make that work.

## Parts

- [Arduino Uno](https://amzn.to/3r756LT)
- Three [100K ohm thermistors](https://amzn.to/3oDencJ)
- Three 100K ohm resistors
- [I2C 1602 display](https://amzn.to/36rvqbs)
