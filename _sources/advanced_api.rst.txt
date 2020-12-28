
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
    don't execute an SPI transaction are :func:`~RF24::irqDf()`, :func:`~RF24::irqDd()`,
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

powerUp()
******************************

.. doxygenfunction:: powerUp

powerDown()
******************************

.. doxygenfunction:: powerDown

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

Empty OR Full condition
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: isFifo(bool, bool)

Empty AND Full condition
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygenfunction:: isFifo(bool)

lastTxArc()
******************************

.. doxygenfunction:: lastTxArc

isPVariant()
******************************

.. doxygenfunction:: isPVariant

Ambiguous Signal detection
******************************

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
