MRAA
====

MRAA is a Low Level Skeleton Library for Communication on GNU/Linux platforms
See `MRAA docs <http://iotdk.intel.com/docs/master/mraa/index.html>`_ for more information

RF24 supports all MRAA supported platforms, but might not be tested on each individual platform due to the wide range of hardware support:

`Report an RF24 bug or issue <https://github.com/2bndy5/RF24/issues>`_

Setup Setup and installation
****************************

Build using the `MRAA library <http://iotdk.intel.com/docs/master/mraa/index.html>`_
The MRAA library is not included.

1. Install, and build MRAA

   .. code-block:: shell

       git clone https://github.com/intel-iot-devkit/mraa.git
       cd mraa
       mkdir build
       cd build
       cmake .. -DBUILDSWIGNODE=OFF
       sudo make install
       sudo ldconfig

   .. seealso:: These instructions are taken generically from the MRAA library documentation.
       For more details, please review the `MRAA library's building instructions <http://iotdk.intel.com/docs/master/mraa/building.html>`_.

2. Install RF24, using MRAA

   See `Linux Installation <linux_install.html#linux-installation>`_.
