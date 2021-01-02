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
2. Complete the install

   open a text editor

   .. code-block:: shell

       nano /etc/ld.so.conf

   Add the line

   .. code-block:: text

       /usr/local/lib/arm-linux-gnueabihf

   Run

   .. code-block:: shell

       sudo ldconfig
3. Install RF24, using MRAA

   See `Linux Installation <linux_install.html#linux-installation>`_
