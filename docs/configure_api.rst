
Configuration API
-----------------

Address Length feature
**********************

setAddressLength()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: setAddressLength

getAddressLength()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: getAddressLength

Dynamic Payload Length feature
******************************

.. note:: If the Dynamic Payload Length feature is enabled for any pipe, then the
    `Static Payload Length feature`_ setting for that pipe(s) is not used.

Dynamic Payload Length setters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Unary pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloads(bool)

Binary pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloadsBin(uint8_t)

Individual pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloads(bool, uint8_t)

Dynamic Payload Length getters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Individual Pipe Representation of Dynamic Payload Length
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: getDynamicPayloads(uint8_t)

Binary Representation of Dynamic Payload Length
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: getDynamicPayloadsBin

Static Payload Length feature
******************************

All pipes are configured to use the maximum default length of 32 bytes.

.. note:: If the
    `Dynamic Payload Length feature`_ is enabled for any pipe, then the Static
    Payload Length setting is not used for that pipe(s).

Static Payload Length setters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Unary pipe control of Static Payload Lengths
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setPayloadLength(uint8_t)

Individual pipe control of Static Payload Length
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setPayloadLength(uint8_t, uint8_t)

getPayloadLength()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: getPayloadLength

Auto-Ack feature
******************************

Auto-acknowledgement responds to every recieved payload with an empty
ACK packet. These ACK packets get sent from the receiving radio back
to the transmitting radio. To attach an ACK payload to a ACK packet,
use :func:`~RF24::writeAck()`.

Pipe 0 is used for TX operations, which include sending ACK packets. If
using this feature on both TX & RX nodes, then pipe 0 must have this
feature enabled for the RX & TX operations. If this feature is disabled
on a transmitting radio's pipe 0, then the transmitting radio will
always report that the payload was sent (even if it was not).
Remember to also enable this feature for any pipe that is openly
listening to a transmitting radio with this feature enabled.

.. warning:: If this feature is enabled for pipe 0, then the ``multicast``
    parameter to :func:`~RF24::send()` can be used to disable this feature for an
    individual payload. However, if this feature is disabled for pipe 0,
    then the ``multicast`` parameter will have no effect.
.. note:: If disabling auto-acknowledgment packets on pipe 0, the
    `Ack Payload feature`_ is also disabled as this feature is required on pipe 0 to send ACK payloads.

Auto-Ack setters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Unary pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAck(bool)

Binary pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAckBin(uint8_t)

Individual pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAck(bool, uint8_t)

Auto-Ack getters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Binary Representation of Auto-Ack
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: getAutoAckBin(void)

Individual Pipe Representation of Auto-Ack
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: getAutoAck(uint8_t)

Auto-Retry feature
**********************************

.. important:: The Auto-Retry feature requires the `Auto-Ack feature`_
    enabled for pipe 0.
.. hint:: Disabling the auto-retry feature on a transmitter still uses the
    auto-ack feature (if enabled), except it will not retry to transmit if
    the payload was not acknowledged on the first attempt.
.. seealso:: :func:`~RF24::lastTxArc()`

Auto-Retry setters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

setAutoRetry()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoRetry

setArd()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setArd

setArc()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setArc

Auto-Retry getters
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

getAutoRetry()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: getAutoRetry

getArc()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: getArc

getArd()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: getArd

Ack Payload feature
**********************************

ACK payloads are a handy way to return data back to senders without
manually changing the radio modes on both units.

.. important:: ACK payloads are dynamically sized payloads. Thus, the ACK payload
    feature requires the `Auto-Ack feature`_ and the
    `Dynamic Payload Length feature`_ to be enabled for any pipe using ACK payloads.

.. seealso:: :func:`~RF24::setAutoAck()`, :func:`~RF24::writeAck()`

enableAckPayload()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: enableAckPayload

disableAckPayload()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: disableAckPayload

Multicast feature
**********************************

allowMulticast()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: allowMulticast

isAllowMulticast()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: isAllowMulticast

interruptConfig()
******************************

.. doxygenfunction:: interruptConfig

RF Data Rate
******************************

Data Rate enum
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: rf24_datarate_e

setDataRate()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: setDataRate

getDataRate()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: getDataRate

RF Channel
******************************

setChannel()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: setChannel

getChannel()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: getChannel

CRC checking
******************************

setCrc()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: setCrc

getCrc()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: getCrc

Power Amplifier Level
******************************

Power Amplifier Level enum
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenenum:: rf24_pa_dbm_e

setPaLevel()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: setPaLevel

getPaLevel()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: getPaLevel
