ATTiny Support
==============

ATTiny support for this library relys on the SpenceKonde ATTinyCore.
Be sure to have added this core to the Arduino Boards Manager by
`following this guide <http://highlowtech.org/?p=1695>`_

See the included rf24ping85 example for pin info and usage

Some versions of Arduino IDE may require a patch to allow use of the full program space on ATTiny<br>
See https://github.com/TCWORLD/ATTinyCore/tree/master/PCREL%20Patch%20for%20GCC for ATTiny patch

Hardware Hardware Configuration
*******************************

ATTiny board support initially added from `jscrane's fork <https://github.com/jscrane/RF24>`_
The pin layouts found here and rf24_ATTiny example written by `tong67 <https://github.com/tong67>`_

ATtiny25/45/85
--------------

Pin map with CE_PIN 3 and CSN_PIN 4

.. code-block:: text

                                +-\/-+
                          PB5  1|o   |8  Vcc --- nRF24L01  VCC --- LED --- 5V
         nRF24L01  CE --- PB3  2|    |7  PB2 --- nRF24L01  SCK
         nRF24L01 CSN --- PB4  3|    |6  PB1 --- nRF24L01 MOSI
         nRF24L01 GND --- GND  4|    |5  PB0 --- nRF24L01 MISO
                                +----+

ATtiny25/45/85 using 3 pins
---------------------------

Pin map with CE_PIN 3 and CSN_PIN 3. PB3 and PB4 are free to use for application
Circuit idea from `NerdRalph' 3 pin solution <http://nerdralph.blogspot.ca/2014/01/nrf24l01-control-with-3-attiny85-pins.html>`_
Original RC combination was 1K/100nF. 22K/10nF combination worked better.
For best settletime delay value in RF24Revamped::csn() the timingSearch3pin.ino sketch can be used.
This configuration is enabled when CE_PIN and CSN_PIN are equal, e.g. both 3
Because CE is always high the power consumption is higher than for 5 pins solution

.. code-block:: text


                                                                                     ^^
                                +-\/-+           nRF24L01   CE ------|              //
                          PB5  1|o   |8  Vcc --- nRF24L01  VCC ------x----------x--|<|-- 5V
                          PB3  2|    |7  PB2 --- nRF24L01  SCK --|<|---x-[22k]--|  LED
                          PB4  3|    |6  PB1 --- nRF24L01 MOSI  1n4148 |
         nRF24L01 GND -x- GND  4|    |5  PB0 --- nRF24L01 MISO         |
                       |        +----+                                 |
                       |-----------------------------------------||----x-- nRF24L01 CSN, pin4
                                                                     10nF

ATtiny24/44/84
--------------

Pin map with CE_PIN 8 and CSN_PIN 7

Schematic provided and successfully tested by `Carmine Pastore <https://github.com/Carminepz>`_

.. code-block:: text


                               +-\/-+
       nRF24L01  VCC --- VCC  1|o   |14 GND --- nRF24L01  GND
                         PB0  2|    |13 AREF
                         PB1  3|    |12 PA1
                         PB3  4|    |11 PA2 --- nRF24L01   CE
                         PB2  5|    |10 PA3 --- nRF24L01  CSN
                         PA7  6|    |9  PA4 --- nRF24L01  SCK
       nRF24L01 MISO --- PA6  7|    |8  PA5 --- nRF24L01 MOSI
                               +----+

ATtiny2313/4313
---------------

Pin map with CE_PIN 12 and CSN_PIN 13

.. code-block:: text

                               +-\/-+
                         PA2  1|o   |20 VCC --- nRF24L01  VCC
                         PD0  2|    |19 PB7 --- nRF24L01  SCK
                         PD1  3|    |18 PB6 --- nRF24L01 MOSI
                         PA1  4|    |17 PB5 --- nRF24L01 MISO
                         PA0  5|    |16 PB4 --- nRF24L01  CSN
                         PD2  6|    |15 PB3 --- nRF24L01   CE
                         PD3  7|    |14 PB2
                         PD4  8|    |13 PB1
                         PD5  9|    |12 PB0
       nRF24L01  GND --- GND 10|    |11 PD6
                               +----+
