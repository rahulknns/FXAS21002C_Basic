# FXAS21002C_Basic
Provides access to basic functions of FXAS21002C sensor through CPP API for Any arduino based board.

# Usage
* create an object of FXAS with address and optionally  TwoWire object.  Default value is Wire.
* Change ODR, FSR accordingly using the respective functions if needed. Default value is defined in Header file.
* Pass float pointers to updateData function as input to get real time values read from the sensor. Call them everytime you need updated value of the sensor.
