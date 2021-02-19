/*
 * CFont.h
 *
 *  Created on: Sep 29, 2015
 *      Author: krzysiek
 */

#ifndef CFONT_H_
#define CFONT_H_

#include "CGraphicFont.h"

class CFont
{
public:
    static const uint16_t FONT_1 = 1;
    static const uint16_t FONT_2 = 2;
    static const uint16_t FONT_3 = 3;
    static const uint16_t FONT_4 = 4;
    static const uint16_t FONT_5 = 5;
    static const uint16_t FONT_ASCII = 10;

private:
    static const CGraphicFont::TImgCharMap CHAR_MAP_FONT_1[];
    static const CGraphicFont::TImgCharMap CHAR_MAP_FONT_2[];
    static const CGraphicFont::TImgCharMap CHAR_MAP_FONT_3[];
    static const CGraphicFont::TImgCharMap CHAR_MAP_FONT_4[];
    static const CGraphicFont::TImgCharMap CHAR_MAP_FONT_5[];
    static const CGraphicFont::TImgCharMap CHAR_MAP_FONT_ASCII[];

public:
    static void init();
    static uint32_t getCharImgAddress(uint16_t fontID, wchar_t charCode);
};

#endif /* CFONT_H_ */
