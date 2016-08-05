# afshawn_watch
This is a clock that hacked a PiTft to be compatible with Arduino.
If you are also using a PiTFT use the following pinings.

13 to 23 (SPI_SCLK)
12 to 21 (SPI_MISO)
11 to 19 (SPI_MOSI)
10 to 24 (#SPI_CE0 aka TFT_CS_3V) 
9 to 22 (GPIO25 aka TFT_DC_3V) 
8 to 18 (GPIO24 aka RT_INT)

You will also need to create a voltage dropper to allow the PiTFT to work with Arduino.
Layout as so:
Arduino digital pin xx (5V) ------- # -----|4,7k|---- + ----|10k|-----# GND
                                                      |
                                                      |
                                         TFT header input yy (3.3V)




Otherwise you can use this code with any other (ILI9340C or ILI9341) compatible LCD.
The following prerequisite software is required.
The Adafruit GFX Library https://github.com/adafruit/Adafruit-GFX-Library
The Arduino Time Library https://github.com/PaulStoffregen/Time
