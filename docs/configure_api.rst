
Configuration API
-----------------

PaLevel enum
****************

.. doxygengroup:: PaLevel

Datarate enum
****************

.. doxygengroup:: Datarate

setDynamicPayloads()
******************************

Unilateral pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloads(bool)

Binary pipe control of Dynamic Payloads
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setDynamicPayloads(uint8_t)

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

Unilateral pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAck(bool)

Binary pipe control of AutoAck
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: setAutoAck(uint8_t)

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
