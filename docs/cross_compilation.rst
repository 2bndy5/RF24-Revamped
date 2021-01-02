Linux cross-compilation
=======================

RF24 library supports cross-compilation. Advantages of cross-compilation:

- development tools don't have to be installed on target machine
- resources of target machine don't have to be sufficient for compilation
- compilation time can be reduced for large projects

Mandatory Prerequisites
***********************

Following prerequisites need to be assured:

- ssh passwordless access to target machine `read this article for help <https://linuxconfig.org/passwordless-ssh>`_
- sudo of a remote user without password `read this forum post for help <http://askubuntu.com/questions/334318/sudoers-file-enable-nopasswd-for-user-all-commands>`_
- cross-compilation toolchain for your target machine

  For the Raspberry Pi:

  .. code-block:: shell

      git clone https://github.com/raspberrypi/tools rpi_tools

  and cross-compilation tools must be in PATH, for example

  .. code-block:: shell

      export PATH=$PATH:/your/dir/rpi-tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin

Cross compilation steps
***********************

1. clone RF24 to a machine for cross-compilation

   .. code-block:: shell

       git clone https://github.com/2bndy5/RF24-Revamped
       cd RF24-Revamped
       git checkout revamp
2. configure for cross compilation

   .. code-block:: shell

       ./configure --remote=pi@target_linux_host

   or to manually specify a driver

   .. code-block:: shell

       ./configure --remote=pi@target_linux_host --driver=<driver>

   .. seealso:: Read the output descriptions from the following command:

       .. code-block:: shell

           ./configure --help

3. build

   .. code-block:: shell

       make

4. (optional) install library to cross-compilation machine into cross-exvironment - important for compilation of examples

   .. code-block:: shell

       sudo make install

5. upload library to target machine

   .. code-block:: shell

       make upload

6. (optional) compile examples

   .. code-block:: shell

       cd examples_linux
       make

7. (optional) upload examples to target machine

   .. code-block:: shell

       make upload
