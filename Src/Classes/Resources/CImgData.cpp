/*
 * CImgData.h
 *
 *  Created on: Sep 29, 2015
 *      Author: krzysiek
 */

#include "CImgData.h"

const uint8_t CImgData::FLASH_DATA[] = {
#include "flashGraphics.h"
        };

uint16_t CImgData::getImgWidth(uint32_t address)
{
    return CImgData::FLASH_DATA[address];
}

uint16_t CImgData::getImgHeight(uint32_t address)
{
    return CImgData::FLASH_DATA[address + 1];
}
