# Linux Installation
Generic Linux devices are supported via the following drivers:
* SPIDEV
* MRAA
* RPi (native via BCM2835)
* LittleWire

```eval_rst
.. note::
    The ``./configure --driver=SPIDEV`` option should work
    with most Linux systems supporting spi userspace device.
```

## Generic Manual Install
1. Install prerequisites if there are any (MRAA, LittleWire libraries, setup SPI device etc)

    ```eval_rst
    .. note:: See the `MRAA documentation <http://iotdk.intel.com/docs/master/mraa/index.html>`_
        for more info on installing MRAA
    ```
2. Make a directory to contain the RF24 and possibly RF24Network lib and enter it

    ```shell
    mkdir ~/rf24libs
    cd ~/rf24libs
    ```
3. Clone the RF24 repo

    ```shell
    git clone https://github.com/2bndy5/RF24.git RF24
    ```
4. Change to the new RF24 directory

    ```shell
    cd RF24
    ```
5. Configure build environment using

    ```shell
    ./configure
    ```

    This script automatically detects device and build environment.

    For overriding automatic detections, use command-line switches,
    see `./configure --help` for description.
6. Build the library, and run an example file

    ```shell
    make
    sudo make install
    cd examples_linux
    ```

    Edit the gettingstarted example to set your pin configuration.

    ```shell
    nano gettingstarted.cpp
    make
    sudo ./gettingstarted
    ```

## Build using SPIDEV

1. Make sure that spi device support is enabled and /dev/spidev\<a\>.\<b\> is present
2. Manual Install using SPIDEV:

    ```shell
    ./configure --driver=SPIDEV
    make
    sudo make install
    ```
3. Verify install by running an example.
    ```eval_rst
    See the `gettingstarted.cpp example <cpp_examples.html#gettingstarted-cpp>`_ for an example of pin configuration.
    ```
