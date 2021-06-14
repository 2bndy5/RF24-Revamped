Arduino
=======

RF24 is fully compatible with Arduino boards

.. seealso::
    `Arduino Board Reference <http://www.arduino.cc/en/Reference/Board>`_
    and `SPI Reference <http://arduino.cc/en/Reference/SPI>`_
    have more information

RF24 makes use of the standard hardware SPI pins (MISO, MOSI, SCK) and requires two additional pins, to control
the chip-select and chip-enable functions.

These pins must be chosen and designated by the user, in
``RF24Revamped radio(ce_pin, cs_pin);`` and can use any available pins.

Alternate SPI Support
*********************

RF24 supports alternate SPI methods, in case the standard hardware SPI pins are otherwise unavailable.

Software Driven SPI
-------------------

Software driven SPI is provided by the `DigitalIO <https://github.com/greiman/DigitalIO>`_ library.

Setup:

1. Install the digitalIO library
2. Open RF24_config.h in a text editor.
   Uncomment the line

   .. code-block:: cpp

       #define SOFTSPI


   or add the build flag/option

   .. code-block:: shell

      -DSOFTSPI

3. In your sketch, add

   .. code-block:: cpp

       #include DigitalIO.h

   .. note::
       Pins are listed as follows and can be modified by editing the RF24_config.h file.

       .. code-block:: cpp

           #define SOFT_SPI_MISO_PIN 16
           #define SOFT_SPI_MOSI_PIN 15
           #define SOFT_SPI_SCK_PIN 14

       Or add the build flag/option

       .. code-block:: shell

           -DSOFT_SPI_MISO_PIN=16 -DSOFT_SPI_MOSI_PIN=15 -DSOFT_SPI_SCK_PIN=14

Alternate Hardware (UART) Driven  SPI
-------------------------------------

The Serial Port (UART) on Arduino can also function in SPI mode, and can double-buffer data, while the
default SPI hardware cannot.

The SPI_UART library is available at `TMRh20's Sketches repo <https://github.com/TMRh20/Sketches/tree/master/SPI_UART>`_

Enabling:

1. Install the SPI_UART library
2. Edit RF24_config.h and uncomment

   .. code-block:: cpp

       #define SPI_UART

3. In your sketch, add

   .. code-block:: cpp

       #include <SPI_UART.h>

.. csv-table:: SPI_UART SPI Pin Connections
    :header: nRF24L01, "Arduino Uno Pin"

    MOSI, TX(0)
    MISO, RX(1)
    SCK, XCK(4)
    CE, "User Specified"
    CSN, "User Specified"

.. note:: SPI_UART on Mega boards requires soldering to an unused pin on the chip.
    See `#24 <https://github.com/TMRh20/RF24/issues/24>`_  for more information on
    SPI_UART.

Using a specific SPI Bus
------------------------

An alternate SPI bus can be specified using the overloaded `RF24Revamped::begin(_SPI*) <basic_api.html#begin-spi>`_ method.
This is useful for some boards that offer more than 1 hardware-driven SPI bus or cetain Arduino
cores that implement a software-driven (AKA bit-banged) SPI bus that does not use the DigitalIO
library.

.. warning:: The SPI bus object's ``SPIClass::begin()`` method **must** be called before
    calling the overloaded `begin(_SPI*) <basic_api.html#begin-spi>`_ method.

Below are some example snippets that demonstrate how this can be done.

ESP8266 example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. seealso:: The following example code is meant for the popular NodeMCU board. Please refer to the
    `ESP8266 ArduinoCore's SPI documentation <https://arduino-esp8266.readthedocs.io/en/latest/libraries.html#spi>`_
    for `other ESP8266-based boards <https://arduino-esp8266.readthedocs.io/en/latest/boards.html#>`_.

.. code-block:: cpp

    #include <SPI.h>
    #include <RF24Revamped.h>

    // notice these pin numbers are not the same used in the library examples
    RF24Revamped radio(D4, D3); // the (ce_pin, csn_pin) connected to the radio

    void setup() {
      Serial.begin(115200);
      while (!Serial) {} //some boards need this

      // by default (with no arguments passed) SPI uses D5 (HSCLK), D6 (HMISO), D7 (HMOSI)
      SPI.pins(6, 7, 8, 0);
      // this means the following pins are used for the SPI bus:
      // MOSI = SD1
      // MISO = SD0
      // SCLK = CLK
      // CSN = GPIO0 (labeled D3 on the board)
      // **notice we also passed `D3` to the RF24Revamped contructor's csn_pin parameter**

      SPI.begin();

      if (!radio.begin(&SPI)) {
        Serial.println(F("radio hardware not responding!!"));
        while (1) {} // hold program in infinite loop to prevent subsequent errors
      }

      // ... continue with program as normal (see library examples/ folder)
    }

ESP32 example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. seealso:: Please review the Espressif's
    `SPI_Multiple_Buses.ino example for the ESP32 <https://github.com/espressif/arduino-esp32/blob/master/libraries/SPI/examples/SPI_Multiple_Buses/SPI_Multiple_Buses.ino>`_
    located in their ArduinoCore repository (along with the SPI library for the ESP32).

.. code-block:: cpp

    #include <SPI.h>
    #include <RF24Revamped.h>

    // to use custom-defined pins, uncomment the following
    // #define MY_MISO 26
    // #define MY_MOSI 27
    // #define MY_SCLK 25
    // #define MY_SS   32  // pass MY_SS as the csn_pin parameter to the RF24 constructor

    // notice these pin numbers are not the same used in the library examples
    RF24Revamped radio(2, 0); // the (ce_pin, csn_pin) connected to the radio

    SPIClass* hspi = nullptr; // we'll instantiate this in the `setup()` function
    // by default the HSPI bus predefines the following pins
    // HSPI_MISO = 12
    // HSPI_MOSI = 13
    // HSPI_SCLK = 14
    // HSPI_SS   = 15

    void setup() {
      Serial.begin(115200);
      while (!Serial) {} //some boards need this

      hspi = new SPIClass(HSPI); // by default VSPI is used
      hspi->begin();
      // to use the custom defined pins, uncomment the following
      // hspi->begin(MY_SCLK, MY_MISO, MY_MOSI, MY_SS)

      if (!radio.begin(hspi)) {
        Serial.println(F("radio hardware not responding!!"));
        while (1) {} // hold program in infinite loop to prevent subsequent errors
      }

      // ... continue with program as normal (see library examples/ folder)
    }

Teensy example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. seealso:: The overloaded `RF24Revamped::begin(_SPI*) <basic_api.html#begin-spi>`_ is not needed according to the
    `Teensyduino SPI documentation <https://www.pjrc.com/teensy/td_libs_SPI.html>`_.
    Please review the table provided in the
    `Teensyduino documentation <https://www.pjrc.com/teensy/td_libs_SPI.html>`_ for what pins are used by
    default for certain Teensy boards.


.. code-block:: cpp

    #include <SPI.h>
    #include <RF24Revamped.h>

    // these pins are the alternate SPI pins available for Teensy LC/3.0/3.1/3.2/3.5/3.6
    #define MY_MISO 8
    #define MY_MOSI 7
    #define MY_SCLK 14

    // notice these pin numbers are not the same used in the library examples
    RF24Revamped radio(2, 0); // the (ce_pin, csn_pin) connected to the radio

    void setup() {
      Serial.begin(115200);
      while (!Serial) {} //some boards need this

      SPI.setMOSI(MY_MOSI);
      SPI.setMISO(MY_MISO);
      SPI.setSCK(MY_SCLK);

      if (!radio.begin()) {
        Serial.println(F("radio hardware not responding!!"));
        while (1) {} // hold program in infinite loop to prevent subsequent errors
      }

      // ... continue with program as normal (see library examples/ folder)
    }
