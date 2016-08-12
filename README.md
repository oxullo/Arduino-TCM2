# Arduino-TCM2

[![Build Status](https://travis-ci.org/oxullo/Arduino-TCM2.svg?branch=master)](https://travis-ci.org/oxullo/Arduino-TCM2)

Arduino library for the MPico systems TCM2 (Timing Controller Module gen2) / TC2 (Timing Controller
gen2) E-Ink display controller. Currently supporting the 4.41" version (TCS2-P441-231_v1.1).

![TCM2-P441](http://www.pervasivedisplays.com/images/Kits/Mpico/4.41DevKit/MpicoSys%204.41%20TCM_panel/MPico4.41_TCM_4.41panel.png)

https://www.mpicosys.com/news/timing-controller-solutions-generation-2/

## Hardware

### Arduinos

The library has been developed and tested under Arduino Pro 3.3V 8MHz and Arduino/Genuino MKR1000.
The examples provided can be easily adjusted for both: the only relevant difference is the pin
used for the SPI chip select (10 on the Pro, 7 on the MKR).

### TC Module

The TCM2 module tested is a bundle with a Pervasive Display Aurora Mb v231 4.41", 400x300px (113dpi).

### Connections

* Arduino Pro mini 3V3 8MHz <> MPico TCM2

```
2       -> /TC_BUSY
3       -> /TC_EN
10/SS   -> /TC_SS
11/MOSI -> TC_MOSI
12/MISO -> TC_MISO
13/SCK  -> TC_SCK
3.3V    -> VDDIN, VIN
GND     -> GND
```

* Arduino MKR1000 <> MPico TCM2

```
2       -> /TC_BUSY
3       -> /TC_EN
7       -> /TC_SS
8/MOSI  -> TC_MOSI
9/SCK   -> TC_SCK
10/MISO -> TC_MISO
VCC     -> VDDIN, VIN
GND     -> GND
```

## EPD conversion

TCM2 accepts EPD data formats. A tool for converting arbitrary graphics into EPD type 0 can
be found in the tools folder. This tool supports only the 4.41" version.

### Usage

```
$ ./epd_convert.py input-image.png output.h
```

The header can be used in conjunction with the _image_upload_ example.

## Links

* Pervasive Displays Aurora Mb panel: http://www.pervasivedisplays.com/products/441
* Bundle kit S1441CS121: http://www.pervasivedisplays.com/kits/mpicosys441
* MPico TCM2 documentation: http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=228895
  * Errata: http://www.pervasivedisplays.com/LiteratureRetrieve.aspx?ID=232053
