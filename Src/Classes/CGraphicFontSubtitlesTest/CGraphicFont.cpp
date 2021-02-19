/*
 * CGraphicFont.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: krzysiek
 */

#include "CGraphicFont.h"

#include "CTextResources.h"
#include "CColor.h"
#ifdef SUBTITLES_TEST
#include "CGraphicFontSubtitlesTest.h"
#endif

CGraphicFont::SFont CGraphicFont::m_fonts[FONTS_LENGTH];

void CGraphicFont::addFont(uint16_t fontID, const TImgCharMap* imgCharMap, uint16_t length, uint16_t fontHeight,
        uint8_t spaceSize)
{
    for (uint16_t i = 0; i < FONTS_LENGTH; i++)
    {
        if (m_fonts[i].imgCharMap == NULL)
        {
            m_fonts[i].imgCharMap = imgCharMap;
            m_fonts[i].length = length;
            m_fonts[i].fontID = fontID;
            m_fonts[i].spaceSize = spaceSize;
            m_fonts[i].fontHeight = fontHeight;
            break;
        }
    }
}

int16_t CGraphicFont::getHeightMultilineText(int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2,
        uint32_t strId, const char* str, uint16_t fontID, TPrintCase printCase, TAlignText alignText, TMultiline mulitiline,
        const TColorDesc& COLOR)
{
    CGraphicFont::SFont *font = getFont(fontID);

    int16_t fontHeight = font->fontHeight;
    int16_t textWidth = 0;
    int16_t posX = 0;
    int16_t posY = 0;
    wchar_t znak = 0;
    int16_t startIndex = 0;
    int16_t endIndex = 0;
    wchar_t stringBufferUtf[STRING_BUFFER_SIZE];

    if (strId != NULL)
    {
        CTextResources::copyTextToBuffer(stringBufferUtf, strId, STRING_BUFFER_SIZE);
    }
    else
    {
        if (str != NULL)
        {
            CTextResources::copyUtfToWchar(stringBufferUtf, str);
        }
        else
        {
            return 0;
        }
    }

    createLineBreaks(font, posX2 - posX1, posY2 - posY1, stringBufferUtf, printCase);

    znak = stringBufferUtf[startIndex];

    while (znak)
    {
        if ((znak == '|') || (znak == '^') || (startIndex == 0))
        {
            if ((znak == '|') || (znak == '^'))
            {
                startIndex++;
            }
            endIndex = startIndex;

            znak = stringBufferUtf[endIndex];
            while ((znak != '|') && (znak != '^') && (znak != 0))
            {
                endIndex++;
                znak = stringBufferUtf[endIndex];
            }
            endIndex--;

            textWidth = drawRamTextInternall( //
                    0,
                    0,
                    stringBufferUtf,
                    startIndex,
                    endIndex,
                    font,
                    true,
                    printCase,
                    COLOR);
            posX = getAlignTextPosX(posX1, posX2, textWidth, alignText);
            posY += fontHeight;
            startIndex = endIndex;
        }
        startIndex++;
        znak = stringBufferUtf[startIndex];
    }

    return posY;
}

void CGraphicFont::drawText(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t stringAddress,
        const char* stringPtr, uint16_t fontID, TPrintCase printCase, TAlignText alignText, TMultiline mulitiline,
        const TColorDesc& COLOR, bool escaping)
{
#ifdef SUBTITLES_TEST
    CGraphicFontSubtitlesTest::drawText(x1, y1, x2, y2, stringAddress, fontID, printCase, alignText, mulitiline);
#endif

    CGraphicFont::SFont *font = getFont(fontID);
    switch (mulitiline)
    {
        case MULTILINE_OFF:
            switch (alignText)
            {
                case AT_CENTER:
                {
                    int16_t textWidth;
                    int16_t posX;

                    textWidth = drawTextInternall( //
                            0,
                            0,
                            stringAddress,
                            stringPtr,
                            font,
                            true,
                            printCase,
                            COLOR,
                            escaping);
                    posX = ((x1 + x2) >> 1) - (textWidth >> 1) + 1;
                    drawTextInternall( //
                            posX,
                            y1,
                            stringAddress,
                            stringPtr,
                            font,
                            false,
                            printCase,
                            COLOR,
                            escaping);

                }
                break;

                case AT_RIGHT:
                {
                    int16_t length = drawTextInternall( //
                            0,
                            0,
                            stringAddress,
                            stringPtr,
                            font,
                            true,
                            printCase,
                            COLOR,
                            escaping);

                    length--;
                    if (length > x2 - x1)
                        length = x2 - x1;
                    x1 = x2 - length;

                    drawTextInternall( //
                            x1,
                            y1,
                            stringAddress,
                            stringPtr,
                            font,
                            false,
                            printCase,
                            COLOR,
                            escaping);
                }
                break;
                case AT_LEFT:
                    drawTextInternall( //
                            x1,
                            y1,
                            stringAddress,
                            stringPtr,
                            font,
                            false,
                            printCase,
                            COLOR,
                            escaping);
                break;
            }
        break;

        case MULTILINE_ON:
        case MULTILINE_CENTER:
        case MULTILINE_SPACE_SEPARATOR:
            drawTextMultiline( //
                    x1,
                    y1,
                    x2,
                    y2,
                    stringAddress,
                    stringPtr,
                    font,
                    printCase,
                    alignText,
                    mulitiline,
                    COLOR);
        break;
    }
}

int16_t CGraphicFont::getFontHeight(uint16_t fontID)
{
    CGraphicFont::SFont *font = getFont(fontID);
    return font->fontHeight;
}

int16_t CGraphicFont::getSpaceSize(uint16_t fontID)
{
    CGraphicFont::SFont *font = getFont(fontID);
    return font->spaceSize;
}

int16_t CGraphicFont::getTextWidth(uint32_t stringAddress, const char* stringPtr, uint16_t fontID, TPrintCase printCase)
{
    CGraphicFont::SFont *font = getFont(fontID);
    return drawTextInternall( //
            0,
            0,
            stringAddress,
            stringPtr,
            font,
            true,
            printCase,
            CColor::COLOR_TRANSPARENT);
}

int16_t CGraphicFont::getCharWidth(wchar_t charCode, uint16_t fontID, TPrintCase printCase)
{
    CGraphicFont::SFont *font = getFont(fontID);
    charCode = convertChar(font, charCode, printCase);
    uint32_t imgAddress = getCharImgAddress(font, charCode);
    return getImageWidth(imgAddress);
}

CGraphicFont::SFont *CGraphicFont::getFont(uint16_t fontID)
{
    for (uint16_t i = 0; i < FONTS_LENGTH; i++)
    {
        if (m_fonts[i].fontID == fontID)
        {
            return &m_fonts[i];
        }
    }
    return NULL;
}

wchar_t CGraphicFont::convertChar(SFont *font, wchar_t charCode, TPrintCase printCase)
{
    wchar_t outChar = charCode;

    switch (printCase)
    {
        case PR_NORMAL:
        break;

        case PR_UPPER:
        {
            int32_t aIndex = -1;
            for (int32_t i = 0; i < font->length; i++)
            {
                if (font->imgCharMap[i].charCode == 'a')
                {
                    aIndex = i;
                }

                if (font->imgCharMap[i].charCode == charCode)
                {
                    if ((aIndex != -1) && (i + 1 < font->length) && (i >= aIndex) && (i % 2 == (aIndex % 2)))
                    {
                        outChar = font->imgCharMap[i + 1].charCode;
                    }
                    break;
                }
            }
        }
        break;

        case PR_LOWER:
        {
            int32_t aIndex = -1;
            for (int32_t i = 0; i < font->length; i++)
            {
                if (font->imgCharMap[i].charCode == 'a')
                {
                    aIndex = i;
                }

                if (font->imgCharMap[i].charCode == charCode)
                {
                    if ((aIndex != -1) && (i - 1 >= 0) && (i >= aIndex) && (i % 2 != (aIndex % 2)))
                    {
                        outChar = font->imgCharMap[i - 1].charCode;
                    }
                    break;
                }
            }
        }
        break;
    }

    return outChar;
}

uint32_t CGraphicFont::getCharImgAddress(SFont *font, wchar_t charCode, bool hideHash)
{
    int16_t index = 0;
    uint32_t imgAddress = 0;
    uint32_t hashAddress = 0;

    for (index = 0; index < font->length; index++)
    {
        if (font->imgCharMap[index].charCode == charCode)
        {
            imgAddress = font->imgCharMap[index].imgAddress;
            break;
        }
        // dla każdego fonta sprawdzam gdzie lezy znak '#' jeśli nie znajdę znaku podanego jako charCode to wstawiam tam '?'
        // zabieg ten ma umożliwić szybkie odnalezienie braku jakiegoś znaku (np. diakrytycznego) w czcionce
        if (font->imgCharMap[index].charCode == (hideHash ? ' ' : '?'))
        {
            hashAddress = font->imgCharMap[index].imgAddress;
        }
    }
    // jeśli poszukiwany znak nie został odnaleziony w czcionce to zostanie zastąpiony przez '?'
    imgAddress = imgAddress == 0? hashAddress : imgAddress;

    return imgAddress;
}

void CGraphicFont::createLineBreaks(SFont *font, int16_t maxWidth, int16_t maxHeight, wchar_t* buffer,
        TPrintCase printCase)
{
    if (maxWidth > 50 && maxHeight > 0)
    {
        wchar_t stringBufferUtf[STRING_BUFFER_SIZE];
        int16_t i = 0;
        do
        {
            stringBufferUtf[i] = buffer[i];
        }
        while (stringBufferUtf[i++]);

        createLineBreaks(font, maxWidth - (font->fontHeight / 2), 0, stringBufferUtf, printCase);
        int16_t lines = 1;
        for (int16_t i = 0; buffer[i] != 0; i++)
        {
            if (stringBufferUtf[i] == '|')
            {
                lines++;
            }
        }

        if ((lines == 1) || (lines * font->fontHeight < maxHeight))
        {
            int16_t i = 0;
            do
            {
                buffer[i] = stringBufferUtf[i];
            }
            while (buffer[i++]);

            return;
        }
    }

    int8_t charWidth[STRING_BUFFER_SIZE];
    int16_t start = 0;
    int16_t index = 0;

    for (int16_t i = 0; buffer[i] != 0; i++)
    {
        switch (buffer[i])
        {
            case '^':
                charWidth[i] = 0;
            break;

            case '|':
                return;

            default:
                charWidth[i] = drawRamTextInternall( //
                        0,
                        0,
                        buffer,
                        i,
                        i,
                        font,
                        true,
                        printCase,
                        CColor::COLOR_TRANSPARENT) + font->spaceSize;
            break;
        }
    }

    do
    {
        if ((buffer[index] == '^') || (buffer[index] == ' ') || (buffer[index] == 0))
        {
            int16_t width = 0;
            for (int16_t i = start; i < index; i++)
            {
                width += charWidth[i];
            }

            if (width >= maxWidth)
            {
                for (int16_t i = index - 1; i >= start; i--)
                {
                    if ((buffer[i] == '^') || (buffer[i] == ' '))
                    {
                        buffer[i] = '|';
                        start = i + 1;
                        break;
                    }
                }
            }
        }
    }
    while (buffer[index++]);

    for (int16_t i = 0; buffer[i] != 0; i++)
    {
        if (buffer[i] == '^')
        {
            for (int16_t j = i; buffer[j] != 0; j++)
            {
                buffer[j] = buffer[j + 1];
            }
        }
    }
}

int16_t CGraphicFont::drawTextInternall(int16_t posX, int16_t posY, uint32_t strId, const char* str, SFont *font,
        bool getLength, TPrintCase printCase, const TColorDesc& COLOR, bool escaping)
{
    int16_t retVal = 0;
    int16_t endIndex = 0;
    wchar_t stringBufferUtf[STRING_BUFFER_SIZE];

    if (strId != NULL)
    {
        endIndex = CTextResources::copyTextToBuffer(stringBufferUtf, strId, STRING_BUFFER_SIZE);
        retVal = drawRamTextInternall( //
                posX,
                posY,
                stringBufferUtf,
                0,
                endIndex,
                font,
                getLength,
                printCase,
                COLOR,
                escaping);
    }
    else
    {
        if (str != NULL)
        {
            endIndex = CTextResources::copyUtfToWchar(stringBufferUtf, str);
            retVal = drawRamTextInternall( //
                    posX,
                    posY,
                    stringBufferUtf,
                    0,
                    endIndex,
                    font,
                    getLength,
                    printCase,
                    COLOR,
                    escaping);
        }
    }

    return retVal;
}

int16_t CGraphicFont::drawRamTextInternall(int16_t posX, int16_t posY, wchar_t* str, int16_t startIndex,
        int16_t endIndex, SFont *font, bool getLength, TPrintCase printCase, const TColorDesc& COLOR, bool escaping)
{
    wchar_t znak = 0;
    int16_t index = 0;
    int16_t offsetX = 0;
    uint32_t imgAddress = 0;

    if (startIndex > endIndex)
    {
        return 0;
    }

    for (index = startIndex; index <= endIndex; index++)
    {
        znak = str[index];
        if (znak == '|' && !escaping)
        {
            znak = ' ';
        }

        if (znak != '^' || escaping)
        {
            znak = convertChar(font, znak, printCase);
            imgAddress = getCharImgAddress(font, znak, escaping);
            if (!getLength)
            {
#ifdef SUBTITLES_TEST
                CGraphicFontSubtitlesTest::drawImage(imgAddress, posX + offsetX, posY);
                if(!CGraphicFontSubtitlesTest::m_staticTest)
#endif
                drawImage(imgAddress, posX + offsetX, posY, COLOR);
            }
            offsetX += getImageWidth(imgAddress) + font->spaceSize;
        }
    }
    offsetX -= font->spaceSize;

    return offsetX;
}

void CGraphicFont::drawTextMultiline(int16_t posX1, int16_t posY1, int16_t posX2, int16_t posY2, uint32_t strId,
        const char* str, SFont *font, TPrintCase printCase, TAlignText alignText, TMultiline mulitiline,
        const TColorDesc& COLOR)
{
    int16_t fontHeight = font->fontHeight;
    int16_t textWidth = 0;
    int16_t posX = 0;
    int16_t posY = 0;
    wchar_t znak = 0;
    int16_t startIndex = 0;
    int16_t endIndex = 0;
    wchar_t stringBufferUtf[STRING_BUFFER_SIZE];

    if (mulitiline == MULTILINE_CENTER)
    {
        if (posY2 > posY1)
        {
            if (strId != NULL)
            {
                CTextResources::copyTextToBuffer(stringBufferUtf, strId, STRING_BUFFER_SIZE);
            }
            else
            {
                if (str != NULL)
                {
                    CTextResources::copyUtfToWchar(stringBufferUtf, str);
                }
                else
                {
                    return;
                }
            }

            createLineBreaks(font, posX2 - posX1, posY2 - posY1, stringBufferUtf, printCase);

            int16_t index = 0;
            int8_t lines = 0;

            wchar_t znak = stringBufferUtf[index];
            while (znak)
            {
                if ((znak == '|') || (znak == '^') || (index == 0))
                    lines++;

                index++;

                znak = stringBufferUtf[index];
            }

            int16_t heigth = lines * fontHeight;
            if (posY2 - posY1 > heigth)
                posY1 += ((posY2 - posY1) - heigth) / 2;
        }
    }

    posY = posY1;

    if (strId != NULL)
    {
        CTextResources::copyTextToBuffer(stringBufferUtf, strId, STRING_BUFFER_SIZE);
    }
    else
    {
        if (str != NULL)
        {
            CTextResources::copyUtfToWchar(stringBufferUtf, str);
        }
        else
        {
            return;
        }
    }
    createLineBreaks(font, posX2 - posX1, posY2 - posY1, stringBufferUtf, printCase);

    znak = stringBufferUtf[startIndex];

    while (znak)
    {
        if (mulitiline == MULTILINE_SPACE_SEPARATOR ? (znak == '|') || (znak == '^') || (znak == ' ') || (startIndex == 0) : (znak == '|') || (znak == '^') || (startIndex == 0))
        {
            if (mulitiline == MULTILINE_SPACE_SEPARATOR ? (znak == '|') || (znak == ' ') || (znak == '^') : (znak == '|') || (znak == '^'))
            {
                startIndex++;
            }
            endIndex = startIndex;

            znak = stringBufferUtf[endIndex];
            while (mulitiline == MULTILINE_SPACE_SEPARATOR ? (znak != '|') && (znak != ' ') && (znak != '^') && (znak != 0) : (znak != '|') && (znak != '^') && (znak != 0))
            {
                endIndex++;
                znak = stringBufferUtf[endIndex];
            }
            endIndex--;

            textWidth = drawRamTextInternall( //
                    0,
                    0,
                    stringBufferUtf,
                    startIndex,
                    endIndex,
                    font,
                    true,
                    printCase,
                    COLOR);
            posX = getAlignTextPosX(posX1, posX2, textWidth, alignText);
            drawRamTextInternall( //
                    posX,
                    posY,
                    stringBufferUtf,
                    startIndex,
                    endIndex,
                    font,
                    false,
                    printCase,
                    COLOR);
            posY += fontHeight;
            startIndex = endIndex;
        }
        startIndex++;
        znak = stringBufferUtf[startIndex];
    }
}

int16_t CGraphicFont::getAlignTextPosX(int16_t windowX1, int16_t windowX2, int16_t textWidth, TAlignText alignText)
{
    int16_t posX = 0;

    switch (alignText)
    {
        case AT_LEFT:
            posX = windowX1;
        break;

        case AT_RIGHT:
            posX = windowX2 - textWidth;
        break;

        case AT_CENTER:
            posX = ((windowX1 + windowX2) >> 1) - (textWidth >> 1);
        break;
    }

    return posX;
}
