/*
 * CGraphicFontHAL_template.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: krzysiek
 */

#include "CGraphicFontHAL.h"

void CGraphicFontHAL::drawImage(uint32_t address, int16_t x1, int16_t y1, const TColorDesc& COLOR)
{
    CSSD1963GraphDriver::copyImgFromFlashAlpha(address, x1, y1, true, COLOR, false, 0, 0, 0, 0);
    // lub np.
    CST7565Driver::imgBitBlt(x1, y1, address, (CST7565Driver::TBitOperation) COLOR.RGBA);
}

uint16_t CGraphicFontHAL::getImageWidth(uint32_t address)
{
    return CImgData::getImgWidth(address);
}
