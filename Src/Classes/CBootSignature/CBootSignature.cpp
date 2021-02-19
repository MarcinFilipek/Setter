/*
 * CBootSignature.cpp
 *
 *  Created on: Nov 17, 2015
 *      Author: krzysiek
 */

#include "CBootSignature.h"
#include <string.h>

#if defined(STM32F10X_CL) || defined(__SYSTEM_STM32F10X)
const uint32_t CBootSignature::UNIQUE_ID_OFFSET = 0x1FFFF7E8;
#elif STM32F205xx
const uint32_t CBootSignature::UNIQUE_ID_OFFSET = 0x1FFF7A10;
#elif defined(STM32L053xx)
const uint32_t CBootSignature::UNIQUE_ID_OFFSET = 0x1FF80050;
#else
#error Brak definicji procesora!
#endif

CBootSignature::CBootSignature(uint32_t appOffset)
{
    m_appOffset = appOffset;
}

bool CBootSignature::isSignatureAvailable()
{
    void *ptr = (void*) (FLASH_OFFSET + m_appOffset - 4);
    uint32_t signature;
    memcpy(&signature, ptr, sizeof(signature));
    return (signature == SIGNATURE);
}

int32_t CBootSignature::getCustomValue(uint8_t ID)
{
    if (isSignatureAvailable() == false)
    {
        return 0;
    }

    void *ptr = (void*) (FLASH_OFFSET + m_appOffset - 5);

    while (true)
    {
        uint8_t IDvalue;
        memcpy(&IDvalue, ptr, sizeof(IDvalue));

        if (IDvalue == 0)
        {
            return 0;
        }

        if (IDvalue == ID)
        {
            ptr -= 4;
            int32_t customValue;
            memcpy(&customValue, ptr, sizeof(customValue));
            return customValue;
        }

        ptr -= 5;
    }
}

int32_t CBootSignature::getBoardVersion()
{
    return getCustomValue(ID_BOARD_VERSION);
}

int32_t CBootSignature::getBoardSubversion()
{
    return getCustomValue(ID_BOARD_SUBVERSION);
}

int32_t CBootSignature::getControllerVersion()
{
    return getCustomValue(ID_CONTROLLER_VERSION);
}

int32_t CBootSignature::getFirm()
{
    return getCustomValue(ID_FIRM);
}

SVersion CBootSignature::getBootloaderVersion()
{
    return getCustomValue(ID_BOOTLOADER_VERSION);
}

int8_t CBootSignature::getChipID(uint8_t *buffer)
{
    uint8_t *chipID = (uint8_t*) UNIQUE_ID_OFFSET;
    memcpy(buffer, chipID, 12);
    return 12;
}

char* CBootSignature::toString(uint32_t value)
{
    memcpy(stringBuff, &value, 4);
    stringBuff[4] = 0;
    return stringBuff;
}

int32_t CBootSignature::getAdres()
{
    return getCustomValue(ID_ADRES);
}


