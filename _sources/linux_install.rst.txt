Linux Installation
==================

Generic Linux devices are supported via the following drivers:

* SPIDEV
* MRAA
* RPi (native via BCM2835)
* LittleWire

.. note:: The following ``SPIDEV`` option should work with most Linux systems
    supporting SPI userspace device.

Using a package manager
***********************

The RF24 library now (as of v1.4.1) has pre-built packages (\*.deb or \*.rpm files) that can be installed on a
Raspberry Pi. These packages can be found on the library's
`GitHub release page <https://GitHub.com/2bndy5/RF24/releases>`_

.. warning:: If you have previously installed the library from source code, then you will need
    to uninstall it manually to avoid runtime conflicts.

.. code-block:: shell

    sudo rm /usr/local/lib/librf24revamped.*
    sudo rm -r /usr/local/include/RF24Revamped

1. Download the appropriate package for your machine

   Go to the library's [GitHub release page](https://GitHub.com/2bndy5/RF24/releases), and look for
   the latest release's assets.

   For all Raspberry Pi variants using the Raspberry Pi OS (aka Raspbian), you need the file marked
   for **armhf** architecture.

   For Raspberry Pi variants using a 64-bit OS (like Ubuntu), you need the file marked for
   **arm64** architecture.

   Notice that the filenames will include the name of the utility driver that the package was built with.
   This does not mean that the LittleWire, MRAA, or wiringPi libraries are included in the package (you will still
   need to install those yourself beforehand).
2. Install the downloaded pkg

   If you downloaded the file directly from your target machine using the desktop environment, then
   you only need to double-click the package (deb or rpm) file, and the OS should do the rest.

   If you downloaded the file remotely and want to copy it over ssh, then use the ``scp`` command in a terminal.

   .. code-block:: shell

       scp pkg_filename.deb pi@host_name:~/Downloads

   .. note:: You do not need to do this from within an ssh session. Also, you can use the target machine's IP
       address instead of its host name

   The ``scp`` command will ask you for a password belonging to the user's name on the remote machine (we used
   ``pi`` in the above example).

   Now you can open up a ssh session and install the copied package from the terminal.

   .. code-block:: shell

       ssh pi@host_name
       cd Downloads
       dpkg -i pkg_filename.deb


Building from Source
**********************

1. Install prerequisites if there are any (MRAA, LittleWire libraries, setup SPI device etc)

   CMake may need to be installed

   .. code-block:: shell

       sudo apt-get install cmake

   .. note:: See the `MRAA documentation <http://iotdk.intel.com/docs/master/mraa/index.html>`_
       for more info on installing MRAA
2. Make a directory to contain the RF24 and possibly RF24Network lib and enter it

   .. code-block:: shell

       mkdir ~/rf24libs
       cd ~/rf24libs
3. Clone the RF24 repo and navigate to it

   .. code-block:: shell

       git clone https://github.com/2bndy5/RF24.git RF24Revamped
       cd RF24Revamped
4. Create a build directory inside the RF24 directory and navigate to it.

   .. code-block:: shell

       mkdir build
       cd build
5. Configure build environment

   .. code-block:: shell

       cmake .. -D RF24_DRIVER=SPIDEV

   Instead of using ``SPIDEV`` driver (recommended), you can also specify the ``RPi``, ``wiringPi``,
   ``MRAA``, or ``LittleWire`` as alternative drivers.

   .. note::
       If the ``RF24_DRIVER`` option is not specified, then it will be automatically configured based
       on the detected CPU or installed libraries (defaults to ``SPIDEV`` when auto-detection fails).
6. Build and install the library

   .. code-block:: shell

       make
       sudo make install
7. Build the examples

   Navigate to the *examples_linux* directory

   .. code-block:: shell

       cd ../examples_linux

   Make sure the pins used in the examples match the pins you used to connect the radio module

   .. code-block:: shell

       nano gettingstarted.cpp

   and edit the pin numbers as directed in the `linux/RPi general documation <rpi_general.html>`_.

   Create a build directory in the examples_linux directory and navigate to it.

   .. code-block:: shell

       mkdir build
       cd build

   Now you are ready to build the examples.<br>

   .. code-block:: shell

       cmake ..
       make

   If using the ``MRAA`` or ``wiringPi`` drivers, then you may need to specify the `RF24_DRIVER`
   option again.

   .. code-block:: shell

       cmake .. -D RF24_DRIVER=wiringPi
       make
8. Run an example file

   .. code-block:: shell

       sudo ./gettingstarted

Cross-compiling the library
***************************

The RF24 library comes with some pre-made toolchain files (located in the *RF24/cmake/toolchains*
directory) to use in CMake. To use these toolchain files, additional command line options are needed
when configuring CMake to build the library (step 5 in the above instructions to build from source).

.. code-block:: shell

    cmake .. -D CMAKE_TOOLCHAIN_FILE=cmake/toolchains/armhf.cmake
    make

If you plan on using the cross-compiled library with your personal cross-compiled project, then
it is advised to specify the path that your project will look in when linking to the RF24 library:

.. code-block:: shell

    cmake .. -D CMAKE_INSTALL_PREFIX=/usr/arm-linux-gnueabihf -D CMAKE_TOOLCHAIN_FILE=cmake/toolchains/armhf.cmake
    make
    sudo make install

Remember to also specify the ``RF24_DRIVER`` option if not using the auto-configuration feature (see step 5
in the above instructions to build from source).

Installing the library remotely
*******************************

To install remotely, you can create an installable package file using CMake's built-in program called CPack.

.. code-block:: shell

    cmake .. -D CMAKE_TOOLCHAIN_FILE=cmake/toolchains/armhf.cmake
    make
    cpack

This will create a deb file and a rpm file in a new sub-directory called "pkgs" within the build directory.
You can use either of these packages to install the library to your target machine (see the above
instructions about using a package manager).
