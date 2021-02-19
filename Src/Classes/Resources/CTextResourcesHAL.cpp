/*
 * CTextResourcesHAL_template.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: krzysiek
 */

#include "CTextResourcesHAL.h"
#include "CNapisy.h"

void CTextResourcesHAL::readData(uint32_t address, void *buffer, int16_t size)
{
    memcpy(buffer, CNapisy::FLASH_DATA + address, size);
}
