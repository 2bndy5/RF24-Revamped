/**
 * @file RF24.h
 * @brief A wrapper to patch yje old RF24 API into the newer RF24Rebamped API
 */
#ifndef __RF24_H_
#define __RF24_H_
#include "RF24Revamped.h"

// comment out this line to save some space (not much though)
#define FAILURE_HANDLING

class RF24 : protected RF24Revamped
{
public:
    RF24(uint16_t _csn_pin, uint16_t _ce_pin, uint32_t _spi_speed = RF24_SPI_SPEED)
        : RF24Revamped(_csn_pin, _ce_pin, _spi_speed)
    {
    }

    RF24(uint32_t _spi_speed = RF24_SPI_SPEED) : RF24Revamped(_spi_speed)
    {
    }

    #if defined (RF24_LINUX)
    virtual ~RF24() {};
    #endif

    uint32_t txDelay;

    uint32_t csDelay;

    bool begin(void) { return RF24Revamped::begin(); }

    #if defined (RF24_SPI_PTR) || defined (DOXYGEN_FORCED)
    bool begin(_SPI* spiBus) { return RF24Revamped::begin(spiBus); }

    bool begin(_SPI* spiBus, uint16_t _cepin, uint16_t _cspin) { return RF24Revamped::begin(spiBus, _cepin, _cspin); }
    #endif // defined (RF24_SPI_PTR) || defined (DOXYGEN_FORCED)

    bool begin(uint16_t _cepin, uint16_t _cspin) { return RF24Revamped::begin(_cepin, _cspin); }

    bool isChipConnected() { return RF24Revamped::isChipConnected(); }

    void startListening(void) { RF24Revamped::startListening(void); }

    void stopListening(void) { RF24Revamped::stopListening(void); }

    bool available(void) { return RF24Revamped::available(); }

    void read(void* buf, uint8_t len) { RF24Revamped::read(buf, len); }

    void openWritingPipe(const uint8_t* address) { RF24Revamped::openWritingPipe(address); }

    void openReadingPipe(uint8_t number, const uint8_t* address) { RF24Revamped::openReadingPipe(number, address); }

    #if !defined(MINIMAL)
    void printPrettyDetails(void) { RF24Revamped::printDetails(true); }

    void printDetails(void)
    {
        #if defined(RF24_LINUX)
        printf("================ SPI Configuration ================\n" );
        uint8_t bus_ce = csn_pin % 10;
        uint8_t bus_numb = (csn_pin - bus_ce) / 10;
        printf("CSN Pin\t\t= /dev/spidev%d.%d\n", bus_numb, bus_ce);
        printf("CE Pin\t\t= Custom GPIO%d\n", ce_pin);
        #endif
        printf_P(PSTR("SPI Speedz\t= %d Mhz\n"),(uint8_t)(spi_speed/1000000)); //Print the SPI speed on non-Linux devices
        #if defined(RF24_LINUX)
        printf("================ NRF Configuration ================\n");
        #endif // defined(RF24_LINUX)

        print_status(get_status());

        print_address_register(PSTR("RX_ADDR_P0-1"), RX_ADDR_P0, 2);
        print_byte_register(PSTR("RX_ADDR_P2-5"), RX_ADDR_P2, 4);
        print_address_register(PSTR("TX_ADDR\t"), TX_ADDR);

        print_byte_register(PSTR("RX_PW_P0-6"), RX_PW_P0, 6);
        print_byte_register(PSTR("EN_AA\t"), EN_AA);
        print_byte_register(PSTR("EN_RXADDR"), EN_RXADDR);
        print_byte_register(PSTR("RF_CH\t"), RF_CH);
        print_byte_register(PSTR("RF_SETUP"), RF_SETUP);
        print_byte_register(PSTR("CONFIG\t"), NRF_CONFIG);
        print_byte_register(PSTR("DYNPD/FEATURE"), DYNPD, 2);

        printf_P(PSTR("Data Rate\t"
        PRIPSTR
        "\r\n"),(char*)pgm_read_ptr(&rf24_datarate_e_str_P[getDataRate()]));
        printf_P(PSTR("Model\t\t= "
        PRIPSTR
        "\r\n"),(char*)pgm_read_ptr(&rf24_model_e_str_P[isPVariant()]));
        printf_P(PSTR("CRC Length\t"
        PRIPSTR
        "\r\n"),(char*)pgm_read_ptr(&rf24_crclength_e_str_P[getCRCLength()]));
        printf_P(PSTR("PA Power\t"
        PRIPSTR
        "\r\n"),(char*)pgm_read_ptr(&rf24_pa_dbm_e_str_P[getPALevel()]));
        printf_P(PSTR("ARC\t\t= %d\r\n"), getARC());
    }
    #endif // defined (MINIMAL)

    bool available(uint8_t* pipe_num)
    {
        if (RF24Revamped::avaiable()) {
            *pipe_num = RF24Revamped::pipe();
            return true;
        }
        return false;
    }

    void powerDown(void) { RF24Revamped::powerDown(); }

    void powerUp(void) { RF24Revamped::powerUp(); }

    bool writeBlocking(const void* buf, uint8_t len, uint32_t timeout)
    {
        //Block until the FIFO is NOT full.
        //Keep track of the MAX retries and set auto-retry if seeing failures
        //This way the FIFO will fill up and allow blocking until packets go through
        //The radio will auto-clear everything in the FIFO as long as CE remains high

        uint32_t timer = millis();                               // Get the time that the payload transmission started

        while ((get_status() & (_BV(TX_FULL)))) {                // Blocking only if FIFO is full. This will loop and block until TX is successful or timeout

            if (status & _BV(MAX_RT)) {                          // If MAX Retries have been reached
                reUseTX();                                       // Set re-transmit and clear the MAX_RT interrupt flag
                if (millis() - timer > timeout) {
                    return 0;                                    // If this payload has exceeded the user-defined timeout, exit and return 0
                }
            }
            #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
            if (millis() - timer > (timeout + 95)) {
                errNotify();
                #if defined(FAILURE_HANDLING)
                return 0;
                #endif
            }
            #endif

        }

        //Start Writing
        startFastWrite(buf, len, 0);                             // Write the payload if a buffer is clear

        return 1;                                                // Return 1 to indicate successful transmission
    }

    bool txStandBy()
    {

        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        uint32_t timeout = millis();
        #endif
        while (!(read_register(FIFO_STATUS) & _BV(TX_EMPTY))) {
            if (status & _BV(MAX_RT)) {
                write_register(NRF_STATUS, _BV(MAX_RT));
                ce(LOW);
                flush_tx();    //Non blocking, flush the data
                return 0;
            }
            #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
            if (millis() - timeout > 95) {
                errNotify();
                #if defined(FAILURE_HANDLING)
                return 0;
                #endif
            }
            #endif
        }

        ce(LOW);               //Set STANDBY-I mode
        return 1;
    }

    bool txStandBy(uint32_t timeout, bool startTx)
    {

        if (startTx) {
            stopListening();
            ce(HIGH);
        }
        uint32_t start = millis();

        while (!(read_register(FIFO_STATUS) & _BV(TX_EMPTY))) {
            if (status & _BV(MAX_RT)) {
                write_register(NRF_STATUS, _BV(MAX_RT));
                ce(LOW); // Set re-transmit
                ce(HIGH);
                if (millis() - start >= timeout) {
                    ce(LOW);
                    flush_tx();
                    return 0;
                }
            }
            #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
            if (millis() - start > (timeout + 95)) {
                errNotify();
                #if defined(FAILURE_HANDLING)
                return 0;
                #endif
            }
            #endif
        }

        ce(LOW);  //Set STANDBY-I mode
        return 1;
    }

    bool rxFifoFull() { return RF24Revamped::isFifo(false, false); }

    void maskIRQ(bool tx_ok, bool tx_fail, bool rx_ready) { RF24Revamped::interruptConfig(!rx_ready, !tx_ok, !tx_fail); }

    void whatHappened(bool& tx_ok, bool& tx_fail, bool& rx_ready)
    {
        RF24Revamped::clearStatusFlags();
        tx_ok = RF24Revamped::irqDs();
        tx_fail = RF24Revamped::irqDf();
        rx_ready = RF24Revamped::irqDr();
    }

    void enableDynamicAck() { RF24Revamped::allowMulticast(true); }

    void flush_rx() { RF24Revamped::flushRx(); }

    void flush_tx() { RF24Revamped::flushTx(); }

    bool isPVariant(void) { return RF24Revamped::isPlusVariant(); }

    uint8_t getDynamicPayloadSize(void)
    {
        uint8_t result = read_register(R_RX_PL_WID);

        if (result > 32) {
            flush_rx();
            delay(2);
            return 0;
        }
        return result;
    }

    void setRetries(uint8_t delay, uint8_t count) { RF24Revamped::setAutoRetry(delay * 250 + 250, count); }

    uint8_t getARC(void) { return RF24Revamped::lastTxArc(); }

    void setPALevel(uint8_t level, bool lnaEnable = 1) { RF24Revamped::setPaLevel(level, lnaEnable); }

    uint8_t getPALevel(void) { return RF24Revamped::getPaLevel(); }

    void setCRCLength(rf24_crclength_e length) { RF24Revamped::setCrc(length); }

    void disableCRC(void) { RF24Revamped::setCrc(0); }

    rf24_crclength_e getCRCLength(void) { return RF24Revamped::getCrc(); }

    bool setDataRate(rf24_datarate_e speed) { return RF24Revamped::setDataRate(speed); }

    rf24_datarate_e getDataRate(void) { return RF24Revamped::getDataRate(); }

    void setAddressWidth(uint8_t a_width) { RF24Revamped::setAddressLength(a_width); }

    void setPayloadSize(uint8_t size) { RF24Revamped::setPayloadLength(size); }

    uint8_t getPayloadSize(void) { return RF24Revamped::getPayloadLength(); }

    void enableDynamicPayloads(void) { RF24Revamped::setDynamicPayloads(true); }

    void disableDynamicPayloads(void) { RF24Revamped::setDynamicPayloads(false); }

    bool testCarrier(void) { return RF24Revamped::testRpd(); }

    bool testRPD(void) { return RF24Revamped::testRpd(); }

    void stopConstCarrier(void) { RF24Revamped::stopCarrierWave(); }

    void startConstCarrier(rf24_pa_dbm_e level, uint8_t channel)
    {
        RF24Revamped::setPaLevel(level);
        RF24Revamped::setChannel(channel);
        RF24Revamped::startCarrierWave();
    }

    void reUseTX()
    {
        write_register(NRF_STATUS, _BV(MAX_RT));  //Clear max retry flag
        write_register(REUSE_TX_PL, RF24_NOP, true);
        ce(LOW);                                  //Re-Transfer packet
        ce(HIGH);
    }

    bool isValid() { return RF24Revamped::isValid(); }

    void closeReadingPipe(uint8_t pipe) { RF24Revamped::closeReadingPipe(pipe); }

    void enableAckPayload(void) { RF24Revamped::enableAckPayload(); }

    void disableAckPayload(void) { RF24Revamped::disableAckPayload(); }

    bool writeAckPayload(uint8_t pipe, const void* buf, uint8_t len) { return RF24Revamped::writeAck(pipe, buf, len); }

    void startFastWrite(const void* buf, uint8_t len, const bool multicast, bool startTx)
    {
        write_payload(buf, len, multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD);
        if (startTx) {
            ce(HIGH);
        }
    }

    bool startWrite(const void* buf, uint8_t len, const bool multicast)
    {

        // Send the payload
        write_payload(buf, len, multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD);
        ce(HIGH);
        #if !defined(F_CPU) || F_CPU > 20000000
        delayMicroseconds(10);
        #endif
        ce(LOW);
        return !(status & _BV(TX_FULL));
    }
    #if defined (FAILURE_HANDLING) || defined (RF24_LINUX)

    bool failureDetected;

    void errNotify()
    {
        #if defined (SERIAL_DEBUG) || defined (RF24_LINUX)
        printf_P(PSTR("RF24 HARDWARE FAIL: Radio not responding, verify pin connections, wiring, etc.\r\n"));
        #endif
        #if defined (FAILURE_HANDLING)
        failureDetected = 1;
        #else
        delay(5000);
        #endif
    }

    #endif // defined (FAILURE_HANDLING) || defined (RF24_LINUX)

    bool writeFast(const void* buf, uint8_t len, const bool multicast)
    {
        //Block until the FIFO is NOT full.
        //Keep track of the MAX retries and set auto-retry if seeing failures
        //Return 0 so the user can control the retrys and set a timer or failure counter if required
        //The radio will auto-clear everything in the FIFO as long as CE remains high

        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        uint32_t timer = millis();
        #endif

        //Blocking only if FIFO is full. This will loop and block until TX is successful or fail
        while ((get_status() & (_BV(TX_FULL)))) {
            if (status & _BV(MAX_RT)) {
                return 0;                                        //Return 0. The previous payload has not been retransmitted
                // From the user perspective, if you get a 0, just keep trying to send the same payload
            }
            #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
            if (millis() - timer > 95) {
                errNotify();
                #if defined(FAILURE_HANDLING)
                return 0;
                #endif // defined(FAILURE_HANDLING)
            }
            #endif
        }
        startFastWrite(buf, len, multicast);                     // Start Writing

        return 1;
    }

    bool writeFast(const void* buf, uint8_t len) { return writeFast(buf, len, 0); }

    bool write(const void* buf, uint8_t len, const bool multicast)
    {
        //Start Writing
        startFastWrite(buf, len, multicast);

        //Wait until complete or failed
        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        uint32_t timer = millis();
        #endif // defined(FAILURE_HANDLING) || defined(RF24_LINUX)

        while (!(get_status() & (_BV(TX_DS) | _BV(MAX_RT)))) {
            #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
            if (millis() - timer > 95) {
                errNotify();
                #if defined(FAILURE_HANDLING)
                return 0;
                #else
                delay(100);
                #endif
            }
            #endif
        }

        ce(LOW);

        write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT));

        //Max retries exceeded
        if (status & _BV(MAX_RT)) {
            flush_tx(); // Only going to be 1 packet in the FIFO at a time using this method, so just flush
            return 0;
        }
        //TX OK 1 or 0
        return 1;
    }

    bool write(const void* buf, uint8_t len) { return write(buf, len, 0); }

private:

    uint8_t get_status(void) { return RF24Revamped::update(); }

}

#endif // __RF24_H_