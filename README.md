# STM32 Motion Controller

The goal of this project is making a headless gcode interpreter to use in different automation applications where usually you seek of compactness but at the same time ease of use and installation.

With this motion controller you can get up to 6 axes running with external drivers.

It reads a gcode file from an sd-card which can be easily adapted to this board only by soldering an sd-card adapter.

It can also print the information to an I2C screen attached directly to the I2C bus.


# TODO

- Implement all 6 axes and assign pinout.
- Implement all possible gcode instructions.
- I2C communication for multiple serial drivers.
- Compatibility with ODrive.
- Create an interface for I2C liquid display.
