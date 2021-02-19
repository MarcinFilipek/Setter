/*
 * CDeviceID.h
 *
 *  Created on: Sep 5, 2014
 *      Author: krzysiek
 */

#ifndef CDEVICEID_H_
#define CDEVICEID_H_

#include "CBootSignature.h"

class CDeviceID
{
    static const uint32_t FLASH_OFFSET = 0x08000000;

    CBootSignature m_bootSignature;
    uint32_t m_appOffset;

public:
    CDeviceID(uint32_t appOffset = 0xA000);

    uint8_t getByteID(int8_t index);
    bool getTextID(char *buffer, uint16_t length);

    int32_t getBoardVersion();
    int32_t getBoardSubversion();
    int32_t getControllerVersion();
    int32_t getFirm();
    SVersion getBootloaderVersion();
};

#endif /* CDEVICEID_H_ */
