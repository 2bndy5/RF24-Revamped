.. |get_start_desc| replace:: A simple example of sending data from 1 nRF24L01 transceiver to another.
.. |ac_pl_desc| replace:: A simple example of sending data from 1 nRF24L01 transceiver to another with Acknowledgement (ACK) payloads attached to ACK packets.
.. |manack_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi to transmit and respond with acknowledgment (ACK) transmissions. Notice that the auto-ack feature is enabled, but this example doesn't use automatic ACK payloads because automatic ACK payloads' data will always be outdated by 1 transmission. Instead, this example uses a call and response paradigm.
.. |multiceiver_desc| replace:: A simple example of sending data from as many as 6 nRF24L01 transceivers to 1 receiving transceiver. This technique is trademarked by Nordic Semiconductors as "MultiCeiver".
.. |streaming_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi for streaming multiple payloads.
.. |interrupt_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi to detecting (and verifying) the IRQ (interrupt) pin on the nRF24L01.
.. |scanner_desc| replace:: This example is best used as a diagnostic tool to determine what RF channels have less interference in your vicinity.
.. |ctrl_c_quit| replace:: Use ``ctrl+c`` to quit at any time, but remember state the radio will persist until another example or application uses it.
.. |2_or_more_devs| replace:: This example was written to be used on 2 devices acting as "nodes".

Linux examples
==============

gettingstarted.cpp
-----------------------

|get_start_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/gettingstarted.cpp
    :caption: /examples_linux/gettingstarted.cpp
    :lineno-start: 13
    :lines: 13-

acknowledgementPayloads.cpp
-------------------------------

|ac_pl_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/acknowledgementPayloads.cpp
    :caption: /examples_linux/acknowledgementPayloads.cpp
    :lineno-start: 14
    :lines: 14-

manualAcknowledgements.cpp
------------------------------

|manack_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/manualAcknowledgements.cpp
    :caption: /examples_linux/manualAcknowledgements.cpp
    :lineno-start: 19
    :lines: 19-

multiceiverDemo.cpp
-----------------------

|multiceiver_desc|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/multiceiverDemo.cpp
    :caption: /examples_linux/multiceiverDemo.cpp
    :lineno-start: 16
    :lines: 16-

streamingData.cpp
-----------------------

|streaming_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/streamingData.cpp
    :caption: /examples_linux/streamingData.cpp
    :lineno-start: 13
    :lines: 13-

interruptConfigure.cpp
--------------------------

|interrupt_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/interruptConfigure.cpp
    :caption: /examples_linux/interruptConfigure.cpp
    :lineno-start: 16
    :lines: 16-


scanner.cpp
--------------------------

|scanner_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/scanner.cpp
    :caption: /examples_linux/scanner.cpp
    :lineno-start: 25
    :lines: 25-
