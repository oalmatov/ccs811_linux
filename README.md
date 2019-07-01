# ccs811_linux

This is a C++ class designed to control the CCS811 sensor.

This has been tested with Raspberry Pi 3.

Repository Contents
--------------------

* **/examples** - Example for the library and Makefile. 
* **/src** - Source files for the library (.cpp, .h).
* **/library.properties** - General library properties for the package manager.

Methods
--------------------

* **readData()** - Reads CCS811 sensor data.
* **reset()** - Resets device.
* **setEnvironmentalData()** - Inputs humidity and temperature data from an external source to yield more accurate results.
* **co2()** - Outputs CO2 concentration (ppm).
* **tvoc()** - Outputs TVOC concentration (ppb).


