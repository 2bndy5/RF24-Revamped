
=========================================
Welcome to RF24 Revemped's documentation!
=========================================

RF24 Revamped is a simplified and extensible API for TMRh20's popular
Optimized High Speed Driver for nRF24L01(+) 2.4GHz Wireless Transceiver

Goals Design Goals
------------------

This library fork is still designed to be...

* More compliant with the manufacturer specified operation of the chip, while allowing
  advanced users to work outside the recommended operation.
* Utilize the capabilities of the radio to their full potential via multiple platforms
  (i.e. Arduino & Raspberry Pi)
* More reliable, responsive, bug-free and feature rich
* Easy for beginners to use, with well documented examples and features
* Consumed with a public interface that's similar to other Arduino standard libraries

Change Log
----------

See `the releases <http://github.com/2bndy5/RF24/releases>`_ for a details on what was
changed in each version of the library

Useful References
-----------------

* `RF24 Class Documentation <basic_api.html>`_
* `Support & Configuration <pages.html>`_
* `Source Code <https://github.com/2bndy5/RF24/tree/revamp>`_
* `nRF24L01 v2.0 Datasheet <http://github.com/2bndy5/RF24/raw/master/datasheets/nRF24L01_datasheet_v2.pdf>`_
* `nRF24L01+ v1.0 Datasheet <http://github.com/2bndy5/RF24/raw/master/datasheets/nRF24L01P_datasheet_v1.pdf>`_

Platform Support Pages
----------------------

* `Arduino (Uno, Nano, Mega, Due, Galileo, etc) <arduino.html>`_
* `ATTiny <attiny.html>`_
* `Linux Installation <linux_install.html>`_

  * `Linux/RPi General <rpi_general.html>`_
  * `MRAA (Galileo, Edison, etc) supported board <mraa.html>`_
  * `LittleWire <LittleWire.html>`_
* `Cross-compilation for linux devices <cross_compilation.html>`_

.. * `Python wrapper available for Linux devices <python_wrapper.html>`_

General Microcontroller Pin layout
----------------------------------

See the individual board support pages (links in the sidebar) for more info

.. image:: https://lastminuteengineers.com/wp-content/uploads/2018/07/Pinout-nRF24L01-Wireless-Transceiver-Module.png
    :target: https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/#nrf24l01-transceiver-module-pinout

The table below shows how to connect the the pins of the NRF24L01(+) to
different boards. Only the IRQ, CE, and CSN pins are configurable.

.. csv-table::
   :header: "NRF24L01", "Arduino UNO", "ATtiny25/45/85 [0]_", "ATtiny44/84 [1]_", "LittleWire [2]_", "RPi", "RPi -P1 Connector"

   "GND", "GND", "pin 4", "pin 14", "GND", "rpi-gnd", "25"
   "VCC", "3.3V", "pin 8", "pin 1", "regulator 3.3V required", "rpi-3v3", "17"
   "CE", "digIO 7", "pin 2", "pin 12", "pin to 3.3V", "rpi-gpio22", "15"
   "CSN", "digIO 8", "pin 3", "pin 11", "RESET", "rpi-gpio8", "24"
   "SCK", "digIO 13", "pin 7", "pin 9", "SCK", "rpi-sckl", "23"
   "MOSI", "digIO 11", "pin 6", "pin 7", "MOSI", "rpi-mosi", "19"
   "MISO", "digIO 12", "pin 5", "pin 8", "MISO", "rpi-miso", "21"
   "IRQ", "\-", "\-", "\-", "\-", "\-", "\-"

.. [0] https://learn.sparkfun.com/tutorials/tiny-avr-programmer-hookup-guide/attiny85-use-hints
.. [1] http://highlowtech.org/?p=1695
.. [2] http://littlewire.cc/


.. toctree::
   :maxdepth: 1
   :caption: Examples

   ino_examples
   cpp_examples
   attiny_examples

.. toctree::
   :maxdepth: 1
   :caption: API Reference

   basic_api
   advanced_api
   configure_api

.. toctree::
   :maxdepth: 1
   :caption: Related Pages

   common_issues
   arduino
   attiny
   linux_install
   mraa
   rpi_general
   cross_compilation
   atxmega
   portability
   templates

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
