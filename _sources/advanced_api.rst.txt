
Advanced API
------------

resend()
******************************

.. doxygenfunction:: resend

write()
******************************

.. doxygenfunction:: RF24::write

ce()
******************************

.. doxygenfunction:: ce

writeAck()
******************************

.. doxygenfunction:: writeAck

Status Byte
******************************

.. important:: Calling most of these status byte related functions do not update the
    data they return. Use :func:`~RF24::update()` to refresh the status byte data as needed.

    The status byte data is updated on every SPI transaction. The only functions that
    don't execute an SPI transaction are :func:`~RF24::irqDf()`, :func:`~RF24::irqDs()`,
    :func:`~RF24::irqDr()`, :func:`~RF24::isTxFull()`, and :func:`~RF24::pipe()`.

update()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: update

isTxFull()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: isTxFull

pipe()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: pipe

irqDr()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: irqDr

irqDf()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: irqDf

irqDs()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: irqDs

clearStatusFlags()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: clearStatusFlags

Power mode
******************************

powerUp()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: powerUp

powerDown()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: powerDown

setPower()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: setPower

isPower()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: isPower

FIFO managment
******************************

flushRx()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: flushRx

flushTx()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: flushTx

isFifo()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: isFifo(bool, bool)

lastTxArc()
******************************

.. doxygenfunction:: lastTxArc

isPlusVariant()
******************************

.. doxygenfunction:: isPlusVariant

Ambiguous Signal detection
******************************

The nRF24L01 comes with access to perform hardware specifications
testing to ensure the radio is not defective. The constant carrier
wave test and Received Power Detection (RPD) are common stipulations
mandated by authoritative agencies (i.e. the FCC in the United States).

testRpd()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: testRpd

startCarrierWave()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: startCarrierWave

stopCarrierWave()
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. doxygenfunction:: stopCarrierWave

printDetails()
******************************

.. doxygenfunction:: printDetails
