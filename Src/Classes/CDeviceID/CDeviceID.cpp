/*
 * CDeviceID.cpp
 *
 *  Created on: Sep 5, 2014
 *      Author: krzysiek
 */

#include "CDeviceID.h"

CDeviceID::CDeviceID(uint32_t appOffset) :
        m_bootSignature(appOffset)
{
    m_appOffset = appOffset;
}

uint8_t CDeviceID::getByteID(int8_t index)
{
    uint8_t buffer[16];
    m_bootSignature.getChipID(buffer);
    return buffer[index];
}

bool CDeviceID::getTextID(char* buffer, uint16_t length)
{
    uint8_t buffer1[16];
    m_bootSignature.getChipID(buffer1);
    uint32_t *id = (uint32_t*) buffer1;
    return snprintf(buffer, length, "%08X%08X%08X", id[0], id[1], id[2]) < length;
}

int32_t CDeviceID::getBoardVersion()
{
    if (m_bootSignature.isSignatureAvailable())
    {
        return m_bootSignature.getBoardVersion();
    }
    return *(int32_t*) (FLASH_OFFSET + m_appOffset - 4);
}

int32_t CDeviceID::getBoardSubversion()
{
    if (m_bootSignature.isSignatureAvailable())
    {
        return m_bootSignature.getBoardSubversion();
    }
    return *(int32_t*) (FLASH_OFFSET + m_appOffset - 8);
}

int32_t CDeviceID::getControllerVersion()
{
    if (m_bootSignature.isSignatureAvailable())
    {
        return m_bootSignature.getControllerVersion();
    }
    return *(int32_t*) (FLASH_OFFSET + m_appOffset - 12);
}

int32_t CDeviceID::getFirm()
{
    if (m_bootSignature.isSignatureAvailable())
    {
        return m_bootSignature.getFirm();
    }
    return *(int32_t*) (FLASH_OFFSET + m_appOffset - 20);
}

SVersion CDeviceID::getBootloaderVersion()
{
    if (m_bootSignature.isSignatureAvailable())
    {
        return m_bootSignature.getBootloaderVersion();
    }
    return SVersion(*(int32_t*) (FLASH_OFFSET + m_appOffset - 24));
}
