/*
 * CImgData.h
 *
 *  Created on: Sep 29, 2015
 *      Author: krzysiek
 */

#ifndef CIMGDATA_H_
#define CIMGDATA_H_

#include <stdint.h>

class CImgData
{
public:
    static const uint8_t FLASH_DATA[];

public:
    typedef enum
    {
#include "graphicsIdEnum.h"
    } TImgAddress;

public:
    static uint16_t getImgWidth(uint32_t address);
    static uint16_t getImgHeight(uint32_t address);
};

#endif /* CIMGDATA_H_ */
