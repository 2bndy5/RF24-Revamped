
Basic API
---------

Constructors
******************

.. doxygenclass:: RF24
    :members: RF24

begin()
**********************

.. doxygenfunction:: RF24::begin(void)

begin(_SPI*)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: RF24::begin(_SPI*)

begin(uint16_t, uint16_t)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: RF24::begin(uint16_t, uint16_t)

begin(_SPI*, uint16_t, uint16_t)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: RF24::begin(_SPI*, uint16_t, uint16_t)

openReadingPipe()
******************

.. doxygenfunction:: RF24::openReadingPipe(uint8_t number, const uint8_t* address)

.. doxygenfunction:: RF24::openReadingPipe(uint8_t number, uint64_t address)

closeReadingPipe()
******************

.. doxygenfunction:: closeReadingPipe

openWritingPipe()
******************

.. doxygenfunction:: openWritingPipe(const uint8_t* address)

.. doxygenfunction:: openWritingPipe(uint64_t address)

startListening()
******************

.. doxygenfunction:: startListening

stopListening()
******************

.. doxygenfunction:: stopListening

any()
******************

.. doxygenfunction:: any

available()
******************

.. doxygenfunction:: available

read()
******************

.. doxygenfunction:: RF24::read

send()
******************

.. doxygenfunction:: send(const void *buf, uint8_t len, const bool multicast)
