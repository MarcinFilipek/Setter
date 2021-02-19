/*
 * CTextResourcesHAL_template.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: krzysiek
 */

#include "CTextResourcesHAL.h"

void CTextResourcesHAL::readData(uint32_t address, void *buffer, int16_t size)
{
    CSSD1963GraphDriver::flashStartReadSequentialBytes(address);
    CSSD1963GraphDriver::flashReadSequentialBytes((uint8_t*) buffer, size);
    CSSD1963GraphDriver::flashEndReadSequentialBytes();
}
