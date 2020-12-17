.. |get_start_desc| replace:: A simple example of sending data from 1 nRF24L01 transceiver to another.
.. |ac_pl_desc| replace:: A simple example of sending data from 1 nRF24L01 transceiver to another with Acknowledgement (ACK) payloads attached to ACK packets.
.. |manack_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi to transmit and respond with acknowledgment (ACK) transmissions. Notice that the auto-ack feature is enabled, but this example doesn't use automatic ACK payloads because automatic ACK payloads' data will always be outdated by 1 transmission. Instead, this example uses a call and response paradigm.
.. |multiceiver_desc| replace:: A simple example of sending data from as many as 6 nRF24L01 transceivers to 1 receiving transceiver. This technique is trademarked by Nordic Semiconductors as "MultiCeiver".
.. |streaming_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi for streaming multiple payloads.
.. |interrupt_desc| replace:: This is a simple example of using the RF24 class on a Raspberry Pi to detecting (and verifying) the IRQ (interrupt) pin on the nRF24L01.
.. |use_serial_mon| replace:: Use the Serial Monitor to change each node's behavior.
.. |ctrl_c_quit| replace:: Use ``ctrl+c`` to quit at any time, but remember state the radio will persist until another example or application uses it.
.. |2_or_more_devs| replace:: This example was written to be used on 2 devices acting as "nodes".
.. |nav2py_ex_dir| replace:: then navigate to the "RF24/examples_linux" folder.
.. |required_py_ver| replace:: This example requires python v3.7 or newer because it measures transmission time with

Arduino examples
================

GettingStarted.ino
------------------------

|get_start_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/GettingStarted/GettingStarted.ino
    :caption: ../examples/GettingStarted/GettingStarted.ino
    :linenos:

AcknowledgementPayloads.ino
---------------------------------

|ac_pl_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/AcknowledgementPayloads/AcknowledgementPayloads.ino
    :caption: ../examples/AcknowledgementPayloads/AcknowledgementPayloads.ino
    :linenos:

ManualAcknowledgements.ino
--------------------------------

|manack_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/ManualAcknowledgements/ManualAcknowledgements.ino
    :caption: ../examples/ManualAcknowledgements/ManualAcknowledgements.ino
    :linenos:

MulticeiverDemo.ino
-------------------------

|multiceiver_desc|
|use_serial_mon|

.. literalinclude:: ../examples/MulticeiverDemo/MulticeiverDemo.ino
    :caption: ../examples/MulticeiverDemo/MulticeiverDemo.ino
    :linenos:

StreamingData.ino
-----------------------

|streaming_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/StreamingData/StreamingData.ino
    :caption: ../examples/StreamingData/StreamingData.ino
    :linenos:

InterruptConfigure.ino
----------------------------

|interrupt_desc|
|2_or_more_devs|
|use_serial_mon|

.. literalinclude:: ../examples/InterruptConfigure/InterruptConfigure.ino
    :caption: ../examples/InterruptConfigure/InterruptConfigure.ino
    :linenos:

Linux examples
==============

gettingstarted.cpp
-----------------------

|get_start_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/gettingstarted.cpp
    :caption: ../examples_linux/gettingstarted.cpp
    :linenos:

acknowledgementPayloads.cpp
-------------------------------

|ac_pl_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/acknowledgementPayloads.cpp
    :caption: ../examples_linux/acknowledgementPayloads.cpp
    :linenos:

manualAcknowledgements.cpp
------------------------------

|manack_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/manualAcknowledgements.cpp
    :caption: ../examples_linux/manualAcknowledgements.cpp
    :linenos:

multiceiverDemo.cpp
-----------------------

|multiceiver_desc|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/multiceiverDemo.cpp
    :caption: ../examples_linux/multiceiverDemo.cpp
    :linenos:

streamingData.cpp
-----------------------

|streaming_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/streamingData.cpp
    :caption: ../examples_linux/streamingData.cpp
    :linenos:

interruptConfigure.cpp
--------------------------

|interrupt_desc|
|2_or_more_devs|
|ctrl_c_quit|

.. literalinclude:: ../examples_linux/interruptConfigure.cpp
    :caption: ../examples_linux/interruptConfigure.cpp
    :linenos:

Python Wrapper examples
=======================

getting_started.py
------------------------

|get_start_desc|
|2_or_more_devs|
Remember to `install the Python wrapper <python-wrapper.html>`_, |nav2py_ex_dir|
To run this example, enter

.. code-block:: shell

    python3 getting_started.py

and follow the prompts.

.. note::
    |required_py_ver| :py:func:`time.monotonic_ns()`.

|ctrl_c_quit|

.. literalinclude:: ../examples_linux/getting_started.py
    :caption: ../examples_linux/getting_started.py
    :linenos:
    :language: python

acknowledgement_payloads.py
---------------------------------

|ac_pl_desc|
|2_or_more_devs|
Remember to `install the Python wrapper <python-wrapper.html>`_, |nav2py_ex_dir|
To run this example, enter

.. code-block:: shell

    python3 acknowledgement_payloads.py

and follow the prompts.

.. note::
    |required_py_ver| :py:func:`time.monotonic_ns()`.

|ctrl_c_quit|

.. literalinclude:: ../examples_linux/acknowledgement_payloads.py
    :caption: ../examples_linux/acknowledgement_payloads.py
    :linenos:
    :language: python

manual_acknowledgements.py
--------------------------------

|manack_desc|
|2_or_more_devs|
Remember to `install the Python wrapper <python-wrapper.html>`_, |nav2py_ex_dir|
To run this example, enter

.. code-block:: shell

    python3 manual_acknowledgements.py

and follow the prompts.

.. note::
    |required_py_ver| :py:func:`time.monotonic_ns()`.

|ctrl_c_quit|

.. literalinclude:: ../examples_linux/manual_acknowledgements.py
    :caption: ../examples_linux/manual_acknowledgements.py
    :linenos:
    :language: python

multiceiver_demo.py
-------------------------

|multiceiver_desc|
Remember to `install the Python wrapper <python-wrapper.html>`_, |nav2py_ex_dir|
To run this example, enter

.. code-block:: shell

    python3 multiceiver_demo.py

and follow the prompts.

.. note::
    |required_py_ver| :py:func:`time.monotonic_ns()`.

|ctrl_c_quit|

.. literalinclude:: ../examples_linux/multiceiver_demo.py
    :caption: ../examples_linux/multiceiver_demo.py
    :linenos:
    :language: python

streaming_data.py
-----------------------

|streaming_desc|
|2_or_more_devs|
Remember to `install the Python wrapper <python-wrapper.html>`_, |nav2py_ex_dir|
To run this example, enter

.. code-block:: shell

    python3 streaming_data.py

and follow the prompts.

.. note::
    |required_py_ver| :py:func:`time.monotonic_ns()`.

|ctrl_c_quit|

.. literalinclude:: ../examples_linux/streaming_data.py
    :caption: ../examples_linux/streaming_data.py
    :linenos:
    :language: python

interrup_configure.py
---------------------------

|interrupt_desc|
|2_or_more_devs|
Remember to `install the Python wrapper <python-wrapper.html>`_, |nav2py_ex_dir|
To run this example, enter

.. code-block:: shell

    python3 interrup_configure.py

and follow the prompts.

.. note::
    |required_py_ver| :py:func:`time.monotonic_ns()`.

|ctrl_c_quit|

.. literalinclude:: ../examples_linux/interrupt_configure.py
    :caption: ../examples_linux/interrupt_configure.py
    :linenos:
    :language: python
