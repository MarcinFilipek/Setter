#ifndef WTP3DRIVER_H_
#define WTP3DRIVER_H_

#include <stdint.h>
#include "wtp3structs.h"
#include "IWtp3Device.h"
#include "prot3buff.h"
#include "scrambler.h"
#include "rfm22frame.h"

class IWtp3Device;

class Wtp3Driver
{
    public:
             Wtp3Driver();

        void init(IWtp3Device *devicesArr[], uint16_t devicesArrSize, uint32_t ownAddress,
                uint16_t ownDevice, EReceiveMode receiveMode, uint8_t receivedCmdSizeMax);
        void update();

        void forceReset(uint16_t delay_ms);
        uint32_t getOwnAddress();
        uint16_t getOwnDevice();
        SWtp3AddressHeader *getReceivedAddressHeader();
        EReceiveMode getReceiveMode();
        void setReceiveMode(EReceiveMode mode);
        rfm22frame_state_t getFrameState();
        uint8_t getSignalStrengthPercent();

        void startFrame(uint32_t dest, uint8_t answer, uint8_t signin);
        void addShortCommand(uint8_t command, uint8_t data);
        void addLongCommand(uint8_t command, uint8_t size, uint8_t *data);
        void endFrame();

        uint8_t hasNextCmd();
        uint8_t getNextCmdNumber();
        uint8_t getIsNextCmdShort();
        uint8_t getNextCmdSize();

        /**
         *  @brief  It reads a next command number and command data
         *
         *  If data block is bigger than receivedCmdSizeMax set in init(),
         *  data is not read and error value (0) is returned.
         *
         *  @param   number    Command number
         *  @param   data      Buffer to fill command data bytes
         *  @return            Command data size in bytes. 0 means an error caused
         *                     by too small receivedCmdSizeMax value or insufficient
         *                     data in receiving buffer
         */
        uint8_t readNextCmd(uint8_t *number, uint8_t *data);

    private:
        static const uint16_t SIZE_HEADER_SIZE = 4;
        static const uint16_t ADDRESS_HEADER_SIZE = 10;
        static const uint16_t CRC_SIZE = 4;
        static const uint16_t LIMITED_RX_DELAY_TIME_MILISEC = 100;
        static const uint16_t REINIT_ERROR_COUNT = 10;
        static const uint16_t SIGNAL_POWER_1_PERCENT = 60;
        static const uint16_t SIGNAL_POWER_100_PERCENT = 170;
        static const uint32_t RESET_INTERVAL_MILISEC = 15*60*1000;

        prot3buff_t *txbuf;
        prot3buff_t *rxbuf;

        IWtp3Device **devicesArr;
        uint16_t devicesArrSize;

        uint32_t ownAddress;
        uint16_t ownDevice;
        EReceiveMode receiveMode;
        uint8_t receivedCmdSizeMax;

        SWtp3AddressHeader receivedAddrHeader;
        scrambler_t scrambler;

        rfm22frame_state_t rfm22frameState;

        uint16_t generalErrorsCounter;
        uint16_t txErrorsCounter;
        uint16_t rxErrorsCounter;

        uint8_t isFrameReceived();
        uint8_t isFrameSent();
        void addSizeHeader(uint16_t size, uint8_t replace);
        void addAddressHeader(uint32_t dest, uint32_t sender, uint8_t answer, uint8_t signin);
        uint16_t checkSizeHeader(uint8_t descramble);
        uint8_t checkFrame();

        IWtp3Device *findDevice(uint16_t device);
        IWtp3Device *findDeviceToSend();

        static void incrementErrorCounter(uint16_t *counter);

        static Wtp3Driver *singleton;
        static uint16_t sizeHeaderFirstCheck();
};



#endif /* WTP3DRIVER_H_ */
