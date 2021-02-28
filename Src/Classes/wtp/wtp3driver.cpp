#include <stdlib.h>
#include "wtp3driver.h"
#include "frame_tools.h"
#include "rfm22frame.h"
#include "rfm22driver.h"
#include "crc_tools.h"
#include "crc32_basic.h"
#include "wtp3drivercalls.h"

Wtp3Driver *Wtp3Driver::singleton = NULL;

Wtp3Driver::Wtp3Driver()
{
    if(singleton == NULL)
    {
        singleton = this;
    }
}

void Wtp3Driver::forceReset(uint16_t delay_ms)
{
    wtp3drivercalls_setTimer(2, delay_ms);
}

uint32_t Wtp3Driver::getOwnAddress()
{
    return ownAddress;
}

uint16_t Wtp3Driver::getOwnDevice()
{
    return ownDevice;
}

SWtp3AddressHeader *Wtp3Driver::getReceivedAddressHeader()
{
    return &receivedAddrHeader;
}

EReceiveMode Wtp3Driver::getReceiveMode()
{
    return receiveMode;
}

void Wtp3Driver::setReceiveMode(EReceiveMode mode)
{
    receiveMode = mode;
}

rfm22frame_state_t Wtp3Driver::getFrameState()
{
    return rfm22frameState;
}

uint8_t Wtp3Driver::getSignalStrengthPercent()
{
    uint16_t signal = rfm22frame_get_signal_strength();
    uint8_t result;

    if(signal == 0)
    {
        result = 0;
    }
    else if(signal <= SIGNAL_POWER_1_PERCENT)
    {
        result = 1;
    }
    else if(signal >= SIGNAL_POWER_100_PERCENT)
    {
        result = 100;
    }
    else
    {
        result = ((uint32_t)(signal - SIGNAL_POWER_1_PERCENT) * 100U + (SIGNAL_POWER_100_PERCENT - SIGNAL_POWER_1_PERCENT) / 2)
                 / (SIGNAL_POWER_100_PERCENT - SIGNAL_POWER_1_PERCENT);
        if(result < 1)
        {
            result = 1;
        }
    }
    return result;
}

void Wtp3Driver::init(IWtp3Device *devicesArr[], uint16_t devicesArrSize, uint32_t ownAddress,
        uint16_t ownDevice, EReceiveMode receiveMode, uint8_t receivedCmdSizeMax)
{
    uint16_t i;

    rfm22frame_init(1, sizeHeaderFirstCheck, SIZE_HEADER_SIZE);
    this->rfm22frameState = rfm22frame_get_state();

    this->txbuf = rfm22frame_get_tx_buff();
    this->rxbuf = rfm22frame_get_rx_buff();
    this->devicesArr = devicesArr;
    this->devicesArrSize = devicesArrSize;
    this->ownAddress = ownAddress;
    this->ownDevice = ownDevice;
    this->receiveMode = receiveMode;
    this->receivedCmdSizeMax = receivedCmdSizeMax;
    this->generalErrorsCounter = 0;
    this->txErrorsCounter = 0;
    this->rxErrorsCounter = 0;
    wtp3drivercalls_setTimer(2, RESET_INTERVAL_MILISEC);

    for(i = 0; i < this->devicesArrSize; i++)
    {
        this->devicesArr[i]->init();
    }
    switch(this->receiveMode)
    {
        case RECEIVE_MODE_CONTINUOUS:
            rfm22frame_start_rx_waiting(0);
            break;
        case RECEIVE_MODE_AFTER_TX:
        case RECEIVE_MODE_OFF:
            //it stays in FRS_IDLE
            break;
    }
}

void Wtp3Driver::update()
{
    uint16_t i;

    //rfm22frame update
    rfm22frame_update();

    //counters update
    wtp3drivercalls_updateCounters();

    //devices update
    for(i = 0; i < devicesArrSize; i++)
    {
        devicesArr[i]->update();
    }

    //main part
    switch(rfm22frame_get_state())
    {
        case FRS_IDLE:
            {
                uint8_t actionDone = 0;

                if(!actionDone)
                {
                    uint8_t error = 0;

                    if(rfm22frame_is_general_error())
                    {
                        incrementErrorCounter(&generalErrorsCounter);
                        error = 1;
                    }
                    if(rfm22frame_is_rx_error())
                    {
                        incrementErrorCounter(&rxErrorsCounter);
                        error = 1;
                    }
                    if(rfm22frame_is_rx_callback_error())
                    {
                        error = 1;
                    }
                    if(rfm22frame_is_tx_error())
                    {
                        incrementErrorCounter(&txErrorsCounter);
                        error = 1;
                    }
                    if(error || wtp3drivercalls_isTimerZero(2))
                    {
                        if(rfm22frame_is_general_error() || ((rxErrorsCounter + txErrorsCounter) >= REINIT_ERROR_COUNT)
                                || wtp3drivercalls_isTimerZero(2))
                        {
                            rfm22frame_init(0, sizeHeaderFirstCheck, SIZE_HEADER_SIZE);
                            //rfm22frame interrupt in FRS_IDLE possible here
                            //generalErrorsCounter is never cleared
                            rxErrorsCounter = 0;
                            txErrorsCounter = 0;
                            wtp3drivercalls_setTimer(2, RESET_INTERVAL_MILISEC);
                        }
                        rfm22frame_clear_error_flags();
                        prot3buff_clear(txbuf);
                        prot3buff_clear(rxbuf);
                        switch(receiveMode)
                        {
                            case RECEIVE_MODE_CONTINUOUS:
                                rfm22frame_start_rx_waiting(0);
                                break;
                            case RECEIVE_MODE_AFTER_TX:
                            case RECEIVE_MODE_OFF:
                                //it stays in FRS_IDLE
                                break;
                        }
                        actionDone = 1;
                    }
                }
                if(!actionDone && isFrameReceived())
                {
                    IWtp3Device *device = NULL;

                    if(checkFrame())
                    {
                        if(((receivedAddrHeader.dest == WTP3_BROADCAST) || (receivedAddrHeader.dest == ownAddress))
                                && (receivedAddrHeader.sender != ownAddress))
                        {
                            //crc and address conditions verified
                            device = findDevice(receivedAddrHeader.device);
                        }
                    }
                    if(device != NULL)
                    {
                        ERecFrameResult recFrameResult = REC_FRAME_NO_ANSWER;

                        prot3buff_clear(txbuf);
                        recFrameResult = device->receiveFrame(this);
                        prot3buff_clear(rxbuf);
                        switch(recFrameResult)
                        {
                            case REC_FRAME_ANSWER:
                                rfm22frame_start_tx();
                                break;
                            case REC_FRAME_NO_ANSWER:
                                switch(receiveMode)
                                {
                                    case RECEIVE_MODE_CONTINUOUS:
                                    case RECEIVE_MODE_AFTER_TX:
                                        rfm22frame_start_rx_waiting(0);
                                        break;
                                    case RECEIVE_MODE_OFF:
                                        //it's possible if receiveMode's been changed
                                        break;
                                }
                                break;
                            case REC_FRAME_NO_ANSWER_STOP_RX:
                                switch(receiveMode)
                                {
                                    case RECEIVE_MODE_CONTINUOUS:
                                        //not so correct recFrameResult returned
                                        rfm22frame_start_rx_waiting(0);
                                        break;
                                    case RECEIVE_MODE_AFTER_TX:
                                    case RECEIVE_MODE_OFF:
                                        //it stays in FRS_IDLE
                                        //RECEIVE_OFF is possible if receiveMode's been changed
                                        break;
                                }
                                break;
                        }
                    }
                    else
                    {
                        prot3buff_clear(txbuf);
                        prot3buff_clear(rxbuf);
                        switch(receiveMode)
                        {
                            case RECEIVE_MODE_CONTINUOUS:
                            case RECEIVE_MODE_AFTER_TX:
                                rfm22frame_start_rx_waiting(0);
                                break;
                            case RECEIVE_MODE_OFF:
                                //it's possible if receiveMode's been changed
                                break;
                        }
                    }
                    actionDone = 1;
                }
                if(!actionDone && isFrameSent())
                {
                    //sending done
                    prot3buff_clear(txbuf);
                    prot3buff_clear(rxbuf);
                    switch(receiveMode)
                    {
                        case RECEIVE_MODE_CONTINUOUS:
                        case RECEIVE_MODE_AFTER_TX:
                            //timer set for RECEIVE_MODE_CONTINUOUS too, for the case of state changed
                            wtp3drivercalls_setTimer(0, LIMITED_RX_DELAY_TIME_MILISEC);
                            rfm22frame_start_rx_waiting(0);
                            break;
                        case RECEIVE_MODE_OFF:
                            //it stays in FRS_IDLE
                            break;
                    }
                    actionDone = 1;
                }
                if(!actionDone)
                {
                    switch(receiveMode)
                    {
                        case RECEIVE_MODE_CONTINUOUS:
                            break;
                        case RECEIVE_MODE_AFTER_TX:
                        case RECEIVE_MODE_OFF:
                            {
                                IWtp3Device *device = findDeviceToSend();
                                if(device != NULL)
                                {
                                    device->createFrame(this);
                                    rfm22frame_start_tx();
                                    actionDone = 1;
                                }
                            }
                            break;
                    }
                }
            }
            break;

        case FRS_RX_WAIT:
            switch(receiveMode)
            {
                case RECEIVE_MODE_CONTINUOUS:
                    {
                        if(wtp3drivercalls_isTimerZero(2))
                        {
                            //if FRS_RX_WAIT->FRS_RX hazard happened, incoming frame will be handled normally
                            rfm22frame_stop_rx_waiting();
                        }
                        else
                        {
                            IWtp3Device *device = findDeviceToSend();

                            if(device != NULL)
                            {
                                //if FRS_RX_WAIT->FRS_RX hazard, state is not changed
                                rfm22frame_stop_rx_waiting();
                                if(rfm22frame_get_state() == FRS_IDLE)
                                {
                                    device->createFrame(this);
                                    rfm22frame_start_tx();
                                }
                            }
                        }
                    }
                    break;
                case RECEIVE_MODE_AFTER_TX:
                    if(wtp3drivercalls_isTimerZero(0))
                    {
                        //if FRS_RX_WAIT->FRS_RX hazard happened, incoming frame will be handled normally
                        rfm22frame_stop_rx_waiting();
                    }
                    break;
                case RECEIVE_MODE_OFF:
                    //if FRS_RX_WAIT->FRS_RX hazard happened, incoming frame will be handled normally
                    rfm22frame_stop_rx_waiting();
                    break;
            }
            break;

        case FRS_RX:
        case FRS_TX:
            break;
    }
    rfm22frameState = rfm22frame_get_state();
}

void Wtp3Driver::startFrame(uint32_t dest, uint8_t answer, uint8_t signin)
{
    prot3buff_clear(txbuf);
    addSizeHeader(0, 0);
    addAddressHeader(dest, ownAddress, answer, signin);
}

void Wtp3Driver::addAddressHeader(uint32_t dest, uint32_t sender, uint8_t answer, uint8_t signin)
{
    uint8_t arr[ADDRESS_HEADER_SIZE];

    answer = (answer != 0);
    signin = (signin != 0);
    frame_tools_uint32_to_bytes_LSB(dest, &arr[0]);
    frame_tools_uint32_to_bytes_LSB(sender, &arr[4]);
    arr[8] = (answer << 7) | (signin << 6) | ((ownDevice >> 8) & 0x07);
    arr[9] = (uint8_t)ownDevice;

    prot3buff_putBytes(txbuf, arr, ADDRESS_HEADER_SIZE);
}

void Wtp3Driver::addShortCommand(uint8_t command, uint8_t data)
{
    command &= 0x7F;
    prot3buff_putByte(txbuf, command);
    prot3buff_putByte(txbuf, data);
}

void Wtp3Driver::addLongCommand(uint8_t command, uint8_t size, uint8_t *data)
{
    command |= 0x80;
    prot3buff_putByte(txbuf, command);
    prot3buff_putByte(txbuf, size);
    prot3buff_putBytes(txbuf, data, size);
}


void Wtp3Driver::endFrame()
{
    uint32_t crc = crc_tools_32_get_initial_value();
    uint16_t size;
    uint8_t arr[CRC_SIZE];
    uint8_t byte;

    //crc and reader reset to 0 pos
    prot3buff_setReaderToPos(txbuf, SIZE_HEADER_SIZE);
    while(prot3buff_isByteAvailable(txbuf))
    {
        crc = crc32_basic_update(crc, (uint8_t)prot3buff_readByte(txbuf));
    }
    frame_tools_uint32_to_bytes_LSB(crc, arr);
    prot3buff_putBytes(txbuf, arr, CRC_SIZE);

    //replace size header
    //size includes size-header & crc
    size = prot3buff_getWriterPos(txbuf);
    addSizeHeader(size, 1);

    //scramble
    prot3buff_setReaderToPos(txbuf, 1);
    scrambler_reset_state(&scrambler);
    while(prot3buff_isByteAvailable(txbuf))
    {
        byte = (uint8_t)prot3buff_readByte(txbuf);
        byte = scrambler_update(&scrambler, byte);
        prot3buff_replaceLastReadByte(txbuf, byte);
    }

    //reset reader to 0 pos
    prot3buff_setReaderToPos(txbuf, 0);
}

uint8_t Wtp3Driver::isFrameReceived()
{
    return (prot3buff_getWriterPos(rxbuf) > 0) && prot3buff_isByteAvailable(rxbuf);
}

uint8_t Wtp3Driver::isFrameSent()
{
    return (prot3buff_getWriterPos(txbuf) > 0) && !prot3buff_isByteAvailable(txbuf);
}

void Wtp3Driver::addSizeHeader(uint16_t size, uint8_t replace)
{
    uint16_t pos;
    uint8_t arr[SIZE_HEADER_SIZE];

    arr[0] = 0x03;
    arr[1] = (size >> 8) & 0x07;
    arr[2] = size & 0xFF;
    arr[3] = crc_tools_ibutton_calculate(arr, SIZE_HEADER_SIZE - 1);

    if(replace)
    {
        pos = prot3buff_getWriterPos(txbuf);
        prot3buff_setWriterToPos(txbuf, 0);
    }
    prot3buff_putBytes(txbuf, arr, SIZE_HEADER_SIZE);
    if(replace)
    {
        prot3buff_setWriterToPos(txbuf, pos);
    }
}

uint16_t Wtp3Driver::checkSizeHeader(uint8_t descramble)
{
    uint8_t arr[SIZE_HEADER_SIZE];
    uint8_t read;
    uint8_t i;
    uint8_t crc;
    uint16_t size = 0xFFFF;

    read = prot3buff_readBytes(rxbuf, arr, SIZE_HEADER_SIZE);
    if(read == SIZE_HEADER_SIZE)
    {
        //descramble
        if(descramble)
        {
            scrambler_reset_state(&scrambler);
            //byte 0 is not scrambled
            for(i = 1; i < SIZE_HEADER_SIZE; i++)
            {
                arr[i] = descrambler_update(&scrambler, arr[i]);
            }
            prot3buff_replaceLastNReadBytes(rxbuf, arr, SIZE_HEADER_SIZE);
        }
        crc = crc_tools_ibutton_calculate(arr, SIZE_HEADER_SIZE - 1);
        if((arr[0] == 0x03) && (crc == arr[SIZE_HEADER_SIZE - 1]))
        {
            size = ((arr[1] & 0x07) << 8) | arr[2];
        }
    }
    prot3buff_setReaderToPos(rxbuf, 0);
    return size;
}

uint16_t Wtp3Driver::sizeHeaderFirstCheck()
{
    return singleton->checkSizeHeader(1);
}

uint8_t Wtp3Driver::checkFrame()
{
    uint8_t arr[ADDRESS_HEADER_SIZE];
    uint16_t size;
    uint32_t crc = crc_tools_32_get_initial_value();
    uint32_t crcFrame;
    uint16_t i;
    uint8_t byte;
    uint8_t result = 0;

    //crc check
    prot3buff_setReaderToPos(rxbuf, 0);
    size = checkSizeHeader(0);
    if(size != 0xFFFF)
    {
        if(size == prot3buff_getBytesAvail(rxbuf))
        {
            //descramble, size header already descrambled
            prot3buff_setReaderToPos(rxbuf, SIZE_HEADER_SIZE);
            while(prot3buff_isByteAvailable(rxbuf))
            {
                byte = (uint8_t)prot3buff_readByte(rxbuf);
                byte = descrambler_update(&scrambler, byte);
                prot3buff_replaceLastReadByte(rxbuf, byte);
            }

            //calculation of data part size
            if(size >= (SIZE_HEADER_SIZE + CRC_SIZE))
            {
                size -= (SIZE_HEADER_SIZE + CRC_SIZE);
            }
            else
            {
                size = 0;
            }
            //crc check
            prot3buff_setReaderToPos(rxbuf, SIZE_HEADER_SIZE);
            for(i = 0; i < size; i++)
            {
                crc = crc32_basic_update(crc, (uint8_t)prot3buff_readByte(rxbuf));
            }
            prot3buff_readBytes(rxbuf, arr, CRC_SIZE);
            crcFrame = frame_tools_bytes_LSB_to_uint32(arr);
            if(crc == crcFrame)
            {
                result = 1;
            }
        }
    }

    if(result != 0)
    {
        //delete crc
        prot3buff_setWriterToPos(rxbuf, prot3buff_getWriterPos(rxbuf) - CRC_SIZE);

        //received address header
        prot3buff_setReaderToPos(rxbuf, SIZE_HEADER_SIZE);
        prot3buff_readBytes(rxbuf, arr, ADDRESS_HEADER_SIZE);

        receivedAddrHeader.dest = frame_tools_bytes_LSB_to_uint32(&arr[0]);

        receivedAddrHeader.sender = frame_tools_bytes_LSB_to_uint32(&arr[4]);
        receivedAddrHeader.answer = (arr[8] & (1 << 7)) != 0;
        receivedAddrHeader.signin = (arr[8] & (1 << 6)) != 0;
        receivedAddrHeader.device = ((arr[8] & 0x07) << 8) | arr[9];
    }

    return result;
}

uint8_t Wtp3Driver::hasNextCmd()
{
    return prot3buff_isByteAvailable(rxbuf);
}

uint8_t Wtp3Driver::getNextCmdNumber()
{
    uint16_t pos;
    uint8_t cmd = 0;

    if(prot3buff_isByteAvailable(rxbuf))
    {
        pos = prot3buff_getReaderPos(rxbuf);
        cmd = prot3buff_readByte(rxbuf);
        prot3buff_setReaderToPos(rxbuf, pos);
    }
    return cmd;
}

uint8_t Wtp3Driver::getIsNextCmdShort()
{
    return (getNextCmdNumber() & 0x80) == 0;
}

uint8_t Wtp3Driver::getNextCmdSize()
{
    uint16_t pos;
    uint8_t arr[2];
    uint8_t size = 0;

    pos = prot3buff_getReaderPos(rxbuf);
    if(prot3buff_readBytes(rxbuf, arr, 2) == 2)
    {
        //Most sign. bit of a command
        if(arr[0] & 0x80)
        {
            //long command
            size = arr[1];
        }
        else
        {
            //arr[1] is command data
            size = 1;
        }

    }
    prot3buff_setReaderToPos(rxbuf, pos);
    return size;
}

uint8_t Wtp3Driver::readNextCmd(uint8_t *number, uint8_t *data)
{
    uint8_t arr[2];
    uint8_t readBytes;
    uint8_t cmdSize = 0;

    readBytes = prot3buff_readBytes(rxbuf, arr, 2);
    if(readBytes == 2)
    {
        *number = arr[0];
        if(*number & 0x80)
        {
            //long command
            if((0 < arr[1]) && (arr[1] <= receivedCmdSizeMax))
            {
                readBytes = prot3buff_readBytes(rxbuf, data, arr[1]);
                if(readBytes == arr[1])
                {
                    cmdSize = readBytes;
                }
            }
            else
            {
                //skip bytes
                //cmdSize remains 0
                readBytes = prot3buff_readBytes(rxbuf, NULL, arr[1]);
            }
        }
        else
        {
            *data = arr[1];
            cmdSize = 1;
        }
    }
    return cmdSize;
}

IWtp3Device* Wtp3Driver::findDevice(uint16_t device)
{
    IWtp3Device *result = NULL;
    uint16_t i;

    for(i = 0; i < devicesArrSize; i++)
    {
        uint16_t _device = devicesArr[i]->getDeviceNumber();

        if((_device == device) || (_device == IWtp3Device::ANY_DEVICE_NUMBER))
        {
            result = devicesArr[i];
            break;
        }
    }
    return result;
}

IWtp3Device* Wtp3Driver::findDeviceToSend()
{
    IWtp3Device *result = NULL;
    uint16_t i;

    for(i = 0; i < devicesArrSize; i++)
    {
        if(devicesArr[i]->sendNeeded())
        {
            result = devicesArr[i];
            break;
        }
    }
    return result;
}

void Wtp3Driver::incrementErrorCounter(uint16_t *counter)
{
    if(*counter < 0xFFFF)
    {
        (*counter)++;
    }
}

