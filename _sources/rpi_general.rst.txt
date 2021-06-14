General Linux/Raspberry Pi
==========================

RF24 supports a variety of Linux based devices via various drivers.
Some boards like RPi can utilize multiple methods to drive the GPIO and SPI functionality.

Potential PreConfiguration
**************************

If SPI is not already enabled, load it on boot:

.. code-block:: shell

    sudo raspi-config

1. Update the tool via the menu as required
2. Select **Advanced** and **enable the SPI kernel module**
3. Update other software and libraries

   .. code-block:: shell

       sudo apt-get update
       sudo apt-get upgrade

Build Options
*************

The default build on Raspberry Pi utilizes the included `BCM2835 driver <http://www.airspayce.com/mikem/bcm2835>`_

.. seealso:: For available build options, read the output from

    .. code-block:: shell

        ./configure --help

Configure the build options automatically by running

.. code-block:: shell

    ./configure

Manual install
--------------

.. code-block:: shell

    make
    sudo make install

Pins Connections and Pin Configuration
**************************************

Using pin 15/GPIO 22 for CE, pin 24/GPIO8 (CE0) for CSN

Can use any available SPI BUS for CSN.

In general, use ``RF24Revamped radio(<ce_pin>, <a>*10+<b>);`` for proper constructor to
address correct spi device at /dev/spidev<a>.<b>

Choose any GPIO output pin for radio CE pin.

General Contructor
------------------

.. code-block:: c++

    RF24Revamped radio(22, 0);

MRAA Constructor
----------------

.. code-block:: c++

    RF24Revamped radio(15, 0);

See `MRAA docs about the Raspberry Pi <http://iotdk.intel.com/docs/master/mraa/rasppi.html>`_

SPI_DEV Constructor
-------------------

.. code-block:: c++

    RF24Revamped radio(22, 0);

See `Raspberry Pi Documentation <https://www.raspberrypi.org/documentation/usage/gpio/>`_
about using the GPIO pins

.. csv-table::
    :header: PIN, NRF24L01, RPI, "RPi -P1 Connector"

    "1", "GND", "rpi-gnd", "25"
    "2", "VCC", "rpi-3v3", "17"
    "3", "CE", "rpi-gpio22", "15"
    "4", "CSN", "rpi-gpio8", "24"
    "5", "SCK", "rpi-sckl", "23"
    "6", "MOSI", "rpi-mosi", "19"
    "7", "MISO", "rpi-miso", "21"
    "8", "IRQ", "\-", "\-"

Based on the arduino lib from `J. Coliz <maniacbug@ymail.com>`_

the library was berryfied by `Purinda Gunasekara <purinda@gmail.com>`_

then forked from https://github.com/stanleyseow/RF24 to https://github.com/jscrane/RF24-rpi

Network lib also based on https://github.com/farconada/RF24Network
