
ATTiny examples
================

rf24ping85
----------------

2014 Contribution by `tong67 <https://github.com/tong67>`_

Updated 2020 by `2bndy5 <http://github.com/2bndy5>`_ for the
`SpenceKonde ATTinyCore <https://github.com/SpenceKonde/ATTinyCore>`_

The RF24 library uses the `ATTinyCore by SpenceKonde
<https://github.com/SpenceKonde/ATTinyCore>`_

This sketch is a duplicate of the `ManualAcknowledgements.ino example
<ino_examples.html#manualacknowledgements-ino>`_
(without all the Serial input/output code), and it demonstrates
a ATTiny25/45/85 or ATTiny24/44/84 driving the nRF24L01 transceiver using
the RF24 class to communicate with another node.

A simple example of sending data from 1 nRF24L01 transceiver to another
with manually transmitted (non-automatic) Acknowledgement (ACK) payloads.
This example still uses ACK packets, but they have no payloads. Instead the
acknowledging response is sent with :func:`RF24::send()`. This tactic allows
for more updated acknowledgement payload data, where actual ACK payloads' data
are outdated by 1 transmission because they have to loaded before receiving a
transmission.

This example was written to be used on 2 devices acting as "nodes".

.. literalinclude:: ../examples/rf24_ATTiny/rf24ping85/rf24ping85.ino
    :caption: /examples/rf24_ATTiny/rf24ping85/rf24ping85.ino
    :lineno-start: 85
    :lines: 85-

timingSearch3pin
----------------

2014 Contribution by `tong67 <https://github.com/tong67>`_

Updated 2020 by `2bndy5 <http://github.com/2bndy5>`_ for the
`SpenceKonde ATTinyCore <https://github.com/SpenceKonde/ATTinyCore>`_

The RF24 library uses the `ATTinyCore by SpenceKonde
<https://github.com/SpenceKonde/ATTinyCore>`_

This sketch can determine the best settle time values to use for
macros, defined as ``RF24_CSN_SETTLE_HIGH_DELAY`` and ``RF24_CSN_SETTLE_LOW_DELAY``,
:var:`RF24::csDelay` in RF24::csn() (private function).

.. seealso:: :var:`RF24::csDelay`

The settle time values used here are 100/20. However, these values depend
on the actual used RC combiniation and voltage drop by LED. The
intermediate results are written to TX (PB3, pin 2 -- using Serial).

For schematic details, see introductory comment block in the rf24ping85.ino sketch.

.. literalinclude:: ../examples/rf24_ATTiny/timingSearch3pin/timingSearch3pin.ino
    :caption: /examples/rf24_ATTiny/timingSearch3pin/timingSearch3pin.ino
    :lines: 20-
    :lineno-start: 20

