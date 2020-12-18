
Basic API
---------

Constructor
******************

.. doxygenclass:: RF24

.. doxygenfunction:: RF24

begin()
**********************

.. doxygenfunction:: RF24::begin

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

.. doxygenfunction:: any()

available()
******************

.. doxygenfunction:: available(void)

.. doxygenfunction:: available(uint8_t* pipe_num)

read()
******************

.. doxygenfunction:: RF24::read

send()
******************

.. doxygenfunction:: send(const void *buf, uint8_t len)

.. doxygenfunction:: send(const void *buf, uint8_t len, const bool multicast)

