
Configuration API
-----------------

Power Amplifier Level enum
***************************

.. doxygenenum:: rf24_pa_dbm_e

Data Rate enum
****************

.. doxygenenum:: rf24_datarate_e

setDynamicPayloads()
******************************

Unary pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloads(bool)

Binary pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloadsBin(uint8_t)

Individual pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloads(bool, uint8_t)

getDynamicPayloads()
******************************

.. doxygenfunction:: getDynamicPayloads(uint8_t)

.. doxygenfunction:: getDynamicPayloads(void)

setPayloadLength()
******************************

.. doxygenfunction:: setPayloadLength(uint8_t)

.. doxygenfunction:: setPayloadLength(uint8_t, uint8_t)

getPayloadLength()
******************************

.. doxygenfunction:: getPayloadLength

setAutoAck()
******************************

Auto-acknowledgement responds to every recieved payload with an empty
ACK packet. These ACK packets get sent from the receiving radio back
to the transmitting radio. To attach an ACK payload to a ACK packet,
use :func:`writeAck()`.

Pipe 0 is used for TX operations, which include sending ACK packets. If
using this feature on both TX & RX nodes, then pipe 0 must have this
feature enabled for the RX & TX operations. If this feature is disabled
on a transmitting radio's pipe 0, then the transmitting radio will
always report that the payload was recieved (even if it was not).
Remember to also enable this feature for any pipe that is openly
listening to a transmitting radio with this feature enabled.

.. warning:: If this feature is enabled for pipe 0, then the ``multicast``
    parameter to :func:`send()` can be used to disable this feature for an
    individual payload. However, if this feature is disabled for pipe 0,
    then the ``multicast`` parameter will have no effect.
.. note:: If disabling auto-acknowledgment packets on pipe 0, the ACK
    payloads feature is also disabled as this feature is required on pipe 0
    to send ACK payloads.

Unary pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAck(bool)

Binary pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAckBin(uint8_t)

Individual pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAck(bool, uint8_t)

getAutoAck()
******************************

.. doxygenfunction:: getAutoAck(void)

.. doxygenfunction:: getAutoAck(uint8_t)

setRetries()
******************************

.. doxygenfunction:: setRetries

enableAckPayload()
******************************

.. doxygenfunction:: enableAckPayload

disableAckPayload()
******************************

.. doxygenfunction:: disableAckPayload

allowMulticast()
******************************

.. doxygenfunction:: allowMulticast

isAllowMulticast()
******************************

.. doxygenfunction:: isAllowMulticast

interruptConfig()
******************************

.. doxygenfunction:: interruptConfig

setDataRate()
******************************

.. doxygenfunction:: setDataRate

getDataRate()
******************************

.. doxygenfunction:: getDataRate

setChannel()
******************************

.. doxygenfunction:: setChannel

getChannel()
******************************

.. doxygenfunction:: getChannel

setCrc()
******************************

.. doxygenfunction:: setCrc

getCrc()
******************************

.. doxygenfunction:: getCrc

setPaLevel()
******************************

.. doxygenfunction:: setPaLevel

getPaLevel()
******************************

.. doxygenfunction:: getPaLevel
