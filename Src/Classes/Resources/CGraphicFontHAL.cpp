/*
 * CGraphicFontHAL_template.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: krzysiek
 */

#include "CGraphicFontHAL.h"
#include "st7565Driver.h"
#include "CImgData.h"

void CGraphicFontHAL::drawImage(uint32_t address, int16_t x1, int16_t y1, const TColorDesc& COLOR)
{
    CST7565Driver::imgBitBlt(x1, y1, address, (CST7565Driver::TBitOperation) COLOR.RGBA);
}

uint16_t CGraphicFontHAL::getImageWidth(uint32_t address)
{
    return CImgData::getImgWidth(address);
}
