# Python Wrapper Installation
wrapper was initially written by [mz-fuzzy](https://github.com/mz-fuzzy)

```eval_rst
.. warning:: Python2 is no longer supported
```

## Prerequisites Prerequisites
### Python3
The [python examples](examples.html#python-wrapper-examples) need Python v3.7 because of the `time.monotonic_ns()` call for measuring microseconds.

```shell
sudo apt-get install python3-dev libboost-python-dev python3-setuptools python3-rpi.gpio
```
### RF24 (C++ library)
The RF24 lib needs to be built in C++ & installed for the python wrapper to wrap it

```eval_rst
See `Linux Installation <linux_install.html>`_ and
`Linux/RPi General <rpi_general.html>`_
```
## Install Installation:
1. For python3 in Raspberry Pi OS (formerly known as Raspbian), it's needed to manually link python boost library, like this:

    ```shell
    sudo ln -s $(ls /usr/lib/arm-linux-gnueabihf/libboost_python3-py3*.so | tail -1) /usr/lib/arm-linux-gnueabihf/libboost_python3.so
    ```
2. Build the library. From the rf24libs/RF24/pyRF24 directory:

    ```shell
    python3 setup.py build
    ```

    ```eval_rst
    .. note::
        Build takes several minutes on arm-based machines. Machines with less than
        1 GB of RAM may need to increase amount of swap for build.
    ```
3. Install the library

    ```shell
    sudo python3 setup.py install
    ```

    ```eval_rst
    See the included `*.py files in the "examples_linux" folder <examples.html#python-wrapper-examples>`_
    and the `RF24 documentation <rf24_api>`_ for usage information.
    ```
4. Running the Example:

    ```eval_rst
    See the additional `Linux General page <rpi_general.html>`_ for information on connecting your hardware.
    ```

    Edit the getting_started.py example to configure the appropriate pins per the link:

    ```shell
    nano getting_started.py
    ```

    ```eval_rst
    Configure another device with one of:

    * `getting_started.py Python example <examples.html#getting-started-py>`_
    * `GettingStarted.ino Arduino example <examples.html#gettingstarted-ino>`_
    * `gettingStarted.cpp Linux example <examples.html#gettingStarted-cpp>`_
    ```
    Run the example
    ```shell
    sudo python3 getting_started.py
    ```
