.. |get_start_desc| replace:: A simple example of sending data from 1 nRF24L01 transceiver to another.
.. |ac_pl_desc| replace:: A simple example of sending data from 1 nRF24L01 transceiver to another with Acknowledgement (ACK) payloads attached to ACK packets.
.. |manack_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi to transmit and respond with acknowledgment (ACK) transmissions. Notice that the auto-ack feature is enabled, but this example doesn't use automatic ACK payloads because automatic ACK payloads' data will always be outdated by 1 transmission. Instead, this example uses a call and response paradigm.
.. |multiceiver_desc| replace:: A simple example of sending data from as many as 6 nRF24L01 transceivers to 1 receiving transceiver. This technique is trademarked by Nordic Semiconductors as "MultiCeiver".
.. |streaming_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi for streaming multiple payloads.
.. |interrupt_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi to detecting (and verifying) the IRQ (interrupt) pin on the nRF24L01.
.. |use_serial_mon| replace:: Use the Serial Monitor to change each node's behavior.
.. |2_or_more_devs| replace:: This example was written to be used on 2 devices acting as "nodes".

Arduino examples
================

GettingStarted.ino
------------------------

|get_start_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/GettingStarted/GettingStarted.ino
    :caption: /examples/GettingStarted/GettingStarted.ino
    :lineno-start: 13
    :lines: 13-

AcknowledgementPayloads.ino
---------------------------------

|ac_pl_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/AcknowledgementPayloads/AcknowledgementPayloads.ino
    :caption: /examples/AcknowledgementPayloads/AcknowledgementPayloads.ino
    :lineno-start: 14
    :lines: 14-

ManualAcknowledgements.ino
--------------------------------

|manack_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/ManualAcknowledgements/ManualAcknowledgements.ino
    :caption: /examples/ManualAcknowledgements/ManualAcknowledgements.ino
    :lineno-start: 19
    :lines: 19-

MulticeiverDemo.ino
-------------------------

|multiceiver_desc|
|use_serial_mon|

.. literalinclude:: ../examples/MulticeiverDemo/MulticeiverDemo.ino
    :caption: /examples/MulticeiverDemo/MulticeiverDemo.ino
    :lineno-start: 16
    :lines: 16-

StreamingData.ino
-----------------------

|streaming_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/StreamingData/StreamingData.ino
    :caption: /examples/StreamingData/StreamingData.ino
    :lineno-start: 13
    :lines: 13-

InterruptConfigure.ino
----------------------------

|interrupt_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/InterruptConfigure/InterruptConfigure.ino
    :caption: /examples/InterruptConfigure/InterruptConfigure.ino
    :lineno-start: 16
    :lines: 16-
