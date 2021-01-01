# ATXMEGA
The RF24 driver can be build as a static library with Atmel Studio 7 in order to be included as any other library in another program for the XMEGA family.

Currently only the **ATXMEGA D3** family is implemented.

## Preparation

Create an empty GCC Static Library project in AS7.

As not all files are required, copy the following directory structure in the project:


```eval_rst
.. |rev7| unicode:: u250c .. upsidedownL
    :rtrim:
.. |backL| unicode:: u2514 .. backwardsL
    :rtrim:
.. |T| unicode:: u251c .. T-joint
    :rtrim:
.. |indent| unicode:: u00a0 u00a0 u00a0 u00a0 .. tab4spaces
    :rtrim:

| |rev7| nRF24L01.h
| |T| printf.h
| |T| RF24.cpp
| |T| RF24.h
| |T| RF24_config.h
| |backL| utility\\
| |indent| |backL| ATXMegaD3\\
| |indent| |indent| |T| compatibility.c
| |indent| |indent| |T| compatibility.h
| |indent| |indent| |T| gpio.cpp
| |indent| |indent| |T| gpio.h
| |indent| |indent| |T| gpio_helper.c
| |indent| |indent| |T| gpio_helper.h
| |indent| |indent| |T| includes.h
| |indent| |indent| |T| RF24_arch_config.h
| |indent| |indent| |T| spi.cpp
| |indent| |indent| |backL| spi.h
```

## Usage
Add the library to your project!

In the file where the `main()` is located, put the following code snippet to update the millisecond functionality:
```cpp
ISR(TCE0_OVF_vect)
{
    update_milisec();
}
```

Declare the rf24 radio with
```c++
RF24 radio(XMEGA_PORTC_PIN3, XMEGA_SPI_PORT_C);
```

1. First parameter is the CE pin which can be any available pin on the uC.
2. Second parameter is the CS which can be on port C (`XMEGA_SPI_PORT_C`) or on port D (`XMEGA_SPI_PORT_D`).

Call the `__start_timer()` to start the millisecond timer.

```eval_rst
.. note:: Note about the millisecond functionality:

    The millisecond functionality is based on the TCE0 so don't use these pins as IO.
```
The operating frequency of the uC is 32MHz. If you have other frequency change the TCE0 registers appropriatly in function `__start_timer()` in [compatibility.c](templates.h#about-timing) file for your frequency.
