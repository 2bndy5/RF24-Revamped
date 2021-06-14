
Basic API
---------

Constructors
******************

.. doxygenclass:: RF24Revamped
    :members: RF24Revamped

begin()
**********************

.. doxygenfunction:: RF24Revamped::begin(void)

begin(_SPI*)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: RF24Revamped::begin(_SPI*)

begin(uint16_t, uint16_t)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: RF24Revamped::begin(uint16_t, uint16_t)

begin(_SPI*, uint16_t, uint16_t)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: RF24Revamped::begin(_SPI*, uint16_t, uint16_t)

openReadingPipe()
******************

.. doxygenfunction:: RF24Revamped::openReadingPipe(uint8_t number, const uint8_t* address)

.. doxygenfunction:: RF24Revamped::openReadingPipe(uint8_t number, uint64_t address)

closeReadingPipe()
******************

.. doxygenfunction:: RF24Revamped::closeReadingPipe

openWritingPipe()
******************

.. doxygenfunction:: RF24Revamped::openWritingPipe(const uint8_t* address)

.. doxygenfunction:: RF24Revamped::openWritingPipe(uint64_t address)

startListening()
******************

.. doxygenfunction:: RF24Revamped::startListening

stopListening()
******************

.. doxygenfunction:: RF24Revamped::stopListening

any()
******************

.. doxygenfunction:: any

available()
******************

.. doxygenfunction:: RF24Revamped::available

read()
******************

.. doxygenfunction:: RF24Revamped::read

send()
******************

.. doxygenfunction:: send(const void *buf, uint8_t len, const bool multicast)
