/*
 * st7565HAL_Flash_Custom.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: krzysiek
 */

#include "st7565HAL_Flash_Custom.h"
#include "CImgData.h"

uint32_t CST7565_Hal_Flash::m_address;

void CST7565_Hal_Flash::flashStartReadSequentialBytes(uint32_t address)
{
    m_address = address;
}

void CST7565_Hal_Flash::flashReadSequentialBytes(uint8_t* outData, uint16_t dataSize)
{
    memcpy(outData, CImgData::FLASH_DATA + m_address, dataSize);
    m_address += dataSize;
}

void CST7565_Hal_Flash::flashEndReadSequentialBytes()
{
}
