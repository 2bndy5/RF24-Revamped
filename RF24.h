/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * @file RF24.h
 *
 * Class declaration for RF24 and helper enums
 */

#ifndef __RF24_H__
#define __RF24_H__

#include "RF24_config.h"

#if defined (RF24_LINUX) || defined (LITTLEWIRE)
    #include "utility/includes.h"
#elif defined SOFTSPI
    #include <DigitalIO.h>
#endif


/**
 * @defgroup PaLevel Power Amplifier level
 * Power Amplifier level. The units dBm (decibel-milliwatts or dB<sub>mW</sub>)
 * represents a logarithmic signal loss.
 * @see RF24::setPaLevel(), RF24::getPaLevel()
 * @{
 */
typedef enum {
    /**
     * (0) represents:
     * @rst
     * .. csv-table::
     *     :header: nRF24L01, "Si24R1 with lnaEnabled = 1", "Si24R1 with lnaEnabled = 0"
     *
     *     "-18 dBm", "-6 dBm", "-12 dBm"
     * @endrst
     */
    RF24_PA_MIN = 0,
    /**
     * (1) represents:
     * @rst
     * .. csv-table::
     *     :header: nRF24L01, "Si24R1 with lnaEnabled = 1", "Si24R1 with lnaEnabled = 0"
     *
     *     "-12 dBm", "0 dBm", "-4 dBm"
     * @endrst
     */
    RF24_PA_LOW,
    /**
     * (2) represents:
     * @rst
     * .. csv-table::
     *     :header: nRF24L01, "Si24R1 with lnaEnabled = 1", "Si24R1 with lnaEnabled = 0"
     *
     *     "-6 dBm", "3 dBm", "1 dBm"
     * @endrst
     */
    RF24_PA_HIGH,
    /**
     * (3) represents:
     * @rst
     * .. csv-table::
     *     :header: nRF24L01, "Si24R1 with lnaEnabled = 1", "Si24R1 with lnaEnabled = 0"
     *
     *     "0 dBm", "7 dBm", "4 dBm"
     * @endrst
     */
    RF24_PA_MAX,
    /**
     * (4) This should not be used and remains for backward compatibility.
     */
    RF24_PA_ERROR
} rf24_pa_dbm_e;

/**
 * @}
 * @defgroup Datarate datarate
 * How fast data moves through the air. Units are in bits per second (bps).
 * @see RF24::setDataRate(), RF24::getDataRate()
 * @{
 */
typedef enum {
    /** (0) represents 1 Mbps */
    RF24_1MBPS = 0,
    /** (1) represents 2 Mbps */
    RF24_2MBPS,
    /** (2) represents 250 kbps */
    RF24_250KBPS
} rf24_datarate_e;

/**
 * @}
 * @brief Driver class for nRF24L01(+) 2.4GHz Wireless Transceiver
 */

class RF24 {
private:
    #ifdef SOFTSPI
    SoftSPI<SOFT_SPI_MISO_PIN, SOFT_SPI_MOSI_PIN, SOFT_SPI_SCK_PIN, SPI_MODE> spi;
    #elif defined (SPI_UART)
    SPIUARTClass uspi;
    #endif

    #if defined (RF24_LINUX) || defined (XMEGA_D3) /* XMEGA can use SPI class */
    SPI spi;
    #endif
    #if defined (MRAA)
    GPIO gpio;
    #endif

    uint16_t ce_pin; /** "Chip Enable" pin, activates the RX or TX role */
    uint16_t csn_pin; /** SPI Chip select */
    uint32_t spi_speed; /** SPI Bus Speed */
    #if defined (RF24_LINUX) || defined (XMEGA_D3)
    uint8_t spi_rxbuff[32+1] ; //SPI receive buffer (payload max 32 bytes)
    uint8_t spi_txbuff[32+1] ; //SPI transmit buffer (payload max 32 bytes + 1 byte for the command)
    #endif
    uint8_t status; /** The status byte returned from every SPI transaction */
    uint8_t payload_size; /** Fixed size of payloads */
    bool dynamic_payloads_enabled; /** Whether dynamic payloads are enabled. */
    bool ack_payloads_enabled; /** Whether ack payloads are enabled. */
    uint8_t pipe0_reading_address[5]; /** Last address set on pipe 0 for reading. */
    uint8_t addr_width; /** The address width to use - 3,4 or 5 bytes. */
    uint8_t config_reg; /** For storing the value of the NRF_CONFIG register */
    bool _is_p_variant; /** For storing the result of testing the toggleFeatures() affect */


protected:
    /**
     * SPI transactions
     *
     * Common code for SPI transactions including CSN toggle
     */
    inline void beginTransaction();

    inline void endTransaction();

public:

    /**
     * RF24 Constructor
     * @brief Creates a new instance of this driver.
     *
     * Before using, you create an instance and send in the
     * unique pins that this chip is connected to.
     *
     * @rst
     * See `Arduino &lt;arduino.html&gt;`_, `ATTiny &lt;attiny&gt;`_, or `Linux &lt;linux_general&gt;`_ pages for device specific information.
     *
     * .. note::
     *     Users can specify default SPI speed by modifying ``#define RF24_SPI_SPEED`` in RF24_config.h
     *     For Arduino, SPI speed will only be properly configured this way on devices supporting SPI TRANSACTIONS.
     *     Older\/Unsupported Arduino devices will use a default clock divider and settings configuration
     *     Linux: The old way of setting SPI speeds using BCM2835 driver enums has been removed
     * @endrst
     *
     * @param _cepin The pin attached to Chip Enable on the RF module
     * @param _cspin The pin attached to Chip Select
     * @param _spispeed The SPI speed in Hz ie: 1000000 == 1Mhz
     */
    RF24(uint16_t _cepin, uint16_t _cspin, uint32_t _spispeed = RF24_SPI_SPEED);

    #if defined (RF24_LINUX)
    virtual ~RF24() {};
    #endif

    /**
     * Begin operation of the chip
     *
     * Call this in setup(), before calling any other methods.
     * @code radio.begin() @endcode
     */
    bool begin(void);

    /**
     * Checks if the chip is connected to the SPI bus
     */
    bool isChipConnected();

    /**
     * Start listening on the pipes opened for reading.
     *
     * 1. Be sure to call openReadingPipe() first.
     * 2. Do not call send() while in this mode, without first calling stopListening().
     * 3. Call available() to check for incoming traffic, and read() to get it.
     *
     * Open reading pipe 1 using address `0xCCCECCCECC`
     * @rst
     * .. code-block::
     *
     *     byte address[] = {0xCC, 0xCE, 0xCC, 0xCE, 0xCC};
     *     radio.openReadingPipe(1,address);
     *     radio.startListening();
     *
     * .. note:: If there was a call to openReadingPipe() about pipe 0 prior to
     *     calling this function, then this function will re-write the address
     *     that was last set to reading pipe 0. This is because `openWritingPipe()`
     *     will overwrite the address to reading pipe 0 for proper auto-ack
     *     functionality.
     * @endrst
     */
    void startListening(void);

    /**
     * Stop listening for incoming messages, and switch to transmit mode.
     *
     * Do this before calling send().
     * @rst
     * .. code-block::
     *
     *     radio.stopListening();
     *     radio.send(&amp;data, sizeof(data));
     *
     * .. note:: When the ACK payloads feature is enabled, the TX FIFO buffers are
     *     flushed when calling this function. This is meant to discard any ACK
     *     payloads that were not appended to acknowledgment packets.
     * @endrst
     */
    void stopListening(void);

    /**
     * Check whether there are bytes available to be read
     * @rst
     * .. code-block::
     *
     *     if(radio.available()){
     *       radio.read(&amp;data, sizeof(data));
     *     }
     *
     * @endrst
     * @see available(uint8_t*)
     * @return True if there is a payload available, false if none is
     *
     * @rst
     * .. warning:: This function relies on the information about the pipe number
     *     that received the next available payload. According to the datasheet,
     *     the data about the pipe number that received the next available payload
     *     is "unreliable" during a FALLING transition on the IRQ pin. This means
     *     you should call `clearStatusFlags()` before calling this function
     *     during an ISR (Interrupt Service Routine).
     *
     *     For example:
     *
     *     .. code-block::
     *
     *         void isrCallbackFunction() {
     *           bool tx_ds, tx_df, rx_dr;
     *           radio.clearStatusFlags(tx_ds, tx_df, rx_dr); // resets the IRQ pin to HIGH
     *           radio.available();                           // returned data should now be reliable
     *         }
     *
     *         void setup() {
     *           pinMode(IRQ_PIN, INPUT);
     *           attachInterrupt(digitalPinToInterrupt(IRQ_PIN), isrCallbackFunction, FALLING);
     *         }
     * @endrst
     */
    bool available(void);

    /**
     * Read payload data from the RX FIFO buffer(s).
     *
     * The length of data read is usually the next available payload's length
     * @see getPayloadSize(), getDynamicPayloadSize()
     * @rst
     *
     * .. note:: I specifically chose `void*` as a data type to make it easier
     *     for beginners to use.  No casting needed.
     * @endrst
     *
     * @param buf Pointer to a buffer where the data should be written
     * @param len Maximum number of bytes to read into the buffer. This
     * value should match the length of the object referenced using the
     * `buf` parameter. The absolute maximum number of bytes that can be read
     * in one call is 32 (for dynamic payload lengths) or whatever number was
     * previously passed to setPayloadSize() (for static payload lengths).
     * @remark Remember that each call to read() fetches data from the
     * RX FIFO beginning with the first byte from the first available
     * payload. A payload is not removed from the RX FIFO until it's
     * entire length (or more) is fetched using read().<br>
     * - If @a len parameter's value is less than the available payload's
     *   length, then the payload remains in the RX FIFO.
     * - If @a len parameter's value is greater than the first of multiple
     *   available payloads, then the data saved to the @a buf
     *   parameter's object will be supplemented with data from the next
     *   available payload.
     * - If @a len parameter's value is greater than the last available
     *   payload's length, then the last byte in the payload is used as
     *   padding for the data saved to the @a buf parameter's object.
     *   The nRF24L01 will repeatedly use the last byte from the last
     *   payload even when read() is called with an empty RX FIFO.
     *
     * @rst
     * .. note:: To use this function in the python wrapper, remember that
     *     only the ``len`` parameter is required because this function (in the
     *     python wrapper) returns the payload data as a buffer protocol object
     *     (bytearray object).
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         if radio.available():
     *             length = radio.getDynamicPayloadSize()  # or radio.getPayloadSize() for static payload sizes
     *             received_payload = radio.read(length)
     * @endrst
     *
     * @return No return value. Use available().
     * @rst
     * .. note:: This function no longer returns a boolean. Use available to
     *     determine if packets are available. The ``RX_DR`` Interrupt flag is now
     *     cleared with this function instead of when calling `available()`.
     *
     *     .. code-block::
     *
     *         if(radio.available()) {
     *           radio.read(&amp;data, sizeof(data));
     *         }
     * @endrst
     */
    void read(void* buf, uint8_t len);

    /**
     * Be sure to call openWritingPipe() first to set the destination
     * of where to write to.
     *
     * This blocks until the message is successfully acknowledged by
     * the receiver or the timeout/retransmit maxima are reached.  In
     * the current configuration, the max delay here is 60-70ms.
     *
     * The maximum size of data written is the fixed payload size, see
     * getPayloadSize().  However, you can write less, and the remainder
     * will just be filled with zeroes.
     *
     * TX/RX/RT interrupt flags will be cleared every time write is called
     *
     * @param buf Pointer to the data to be sent
     * @param len Number of bytes to be sent
     *
     * @rst
     * .. code-block::
     *
     *     radio.stopListening();
     *     radio.send(&amp;data, sizeof(data));
     *
     * .. note:: The ``len`` parameter must be omitted when using the python
     *     wrapper because the length of the payload is determined automatically.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         buffer = b"Hello World"  # a `bytes` object
     *         radio.send(buffer)
     * @endrst
     *
     * @return
     * - `true` if the payload was delivered successfully and an acknowledgement
     *   (ACK packet) was received. If auto-ack is disabled, then any attempt
     *   to transmit will also return true (even if the payload was not
     *   received).
     * - `false` if the payload was sent but was not acknowledged with an ACK
     *   packet. This condition can only be reported if the auto-ack feature
     *   is on.
     */
    bool send(const void* buf, uint8_t len);

    /**
     * New: Open a pipe for writing via byte array. Old addressing format retained
     * for compatibility.
     *
     * Only one writing pipe can be opened at once, but this function changes
     * the address that is used to transmit (ACK payloads/packets do not apply
     * here). Be sure to call stopListening() prior to calling this function.
     *
     * Addresses are assigned via a byte array, default is 5 byte address length
     *
     * @rst
     * .. code-block::
     *
     *     uint8_t addresses[][6] = {"1Node", "2Node"};
     *     radio.openWritingPipe(addresses[0]);
     *
     * .. code-block::
     *
     *      uint8_t address[] = {0xCC, 0xCE, 0xCC, 0xCE, 0xCC};
     *      radio.openWritingPipe(address);
     *      address[0] = 0x33;
     *      radio.openReadingPipe(1, address);
     *
     * .. warning:: This function will overwrite the address set to reading pipe 0
     *     as stipulated by the datasheet for proper auto-ack functionality in TX
     *     mode. Use this function to ensure proper transmission acknowledgement
     *     when the address set to reading pipe 0 (via `openReadingPipe()`) does not
     *     match the address passed to this function. If the auto-ack feature is
     *     disabled, then this function will still overwrite the address for
     *     reading pipe 0 regardless.
     *
     * @endrst
     * @see setAddressWidth(), startListening()
     *
     * @param address The address to be used for outgoing transmissions (uses
     * pipe 0). Coordinate this address amongst other receiving nodes (the
     * pipe numbers don't need to match).
     *
     * @remark There is no address length parameter because this function will
     * always write the number of bytes that the radio addresses are configured
     * to use (set with setAddressWidth()).
     */

    void openWritingPipe(const uint8_t* address);

    /**
     * Open a pipe for reading
     *
     * Up to 6 pipes can be open for reading at once.  Open all the required
     * reading pipes, and then call startListening().
     *
     * @see openWritingPipe(), setAddressWidth()
     * @rst
     *
     * .. note:: Pipes 0 and 1 will store a full 5-byte address. Pipes 2-5 will
     *     technically only store a single byte, borrowing up to 4 additional bytes
     *     from pipe 1 per the assigned address width.
     *
     *     Pipes 1-5 should share the same address, except the first byte.
     *     Only the first byte in the array should be unique, e.g.
     *
     *     .. code-block::
     *
     *         uint8_t addresses[][6] = {"Prime", "2Node", "3xxxx", "4xxxx"};
     *         openReadingPipe(0, addresses[0]); // address used is "Prime"
     *         openReadingPipe(1, addresses[1]); // address used is "2Node"
     *         openReadingPipe(2, addresses[2]); // address used is "3Node"
     *         openReadingPipe(3, addresses[3]); // address used is "4Node"
     *
     * .. warning:: If the reading pipe 0 is opened by this function, the address
     *     passed to this function (for pipe 0) will be restored at every call to
     *     `startListening()`, but the address for pipe 0 is ONLY restored if the LSB is a
     *     non-zero value.
     *
     *     Read http:\/\/maniacalbits.blogspot.com\/2013\/04\/rf24-addressing-nrf24l01-radios-require.html
     *     to understand how to avoid using malformed addresses. This address
     *     restoration is implemented because of the underlying neccessary
     *     functionality of `openWritingPipe()`.
     * @endrst
     * @param number Which pipe to open. Only pipe numbers 0-5 are available,
     * an address assigned to any pipe number not in that range will be ignored.
     * @param address The 24, 32 or 40 bit address of the pipe to open.
     *
     * There is no address length parameter because this function will
     * always write the number of bytes (for pipes 0 and 1) that the radio
     * addresses are configured to use (set with setAddressWidth()).
     */

    void openReadingPipe(uint8_t number, const uint8_t* address);

    /**
     * Print a giant block of debugging information to stdout
     *
     * @rst
     * .. warning:: Does nothing if stdout is not defined. See fdevopen in stdio.h
     *     The printf.h file is included with the library for Arduino.
     *
     *     .. code-block::
     *
     *         #include "printf.h"
     *         setup(){
     *           Serial.begin(115200);
     *           printf_begin();
     *           ...
     *         }
     * @endrst
     */
    void printDetails(void);

    /**
     * Print a giant block of debugging information to stdout. This function
     * differs from printDetails() because it makes the information more
     * understandable without having to look up the datasheet or convert
     * hexadecimal to binary. Only use this function if your application can
     * spare a few extra bytes of memory.
     *
     * @rst
     * .. warning:: Does nothing if stdout is not defined. See fdevopen in stdio.h
     *     The printf.h file is included with the library for Arduino.
     *
     *     .. code-block::
     *
     *         #include "printf.h"
     *         setup(){
     *           Serial.begin(115200);
     *           printf_begin();
     *           ...
     *         }
     * @endrst
     */
    void printPrettyDetails(void);

    /**
     * Test whether there are bytes available to be read from the
     * FIFO buffers.
     *
     * @rst
     * .. note:: This function is named `available_pipe()` in the python wrapper.
     *     Additionally, the `available_pipe()` function (which
     *     takes no arguments) returns a 2 item tuple containing (ordered by
     *     tuple's indices):
     *
     *     - A boolean describing if there is a payload available to read from
     *       the RX FIFO buffers.
     *     - The pipe number that received the next available payload in the RX
     *       FIFO buffers. If the item at the tuple's index 0 is `False`, then
     *       this pipe number is invalid.
     * .. note:: To use this function in python:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instatiated RF24 object
     *         has_payload, pipe_number = radio.available_pipe()  # expand the tuple to 2 variables
     *         if has_payload:
     *             print("Received a payload with pipe", pipe_number)
     * @endrst
     *
     * @param[out] pipe_num Which pipe has the payload available
     * @rst
     * .. code-block::
     *
     *     uint8_t pipeNum;
     *     if(radio.available(&amp;pipeNum)){
     *       radio.read(&amp;data, sizeof(data));
     *       Serial.print("Received data on pipe ");
     *       Serial.println(pipeNum);
     *     }
     *
     * .. warning:: According to the datasheet, the data saved to the ``pipe_num``
     *     parameter is "unreliable" during a FALLING transition on the IRQ pin.
     *     This means you should call `clearStatusFlags()` before calling this
     *     function during an ISR (Interrupt Service Routine).
     *
     * For example:
     * .. code-block::
     *
     *     void isrCallbackFunction() {
     *       bool tx_ds, tx_df, rx_dr;
     *       radio.clearStatusFlags(tx_ds, tx_df, rx_dr); // resets the IRQ pin to HIGH
     *       uint8_t pipe;                                // initialize pipe data
     *       radio.available(&amp;pipe);                  // pipe data should now be reliable
     *     }
     *
     *     void setup() {
     *       pinMode(IRQ_PIN, INPUT);
     *       attachInterrupt(digitalPinToInterrupt(IRQ_PIN), isrCallbackFunction, FALLING);
     *     }
     * @endrst
     *
     * @return
     * - `true` if there is a payload available in the top (first out)
     *   level RX FIFO.
     * - `false` if there is nothing available in the RX FIFO because it is
     *   empty.
     */
    bool available(uint8_t* pipe_num);

    /**
     * Use this function to check if the radio's RX FIFO levels are all
     * occupied. This can be used to prevent data loss because any incoming
     * transmissions are rejected if there is no unoccupied levels in the RX
     * FIFO to store the incoming payload. Remember that each level can hold
     * up to a maximum of 32 bytes.
     * @return
     * - `true` if all three 3 levels of the RX FIFO buffers are occupied.
     * - `false` if there is one or more levels available in the RX FIFO
     *   buffers. Remember that this does not always mean that the RX FIFO
     *   buffers are empty; use available() to see if the RX FIFO buffers are
     *   empty or not.
     */
    bool isFifo(bool about_tx, bool check_empty);
    uint8_t isFifo(bool about_tx);

    /**
     * Enter low-power mode
     *
     * To return to normal power mode, call powerUp().
     * @rst
     * .. note:: After calling startListening(), a basic radio will consume about
     *     13.5mA at max PA level. During active transmission, the radio will consume
     *     about 11.5mA, but this will be reduced to 26uA (.026mA) between sending.
     *     In full powerDown mode, the radio will consume approximately 900nA (.0009mA)
     *
     * .. code-block::
     *
     *     radio.powerDown();
     *     avr_enter_sleep_mode(); // Custom function to sleep the device
     *     radio.powerUp();
     * @endrst
     */
    void powerDown(void);

    /**
     * Leave low-power mode - required for normal radio operation after calling powerDown()
     *
     * To return to low power mode, call powerDown().
     * @rst
     * .. note:: This will take up to 5ms for maximum compatibility.
     * @endrst
     */
    void powerUp(void);

    /**
     * Write for single NOACK writes. Optionally disable
     * acknowledgements/auto-retries for a single payload using the
     * multicast parameter set to true.
     *
     * Can be used with enableAckPayload() to request a response
     * @see setAutoAck(), send()
     * @param buf Pointer to the data to be sent
     * @param len Number of bytes to be sent
     * @param multicast Request ACK response (false), or no ACK response
     * (true). Be sure to have called allowMulticast() at least once before
     * setting this parameter.
     * @return
     * - `true` if the payload was delivered successfully and an acknowledgement
     *   (ACK packet) was received. If auto-ack is disabled, then any attempt
     *   to transmit will also return true (even if the payload was not
     *   received).
     * - `false` if the payload was sent but was not acknowledged with an ACK
     *   packet. This condition can only be reported if the auto-ack feature
     *   is on.
     *
     * @rst
     * .. note:: The ``len`` parameter must be omitted when using the python
     *     wrapper because the length of the payload is determined automatically.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         buffer = b"Hello World"  # a `bytes` object
     *         radio.send(buffer, False)  # False = the multicast parameter
     * @endrst
     */
    bool send(const void* buf, uint8_t len, const bool multicast);

    /**
     * Write an acknowledgement (ACK) payload for the specified pipe
     *
     * The next time a message is received on a specified @p pipe, the data in
     * @p buf`` will be sent back in the ACK payload.
     *
     * @see enableAckPayload(), enableDynamicPayloads()
     * @rst
     *
     * .. note:: ACK payloads are handled automatically by the radio chip when a
     *     regular payload is received. It is important to discard regular payloads
     *     in the TX FIFO (using `flushTx()`) before loading the first ACK payload
     *     into the TX FIFO. This function can be called before and after calling
     *     startListening().
     *
     * .. warning:: Only three of these can be pending at any time as there are
     *     only 3 FIFO buffers.
     *
     *     Dynamic payloads must be enabled.
     *
     * .. note:: ACK payloads are dynamic payloads. Calling `enableAckPayload()`
     *     will automatically enable dynamic payloads on pipe 0 (required for TX
     *     mode when expecting ACK payloads). To use ACK payloads on any other
     *     pipe in RX mode, call `enableDynamicPayloads()`.
     * @endrst
     * @param pipe Which pipe# (typically 1-5) will get this response.
     * @param buf Pointer to data that is sent
     * @param len Length of the data to send, up to 32 bytes max.  Not affected
     * by the static payload set by setPayloadSize().
     *
     * @rst
     * .. note:: The ``len`` parameter must be omitted when using the python
     *     wrapper because the length of the payload is determined automatically.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         buffer = b"Hello World"  # a `bytes` object
     *         radio.writeAckPayload(1, buffer)  # load an ACK payload for response on pipe 1
     * @endrst
     *
     * @return
     * - `true` if the payload was loaded into the TX FIFO.
     * - `false` if the payload wasn't loaded into the TX FIFO because it is
     *   already full or the ACK payload feature is not enabled using
     *   enableAckPayload().
     */
    bool writeAckPayload(uint8_t pipe, const void* buf, uint8_t len);

    /**
     * Call this when you get an Interrupt Request (IRQ) to find out why
     *
     * This function describes what event triggered the IRQ pin to go active
     * LOW and clears the status of all events.
     *
     * @see interruptConfig()
     * @param dataReady There is a newly received payload (RX_DR) saved to
     * RX FIFO buffers. Remember that the RX FIFO can only hold up to 3
     * payloads. Once the RX FIFO is full, all further received transmissions
     * are rejected until there is space to save new data in the RX FIFO
     * buffers.
     * @param dataSent The transmission attempt completed (TX_DS). This does
     * not imply that the transmitted data was received by another radio, rather
     * this only reports if the attempt to send was completed. This will
     * always be `true` when the auto-ack feature is disabled.
     * @param dataFail The transmission failed to be acknowledged, meaning
     * too many retries (MAX_RT) were made while expecting an ACK packet. This
     * event is only triggered when auto-ack feature is enabled.
     */
    void clearStatusFlags(bool dataReady=true, bool dataSent=true, bool dataFail=true);

    /**
     * Non-blocking write to the open writing pipe used for buffered writes
     *
     * @rst
     * .. note:: Optimization: This function now leaves the CE pin high, so the radio
     *     will remain in TX or STANDBY-II Mode until a `txStandBy()` command is issued.
     *     Can be used as an alternative to `startWrite()` if writing multiple payloads
     *     at once.
     * .. warning:: It is important to never keep the nRF24L01 in TX mode with FIFO full
     *     for more than 4ms at a time. If the auto retransmit/autoAck is enabled, the nRF24L01
     *     is never in TX mode long enough to disobey this rule. Allow the FIFO to clear by
     *     issuing `txStandBy()` or ensure appropriate time between transmissions.
     *
     * @endrst
     * @see send(); For single noAck writes: setAutoAck(uint8_t, bool)
     * @param buf Pointer to the data to be sent
     * @param len Number of bytes to be sent
     * @param multicast Request ACK response (false), or no ACK response
     * (true). Be sure to have called allowMulticast() at least once before
     * setting this parameter.
     * @param write_only If this is set to `true`, then this function sets the
     * nRF24L01's CE pin to active (enabling TX transmissions). `false` has no
     * effect on the nRF24L01's CE pin and simply loads the payload into the
     * TX FIFO.
     *
     * @return
     * - `true` if the payload was loaded into the TX FIFO.
     * - `false` if the payload wasn't loaded into the TX FIFO because it is
     *   already full
     * @rst
     * .. note:: The ``len`` parameter must be omitted when using the python
     *     wrapper because the length of the payload is determined automatically.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         buffer = b"Hello World"  # a `bytes` object
     *         radio.send(buffer, False, True)  # 3rd parameter is optional
     *         #     False means expecting ACK response (multicast parameter)
     *         #     True means initiate transmission (write_only parameter)
     * @endrst
     */
    bool write(const void* buf, uint8_t len, const bool multicast, bool write_only=0);

    /**
     * The function will instruct the radio to re-use the payload in the
     * top level (first out) of the TX FIFO buffers when a TX failure
     * occurs. Retries are automatically initiated except with the standard
     * send(). This way, data is not flushed from the buffer until calling
     * flushTx(). If the TX FIFO has only the one payload (in the top level),
     * the re-used payload can be overwritten by using send() or write().
     * If the TX FIFO has other payloads enqueued, then the aforementioned
     * functions will attempt to enqueue the a new payload in the TX FIFO
     * (does not overwrite the top level of the TX FIFO). Currently,
     * stopListening() also calls flushTx() when ACK payloads are enabled
     * (via enableAckPayload()).
     *
     * This function only applies when taking advantage of the
     * auto-retry feature. See setAutoAck() and setRetries() to configure the
     * auto-retry feature.
     * @rst
     * .. note:: This is to be used AFTER auto-retry fails if wanting to resend
     *     using the built-in payload reuse feature. In the event of a
     *     re-transmission failure, simply call this function again to
     *     resume re-transmission of the same payload.
     * @endrst
     * @returns
     * - true if re-transmission was successful.
     * - false if the re-transmission failed or the TX FIFO was already empty.
     */
    bool resend();

    /**
     * Empty all 3 of the TX (transmit) FIFO buffers. This is automatically
     * called by stopListening() if ACK payloads are enabled. However,
     * startListening() does not call this function.
     *
     * @return Current value of status register
     */
    uint8_t flushTx(void);

    /**
     * Empty all 3 of the RX (receive) FIFO buffers.
     *
     * @return Current value of status register
     */
    uint8_t flushRx(void);

    /**
     * Test whether there was a carrier on the line for the
     * previous listening period.
     *
     * Useful to check for interference on the current channel.
     *
     * @return true if was carrier, false if not
     */
    bool testCarrier(void);

    /**
     * Test whether a signal (carrier or otherwise) greater than
     * or equal to -64dBm is present on the channel. Valid only
     * on nRF24L01P(+) hardware. On nRF24L01, use testCarrier().
     *
     * Useful to check for interference on the current channel and
     * channel hopping strategies.
     *
     * @rst
     * .. code-block::
     *
     *     bool goodSignal = radio.testRPD();
     *     if(radio.available()){
     *        Serial.println(goodSignal ? "Strong signal &gt; 64dBm" : "Weak signal &lt; 64dBm" );
     *        radio.read(0, 0);
     *     }
     * @endrst
     * @return true if a signal less than or equal to -64dBm was detected,
     * false if not.
     */
    bool testRPD(void);

    /**
     * Test whether this is a real radio, or a mock shim for
     * debugging.  Setting either pin to 0xff is the way to
     * indicate that this is not a real radio.
     *
     * @return true if this is a legitimate radio
     */
    bool isValid()
    {
        return ce_pin != 0xff && csn_pin != 0xff;
    }

    /**
     * Close a pipe after it has been previously opened.
     * Can be safely called without having previously opened a pipe.
     * @param pipe Which pipe number to close, any integer not in range [0, 5]
     * is ignored.
     */
    void closeReadingPipe(uint8_t pipe);

    /**
     * Set the address width from 3 to 5 bytes (24, 32 or 40 bit)
     *
     * @param a_width The address width (in bytes) to use; this can be 3, 4 or
     * 5.
     */
    void setAddressWidth(uint8_t a_width);

    /**
     * Set the number of retry attempts and delay between retry attempts when
     * transmitting a payload. The radio is waiting for an acknowledgement
     * (ACK) packet during the delay between retry attempts.
     *
     * @param delay How long to wait between each retry, in multiples of
     * 250 us. The minumum of 0 means 250 us, and the maximum of 15 means
     * 4000 us. The default value of 5 means 1500us (5 * 250 + 250).
     * @param count How many retries before giving up. The default/maximum is 15. Use
     * 0 to disable the auto-retry feature all together.
     *
     * @rst
     * .. note:: Disable the auto-retry feature on a transmitter still uses the
     *     auto-ack feature (if enabled), except it will not retry to transmit if
     *     the payload was not acknowledged on the first attempt.
     * @endrst
     */
    void setRetries(uint8_t delay, uint8_t count);

    /**
     * Set RF communication channel. The frequency used by a channel is
     * calculated as:
     *
     * 2400 MHz + <channel number>
     *
     * Meaning the default channel of 76 uses the approximate frequency of
     * 2476 MHz.
     *
     * @rst
     * .. note:: In the python wrapper, this function is the setter of the
     *     ``channel`` attribute.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *          # let `radio` be the instantiated RF24 object
     *          radio.channel = 2  # set the channel to 2 (2402 MHz)
     * @endrst
     *
     * @param channel Which RF channel to communicate on, 0-125
     */
    void setChannel(uint8_t channel);

    /**
     * Get RF communication channel
     *
     * @rst
     * .. note:: In the python wrapper, this function is the getter of the
     *     ``channel`` attribute.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         chn = radio.channel  # get the channel
     * @endrst
     *
     * @return The currently configured RF Channel
     */
    uint8_t getChannel(void);

    /**
     * Set Static Payload Size
     *
     * This implementation uses a pre-stablished fixed payload size for all
     * transmissions.  If this method is never called, the driver will always
     * transmit the maximum payload size (32 bytes), no matter how much
     * was sent to send().
     *
     * @rst
     * .. note:: In the python wrapper, this function is the setter of the
     *     ``payloadSize`` attribute.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         radio.payloadSize = 16  # set the static payload size to 16 bytes
     * @endrst
     *
     * @param size The number of bytes in the payload
     */
    void setPayloadSize(uint8_t size);

    /**
     * Get Static Payload Size
     *
     * @rst
     * .. note:: In the python wrapper, this function is the getter of the
     *     ``payloadSize`` attribute.
     *
     *     To use this function in the python wrapper:
     *
     *     .. code-block:: python
     *
     *         # let `radio` be the instantiated RF24 object
     *         pl_size = radio.payloadSize  # get the static payload size
     *
     * @endrst
     * @see setPayloadSize()
     * @return The number of bytes in the payload
     */
    uint8_t getPayloadSize(void);

    /**
     * Get Dynamic Payload Size
     *
     * For dynamic payloads, this pulls the size of the payload off
     * the chip
     *
     * @rst
     * .. note:: Corrupt packets are now detected and flushed per the
     *     manufacturer.
     *
     *     ..code-block::
     *
     *         if(radio.available()){
     *           if(radio.getDynamicPayloadSize() &lt; 1){
     *             // Corrupt payload has been flushed
     *             return;
     *           }
     *           radio.read(&amp;data, sizeof(data));
     *         }
     * @endrst
     *
     * @return Payload length of last-received dynamic payload
     */
    uint8_t getDynamicPayloadSize(void);

    /**
     * Enable custom payloads in the acknowledge packets
     *
     * ACK payloads are a handy way to return data back to senders without
     * manually changing the radio modes on both units.
     *
     * The ACK payload feature requires the auto-ack feature to be
     * enabled for any pipe using ACK payloads. This function does not
     * automatically enable the auto-ack feature on pipe 0 since the auto-ack
     * feature is enabled for all pipes by default.
     *
     * @rst
     * .. seealso `setAutoAck()`
     *
     * .. note:: ACK payloads are dynamic payloads. This function automatically
     *     enables dynamic payloads on pipe 0 by default. Call
     *     enableDynamicPayloads() to enable on all pipes (especially for RX nodes
     *     that use pipes other than pipe 0 to receive transmissions expecting
     *     responses with ACK payloads).
     * @endrst
     */
    void enableAckPayload(void);

    /**
     * Disable custom payloads on the ackowledge packets
     * @see enableAckPayload()
     */
    void disableAckPayload(void);

    /**
     * Enable dynamically-sized payloads
     *
     * This way you don't always have to send large packets just to send them
     * once in a while.  This enables dynamic payloads on ALL pipes.
     */
    void enableDynamicPayloads(void);

    /**
     * Disable dynamically-sized payloads
     *
     * This disables dynamic payloads on ALL pipes. Since Ack Payloads
     * requires Dynamic Payloads, Ack Payloads are also disabled.
     * If dynamic payloads are later re-enabled and ack payloads are desired
     * then enableAckPayload() must be called again as well.
     *
     */
    void disableDynamicPayloads(void);

    /**
     * Enable dynamic ACKs (single write multicast or unicast) for chosen
     * messages.
     *
     * @rst
     * .. note:: This function must be called once before using the multicast
     *     parameter for any functions that offer it. To use multicast behavior
     *     about all outgoing payloads (using pipe 0) or incoming payloads
     *     (concerning all RX pipes), use setAutoAck()
     *
     *
     * .. code-block::
     *
     *     radio.send(&amp;data, 32, 1); // Sends a payload with no acknowledgement requested
     *     radio.send(&amp;data, 32, 0); // Sends a payload using auto-retry/autoACK
     * @endrst
     * @see setAutoAck(bool) for all pipes or setAutoAck(uint8_t, bool) for individual pipes
     */
    void allowMulticast();

    /**
     * Determine whether the hardware is an nRF24L01+ or not.
     *
     * @return true if the hardware is nRF24L01+ (or compatible) and false
     * if its not.
     */
    bool isPVariant(void);

    /**
     * Enable or disable the auto-acknowledgement feature for all pipes. This
     * feature is enabled by default. Auto-acknowledgement responds to every
     * recieved payload with an empty ACK packet. These ACK packets get sent
     * from the receiving radio back to the transmitting radio. To attach an
     * ACK payload to a ACK packet, use writeAckPayload().
     *
     * If this feature is disabled on a transmitting radio, then the
     * transmitting radio will always report that the payload was recieved
     * (even if it was not). Please remember that this feature's configuration
     * needs to match for transmitting and receiving radios.
     *
     * @rst
     * .. warning:: When using the `multicast` parameter to `send()`, this feature
     *     can be disabled for an individual payload. However, if this feature is
     *     disabled, then the ``multicast`` parameter will have no effect.
     *
     * .. note:: If disabling auto-acknowledgment packets, the ACK payloads
     *     feature is also disabled as this feature is required to send ACK
     *     payloads.
     *
     * @endrst
     * @see send(), writeFast(), write(), startWrite(), writeAckPayload()
     * @param enable Whether to enable (true) or disable (false) the
     * auto-acknowledgment feature for all pipes
     */
    void setAutoAck(bool enable);

    /**
     * Enable or disable the auto-acknowledgement feature for a specific pipe.
     * This feature is enabled by default for all pipes. Auto-acknowledgement
     * responds to every recieved payload with an empty ACK packet. These ACK
     * packets get sent from the receiving radio back to the transmitting
     * radio. To attach an ACK payload to a ACK packet, use writeAckPayload().
     *
     * Pipe 0 is used for TX operations, which include sending ACK packets. If
     * using this feature on both TX & RX nodes, then pipe 0 must have this
     * feature enabled for the RX & TX operations. If this feature is disabled
     * on a transmitting radio's pipe 0, then the transmitting radio will
     * always report that the payload was recieved (even if it was not).
     * Remember to also enable this feature for any pipe that is openly
     * listening to a transmitting radio with this feature enabled.
     *
     * @rst
     * .. warning:: If this feature is enabled for pipe 0, then the ``multicast``
     *     parameter to `send()` can be used to disable this feature for an
     *     individual payload. However, if this feature is disabled for pipe 0,
     *     then the ``multicast`` parameter will have no effect.
     *
     * .. note:: If disabling auto-acknowledgment packets on pipe 0, the ACK
     *     payloads feature is also disabled as this feature is required on pipe 0
     *     to send ACK payloads.
     *
     * @endrst
     * @see send(), writeFast(), write(), startWrite(), writeAckPayload(), enableAckPayloads(), disableAckPayloads()
     * @param pipe Which pipe to configure. This number should be in range [0, 5].
     * @param enable Whether to enable (true) or disable (false) the
     * auto-acknowledgment feature for the specified pipe
     */
    void setAutoAck(uint8_t pipe, bool enable);

    /**
     * Set Power Amplifier (PA) level and Low Noise Amplifier (LNA) state
     *
     * @param level The desired @ref PaLevel as defined by @ref rf24_pa_dbm_e.
     * @param lnaEnable Enable or Disable the LNA (Low Noise Amplifier) Gain.
     * See table for Si24R1 modules below.<br> @p lnaEnable only affects
     * nRF24L01 modules with an LNA chip.
     * @rst
     * .. csv-table::
     *     :header: "``level`` (enum value)", "nRF24L01", "Si24R1 when ``lnaEnable = 1``", "Si24R1 when ``lnaEnable = 0``"
     *
     *     :enumerator:`RF24_PA_MIN` (0), "-18 dBm", "-6 dBm", "-12 dBm"
     *     :enumerator:`RF24_PA_LOW` (1), "-12 dBm", "-0 dBm", "-4 dBm"
     *     :enumerator:`RF24_PA_HIGH` (2), "-6 dBm", "3 dBm", "1 dBm"
     *     :enumerator:`RF24_PA_MAX` (3), "0 dBm", "7 dBm", "4 dBm"
     *
     * .. note:: The `getPaLevel()` function does not care what was passed ``lnaEnable`` parameter.
     * @endrst
     */
    void setPaLevel(uint8_t level, bool lnaEnable=1);

    /**
     * Fetches the current @ref PaLevel.
     *
     * @return One of the values defined by @ref rf24_pa_dbm_e.<br>
     * See tables in @ref rf24_pa_dbm_e or setPaLevel()
     */
    uint8_t getPaLevel(void);

    /**
     * Returns automatic retransmission count (ARC_CNT)
     *
     * Value resets with each new transmission. Allows roughly estimating signal strength.
     *
     * @return Returns values from 0 to 15.
     */
    uint8_t lastTxArc(void);

    /**
     * Set the transmission @ref Datarate
     *
     * @rst
     * .. warning:: Setting `RF24_250KBPS` will fail for non-plus modules (when
     *     `isPVariant()` returns false).
     * @endrst
     * @param speed Specify one of the following values (as defined by
     * @ref rf24_datarate_e):
     * @rst
     * .. csv-table::
     *     :header: "``speed`` (enum value)", "description"
     *
     *     "`RF24_1MBPS` (0)", "for 1 Mbps"
     *     "`RF24_2MBPS` (1)", "for 2 Mbps"
     *     "`RF24_250KBPS` (2)", "for 250 kbs"
     * @endrst
     * @return true if the change was successful
     */
    bool setDataRate(rf24_datarate_e speed);

    /**
     * Fetches the currently configured transmission @ref Datarate
     *
     * @return One of the values defined by @ref rf24_datarate_e.<br>
     * See table in @ref rf24_datarate_e or setDataRate()
     */
    rf24_datarate_e getDataRate(void);

    /**
     * Set the CRC checksum length (in bytes)
     * @rst
     * .. note:: CRC checking cannot be disabled if auto-ack is enabled
     * @endrst
     * @param length Specify the CRC checksum length in bytes
     *
     * @rst
     * .. csv-table::
     *     :header: "length", "description"
     *
     *     "0", "to disable using CRC checksums"
     *     "1", "to use 8-bit checksums        "
     *     "2", "to use 16-bit checksums       "
     * @endrst
     */
    void setCrc(uint8_t length);

    /**
     * Get the CRC checksum length (in bytes)
     * @rst
     * .. note:: CRC checksum is automatically when the auto-ack feature is enabled.
     * @endrst
     * @return The number of bytes used for a CRC checksum (see table in setCrc())
     */
    uint8_t getCrc(void);

    /**
     * Retrieve the current status of the chip
     *
     * @return Current value of status register
     */
    uint8_t update(void);


    /**
     * A flag that describes when the "Data Ready" event has occured.
     *
     * @rst
     * .. note:: Calling this function does not update the data it returns. Use update()
     *     to refresh the data as needed.
     * .. important:: This data is updated on every SPI transaction (which is pratically
     *     every other function).
     * @endrst
     */
    bool irqDr(void);

    /**
     * A flag that describes when the "Data Sent" event has occured.
     *
     * @rst
     * .. note:: Calling this function does not update the data it returns. Use update()
     *     to refresh the data as needed.
     * .. important:: This data is updated on every SPI transaction (which is pratically
     *     every other function).
     * @endrst
     */
    bool irqDs(void);

    /**
     * A flag that describes when the "Data Fail" event has occured.
     *
     * @rst
     * .. note:: Calling this function does not update the data it returns. Use update()
     *     to refresh the data as needed.
     * .. important:: This data is updated on every SPI transaction (which is pratically
     *     every other function).
     * @endrst
     */
    bool irqDf(void);

    /**
     * A flag that describes when all 3 levels of the TX FIFO are occupied with a payload.
     *
     * @rst
     * .. note:: Calling this function does not update the data it returns. Use update()
     *     to refresh the data as needed.
     * .. important:: This data is updated on every SPI transaction (which is pratically
     *     every other function).
     * @endrst
     */
    bool isTxFull(void);

    /**
     * This function is used to configure what events will trigger the Interrupt
     * Request (IRQ) pin active LOW.
     * The following events can be configured:
     * 1. "data sent": This does not mean that the data transmitted was
     * recieved, only that the attempt to send it was complete.
     * 2. "data failed": This means the data being sent was not recieved. This
     * event is only triggered when the auto-ack feature is enabled.
     * 3. "data received": This means that data from a receiving payload has
     * been loaded into the RX FIFO buffers. Remember that there are only 3
     * levels available in the RX FIFO buffers.
     *
     * By default, all events are configured to trigger the IRQ pin active LOW.
     * When the IRQ pin is active, use clearStatusFlags() to determine what events
     * triggered it. Remeber that calling clearStatusFlags() also clears these
     * events' status, and the IRQ pin will then be reset to inactive HIGH.
     *
     * The following code configures the IRQ pin to only reflect the "data received"
     * event:
     * @rst
     * .. code-block::
     *
     *     radio.interruptConfig(0, 0, 1);
     * @endrst
     *
     * @param dataReady `true` ignores the "data received" event, `false` reflects the
     * "data received" event on the IRQ pin.
     * @param dataSent  `true` ignores the "data sent" event, `false` reflects the
     * "data sent" event on the IRQ pin.
     * @param dataFail  `true` ignores the "data failed" event, `false` reflects the
     * "data failed" event on the IRQ pin.
     */
    void interruptConfig(bool dataReady=true, bool dataSent=true, bool dataFail=true);

    /**
     *
     * The driver will delay for this duration when stopListening() is called
     *
     * When responding to payloads, faster devices like ARM(RPi) are much faster than Arduino:
     * 1. Arduino sends data to RPi, switches to RX mode
     * 2. The RPi receives the data, switches to TX mode and sends before the Arduino radio is in RX mode
     * 3. If AutoACK is disabled, this can be set as low as 0. If AA/ESB enabled, set to 100uS minimum on RPi
     *
     * @rst
     * .. warning:: If set to 0, ensure 130uS delay after stopListening() and before any sends
     * @endrst
     */
    uint32_t txDelay;

    /**
     *
     * On all devices but Linux and ATTiny, a small delay is added to the CSN toggling function
     *
     * This is intended to minimise the speed of SPI polling due to radio commands
     *
     * If using interrupts or timed requests, this can be set to 0 Default:5
     */
    uint32_t csDelay;

    /**
     * Transmission of constant carrier wave with defined frequency and output power
     *
     * @param level Output power to use
     * @param channel The channel to use
     *
     * @rst
     * .. warning:: If `isPVariant()` returns true, then this function takes extra
     *     measures that alter some settings. These settings alterations include:
     *
     *     - `setAutoAck()` to false (for all pipes)
     *     - `setRetries()` to retry `0` times with a delay of 250 microseconds
     *     - set the TX address to 5 bytes of `0xFF`
     *     - `flushTx()`
     *     - load a 32 byte payload of `0xFF` into the TX FIFO's top level
     *     - `disableCRC()`
     * @endrst
     */
    void startConstCarrier(rf24_pa_dbm_e level, uint8_t channel);

    /**
     * Stop transmission of constant wave and reset PLL and CONT registers
     *
     * @rst
     * .. warning:: this function will `powerDown()` the radio per recommendation of
     *     datasheet.
     * .. important:: If `isPVariant()` returns true, please remember to re-configure the
     *     radio's settings
     *
     *     .. code-block::
     *
     *         // re-establish default settings
     *         setCrc(RF24_CRC_16);
     *         setAutoAck(true);
     *         setRetries(5, 15);
     *
     * @endrst
     * @see startConstCarrier()
     */
    void stopConstCarrier(void);

    /**
     * Open a pipe for reading
     * @see openReadingPipe(uint8_t, const uint8_t*)
     * @rst
     *
     * .. important:: Pipes 1-5 should share the first 32 bits.
     *     Only the least significant byte should be unique, e.g.
     *
     *     .. code-block::
     *
     *         openReadingPipe(1, 0xF0F0F0F0AA);
     *         openReadingPipe(2, 0xF0F0F0F066);
     *
     * .. warning:: Pipe 0 is also used by the writing pipe so should typically be avoided
     *     as a reading pipe.
     *
     *     If used, the reading pipe 0 address needs to be restored at avery call to
     *     `startListening()`, and the address is ONLY restored if the LSB is a non-zero value.
     *
     *     Read http://maniacalbits.blogspot.com/2013/04/rf24-addressing-nrf24l01-radios-require.html
     * @endrst
     *
     * @param number Which pipe# to open, 0-5.
     * @param address The 40-bit address of the pipe to open.
     */
    void openReadingPipe(uint8_t number, uint64_t address);

    /**
     * Open a pipe for writing
     * @see openWritingPipe(const uint8_t)
     * @rst
     *
     * Addresses are 40-bit hex values, e.g.:
     *
     * .. code-block::
     *
     *     openWritingPipe(0xF0F0F0F0F0);
     * @endrst
     *
     * @param address The 40-bit address of the pipe to open.
     */
    void openWritingPipe(uint64_t address);

private:

    /**
     * Set chip select pin
     *
     * Running SPI bus at PI_CLOCK_DIV2 so we don't waste time transferring data
     * and best of all, we make use of the radio's FIFO buffers. A lower speed
     * means we're less likely to effectively leverage our FIFOs and pay a higher
     * AVR runtime cost as toll.
     *
     * @param mode HIGH to take this unit off the SPI bus, LOW to put it on
     */
    void csn(bool mode);

    /**
     * Set chip enable
     *
     * @param level HIGH to actively begin transmission or LOW to put in standby.  Please see data sheet
     * for a much more detailed description of this pin.
     */
    void ce(bool level);

    /**
     * Read a chunk of data in from a register
     *
     * @param reg Which register. Use constants from nRF24L01.h
     * @param buf Where to put the data
     * @param len How many bytes of data to transfer
     * @return Nothing. Older versions of this function returned the status
     * byte, but that it now saved to a private member on all SPI transactions.
     */
    void read_register(uint8_t reg, uint8_t* buf, uint8_t len);

    /**
     * Read single byte from a register
     *
     * @param reg Which register. Use constants from nRF24L01.h
     * @return Current value of register @p reg
     */
    uint8_t read_register(uint8_t reg);

    /**
     * Write a chunk of data to a register
     *
     * @param reg Which register. Use constants from nRF24L01.h
     * @param buf Where to get the data
     * @param len How many bytes of data to transfer
     * @return Nothing. Older versions of this function returned the status
     * byte, but that it now saved to a private member on all SPI transactions.
     */
    void write_register(uint8_t reg, const uint8_t* buf, uint8_t len);

    /**
     * Write a single byte to a register
     *
     * @param reg Which register. Use constants from nRF24L01.h
     * @param value The new value to write
     * @param is_cmd_only If this is true then only the @p reg parameter is written like a SPI cmd ( @p value parameter is ignored)
     * @return Nothing. Older versions of this function returned the status
     * byte, but that it now saved to a private member on all SPI transactions.
     */
    void write_register(uint8_t reg, uint8_t value, bool is_cmd_only = false);

    /**
     * Write the transmit payload
     *
     * The size of data written is the fixed payload size, see getPayloadSize()
     *
     * @param buf Where to get the data
     * @param len Number of bytes to be sent
     * @param writeType the SPI cmd to prefix the payload written to the TX FIFO
     * @return Nothing. Older versions of this function returned the status
     * byte, but that it now saved to a private member on all SPI transactions.
     */
    void write_payload(const void* buf, uint8_t len, const uint8_t writeType);

    /**
     * Read the receive payload
     *
     * The size of data read is the fixed payload size, see getPayloadSize()
     *
     * @param buf Where to put the data
     * @param len Maximum number of bytes to read
     * @return Nothing. Older versions of this function returned the status
     * byte, but that it now saved to a private member on all SPI transactions.
     */
    void read_payload(void* buf, uint8_t len);

    #if !defined (MINIMAL)

    /**
     * Decode and print the given status to stdout
     *
     * @param status Status value to print
     *
     * @rst
     * .. warning:: Does nothing if stdout is not defined. See fdevopen in stdio.h
     * @endrst
     */
    void print_status(uint8_t status);

    /**
     * Decode and print the given 'observe_tx' value to stdout
     *
     * @param value The observe_tx value to print
     *
     * @rst
     * .. warning:: Does nothing if stdout is not defined. See fdevopen in stdio.h
     * @endrst
     */
    void print_observe_tx(uint8_t value);

    /**
     * Print the name and value of an 8-bit register to stdout
     *
     * Optionally it can print some quantity of successive
     * registers on the same line.  This is useful for printing a group
     * of related registers on one line.
     *
     * @param name Name of the register
     * @param reg Which register. Use constants from nRF24L01.h
     * @param qty How many successive registers to print
     */
    void print_byte_register(const char* name, uint8_t reg, uint8_t qty = 1);

    /**
     * Print the name and value of a 40-bit address register to stdout
     *
     * Optionally it can print some quantity of successive
     * registers on the same line.  This is useful for printing a group
     * of related registers on one line.
     *
     * @param name Name of the register
     * @param reg Which register. Use constants from nRF24L01.h
     * @param qty How many successive registers to print
     */
    void print_address_register(const char* name, uint8_t reg, uint8_t qty = 1);

    #endif

    /**
     * Turn on or off the special features of the chip
     *
     * The chip has certain 'features' which are only available when the 'features'
     * are enabled.  See the datasheet for details.
     */
    void toggle_features(void);

};

/**
 * @example{lineno} examples/old_backups/pingpair_irq/pingpair_irq.ino
 * Updated by [TMRh20](https://github.com/TMRh20)
 *
 * This is an example of how to user interrupts to interact with the radio, and a demonstration
 * of how to use them to sleep when receiving, and not miss any payloads.<br>
 * The pingpair_sleepy example expands on sleep functionality with a timed sleep option for the transmitter.
 * Sleep functionality is built directly into my fork of the RF24Network library<br>
 */

/**
 * @example{lineno} examples/old_backups/pingpair_sleepy/pingpair_sleepy.ino
 * Updated by [TMRh20](https://github.com/TMRh20)
 *
 * This is an example of how to use the RF24 class to create a battery-
 * efficient system.  It is just like the GettingStarted_CallResponse example, but the<br>
 * ping node powers down the radio and sleeps the MCU after every
 * ping/pong cycle, and the receiver sleeps between payloads. <br>
 */

/**
 * @example{lineno} examples/rf24_ATTiny/rf24ping85/rf24ping85.ino
 * <b>2014 Contribution by [tong67](https://github.com/tong67)</b><br>
 * Updated 2020 by [2bndy5](http://github.com/2bndy5) for the
 * [SpenceKonde ATTinyCore](https://github.com/SpenceKonde/ATTinyCore)<br>
 * The RF24 library uses the [ATTinyCore by
 * SpenceKonde](https://github.com/SpenceKonde/ATTinyCore)
 *
 * This sketch is a duplicate of the ManualAcknowledgements.ino example
 * (without all the Serial input/output code), and it demonstrates
 * a ATTiny25/45/85 or ATTiny24/44/84 driving the nRF24L01 transceiver using
 * the RF24 class to communicate with another node.
 *
 * A simple example of sending data from 1 nRF24L01 transceiver to another
 * with manually transmitted (non-automatic) Acknowledgement (ACK) payloads.
 * This example still uses ACK packets, but they have no payloads. Instead the
 * acknowledging response is sent with `send()`. This tactic allows for more
 * updated acknowledgement payload data, where actual ACK payloads' data are
 * outdated by 1 transmission because they have to loaded before receiving a
 * transmission.
 *
 * This example was written to be used on 2 devices acting as "nodes".
 */

/**
 * @example{lineno} examples/rf24_ATTiny/timingSearch3pin/timingSearch3pin.ino
 * <b>2014 Contribution by [tong67](https://github.com/tong67)</b><br>
 * Updated 2020 by [2bndy5](http://github.com/2bndy5) for the
 * [SpenceKonde ATTinyCore](https://github.com/SpenceKonde/ATTinyCore)<br>
 * The RF24 library uses the [ATTinyCore by
 * SpenceKonde](https://github.com/SpenceKonde/ATTinyCore)
 *
 * This sketch can be used to determine the best settle time values to use for
 * RF24::csDelay in RF24::csn() (private function).
 * @see RF24::csDelay
 *
 * The settle time values used here are 100/20. However, these values depend
 * on the actual used RC combiniation and voltage drop by LED. The
 * intermediate results are written to TX (PB3, pin 2 -- using Serial).
 *
 * For schematic details, see introductory comment block in the rf24ping85.ino sketch.
 */

/**
 * @example{lineno} examples/old_backups/pingpair_dyn/pingpair_dyn.ino
 *
 * This is an example of how to use payloads of a varying (dynamic) size on Arduino.
 */

/**
 * @example{lineno} examples/old_backups/scanner/scanner.ino
 *
 * Example to detect interference on the various channels available.
 * This is a good diagnostic tool to check whether you're picking a
 * good channel for your application.
 *
 * Inspired by cpixip.
 * See http://arduino.cc/forum/index.php/topic,54795.0.html
 */

#endif // __RF24_H__
