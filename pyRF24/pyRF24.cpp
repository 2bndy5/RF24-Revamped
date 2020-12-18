#include <RF24/RF24.h>
#include <boost/python.hpp>

namespace bp = boost::python;

// ******************** explicit wrappers **************************
// for methods which need it - mostly for buffer operations
//

void throw_ba_exception(void)
{
    PyErr_SetString(PyExc_TypeError, "buf parameter must be bytes or bytearray");
    bp::throw_error_already_set();
}

char *get_bytes_or_bytearray_str(bp::object buf)
{
    PyObject *py_ba;
    py_ba = buf.ptr();
    if (PyByteArray_Check(py_ba))
    {
        return PyByteArray_AsString(py_ba);
    }
    else if (PyBytes_Check(py_ba))
    {
        return PyBytes_AsString(py_ba);
    }
    else
    {
        throw_ba_exception();
    }
    return NULL;
}

int get_bytes_or_bytearray_ln(bp::object buf)
{
    PyObject *py_ba;
    py_ba = buf.ptr();
    if (PyByteArray_Check(py_ba))
    {
        return PyByteArray_Size(py_ba);
    }
    else if (PyBytes_Check(py_ba))
    {
        return PyBytes_Size(py_ba);
    }
    else
    {
        throw_ba_exception();
    }
    return 0;
}

bp::object read_wrap(RF24 &ref, int maxlen)
{
    char *buf = new char[maxlen + 1];
    ref.read(buf, maxlen);
    bp::object
        py_ba(bp::handle<>(PyByteArray_FromStringAndSize(buf, maxlen < ref.getPayloadLength() ? maxlen : ref.getPayloadLength())));
    delete[] buf;
    return py_ba;
}

bool write_wrap1(RF24 &ref, bp::object buf)
{
    return ref.send(get_bytes_or_bytearray_str(buf), get_bytes_or_bytearray_ln(buf));
}

bool write_wrap2(RF24 &ref, bp::object buf, const bool multicast)
{
    return ref.send(get_bytes_or_bytearray_str(buf), get_bytes_or_bytearray_ln(buf), multicast);
}

void writeAck_wrap(RF24 &ref, uint8_t pipe, bp::object buf)
{
    ref.writeAck(pipe, get_bytes_or_bytearray_str(buf), get_bytes_or_bytearray_ln(buf));
}

void write_wrap1(RF24 &ref, bp::object buf, const bool multicast)
{
    ref.write(get_bytes_or_bytearray_str(buf), get_bytes_or_bytearray_ln(buf), multicast);
}

void write_wrap2(RF24 &ref, bp::object buf, const bool multicast, bool write_only)
{
    ref.write(get_bytes_or_bytearray_str(buf), get_bytes_or_bytearray_ln(buf), multicast, write_only);
}

void openWritingPipe_wrap(RF24 &ref, const bp::object address)
{
    ref.openWritingPipe((const uint8_t *)(get_bytes_or_bytearray_str(address)));
}

void openReadingPipe_wrap(RF24 &ref, uint8_t number, const bp::object address)
{
    ref.openReadingPipe(number, (const uint8_t *)(get_bytes_or_bytearray_str(address)));
}

bp::tuple available_wrap(RF24 &ref)
{
    bool result;
    uint8_t pipe;

    result = ref.available(&pipe);
    return bp::make_tuple(result, pipe);
}

void setPaLevel_wrap(RF24 &ref, rf24_pa_dbm_e level)
{
    ref.setPaLevel(level, 1);
}

void clearStatusFlags_wrap2(RF24 &ref, bool dataReady, bool dataSent)
{
    ref.clearStatusFlags(dataReady, dataSent);
}

void clearStatusFlags_wrap1(RF24 &ref, bool dataReady)
{
    ref.clearStatusFlags(dataReady);
}

bool getDynamicPayloads_wrap(RF24 &ref)
{
    return ref.getDynamicPayloads(0);
}

bool getPayloadLength_wrap(RF24 &ref)
{
    return ref.getPayloadLength(0);
}

// ******************** enums **************************
// from both RF24 and bcm2835
//

BOOST_PYTHON_MODULE(RF24)
{

#ifdef BCM2835_H
    bp::enum_<RPiGPIOPin>("RPiGPIOPin")
        .value("RPI_GPIO_P1_03", RPI_GPIO_P1_03)
        .value("RPI_GPIO_P1_05", RPI_GPIO_P1_05)
        .value("RPI_GPIO_P1_07", RPI_GPIO_P1_07)
        .value("RPI_GPIO_P1_08", RPI_GPIO_P1_08)
        .value("RPI_GPIO_P1_10", RPI_GPIO_P1_10)
        .value("RPI_GPIO_P1_11", RPI_GPIO_P1_11)
        .value("RPI_GPIO_P1_12", RPI_GPIO_P1_12)
        .value("RPI_GPIO_P1_13", RPI_GPIO_P1_13)
        .value("RPI_GPIO_P1_15", RPI_GPIO_P1_15)
        .value("RPI_GPIO_P1_16", RPI_GPIO_P1_16)
        .value("RPI_GPIO_P1_18", RPI_GPIO_P1_18)
        .value("RPI_GPIO_P1_19", RPI_GPIO_P1_19)
        .value("RPI_GPIO_P1_21", RPI_GPIO_P1_21)
        .value("RPI_GPIO_P1_22", RPI_GPIO_P1_22)
        .value("RPI_GPIO_P1_23", RPI_GPIO_P1_23)
        .value("RPI_GPIO_P1_24", RPI_GPIO_P1_24)
        .value("RPI_GPIO_P1_26", RPI_GPIO_P1_26)
        .value("RPI_V2_GPIO_P1_03", RPI_V2_GPIO_P1_03)
        .value("RPI_V2_GPIO_P1_05", RPI_V2_GPIO_P1_05)
        .value("RPI_V2_GPIO_P1_07", RPI_V2_GPIO_P1_07)
        .value("RPI_V2_GPIO_P1_08", RPI_V2_GPIO_P1_08)
        .value("RPI_V2_GPIO_P1_10", RPI_V2_GPIO_P1_10)
        .value("RPI_V2_GPIO_P1_11", RPI_V2_GPIO_P1_11)
        .value("RPI_V2_GPIO_P1_12", RPI_V2_GPIO_P1_12)
        .value("RPI_V2_GPIO_P1_13", RPI_V2_GPIO_P1_13)
        .value("RPI_V2_GPIO_P1_15", RPI_V2_GPIO_P1_15)
        .value("RPI_V2_GPIO_P1_16", RPI_V2_GPIO_P1_16)
        .value("RPI_V2_GPIO_P1_18", RPI_V2_GPIO_P1_18)
        .value("RPI_V2_GPIO_P1_19", RPI_V2_GPIO_P1_19)
        .value("RPI_V2_GPIO_P1_21", RPI_V2_GPIO_P1_21)
        .value("RPI_V2_GPIO_P1_22", RPI_V2_GPIO_P1_22)
        .value("RPI_V2_GPIO_P1_23", RPI_V2_GPIO_P1_23)
        .value("RPI_V2_GPIO_P1_24", RPI_V2_GPIO_P1_24)
        .value("RPI_V2_GPIO_P1_26", RPI_V2_GPIO_P1_26)
        .value("RPI_V2_GPIO_P5_03", RPI_V2_GPIO_P5_03)
        .value("RPI_V2_GPIO_P5_04", RPI_V2_GPIO_P5_04)
        .value("RPI_V2_GPIO_P5_05", RPI_V2_GPIO_P5_05)
        .value("RPI_V2_GPIO_P5_06", RPI_V2_GPIO_P5_06)
        .value("RPI_BPLUS_GPIO_J8_03", RPI_BPLUS_GPIO_J8_03)
        .value("RPI_BPLUS_GPIO_J8_05", RPI_BPLUS_GPIO_J8_05)
        .value("RPI_BPLUS_GPIO_J8_07", RPI_BPLUS_GPIO_J8_07)
        .value("RPI_BPLUS_GPIO_J8_08", RPI_BPLUS_GPIO_J8_08)
        .value("RPI_BPLUS_GPIO_J8_10", RPI_BPLUS_GPIO_J8_10)
        .value("RPI_BPLUS_GPIO_J8_11", RPI_BPLUS_GPIO_J8_11)
        .value("RPI_BPLUS_GPIO_J8_12", RPI_BPLUS_GPIO_J8_12)
        .value("RPI_BPLUS_GPIO_J8_13", RPI_BPLUS_GPIO_J8_13)
        .value("RPI_BPLUS_GPIO_J8_15", RPI_BPLUS_GPIO_J8_15)
        .value("RPI_BPLUS_GPIO_J8_16", RPI_BPLUS_GPIO_J8_16)
        .value("RPI_BPLUS_GPIO_J8_18", RPI_BPLUS_GPIO_J8_18)
        .value("RPI_BPLUS_GPIO_J8_19", RPI_BPLUS_GPIO_J8_19)
        .value("RPI_BPLUS_GPIO_J8_21", RPI_BPLUS_GPIO_J8_21)
        .value("RPI_BPLUS_GPIO_J8_22", RPI_BPLUS_GPIO_J8_22)
        .value("RPI_BPLUS_GPIO_J8_23", RPI_BPLUS_GPIO_J8_23)
        .value("RPI_BPLUS_GPIO_J8_24", RPI_BPLUS_GPIO_J8_24)
        .value("RPI_BPLUS_GPIO_J8_26", RPI_BPLUS_GPIO_J8_26)
        .value("RPI_BPLUS_GPIO_J8_29", RPI_BPLUS_GPIO_J8_29)
        .value("RPI_BPLUS_GPIO_J8_31", RPI_BPLUS_GPIO_J8_31)
        .value("RPI_BPLUS_GPIO_J8_32", RPI_BPLUS_GPIO_J8_32)
        .value("RPI_BPLUS_GPIO_J8_33", RPI_BPLUS_GPIO_J8_33)
        .value("RPI_BPLUS_GPIO_J8_35", RPI_BPLUS_GPIO_J8_35)
        .value("RPI_BPLUS_GPIO_J8_36", RPI_BPLUS_GPIO_J8_36)
        .value("RPI_BPLUS_GPIO_J8_37", RPI_BPLUS_GPIO_J8_37)
        .value("RPI_BPLUS_GPIO_J8_38", RPI_BPLUS_GPIO_J8_38)
        .value("RPI_BPLUS_GPIO_J8_40", RPI_BPLUS_GPIO_J8_40)
        .export_values();

    bp::enum_<bcm2835SPIClockDivider>("bcm2835SPIClockDivider")
        .value("BCM2835_SPI_CLOCK_DIVIDER_65536", BCM2835_SPI_CLOCK_DIVIDER_65536)
        .value("BCM2835_SPI_CLOCK_DIVIDER_32768", BCM2835_SPI_CLOCK_DIVIDER_32768)
        .value("BCM2835_SPI_CLOCK_DIVIDER_16384", BCM2835_SPI_CLOCK_DIVIDER_16384)
        .value("BCM2835_SPI_CLOCK_DIVIDER_8192", BCM2835_SPI_CLOCK_DIVIDER_8192)
        .value("BCM2835_SPI_CLOCK_DIVIDER_4096", BCM2835_SPI_CLOCK_DIVIDER_4096)
        .value("BCM2835_SPI_CLOCK_DIVIDER_2048", BCM2835_SPI_CLOCK_DIVIDER_2048)
        .value("BCM2835_SPI_CLOCK_DIVIDER_1024", BCM2835_SPI_CLOCK_DIVIDER_1024)
        .value("BCM2835_SPI_CLOCK_DIVIDER_512", BCM2835_SPI_CLOCK_DIVIDER_512)
        .value("BCM2835_SPI_CLOCK_DIVIDER_256", BCM2835_SPI_CLOCK_DIVIDER_256)
        .value("BCM2835_SPI_CLOCK_DIVIDER_128", BCM2835_SPI_CLOCK_DIVIDER_128)
        .value("BCM2835_SPI_CLOCK_DIVIDER_64", BCM2835_SPI_CLOCK_DIVIDER_64)
        .value("BCM2835_SPI_CLOCK_DIVIDER_32", BCM2835_SPI_CLOCK_DIVIDER_32)
        .value("BCM2835_SPI_CLOCK_DIVIDER_16", BCM2835_SPI_CLOCK_DIVIDER_16)
        .value("BCM2835_SPI_CLOCK_DIVIDER_8", BCM2835_SPI_CLOCK_DIVIDER_8)
        .value("BCM2835_SPI_CLOCK_DIVIDER_4", BCM2835_SPI_CLOCK_DIVIDER_4)
        .value("BCM2835_SPI_CLOCK_DIVIDER_2", BCM2835_SPI_CLOCK_DIVIDER_2)
        .value("BCM2835_SPI_CLOCK_DIVIDER_1", BCM2835_SPI_CLOCK_DIVIDER_1)
        .export_values();

    bp::enum_<bcm2835SPIChipSelect>("bcm2835SPIChipSelect")
        .value("BCM2835_SPI_CS0", BCM2835_SPI_CS0)
        .value("BCM2835_SPI_CS1", BCM2835_SPI_CS1)
        .value("BCM2835_SPI_CS2", BCM2835_SPI_CS2)
        .value("BCM2835_SPI_CS_NONE", BCM2835_SPI_CS_NONE)
        .export_values();

#endif // BCM2835_H

    bp::enum_<rf24_datarate_e>("rf24_datarate_e")
        .value("RF24_1MBPS", RF24_1MBPS)
        .value("RF24_2MBPS", RF24_2MBPS)
        .value("RF24_250KBPS", RF24_250KBPS)
        .export_values();

    bp::enum_<rf24_pa_dbm_e>("rf24_pa_dbm_e")
        .value("RF24_PA_MIN", RF24_PA_MIN)
        .value("RF24_PA_LOW", RF24_PA_LOW)
        .value("RF24_PA_HIGH", RF24_PA_HIGH)
        .value("RF24_PA_MAX", RF24_PA_MAX)
        .value("RF24_PA_ERROR", RF24_PA_ERROR)
        .export_values();

    // ******************** RF24 class  **************************
    //
    bp::class_<RF24>("RF24", bp::init<uint8_t, uint8_t>((bp::arg("_cepin"), bp::arg("_cspin"))))
#if defined(RF24_LINUX) && !defined(MRAA)
        .def(bp::init<uint8_t, uint8_t, uint32_t>((bp::arg("_cepin"), bp::arg("_cspin"), bp::arg("spispeed"))))
#endif
        .def("begin", &RF24::begin)
        .def("setAddressLength", &RF24::setAddressLength)
        .def("openWritingPipe", &openWritingPipe_wrap, (bp::arg("address")))
        .def("openWritingPipe", (void (::RF24::*)(::uint64_t))(&::RF24::openWritingPipe), (bp::arg("address")))
        .def("openReadingPipe", &openReadingPipe_wrap, (bp::arg("number"), bp::arg("address")))
        .def("openReadingPipe", (void (::RF24::*)(::uint8_t, ::uint64_t))(&::RF24::openReadingPipe), (bp::arg("number"), bp::arg("address")))
        .def("closeReadingPipe", &RF24::closeReadingPipe)
        .def("startListening", &RF24::startListening)
        .def("stopListening", &RF24::stopListening)
        .def("available", (bool (::RF24::*)())(&::RF24::available))
        .def("available_pipe", &available_wrap) // needed to rename this method as python does not allow such overloading
        .def("read", &read_wrap, (bp::arg("maxlen")))
        .def("send", &write_wrap1, (bp::arg("buf")))
        .def("send", &write_wrap2, (bp::arg("buf"), bp::arg("multicast")))
        .def("resend", &RF24::resend)
        .def("write", &write_wrap1, (bp::arg("buf"), bp::arg("length"), bp::arg("multicast")))
        .def("write", &write_wrap2, (bp::arg("buf"), bp::arg("length"), bp::arg("multicast"), bp::arg("write_only")))
        .def("allowMulticast", &RF24::allowMulticast)
        .def("flushTx", &RF24::flushTx)
        .def("flushRx", &RF24::flushRx)
        .def("powerDown", &RF24::powerDown)
        .def("powerUp", &RF24::powerUp)
        .def("printDetails", &RF24::printDetails)
        .def("printPrettyDetails", &RF24::printPrettyDetails)
        .add_property("channel", &RF24::getChannel, &RF24::setChannel)
        .def("setRetries", &RF24::setRetries, (bp::arg("delay"), bp::arg("count")))
        .def("setAutoAck", (void (::RF24::*)(bool))(&::RF24::setAutoAck), (bp::arg("enable")))
        .def("setAutoAck", (void (::RF24::*)(bool, uint8_t))(&::RF24::setAutoAck), (bp::arg("enable"), bp::arg("pipe")))
        .def("getAutoAck", &RF24::getAutoAck, (bp::arg("pipe")))
        .add_property("autoAck", &RF24::setAutoAck, &RF24::getAutoAck)
        .def("setPayloadLength", &RF24::setPayloadLength, (bp::arg("enable"), bp::arg("pipe")))
        .def("getPayloadLength", &RF24::getPayloadLength, (bp::arg("pipe")))
        .add_property("payloadLength", &RF24::getPayloadLength, &RF24::setPayloadLength)
        .def("setDynamicPayloads", (void (::RF24::*)(bool))(&RF24::setDynamicPayloads), (bp::arg("enable")))
        .def("setDynamicPayloads", (void (::RF24::*)(bool, uint8_t))(&RF24::setDynamicPayloads), (bp::arg("enable"), bp::arg("pipe")))
        .def("getDynamicPayloads", &RF24::getDynamicPayloads, (bp::arg("pipe")=0))
        .add_property("dynamicPayloads", &RF24::getDynamicPayloads, &RF24::setDynamicPayloads)
        .def("any", &RF24::any)
        .def("enableAckPayload", &RF24::enableAckPayload)
        .def("writeAck", writeAck_wrap, (bp::arg("pipe"), bp::arg("buf")))
        .def("getCrc", &RF24::getCrc)
        .def("setCrc", &RF24::setCrc, (bp::arg("length")))
        .add_property("crc", &RF24::getCrc, &RF24::setCrc)
        .def("getDataRate", &RF24::getDataRate)
        .def("setDataRate", &RF24::setDataRate, (bp::arg("speed")))
        .add_property("dataRate", &RF24::getDataRate, &RF24::setDataRate)
        .def("getPaLevel", &RF24::getPaLevel)
        .def("setPaLevel", &RF24::setPaLevel, (bp::arg("level"), bp::arg("lnaEnable")))
        .def("setPaLevel", &setPaLevel_wrap, (bp::arg("level")))
        .add_property("paLevel", &RF24::getPaLevel, &RF24::setPaLevel_wrap)
        .def("interruptConfig", &RF24::interruptConfig, (bp::arg("dataReady"), bp::arg("dataSent"), bp::arg("dataFail")))
        .def("update", &RF24::update)
        .def("clearStatusFlags", &RF24::clearStatusFlags, (bp::arg("dataReady"), bp::arg("dataSent"), bp::arg("dataFail")))
        .def("clearStatusFlags", &RF24::clearStatusFlags_wrap2, (bp::arg("dataReady"), bp::arg("dataSent")))
        .def("clearStatusFlags", &RF24::clearStatusFlags_wrap1, (bp::arg("dataReady")))
        .def_readwrite("irqDs", &RF24::irqDs)
        .def_readwrite("irqDr", &RF24::irqDr)
        .def_readwrite("irqDf", &RF24::irqDf)
        .def_readwrite("isTxFull", &RF24::isTxFull)
        .def("isFifo", &RF24::isFifo, (bp::arg("about_tx"), bp::arg("check_empty")))
        .def("isFifo", &RF24::isFifo, (bp::arg("about_tx")))
        .def("isPVariant", &RF24::isPVariant)
        .def("isValid", &RF24::isValid)
        .def("testCarrier", &RF24::testCarrier)
        .def("testRpd", &RF24::testRpd)
        .def("startConstCarrier", &RF24::startConstCarrier, (bp::arg("level"), bp::arg("channel")))
        .def("stopConstCarrier", &RF24::stopConstCarrier);
}
