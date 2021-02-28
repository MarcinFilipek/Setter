#ifndef IWTP3DEVICE_H_
#define IWTP3DEVICE_H_

#include <stdint.h>
#include "wtp3driver.h"
#include "wtp3structs.h"

class Wtp3Driver;

class IWtp3Device
{
    public:
        static const uint16_t ANY_DEVICE_NUMBER = 2047;

        virtual void init() = 0;
        virtual void update() = 0;

        /**
         *  @brief  It returns device number supported by implementing class
         *  @return Device number. Values 0..2046 are allowed. If all devices
         *          are supported, it returns ANY_DEVICE_NUMBER and should be
         *          placed last in device array
         */
        virtual uint16_t getDeviceNumber() = 0;
        virtual bool sendNeeded() = 0;
        virtual void createFrame(Wtp3Driver *driver) = 0;

        /**
         *   @return   0 - no answer after received frame;
         *             1 - answer after received frame is prepared;
         *             2 - no answer after received frame and request to end rx mode if "limitedRx" mode is used
         *
         */
        virtual ERecFrameResult receiveFrame(Wtp3Driver *driver) = 0;
};

#endif /* IWTP3DEVICE_H_ */
